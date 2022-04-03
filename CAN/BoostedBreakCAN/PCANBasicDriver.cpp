/***
 *  BoostedBreak - BoostedBreakCAN Program
 *
 *  PCANBasicDriver.cpp
 *
 *  Author: Alexander Krysl (axkrysl47)
 *  Date:   2022/04/03
 **/

#include "PCANBasicDriver.h"

#undef REPEAT_TRANSMIT_IN_RECEIVE

PCANBasicDriver::PCANBasicDriver(TPCANHandle handle, TPCANBaudrate bitrate, bool showOutput)
{
    m_IsInitialized = false;
    m_IsTraceConfigured = false;

    PcanHandle = handle;
    Bitrate = bitrate;

    m_DriverThread = nullptr;

    m_ReceiveQueue = nullptr;
    m_ReceiveQueueFD = nullptr;
    m_TransmitQueue = nullptr;
    m_TransmitQueueFD = nullptr;

    SetDriverThreadErrorLogging(showOutput);

    if (m_DriverThreadErrorLogFlag == true)
    {
        ShowConfigurationHelp(); // Shows information about this sample
        ShowCurrentConfiguration(); // Shows the current parameters configuration
    }

    TPCANStatus stsResult;
    // Initialization of the selected channel
    if (IsFD)
    {
        m_ReceiveQueueFD = new std::deque<TPCANMsgFD>();
        m_TransmitQueueFD = new std::deque<TPCANMsgFD>();
        stsResult = CAN_InitializeFD(PcanHandle, BitrateFD);
    }
    else
    {
        m_ReceiveQueue = new std::deque<TPCANMsg>();
        m_TransmitQueue = new std::deque<TPCANMsg>();
        stsResult = CAN_Initialize(PcanHandle, Bitrate);
    }

    if (stsResult != PCAN_ERROR_OK)
    {
        if (m_DriverThreadErrorLogFlag == true)
        {
            PCANDebugOutput("\n");
            ShowStatus(stsResult);
        }
        return;
    }

    StopDriverThread();
    m_IsInitialized = true;
}

PCANBasicDriver::~PCANBasicDriver()
{
    StopDriverThread();
    CAN_Uninitialize(PCAN_NONEBUS);
    if (IsFD)
    {
        delete m_ReceiveQueueFD;
        delete m_TransmitQueueFD;
    }
    else
    {
        delete m_ReceiveQueue;
        delete m_TransmitQueue;
    }
    m_IsInitialized = false;
    if (m_DriverThreadErrorLogFlag == true)
    {
        PCANDebugOutput("PCAN-Basic De-initialized.\n");
    }
}

bool PCANBasicDriver::GetIsInitialized()
{
    return m_IsInitialized;
}

bool PCANBasicDriver::GetIsTraceConfigured()
{
    return m_IsTraceConfigured;
}

bool PCANBasicDriver::SetDriverThreadErrorLogging(bool flag)
{
    m_DriverThreadErrorLogFlag = flag;
    return m_DriverThreadErrorLogFlag;
}

TPCANStatus PCANBasicDriver::GetDriverStatus()
{
    return CAN_GetStatus(PcanHandle);
}

bool PCANBasicDriver::ConfigureTrace(bool singleFileOnly, bool showDate, bool showTime, bool overwriteEnabled,
    uint32_t fileSizeMegabytes, LPCSTR path, int32_t interval)
{
    if (path == nullptr)
    {
        return false;
    }

    TraceFileSingle = singleFileOnly;
    TraceFileDate = showDate;
    TraceFileTime = showTime;
    TraceFileOverwrite = overwriteEnabled;
    TraceFileSize = fileSizeMegabytes;
    TracePath = path;
    TimerInterval = interval;

    return SetTraceConfiguration();
}

bool PCANBasicDriver::StartDriverThread()
{
    m_DriverThreadActive = true;
    m_DriverThread = new std::thread(&PCANBasicDriver::DriverThreadProcess, this);
    return m_DriverThreadActive;
}

bool PCANBasicDriver::StopDriverThread()
{
    m_DriverThreadActive = false;
    if (m_DriverThread != nullptr)
    {
        m_DriverThread->join();
    }
    m_DriverThread = nullptr;
    return m_DriverThreadActive;
}

bool PCANBasicDriver::Receive(TPCANMsg* msgCanMessage)
{
    if (m_ReceiveQueue == nullptr
        || m_ReceiveQueue->empty() == true)
    {
        return false;
    }

    *msgCanMessage = m_ReceiveQueue->front();
    m_ReceiveQueue->pop_front();

    return true;
}

