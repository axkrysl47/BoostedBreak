/***
 *  BoostedBreak - BoostedBreakCAN Program
 *
 *  PCANBasicDriver.h
 *
 *  Author: Alexander Krysl (axkrysl47)
 *  Date:   2022/04/03
 **/

#pragma once
#include "stdafx.h"
#include "PCANBasic.h"
#include "PCANBasicUtility.h"
#include "PCANBasicParameter.h"

#ifndef __PCANBASICDRIVERH__
#define __PCANBASICDRIVERH__

#define MESSAGE_QUEUE_SIZE (16)

class PCANBasicDriver
{
private:
    // *** Look Up Channel Variables ***
    /// <summary>
    /// Sets a TPCANDevice value. The input can be numeric, in hexadecimal or decimal format, or as string denoting 
    /// a TPCANDevice value name.
    /// </summary>
    LPCSTR DeviceType = "PCAN_USB";
    /// <summary>
    /// Sets value in range of a double. The input can be hexadecimal or decimal format.
    /// </summary>
    LPCSTR DeviceID = "";
    /// <summary>
    /// Sets a zero-based index value in range of a double. The input can be hexadecimal or decimal format.
    /// </summary>
    LPCSTR ControllerNumber = "";
    /// <summary>
    /// Sets a valid Internet Protocol address 
    /// </summary>
    LPCSTR IPAddress = "";

    // *** PCAN-Basic Variables ***
    /// <summary>
    /// Sets the PCANHandle (Hardware Channel)
    /// </summary>
    TPCANHandle PcanHandle = PCAN_USBBUS1;
    /// <summary>
    /// Sets the desired connection mode (CAN = false / CAN-FD = true)
    /// </summary>
    bool IsFD = false;
    /// <summary>
    /// Sets the bitrate for normal CAN devices
    /// </summary>
    TPCANBaudrate Bitrate = PCAN_BAUD_250K;
    /// <summary>
    /// Sets the bitrate for CAN FD devices. 
    /// Example - Bitrate Nom: 1Mbit/s Data: 2Mbit/s:
    ///   "f_clock_mhz=20, nom_brp=5, nom_tseg1=2, nom_tseg2=1, nom_sjw=1, data_brp=2, data_tseg1=3, data_tseg2=1, data_sjw=1"
    /// </summary>
    TPCANBitrateFD BitrateFD = const_cast<LPSTR>("f_clock_mhz=20, nom_brp=5, nom_tseg1=2, nom_tseg2=1, nom_sjw=1, data_brp=2, data_tseg1=3, data_tseg2=1, data_sjw=1");

    // *** Trace File Variables ***
    /// <summary>
    /// Sets if trace continue after reaching maximum size for the first file
    /// </summary>
    bool TraceFileSingle = false;
    /// <summary>
    /// Set if date will be add to filename 
    /// </summary>
    bool TraceFileDate = true;
    /// <summary>
    /// Set if time will be add to filename
    /// </summary>
    bool TraceFileTime = true;
    /// <summary>
    /// Set if existing tracefile overwrites when a new trace session is started
    /// </summary>
    bool TraceFileOverwrite = false;
    /// <summary>
    /// Sets the size (megabyte) of an tracefile 
    /// Example - 100 = 100 megabyte
    /// Range between 1 and 100
    /// </summary>
    UINT32 TraceFileSize = 2;
    /// <summary>
    /// Sets a fully-qualified and valid path to an existing directory. In order to use the default path 
    /// (calling process path) an empty string must be set.
    /// </summary>
    LPCSTR TracePath = "C:\\BoostedBreak\\BoostedBreakCAN\\TraceFiles";
    /// <summary>
    /// Timerinterval (ms) for reading 
    /// </summary>
    int TimerInterval = 250;

    /// *** Listening Thread Variables ***
    /// <summary>
    /// Thread for reading messages
    /// </summary>
    std::thread* m_DriverThread;
    /// <summary>
    /// Shows if thread run
    /// </summary>
    bool m_DriverThreadActive;

    /// *** Message Queue Variables ***
    /// <summary>
    /// Structure to receive messages
    /// </summary>
    std::deque<TPCANMsg>* m_ReceiveQueue;
    /// <summary>
    /// Structure to receive messages in FD mode
    /// </summary>
    std::deque<TPCANMsgFD>* m_ReceiveQueueFD;

    /// <summary>
    /// Structure to transmit messages
    /// </summary>
    std::deque<TPCANMsg>* m_TransmitQueue;
    /// <summary>
    /// Structure to transmit messages in FD mode
    /// </summary>
    std::deque<TPCANMsgFD>* m_TransmitQueueFD;

