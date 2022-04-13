/***
 *  BoostedBreak - BoostedBreakCAN Program
 *
 *  BoostedBreakCAN.cpp
 *
 *  Author: Alexander Krysl (axkrysl47)
 *  Date:   2022/04/03
 **/

#include "BoostedBreakCAN.h" 
#include "ConsoleInterface.h"

#define DISPLAY_TRANSMIT_WITH_RECEIVE
#undef  PRINT_TRANSMIT_MODE

#define TABLE_OFFSET_Y              4

#define CURSOR_TABLE_ERROR          0, 46

#define CURSOR_MESSAGE_COUNTER_X    6
#define CURSOR_MESSAGE_LEGNTH_X     8
#define CURSOR_SENDER_DESCRIPTION_X 35
#define CURSOR_INTERPRETATION_X     70
#define CURSOR_TRANSMITTED_X        128

#define TABLELIST_BREAK_1           14
#define TABLELIST_BREAK_2           30

#define PING_TIMER_MS               100
#define BEAMBREAK_TIMER_MS          250
#define ESC_BTY_REGISTRATION_COMMAND_TIMER_MS 3000

#define ESC_VERSION_SERIAL          0x02070201EEFFC047 // ESC v2.7.2, BoostedBoard47C0FFEE

BoostedBreakCAN::BoostedBreakCAN(PCANBasicDriver* pcan)
{
    m_LastPingTime = std::chrono::high_resolution_clock::now();
    m_TransmitStageTime = std::chrono::high_resolution_clock::now();
    m_LastTransmitCounter = 0;
    m_ControlThread = nullptr;

    // PCAN-Basic Initialization
    m_CommPtr = pcan;

    // Default to Table Mode, not transmitting.
    m_ViewMode = VIEWMODE_TABLE;
    m_TransmitMode = TRANSMITMODE_NONE;
    SetTable();

    m_TransmitStage = 0;
}

BoostedBreakCAN::~BoostedBreakCAN()
{
    StopControlThread();
    ConsolePrint("\nExiting BoostedBreak - BoostedBreakCAN Program . . .\n");
}

bool BoostedBreakCAN::SetViewMode(uint8_t newViewMode)
{
    if (newViewMode != m_ViewMode)
    {
        m_ViewMode = newViewMode;

        if (m_ViewMode == VIEWMODE_STREAM)
        {
            ConsoleClear();
            ConsoleCursor(CURSOR_TABLE_ERROR);
        }
        else if (m_ViewMode == VIEWMODE_TABLE)
        {
            StopControlThread();
            SetTable();

            std::this_thread::sleep_for(std::chrono::microseconds(1000));

            StartControlThread();
        }
        else if (m_ViewMode == VIEWMODE_BRIEF)
        {
            // TODO...
            ConsoleCursor(CURSOR_TABLE_ERROR);
            ConsolePrint(" Brief mode not yet implemented (Pausing previous view mode).");
        }

        return true;
    }

    return false;
}

bool BoostedBreakCAN::SetTransmitMode(uint8_t newTransmitMode)
{
    if (newTransmitMode != m_TransmitMode)
    {
        m_TransmitStage = 0;

        if (newTransmitMode == TRANSMITMODE_NONE)
        {
#ifdef PRINT_TRANSMIT_MODE
            ConsolePrint("Off                         ", CURSOR_TRANSMITMODE);
#endif //PRINT_TRANSMIT_MODE
            m_TransmitMode = TRANSMITMODE_NONE;
        }
        else if (newTransmitMode == TRANSMITMODE_PINGONLY)
        {
#ifdef PRINT_TRANSMIT_MODE
            ConsolePrint("Pinging...                  ", CURSOR_TRANSMITMODE);
#endif //PRINT_TRANSMIT_MODE
            m_TransmitMode = TRANSMITMODE_PINGONLY;
        }
        else if (newTransmitMode == TRANSMITMODE_PINGPOWEROFF)
        {
#ifdef PRINT_TRANSMIT_MODE
            ConsolePrint("Pinging Power Off...        ", CURSOR_TRANSMITMODE);
#endif //PRINT_TRANSMIT_MODE
            m_TransmitMode = TRANSMITMODE_PINGPOWEROFF;
        }
        else if (newTransmitMode == TRANSMITMODE_EMULATEESC)
        {
#ifdef PRINT_TRANSMIT_MODE
            ConsolePrint("Emulating ESC...            ", CURSOR_TRANSMITMODE);
#endif //PRINT_TRANSMIT_MODE
            m_TransmitMode = TRANSMITMODE_EMULATEESC;
        }
        else if (newTransmitMode == TRANSMITMODE_EMULATESRB)
        {
            // TODO
#ifdef PRINT_TRANSMIT_MODE
            ConsolePrint("SRB not yet implemented.    ", CURSOR_TRANSMITMODE);
#endif //PRINT_TRANSMIT_MODE
            m_TransmitMode = TRANSMITMODE_EMULATEESC;
        }
        else if (newTransmitMode == TRANSMITMODE_EMULATEXRB)
        {
            // TODO
#ifdef PRINT_TRANSMIT_MODE
            ConsolePrint("XRB not yet implemented.    ", CURSOR_TRANSMITMODE);
#endif //PRINT_TRANSMIT_MODE
            m_TransmitMode = TRANSMITMODE_EMULATEESC;
        }
        else if (newTransmitMode == TRANSMITMODE_BEAMBREAKSRB)
        {
#ifdef PRINT_TRANSMIT_MODE
            ConsolePrint("Emulating SRB (BeamBreak)...", CURSOR_TRANSMITMODE);
#endif //PRINT_TRANSMIT_MODE
            m_TransmitMode = TRANSMITMODE_BEAMBREAKSRB;
        }
    }

    return true;
}