bool PCANBasicDriver::ReceiveFD(TPCANMsgFD* msgCanMessageFD)
{
    if (m_ReceiveQueueFD == nullptr 
        || m_ReceiveQueueFD->empty() == true)
    {
        return false;
    }

    *msgCanMessageFD = m_ReceiveQueueFD->front();
    m_ReceiveQueueFD->pop_front();

    return true;
}

bool PCANBasicDriver::Transmit(TPCANMsg msgCanMessage)
{
    if (MESSAGE_QUEUE_SIZE <= m_TransmitQueue->size())
    {
        return false; // Transmit Queue full. Try same message next time.
    }
    
    m_TransmitQueue->push_back(msgCanMessage);

#ifdef REPEAT_TRANSMIT_IN_RECEIVE
    if (MESSAGE_QUEUE_SIZE <= m_ReceiveQueue->size())
    {
        // We missed some messages.
        m_ReceiveQueue->pop_front();
        m_ReceiveQueue->push_back(msgCanMessage);
    }
    else
    {
        m_ReceiveQueue->push_back(msgCanMessage);
    }
#endif //REPEAT_TRANSMIT_IN_RECEIVE

    return true;
}

bool PCANBasicDriver::TransmitFD(TPCANMsgFD msgCanMessageFD)
{
    if (MESSAGE_QUEUE_SIZE <= m_TransmitQueueFD->size())
    {
        return false; // Transmit Queue full. Try same message next time.
    }

    m_TransmitQueueFD->push_back(msgCanMessageFD);

#ifdef REPEAT_TRANSMIT_IN_RECEIVE
    if (MESSAGE_QUEUE_SIZE <= m_ReceiveQueueFD->size())
    {
        // We missed some messages.
        m_ReceiveQueueFD->pop_front();
        m_ReceiveQueueFD->push_back(msgCanMessageFD);
    }
    else
    {
        m_ReceiveQueueFD->push_back(msgCanMessageFD);
    }
#endif //REPEAT_TRANSMIT_IN_RECEIVE

    return true;
}

TPCANStatus PCANBasicDriver::TransmitImmediate(TPCANMsg msgCanMessage)
{
    return CAN_Write(PcanHandle, &msgCanMessage);
}

TPCANStatus PCANBasicDriver::TransmitImmediateFD(TPCANMsgFD msgCanMessageFD)
{
    return CAN_WriteFD(PcanHandle, &msgCanMessageFD);
}

bool PCANBasicDriver::StartTrace()
{
    UINT32 iStatus = PCAN_PARAMETER_ON;

    TPCANStatus stsResult = CAN_SetValue(PcanHandle, PCAN_TRACE_STATUS, &iStatus, sizeof(UINT32)); // We activate the tracing by setting the parameter.

    if (m_DriverThreadErrorLogFlag == true && stsResult != PCAN_ERROR_OK)
    {
        ShowStatus(stsResult);
        return false;
    }
    return true;
}

void PCANBasicDriver::StopTrace()
{
    UINT32 iStatus = PCAN_PARAMETER_OFF;

    TPCANStatus stsResult = CAN_SetValue(PcanHandle, PCAN_TRACE_STATUS, &iStatus, sizeof(UINT32)); // We stop the tracing by setting the parameter.

    if (m_DriverThreadErrorLogFlag == true && stsResult != PCAN_ERROR_OK)
        ShowStatus(stsResult);
}

