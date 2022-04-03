/***
 *  BoostedBreak - BoostedBreakCAN Program
 *
 *  BoostedCANMsg.h
 *
 *  Author: Alexander Krysl (axkrysl47)
 *  Date:   2022/04/03
 **/

#pragma once
#include <algorithm>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include "PCANBasic.h"
#include "PCANBasicUtility.h"

#ifndef __BOOSTEDCANMSGH__
#define __BOOSTEDCANMSGH__

class BoostedCANMsg
{
public:
    uint32_t MessageID;
    uint8_t  MessageCounter;
    uint8_t  MessageLength;
    uint8_t  MessageBuffer[8];

    BoostedCANMsg()
    {
        MessageID = 0x00000000;
        MessageCounter = 0;
        MessageLength = 0;

        for (int_fast8_t i = 0; i < 8; i++)
        {
            MessageBuffer[i] = 0x00;
        }
    };

    BoostedCANMsg(const TPCANMsg& CanMsg)
    {
        MessageID       = (uint32_t)(((CanMsg.ID) & CanIDMessageMask) >> CanIDMessageOffset);
        MessageCounter  = (uint8_t)(((CanMsg.ID) & CanIDCounterMask) >> CanIDCounterOffset);
        MessageLength   = (uint8_t)(CanMsg.LEN);
        
        for (int_fast8_t i = 0; i < 8; i++)
        {
            if (i < CanMsg.LEN)
            {
                MessageBuffer[i] = CanMsg.DATA[i];
            }
            else
            {
                MessageBuffer[i] = 0x00;
            }
        }
    }

    BoostedCANMsg(uint32_t messageID, uint8_t messageLength, uint8_t* messageBuffer)
    {
        MessageID = messageID;
        MessageCounter = 0;
        MessageLength = messageLength;

        for (int_fast8_t i = 0; i < 8; i++)
        {
            if (i < messageLength)
            {
                MessageBuffer[i] = messageBuffer[i];
            }
            else
            {
                MessageBuffer[i] = 0x00;
            }
        }
    }

    BoostedCANMsg(uint32_t messageID, uint8_t messageCounter, uint8_t messageLength, uint8_t* messageBuffer)
    {
        MessageID = (messageID & (CanIDMessageMask >> CanIDMessageOffset));
        MessageCounter = (messageCounter & (CanIDCounterMask >> CanIDCounterOffset));
        MessageLength = (8 < messageLength) ? 8 : messageLength;

        for (uint_fast8_t i = 0; i < 8; i++)
        {
            if (i < MessageLength)
            {
                MessageBuffer[i] = messageBuffer[i];
            }
            else
            {
                MessageBuffer[i] = 0x00;
            }
        }
    }

    BoostedCANMsg(uint32_t messageID, uint8_t messageCounter, uint8_t messageLength, uint64_t messageBuffer)
    {
        MessageID = (messageID & (CanIDMessageMask >> CanIDMessageOffset));
        MessageCounter = (messageCounter & (CanIDCounterMask >> CanIDCounterOffset));
        MessageLength = (8 < messageLength) ? 8 : messageLength;

        for (uint_fast8_t i = 0; i < 8; i++)
        {
            if (i < messageLength)
            {
                MessageBuffer[i] = (BYTE)((messageBuffer >> ((messageLength - i - 1) * 8)) & 0xFF);
            }
            else
            {
                MessageBuffer[i] = (BYTE)0x00;
            }
        }
    }

    TPCANMsg AsTPCANMsg() const
    {
        uint32_t canID = CanIDPrefix 
            + ((MessageID << CanIDMessageOffset) & CanIDMessageMask)
            + ((MessageCounter << CanIDCounterOffset) & CanIDCounterMask);
        return CreateTPCANMsg(canID, PCAN_MESSAGE_EXTENDED, MessageLength, (BYTE*)MessageBuffer);
    }

    std::string AsString()
    {
        std::string output;
        char temp[32];

        sprintf_s(temp, 32, "%05lx", MessageID);
        output += temp;
        output += " ";
        sprintf_s(temp, 32, "%01x", MessageCounter);
        output += temp;
        output += " ";
        sprintf_s(temp, 32, "%01d", MessageLength);
        output += temp;
        output += " - ";

        for (int_fast8_t i = 0; i < MessageLength; i++)
        {
            sprintf_s(temp, 32, "%02x", MessageBuffer[i]);
            output += temp;
            output += " ";
        }

        std::transform(output.begin(), output.end(), output.begin(), ::toupper);
        return output;
    }

    std::string CANIDAsString()
    {
        std::string output;
        char temp[32];

        sprintf_s(temp, 32, "%05lx", MessageID);
        output += temp;
        output += " ";

        std::transform(output.begin(), output.end(), output.begin(), ::toupper);
        return output;
    }

    std::string CounterAsStringHex()
    {
        std::string output;
        char temp[32];

        sprintf_s(temp, 32, "%01x", MessageCounter);
        output += temp;
        output += " ";

        std::transform(output.begin(), output.end(), output.begin(), ::toupper);
        return output;
    }

    std::string MessageBufferAsString()
    {
        std::string output;
        char temp[32];

        for (int_fast8_t i = 0; i < MessageLength; i++)
        {
            sprintf_s(temp, 32, "%02x", MessageBuffer[i]);
            output += temp;
        }

        std::transform(output.begin(), output.end(), output.begin(), ::toupper);
        return output;
    }

    std::string MessageBufferAsStringSpaced()
    {
        std::string output;
        char temp[32];

        for (int_fast8_t i = 0; i < MessageLength; i++)
        {
            sprintf_s(temp, 32, "%02x", MessageBuffer[i]);
            output += temp;
            output += " ";
        }

        std::transform(output.begin(), output.end(), output.begin(), ::toupper);
        return output;
    }

    uint64_t MessageBufferAsInteger()
    {
        uint64_t ret = 0;
        for (int_fast8_t i = 0; i < MessageLength; i++)
        {
            ret = ret + ((uint64_t)(MessageBuffer[i]) << (56 - (i * 8)));
        }
        return ret;
    }

    uint64_t MessageBufferAsIntegerBigEndian()
    {
        uint64_t ret = 0;
        for (int_fast8_t i = 0; i < MessageLength; i++)
        {
            ret = ret + ((uint64_t)(MessageBuffer[i]) << (i * 8));
        }
        return ret;
    }

protected:
    uint32_t CanIDPrefix = 0x10000000;
    uint32_t CanIDMessageMask = 0x00FFFFF0;
    uint32_t CanIDMessageOffset = 4;
    uint32_t CanIDCounterMask = 0x0000000F;
    uint32_t CanIDCounterOffset = 0;
};

#endif //__BOOSTEDCANMSGH__