bool BoostedBreakCAN::StartControlThread()
{
    m_ControlThreadActive = true;
    m_ControlThread = new std::thread(&BoostedBreakCAN::ControlThreadProcess, this);
    return m_ControlThreadActive;
}

bool BoostedBreakCAN::StopControlThread()
{
    m_ControlThreadActive = false;
    if (m_ControlThread != nullptr)
    {
        m_ControlThread->join();
    }
    m_ControlThread = nullptr;
    return m_ControlThreadActive;
}

uint8_t BoostedBreakCAN::GetViewMode()
{
    return m_ViewMode;
}

uint8_t BoostedBreakCAN::GetTransmitMode()
{
    return m_TransmitMode;
}

void BoostedBreakCAN::ControlThreadProcess()
{
    while (m_ControlThreadActive)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        ProgramControl();
    }
}

void BoostedBreakCAN::ProgramControl()
{
    TPCANStatus status;
    TPCANMsg msgCanMessage;

    if (m_CommPtr == nullptr)
    {
        return;
    }

    status = m_CommPtr->GetDriverStatus();
    ParseError(status);

    while (m_CommPtr->Receive(&msgCanMessage))
    {
        status = m_CommPtr->GetDriverStatus();
        ParseError(status);
        ParseMessage(msgCanMessage);
    }

    SendMessages(std::chrono::high_resolution_clock::now());
}

void BoostedBreakCAN::ParseError(TPCANStatus status)
{
    TPCANStatus prevStatus = PCAN_ERROR_ILLOPERATION;
    char errorText[64];

    if (m_ViewMode == VIEWMODE_STREAM)
    {
        if (status != PCAN_ERROR_OK)
        {
            CAN_GetErrorText(status, 0x09, errorText);
            ConsolePrint("Status: ");
            ConsolePrint(errorText);
            ConsolePrint("\n");
        }
    }
    else if (m_ViewMode == VIEWMODE_TABLE)
    {
        if (status != PCAN_ERROR_OK)
        {
            ConsoleCursor(CURSOR_TABLE_ERROR);

            CAN_GetErrorText(status, 0x09, errorText);
            ConsolePrint("Status: ");
            ConsolePrint(errorText);
            ConsolePrint("\n");

            prevStatus = status;
        }
        else if (status == PCAN_ERROR_OK && prevStatus != PCAN_ERROR_OK)
        {
            ConsoleCursor(CURSOR_TABLE_ERROR);
            CAN_GetErrorText(status, 0x09, errorText);
            ConsolePrint("                                                                                              \n");
        }
    }
}

void BoostedBreakCAN::ParseMessage(TPCANMsg msgCanMessage)
{
    BoostedCANMsg message(msgCanMessage);
    BoostedCANMsgInfo info(message);
    
    ParseMessageView(message, info);
    ParseMessageTransmit(message);
}