void PCANBasicDriver::TestLookUpChannels()
{
    PCANDebugOutput("LookUpChannel Started...\n");

    ShowCurrentConfiguration(); // Shows the current parameters configuration

    PCANDebugOutput("Start searching...\n");
    PCANDebugSystemPause();
    PCANDebugOutput("\n");

    char sParameters[MAX_PATH];
    if (DeviceType != "")
        sprintf_s(sParameters, sizeof(sParameters), "%s=%s", ConvertDefinesToChar((wchar_t*)LOOKUP_DEVICE_TYPE), DeviceType);
    if (DeviceID != "")
    {
        if (sParameters != "")
            sprintf_s(sParameters, sizeof(sParameters), "%s, ", sParameters);
        sprintf_s(sParameters, sizeof(sParameters), "%s%s=%s", sParameters, ConvertDefinesToChar((wchar_t*)LOOKUP_DEVICE_ID), DeviceID);
    }
    if (ControllerNumber != "")
    {
        if (sParameters != "")
            sprintf_s(sParameters, sizeof(sParameters), "%s, ", sParameters);
        sprintf_s(sParameters, sizeof(sParameters), "%s%s=%s", sParameters, ConvertDefinesToChar((wchar_t*)LOOKUP_CONTROLLER_NUMBER), ControllerNumber);
    }
    if (IPAddress != "")
    {
        if (sParameters != "")
            sprintf_s(sParameters, sizeof(sParameters), "%s, ", sParameters);
        sprintf_s(sParameters, sizeof(sParameters), "%s%s=%s", sParameters, ConvertDefinesToChar((wchar_t*)LOOKUP_IP_ADDRESS), IPAddress);
    }

    TPCANHandle handle;
    TPCANStatus stsResult = CAN_LookUpChannel((LPSTR)sParameters, &handle);

    if (stsResult == PCAN_ERROR_OK)
    {

        if (handle != PCAN_NONEBUS)
        {
            UINT32 iFeatures;
            stsResult = CAN_GetValue(handle, PCAN_CHANNEL_FEATURES, &iFeatures, sizeof(UINT32));

            if (stsResult == PCAN_ERROR_OK)
            {
                char buffer[MAX_PATH];
                FormatChannelName(handle, buffer, (iFeatures & FEATURE_FD_CAPABLE) == FEATURE_FD_CAPABLE);
                PCANDebugOutput("The channel handle ");
                PCANDebugOutput(buffer);
                PCANDebugOutput(" was found\n");
            }
            else
                PCANDebugOutput("There was an issue retrieveing supported channel features\n");
        }
        else
            PCANDebugOutput("A handle for these lookup-criteria was not found\n");
    }

    if (m_DriverThreadErrorLogFlag == true && stsResult != PCAN_ERROR_OK)
    {
        PCANDebugOutput("There was an error looking up the device, are any hardware channels attached?\n");
        ShowStatus(stsResult);
    }

    PCANDebugOutput("\n");
    PCANDebugOutput("Closing...\n");
    PCANDebugSystemPause();
}

void PCANBasicDriver::TestGetSetParameter()
{
    // Setting Parameters...
    PCANDebugOutput("Get/set parameter\n");
    PCANDebugSystemPause();
    PCANDebugOutput("\n");

    //SetPCAN_DEVICE_ID(PcanHandle, 0xFF);
    //PCANDebugOutput("Fill \"GetSetParameter\"-function with parameter functions from \"PCANBasicParameter\"-Region in the code.\n");

    PCANDebugOutput("\n");
    PCANDebugOutput("Closing...\n");
    PCANDebugSystemPause();
}

void PCANBasicDriver::TestManualWrite()
{
    TPCANStatus status;
    BYTE data[8];
    for (BYTE i = 0; i < 8; i++)
    {
        data[i] = i;
    }
    TPCANMsg msgCanMessage = CreateTPCANMsg(0x100, PCAN_MESSAGE_EXTENDED, 8, data);

    // Writing messages...
    PCANDebugOutput("For write: ");
    PCANDebugSystemPause();
    do
    {
        PCANDebugSystemClear();

        status = CAN_Write(PcanHandle, &msgCanMessage);
        if (m_DriverThreadErrorLogFlag == true && status != PCAN_ERROR_OK)
            ShowStatus(status);
        else
            PCANDebugOutput("Message was successfully SENT\n");

        PCANDebugOutput("Do you want to write again? yes[y] or any other key to close\n");
    } while (_getch() == 121);
}

void PCANBasicDriver::TestTraceFiles()
{
    // Trace messages.
    PCANDebugOutput("Starting trace: ");
    PCANDebugSystemPause();
    if (SetTraceConfiguration())
    {
        if (StartTrace())
        {
            m_DriverThreadActive = true;
            m_DriverThread = new std::thread(&PCANBasicDriver::DriverThreadProcess, this);
            PCANDebugOutput("Messages are being traced.\n");
            PCANDebugOutput("Stop trace and quit: ");
            PCANDebugSystemPause();
            StopTrace();
            return;
        }
    }
    PCANDebugOutput("\n");
    PCANDebugOutput("For close: ");
    PCANDebugSystemPause();
}


void PCANBasicDriver::DriverThreadProcess()
{
    while (m_DriverThreadActive)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(50));
        ReceiveProcess();
        TransmitProcess();
    }
}