    /// <summary>
    /// Flag declaring if Driver Thread can log errors to output
    /// </summary>
    bool m_DriverThreadErrorLogFlag;
    /// <summary>
    /// Flag declaring if PCAN-Basic Module is initialized
    /// </summary>
    bool m_IsInitialized = false;
    /// <summary>
    /// Flag declaring if PCAN-Basic Tracing is initialized
    /// </summary>
    bool m_IsTraceConfigured = false;

public:
    // PCAN-Basic Class constructor
    //
    PCANBasicDriver(TPCANHandle handle, TPCANBaudrate bitrate, bool showOutput);

    // PCAN-Basic Class destructor
    //
    ~PCANBasicDriver();

    /// <summary>
    /// Describing if PCAN-Basic Module is initialized
    /// </summary>
    bool GetIsInitialized();
    /// <summary>
    /// Describing if PCAN-Basic Module is initialized
    /// </summary>
    bool GetIsTraceConfigured();

    /// <summary>
    /// Sets Driver Thread error logging flag
    /// </summary>
    bool SetDriverThreadErrorLogging(bool flag);

    /// <summary>
    /// Explicitly configures Trace variables
    /// </summary>
    bool ConfigureTrace(bool singleFileOnly, bool showDate, bool showTime, bool overwriteEnabled, 
        uint32_t fileSizeMegabytes, LPCSTR path, int32_t interval);

    /// <summary>
    /// Retrieves current PCAN-Basic Driver Status.
    /// </summary>
    TPCANStatus GetDriverStatus();

    /// <summary>
    /// Starts the PCAN-Basic Driver thread
    /// </summary>
    bool StartDriverThread();
    /// <summary>
    /// Stops the PCAN-Basic Driver thread
    /// </summary>
    bool StopDriverThread();
    
    /// <summary>
    /// Acquires CAN message from receive queue
    /// </summary>
    bool Receive(TPCANMsg* msgCanMessage);
    /// <summary>
    /// Acquires CAN FD message from receive queue
    /// </summary>
    bool ReceiveFD(TPCANMsgFD* msgCanMessageFD);
    /// <summary>
    /// Inserts CAN message into transmit queue
    /// </summary>
    bool Transmit(TPCANMsg msgCanMessage);
    /// <summary>
    /// Inserts CAN FD message into transmit queue
    /// </summary>
    bool TransmitFD(TPCANMsgFD msgCanMessageFD);
    /// <summary>
    /// Transmits a CAN message immediately - WARNING: May disrupt Driver Thread
    /// </summary>
    TPCANStatus TransmitImmediate(TPCANMsg msgCanMessage);
    /// <summary>
    /// Transmits a CAN Flexible Data message immediately - WARNING: May disrupt Driver Thread
    /// </summary>
    TPCANStatus TransmitImmediateFD(TPCANMsgFD msgCanMessageFD);

    /// <summary>
    /// Activates the PCAN-Basic tracing process
    /// </summary>
    /// <returns>Returns true if no error occurr</returns>
    bool StartTrace();
    /// <summary>
    /// Deactivates the PCAN-Basic tracing process
    /// </summary>
    void StopTrace();

    /// <summary>
    /// Looks up available PCAN-Basic Channels
    /// </summary>
    void TestLookUpChannels();
    /// <summary>
    /// Explicitly sets pre-defined parameters
    /// </summary>
    void TestGetSetParameter();
    /// <summary>
    /// Tests writing messages over PCAN-Basic
    /// </summary>
    void TestManualWrite();
    /// <summary>
    /// Begins Trace File routine.
    /// </summary>
    void TestTraceFiles();

private:
    /// <summary>
    /// Thread function for processing received and to-transmit messages
    /// </summary>
    void DriverThreadProcess();
    /// <summary>
    /// Reads available PCAN-Basic messages
    /// </summary>
    void ReceiveProcess();
    /// <summary>
    /// Transmits queued PCAN-Basic messages
    /// </summary>
    void TransmitProcess();

    /// <summary>
    /// Configures the way how trace files are formatted
    /// </summary>
    bool SetTraceConfiguration();

    /// <summary>
    /// Shows/prints the configurable parameters for this sample and information about them
    /// </summary>
    void ShowConfigurationHelp();

    /// <summary>
    /// Shows/prints the configured paramters
    /// </summary>
    void ShowCurrentConfiguration();
};

#endif //__PCANBASICDRIVERH__