void BoostedBreakCAN::ParseMessageView(BoostedCANMsg message, BoostedCANMsgInfo info)
{
    uint16_t cursorY;
    uint32_t num = 0;

    if (m_ViewMode == VIEWMODE_STREAM)
    {
        ConsolePrint(message.AsString());
        ConsolePrint(info.Sender + " " + info.Description + "\t", CURSOR_SENDER_DESCRIPTION_X);
        ConsolePrint(info.Interpretation + "                " "\n", CURSOR_INTERPRETATION_X);
        return;
    }
    else if (m_ViewMode == VIEWMODE_TABLE && info.Index <= NUM_BOOSTED_CAN_MSG)
    {
        cursorY = info.Index + TABLE_OFFSET_Y;
        if (TABLELIST_BREAK_1 <= info.Index)
        {
            cursorY++;
        }
        if (TABLELIST_BREAK_2 <= info.Index)
        {
            cursorY++;
        }

        ConsolePrint(message.CounterAsStringHex(), CURSOR_MESSAGE_COUNTER_X, cursorY);

        ConsolePrint(std::to_string(message.MessageLength), CURSOR_MESSAGE_LEGNTH_X, cursorY);
        if (info.Length == message.MessageLength
            || info.Length == LENGTH_UNKNOWN)
        {
            ConsolePrint(" ");
        }
        else
        {
            ConsolePrint("!");
        }
        ConsolePrint(message.MessageBufferAsStringSpaced());

        ConsolePrint(info.Interpretation, CURSOR_INTERPRETATION_X, cursorY);
        ConsolePrint("                     ");
    }
    else if (m_ViewMode == VIEWMODE_BRIEF)
    {
        // TODO...
    }
}

void BoostedBreakCAN::ParseMessageTransmit(BoostedCANMsg message)
{
    if (m_TransmitMode == TRANSMITMODE_NONE)
    {
        return;
    }
    else if (m_TransmitMode == TRANSMITMODE_PINGONLY)
    {
        return;
    }
    else if (m_TransmitMode == TRANSMITMODE_PINGPOWEROFF)
    {
        return;
    }
    else if (m_TransmitMode == TRANSMITMODE_EMULATEESC)
    {
        if (m_TransmitStage == 0
            && message.MessageID == 0x33417
            && message.MessageBuffer[0] == 0x01
            && message.MessageBuffer[1] == 0x0A)
        {
            m_TransmitStage = 1;
            //m_TransmitStageTime = std::chrono::high_resolution_clock::now();
        }
        else if (m_TransmitStage == 2
            && message.MessageID == 0x25415)
        {
            m_TransmitStage = 3;
        }
    }
    else if (m_TransmitMode == TRANSMITMODE_EMULATESRB)
    {
        // TODO...
        return;
    }
    else if (m_TransmitMode == TRANSMITMODE_EMULATEXRB)
    {
        // TODO...
        return;
    }
    else if (m_TransmitMode == TRANSMITMODE_BEAMBREAKSRB)
    {
        if (m_TransmitStage == 0)
        {
            m_TransmitStage = 1;
        }
    }
}

void BoostedBreakCAN::SendMessages(std::chrono::steady_clock::time_point timeNow)
{
    uint64_t timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - m_TransmitStageTime).count();

    if (m_TransmitMode == TRANSMITMODE_NONE)
    {
        return;
    }
    else if (m_TransmitMode == TRANSMITMODE_PINGONLY)
    {
        SendPing(timeNow, 0x00);
    }
    else if (m_TransmitMode == TRANSMITMODE_PINGPOWEROFF)
    {
        SendPing(timeNow, 0x02);
    }
    else if (m_TransmitMode == TRANSMITMODE_EMULATEESC)
    {
        if (m_TransmitStage == 0)
        {
            return;
        }
        else if (m_TransmitStage == 1)
        {
            TransmitBoostedCANMessage(0x34344, 8, ESC_VERSION_SERIAL);
            TransmitBoostedCANMessage(0x34316, 3, 0x020600);
            m_TransmitStageTime = std::chrono::high_resolution_clock::now();
            SendPing(timeNow, 0x00);

            m_TransmitStage = 2;
        }
        else if (m_TransmitStage == 2)
        {
            if (ESC_BTY_REGISTRATION_COMMAND_TIMER_MS <= timeDiff)
            {
                TransmitBoostedCANMessage(0x34316, 3, 0x010C00);
                m_TransmitStageTime = std::chrono::high_resolution_clock::now();
            }
            SendPing(timeNow, 0x00);
        }
        else if (m_TransmitStage == 3)
        {
            SendPing(timeNow, 0x00);
        }
    }
    else if (m_TransmitMode == TRANSMITMODE_EMULATESRB)
    {
        // TODO...
    }
    else if (m_TransmitMode == TRANSMITMODE_EMULATEXRB)
    {
        // TODO...
        /*if (m_TransmitStage == 2)
        {
            TransmitBoostedCANMessage(0x33448, 8, 0xB8880000D8590000);
        }*/
    }
    else if (m_TransmitMode == TRANSMITMODE_BEAMBREAKSRB)
    {
        TPCANMsg canMessage;

        if (m_TransmitStage == 0)
        {
            return;
        }
        else if (m_TransmitStage == 1)
        {
            canMessage = CreateTPCANMsg(0x0B57ED00, PCAN_MESSAGE_EXTENDED, 8, 0x0104013366343531);
            m_CommPtr->Transmit(canMessage);
            ShowSentMessage(canMessage);

            canMessage = CreateTPCANMsg(0x0B57ED01, PCAN_MESSAGE_EXTENDED, 8, 0xEEFFC000F78A0101);
            m_CommPtr->Transmit(canMessage);
            ShowSentMessage(canMessage);

            canMessage = CreateTPCANMsg(0x0B57ED03, PCAN_MESSAGE_EXTENDED, 8, 0xD20FCA080C000000);
            m_CommPtr->Transmit(canMessage);
            ShowSentMessage(canMessage);

            m_TransmitStageTime = std::chrono::high_resolution_clock::now();
            m_TransmitStage = 2;
        }
        else if (m_TransmitStage == 2)
        {
            if (BEAMBREAK_TIMER_MS <= timeDiff)
            {
                canMessage = CreateTPCANMsg(0x0B57ED02, PCAN_MESSAGE_EXTENDED, 8, 0x0000C40900000000);
                m_CommPtr->Transmit(canMessage);
                ShowSentMessage(canMessage);

                canMessage = CreateTPCANMsg(0x0B57ED10, PCAN_MESSAGE_EXTENDED, 8, 0xF00CFB0CBB9B0000);
                m_CommPtr->Transmit(canMessage);
                ShowSentMessage(canMessage);

                canMessage = CreateTPCANMsg(0x0B57ED14, PCAN_MESSAGE_EXTENDED, 8, 0x9B07C4092A000500);
                m_CommPtr->Transmit(canMessage);
                ShowSentMessage(canMessage);

                canMessage = CreateTPCANMsg(0x0B57ED15, PCAN_MESSAGE_EXTENDED, 8, 0x0000000000007F00);
                m_CommPtr->Transmit(canMessage);
                ShowSentMessage(canMessage);
            }
        }
    }
}