void PCANBasicDriver::ReceiveProcess()
{
    // We read at least one time the queue looking for messages. If a message is found, we look again trying to 
    // find more. If the queue is empty or an error occurs, we get out from the dowhile statement.
    TPCANStatus stsResult;
    TPCANMsgFD CANMsgFD;
    TPCANMsg CANMsg;
    UINT64 TimestampFD;
    TPCANTimestamp Timestamp;
    do
    {
        if (IsFD == true)
        {
            stsResult = CAN_ReadFD(PcanHandle, &CANMsgFD, &TimestampFD);
            if (m_DriverThreadErrorLogFlag == true 
                && stsResult != PCAN_ERROR_OK && stsResult != PCAN_ERROR_QRCVEMPTY)
            {
                ShowStatus(stsResult);
                return;
            }
            else if (stsResult == PCAN_ERROR_OK)
            {
                if (MESSAGE_QUEUE_SIZE <= m_ReceiveQueueFD->size())
                {
                    m_ReceiveQueueFD->pop_front();
                    m_ReceiveQueueFD->push_back(CANMsgFD);
                }
                else
                {
                    m_ReceiveQueueFD->push_back(CANMsgFD);
                }
            }
        }
        else
        {
            stsResult = CAN_Read(PcanHandle, &CANMsg, &Timestamp);
            if (m_DriverThreadErrorLogFlag == true 
                && stsResult != PCAN_ERROR_OK && stsResult != PCAN_ERROR_QRCVEMPTY)
            {
                ShowStatus(stsResult);
                return;
            }
            else if (stsResult == PCAN_ERROR_OK)
            {
                if (MESSAGE_QUEUE_SIZE <= m_ReceiveQueue->size())
                {
                    // We missed some messages.
                    m_ReceiveQueue->pop_front();
                    m_ReceiveQueue->push_back(CANMsg);
                }
                else
                {
                    m_ReceiveQueue->push_back(CANMsg);
                }
            }
        }
    } while ((!(stsResult & PCAN_ERROR_QRCVEMPTY)));
}

void PCANBasicDriver::TransmitProcess()
{
    TPCANStatus stsResult;
    TPCANMsgFD CANMsgFD;
    TPCANMsg CANMsg;

    if (IsFD)
    {
        while (m_TransmitQueueFD->empty() == false)
        {
            CANMsgFD = m_TransmitQueueFD->front();
            stsResult = CAN_WriteFD(PcanHandle, &CANMsgFD);
            if (m_DriverThreadErrorLogFlag == true 
                && stsResult != PCAN_ERROR_OK 
                && stsResult != PCAN_ERROR_XMTFULL && stsResult != PCAN_ERROR_QXMTFULL)
            {
                ShowStatus(stsResult);
                return;
            }
            else if (stsResult == PCAN_ERROR_XMTFULL || stsResult == PCAN_ERROR_QXMTFULL)
            {
                return; // Transmit Queue full. Try same message next time.
            }
            else if (stsResult == PCAN_ERROR_OK)
            {
                m_TransmitQueueFD->pop_front();
            }
        }
    }
    else
    {
        while (m_TransmitQueue->empty() == false)
        {
            CANMsg = m_TransmitQueue->front();
            stsResult = CAN_Write(PcanHandle, &CANMsg);
            if (m_DriverThreadErrorLogFlag == true
                && stsResult != PCAN_ERROR_OK
                && stsResult != PCAN_ERROR_XMTFULL && stsResult != PCAN_ERROR_QXMTFULL)
            {
                ShowStatus(stsResult);
                return;
            }
            else if (stsResult == PCAN_ERROR_XMTFULL || stsResult == PCAN_ERROR_QXMTFULL)
            {
                return; // Transmit Queue full. Try same message next time.
            }
            else if (stsResult == PCAN_ERROR_OK)
            {
                m_TransmitQueue->pop_front();
            }
        }
    }
}

bool PCANBasicDriver::SetTraceConfiguration()
{
    m_IsTraceConfigured = false;

    UINT32 iSize = TraceFileSize;

    // Sets path to store files
    TPCANStatus stsResult = CAN_SetValue(PcanHandle, PCAN_TRACE_LOCATION, (void*)TracePath, sizeof(TracePath));

    if (stsResult == PCAN_ERROR_OK)
    {
        // Sets the maximum size of a tracefile 
        stsResult = CAN_SetValue(PcanHandle, PCAN_TRACE_SIZE, &iSize, sizeof(UINT32));

        if (stsResult == PCAN_ERROR_OK)
        {
            UINT32 config;
            if (TraceFileSingle)
                config = TRACE_FILE_SINGLE; // Creats one file 
            else
                config = TRACE_FILE_SEGMENTED; // Creats more files

            // Activate overwriting existing tracefile
            if (TraceFileOverwrite)
                config = config | TRACE_FILE_OVERWRITE;

            // Adds date to tracefilename
            if (TraceFileDate)
                config = config | TRACE_FILE_DATE;

            // Adds time to tracefilename
            if (TraceFileTime)
                config = config | TRACE_FILE_TIME;

            // Sets the config
            stsResult = CAN_SetValue(PcanHandle, PCAN_TRACE_CONFIGURE, &config, sizeof(int));

            if (stsResult == PCAN_ERROR_OK)
            {
                m_IsTraceConfigured = true;
                return true;
            }
        }
    }
    if (m_DriverThreadErrorLogFlag == true)
    {
        ShowStatus(stsResult);
    }
    return false;
}

