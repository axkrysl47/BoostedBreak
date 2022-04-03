/***
 *  BoostedBreak - BoostedBreakCAN Program
 *
 *  BoostedBreakCAN.h
 *
 *  Author: Alexander Krysl (axkrysl47)
 *  Date:   2022/04/03
 **/

#pragma once
#include"stdafx.h"
#include "PCANBasicDriver.h"
#include "BoostedCANMsg.h"
#include "BoostedCANMsgInfo.h"

#ifndef __BOOSTEDBREAKCANH__
#define __BOOSTEDBREAKCANH__

#define VIEWMODE_STREAM (0)
#define VIEWMODE_TABLE  (1)
#define VIEWMODE_BRIEF  (2)

#define TRANSMITMODE_NONE (3)
#define TRANSMITMODE_PINGONLY (4)
#define TRANSMITMODE_PINGPOWEROFF (5)
#define TRANSMITMODE_EMULATEESC (6)
#define TRANSMITMODE_EMULATESRB (7)
#define TRANSMITMODE_EMULATEXRB (8)
#define TRANSMITMODE_BEAMBREAKSRB (9)

#define CURSOR_TRANSMITMODE 83, 1
#define CURSOR_TABLE_ERROR 0, 46

#define CURSOR_MESSAGE_COUNTER_X 6
#define CURSOR_MESSAGE_LEGNTH_X 8
#define CURSOR_SENDER_DESCRIPTION_X 35
#define CURSOR_INTERPRETATION_X 70
#define CURSOR_TRANSMITTED_X 128

#define TABLE_OFFSET_Y 4

class BoostedBreakCAN
{
private:
    /// <summary>
    /// Pointer to PCAN-Basic Class Driver
    /// </summary>
    PCANBasicDriver* m_CommPtr = nullptr;

    /// *** Control Thread Variables ***
    /// <summary>
    /// Thread for reading messages
    /// </summary>
    std::thread* m_ControlThread;
    /// <summary>
    /// Shows if thread run
    /// </summary>
    bool m_ControlThreadActive;

    /// <summary>
    /// State variable for receive view 
    /// </summary>
    uint8_t m_ViewMode;
    /// <summary>
    /// State variable for transmit protocol
    /// </summary>
    uint8_t m_TransmitMode;

    /// <summary>
    /// Timestamp for last transmitted message.
    /// </summary>
    std::chrono::steady_clock::time_point m_LastPingTime;
    /// <summary>
    /// Timestamp for current transmit protocol timer.
    /// </summary>
    std::chrono::steady_clock::time_point m_TransmitStageTime;
    /// <summary>
    /// Counter variable for transmit protocol
    /// </summary>
    uint8_t m_LastTransmitCounter;

    uint8_t m_TransmitStage;

public:
    //// Boosted Break constructor
    ////
    //BoostedBreakCAN();

    // Boosted Break constructor
    //
    BoostedBreakCAN(PCANBasicDriver* pcan);

    // Boosted Break destructor
    //
    ~BoostedBreakCAN();

    /// <summary>
    /// Sets the current receive view
    /// </summary>
    bool SetViewMode(uint8_t newMode);
    /// <summary>
    /// Sets the current transmit protocol
    /// </summary>
    bool SetTransmitMode(uint8_t newMode);

    /// <summary>
    /// Starts program control thread
    /// </summary>
    bool StartControlThread();
    /// <summary>
    /// Stops program control thread.
    /// </summary>
    bool StopControlThread();

    /// <summary>
    /// Debug Command, used for testing.
    /// </summary>
    void DebugCommand();

    /// <summary>
    /// Gets the current receive view
    /// </summary>
    uint8_t GetViewMode();
    /// <summary>
    /// Gets the current transmit protocol
    /// </summary>
    uint8_t GetTransmitMode();

protected:
    /// <summary>
    /// Thread function for receiving and transmitting messages
    /// </summary>
    void ControlThreadProcess();
    /// <summary>
    /// High-level Program control function
    /// </summary>
    void ProgramControl();
    /// <summary>
    /// Parses error condition into view
    /// </summary>
    void ParseError(TPCANStatus status);
    /// <summary>
    /// Parses received messages for view and transmission
    /// </summary>
    void ParseMessage(TPCANMsg msgCanMessage);
    /// <summary>
    /// Parses received messages for view
    /// </summary>
    void ParseMessageView(BoostedCANMsg message, BoostedCANMsgInfo info);
    /// <summary>
    /// Parses received messages for transmission
    /// </summary>
    void ParseMessageTransmit(BoostedCANMsg message);
    /// <summary>
    /// Sends messages per current protocol
    /// </summary>
    void SendMessages(std::chrono::steady_clock::time_point timeNow);
    /// <summary>
    /// Creates and transmits a BoostedCANMsg
    /// </summary>
    void TransmitBoostedCANMessage(uint32_t messageID, uint8_t messageLength, uint64_t messageBuffer);
    /// <summary>
    /// Sends ping per current protocol
    /// </summary>
    void SendPing(std::chrono::steady_clock::time_point timeNow, uint8_t param);
    /// <summary>
    /// Displays to user transmitted messages;
    /// </summary>
    void ShowSentMessage(TPCANMsg msgCanMessage);

    /// <summary>
    /// Initializes table view
    /// </summary>
    void SetTable();

    /// <summary>
    /// List of valid Boosted CAN Message identifiers.
    /// </summary>
    const uint32_t BoostedCANMsgList[NUM_BOOSTED_CAN_MSG] =
    {
        0x00000, 0x02402, 0x02411, 0x05415, 0x12402, 0x12411, 0x13417, 0x15415,
        0x22402, 0x22411, 0x23417, 0x25415, 0x32411, 0x33417, 0x33440, 0x33441,
        0x33442, 0x33443, 0x33444, 0x33445, 0x33446, 0x33447, 0x33448, 0x33449,
        0x3344A, 0x3344B, 0x3344C, 0x3344D, 0x3344E, 0x3344F, 0x34316, 0x34344,
        0x3434B, 0x3434C, 0x3434D, 0x3B31A, 0x3B41A, 0x33920, 0x39320
    };
};

#endif //__BOOSTEDBREAKCANH__