void BoostedBreakCAN::TransmitBoostedCANMessage(uint32_t messageID, uint8_t messageLength, uint64_t messageBuffer)
{
    BoostedCANMsg message(messageID, m_LastTransmitCounter, messageLength, messageBuffer);
    if (++m_LastTransmitCounter >= 0x10)
    {
        m_LastTransmitCounter = 0x00;
    }
    m_CommPtr->Transmit(message.AsTPCANMsg());
#ifdef DISPLAY_TRANSMIT_WITH_RECEIVE
    ShowSentMessage(message.AsTPCANMsg());
#endif //DISPLAY_TRANSMIT_WITH_RECEIVE
}

void BoostedBreakCAN::SendPing(std::chrono::steady_clock::time_point timeNow, uint8_t param)
{
    uint64_t timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - m_LastPingTime).count();

    if (PING_TIMER_MS <= timeDiff)
    {
        uint8_t messageBuffer[8] = { param, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        BoostedCANMsg message(0x3434B, m_LastTransmitCounter, 8, messageBuffer);
        if (++m_LastTransmitCounter >= 0x10)
            { m_LastTransmitCounter = 0x00; }
        m_CommPtr->Transmit(message.AsTPCANMsg());

        m_LastPingTime = std::chrono::high_resolution_clock::now();

        ShowSentMessage(message.AsTPCANMsg());
    }
}

void BoostedBreakCAN::ShowSentMessage(TPCANMsg msgCanMessage)
{
    ParseMessage(msgCanMessage);
    ConsolePrint("[TX]", CURSOR_TRANSMITTED_X);
}

void BoostedBreakCAN::SetTable()
{
    uint16_t cursorY;
    uint8_t defaultLength = 8;
    uint8_t defaultMsg[8] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
    
    ConsoleClear();

    for (int_fast8_t i = 0; i < NUM_BOOSTED_CAN_MSG; i++)
    {
        uint32_t messageID = BoostedCANMsgList[i];

        BoostedCANMsg message(messageID, defaultLength, defaultMsg);
        BoostedCANMsgInfo info(message);

        cursorY = info.Index + TABLE_OFFSET_Y;
        if (TABLELIST_BREAK_1 <= info.Index)
        {
            cursorY++;
        }
        if (TABLELIST_BREAK_2 <= info.Index)
        {
            cursorY++;
        }

        ConsolePrint(message.CANIDAsString(), 0, cursorY);
        ConsolePrint(info.Sender + " " + info.Description, CURSOR_SENDER_DESCRIPTION_X, cursorY);
    }
    
    ConsolePrint("\n");
}

void BoostedBreakCAN::DebugCommand()
{
    m_TransmitStage++;
}