void PCANBasicDriver::ShowConfigurationHelp()
{
    PCANDebugOutput("=========================================================================================\n");
    PCANDebugOutput("|                              PCAN-Basic Class Driver                                   |\n");
    PCANDebugOutput("=========================================================================================\n");
    PCANDebugOutput("Following parameters are to be adjusted before launching, according to the hardware used |\n");
    PCANDebugOutput("                                                                                         |\n");
    PCANDebugOutput("* PcanHandle: Numeric value that represents the handle of the PCAN-Basic channel to use. |\n");
    PCANDebugOutput("              See 'PCAN-Handle Definitions' within the documentation                     |\n");
    PCANDebugOutput("* IsFD: Boolean value that indicates the communication mode, CAN (false) or CAN-FD (true)|\n");
    PCANDebugOutput("* Bitrate: Numeric value that represents the BTR0/BR1 bitrate value to be used for CAN   |\n");
    PCANDebugOutput("           communication                                                                 |\n");
    PCANDebugOutput("* BitrateFD: String value that represents the nominal/data bitrate value to be used for  |\n");
    PCANDebugOutput("             CAN-FD communication                                                        |\n");
    PCANDebugOutput("* TraceFileSingle: Boolean value that indicates if tracing ends after one file (true) or |\n");
    PCANDebugOutput("                   continues                                                             |\n");
    PCANDebugOutput("* TraceFileDate: Boolean value that indicates if the date will be added to filename      |\n");
    PCANDebugOutput("* TraceFileTime: Boolean value that indicates if the time will be added to filename      |\n");
    PCANDebugOutput("* TraceFileOverwrite: Boolean value that indicates if existing tracefiles should be      |\n");
    PCANDebugOutput("                      overwritten                                                        |\n");
    PCANDebugOutput("* TraceFileSize: Numeric value that represents the size of a tracefile in meagabytes     |\n");
    PCANDebugOutput("* TracePath: string value that represents a valid path to an existing directory          |\n");
    PCANDebugOutput("* TimerInterval: The time, in milliseconds, to wait before trying to write a message     |\n");
    PCANDebugOutput("=========================================================================================\n");
    PCANDebugOutput("\n");
}

void PCANBasicDriver::ShowCurrentConfiguration()
{
    PCANDebugOutput("Parameter values used\n");
    PCANDebugOutput("----------------------\n");
    char buffer[MAX_PATH];
    FormatChannelName(PcanHandle, buffer, IsFD);
    PCANDebugOutput("* PCANHandle: ");
    PCANDebugOutput(buffer);
    PCANDebugOutput("\n");
    if (IsFD)
        PCANDebugOutput("* IsFD: True\n");
    else
        PCANDebugOutput("* IsFD: False\n");
    ConvertBitrateToString(Bitrate, buffer);
    PCANDebugOutput("* Bitrate: ");
    PCANDebugOutput(buffer);
    PCANDebugOutput("\n");
    PCANDebugOutput("* BitrateFD: ");
    PCANDebugOutput(BitrateFD);
    PCANDebugOutput("\n");
    if (TraceFileSingle)
        PCANDebugOutput("* TraceFileSingle: True\n");
    else
        PCANDebugOutput("* TraceFileSingle: False\n");
    if (TraceFileDate)
        PCANDebugOutput("* TraceFileDate: True\n");
    else
        PCANDebugOutput("* TraceFileDate: False\n");
    if (TraceFileTime)
        PCANDebugOutput("* TraceFileTime: True\n");
    else
        PCANDebugOutput("* TraceFileTime: False\n");
    if (TraceFileOverwrite)
        PCANDebugOutput("* TraceFileOverwrite: True\n");
    else
        PCANDebugOutput("* TraceFileOverwrite: False\n");
    PCANDebugOutput("* TraceFileSize: ");
    PCANDebugOutput(std::to_string(TraceFileSize));
    PCANDebugOutput(" MB\n");
    if (TracePath == "")
    {
        PCANDebugOutput("* TracePath: (calling application path)\n");
    }
    else
    {
        PCANDebugOutput("* TracePath: ");
        PCANDebugOutput(TracePath); 
        PCANDebugOutput("\n");
    }
    PCANDebugOutput("* TimerInterval: ");
    PCANDebugOutput(std::to_string(TimerInterval));
    PCANDebugOutput("\n");
    PCANDebugOutput("\n");
}
