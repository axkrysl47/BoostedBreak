/***
 *  BoostedBreak - BoostedBreakCAN Program
 *
 *  PCANBasicUtility.h
 *
 *  Author: Alexander Krysl (axkrysl47)
 *  Date:   2022/04/03
 **/

#pragma once
#include "stdafx.h"
#include "PCANBasic.h"

#ifndef __PCANBASICUTILITYH__
#define __PCANBASICUTILITYH__

static void PCANDebugOutput(std::string str)
{
    std::cout << str;
}

static void PCANDebugSystemPause()
{
    system("PAUSE");
}

static void PCANDebugSystemClear()
{
    system("cls");
}

static TPCANMsg CreateTPCANMsg(DWORD id, TPCANMessageType MsgType, BYTE Len, BYTE* Data)
{
    TPCANMsg ret;

    ret.ID = id;
    ret.MSGTYPE = MsgType;
    ret.LEN = Len;

    for (BYTE i = 0; i < 8; i++)
    {
        if (i < Len)
        {
            ret.DATA[i] = Data[i];
        }
        else
        {
            ret.DATA[i] = 0x00;
        }
    }

    return ret;
}

static TPCANMsg CreateTPCANMsg(uint32_t id, TPCANMessageType MsgType, uint8_t Len, uint64_t Data)
{
    TPCANMsg ret;

    ret.ID = (DWORD)id;
    ret.MSGTYPE = MsgType;
    ret.LEN = (BYTE)Len;

    for (uint8_t i = 0; i < 8; i++)
    {
        if (i < Len)
        {
            ret.DATA[i] = (BYTE)((Data >> ((Len - i - 1) * 8)) & 0xFF);
        }
        else
        {
            ret.DATA[i] = (BYTE)0x00;
        }
    }

    return ret;
}

/// <summary>
/// Help Function used to get an error as text
/// </summary>
/// <param name="error">Error code to be translated</param>
/// <param name="buffer">A string buffer for the translated error (size MAX_PATH)</param>
static void GetFormattedError(TPCANStatus error, LPSTR buffer)
{
    // Gets the text using the GetErrorText API function. If the function success, the translated error is returned. 
    // If it fails, a text describing the current error is returned.
    if (CAN_GetErrorText(error, 0x09, buffer) != PCAN_ERROR_OK)
        sprintf_s(buffer, MAX_PATH, "An error occurred. Error-code's text (%Xh) couldn't be retrieved", error);
}

/// <summary>
/// Shows formatted status
/// </summary>
/// <param name="status">Will be formatted</param>
static void ShowStatus(TPCANStatus status)
{
    PCANDebugOutput("=========================================================================================\n");
    char buffer[MAX_PATH];
    GetFormattedError(status, buffer);
    PCANDebugOutput(buffer);
    PCANDebugOutput("\n");
    PCANDebugOutput("=========================================================================================\n");
}

/// <summary>
/// Gets name of a TPCANHandle
/// </summary>
/// <param name="handle">TPCANHandle to get name</param>
/// <param name="buffer">A string buffer for the name of the TPCANHandle (size MAX_PATH)</param>
static void GetTPCANHandleName(TPCANHandle handle, LPSTR buffer)
{
    strcpy_s(buffer, MAX_PATH, "PCAN_NONE");
    switch (handle)
    {
    case PCAN_PCIBUS1:
    case PCAN_PCIBUS2:
    case PCAN_PCIBUS3:
    case PCAN_PCIBUS4:
    case PCAN_PCIBUS5:
    case PCAN_PCIBUS6:
    case PCAN_PCIBUS7:
    case PCAN_PCIBUS8:
    case PCAN_PCIBUS9:
    case PCAN_PCIBUS10:
    case PCAN_PCIBUS11:
    case PCAN_PCIBUS12:
    case PCAN_PCIBUS13:
    case PCAN_PCIBUS14:
    case PCAN_PCIBUS15:
    case PCAN_PCIBUS16:
        strcpy_s(buffer, MAX_PATH, "PCAN_PCI");
        break;

    case PCAN_USBBUS1:
    case PCAN_USBBUS2:
    case PCAN_USBBUS3:
    case PCAN_USBBUS4:
    case PCAN_USBBUS5:
    case PCAN_USBBUS6:
    case PCAN_USBBUS7:
    case PCAN_USBBUS8:
    case PCAN_USBBUS9:
    case PCAN_USBBUS10:
    case PCAN_USBBUS11:
    case PCAN_USBBUS12:
    case PCAN_USBBUS13:
    case PCAN_USBBUS14:
    case PCAN_USBBUS15:
    case PCAN_USBBUS16:
        strcpy_s(buffer, MAX_PATH, "PCAN_USB");
        break;

    case PCAN_LANBUS1:
    case PCAN_LANBUS2:
    case PCAN_LANBUS3:
    case PCAN_LANBUS4:
    case PCAN_LANBUS5:
    case PCAN_LANBUS6:
    case PCAN_LANBUS7:
    case PCAN_LANBUS8:
    case PCAN_LANBUS9:
    case PCAN_LANBUS10:
    case PCAN_LANBUS11:
    case PCAN_LANBUS12:
    case PCAN_LANBUS13:
    case PCAN_LANBUS14:
    case PCAN_LANBUS15:
    case PCAN_LANBUS16:
        strcpy_s(buffer, MAX_PATH, "PCAN_LAN");
        break;

    default:
        strcpy_s(buffer, MAX_PATH, "UNKNOWN");
        break;
    }
}

static void FormatChannelName(TPCANHandle handle, LPSTR buffer, bool isFD)
{
    TPCANDevice devDevice;
    BYTE byChannel;

    // Gets the owner device and channel for a PCAN-Basic handle
    if (handle < 0x100)
    {
        devDevice = (TPCANDevice)(handle >> 4);
        byChannel = (BYTE)(handle & 0xF);
    }
    else
    {
        devDevice = (TPCANDevice)(handle >> 8);
        byChannel = (BYTE)(handle & 0xFF);
    }

    // Constructs the PCAN-Basic Channel name and return it
    char handleBuffer[MAX_PATH];
    GetTPCANHandleName(handle, handleBuffer);
    if (isFD)
        sprintf_s(buffer, MAX_PATH, "%s:FD %d (%Xh)", handleBuffer, byChannel, handle);
    else
        sprintf_s(buffer, MAX_PATH, "%s %d (%Xh)", handleBuffer, byChannel, handle);
}

/// <summary>
/// Converts PCANBasic Define (wchar_t*) to char*
/// </summary>
/// <param name="define">Define to be converted</param>
/// <returns>Define as char*</returns>
static char* ConvertDefinesToChar(wchar_t* define)
{
    // Convert the wchar_t string to a char* string. Record
    // the length of the original string and add 1 to it to
    // account for the terminating null character.
    size_t origsize = wcslen(define) + 1;
    size_t convertedChars = 0;

    // Allocate two bytes in the multibyte output string for every wide
    // character in the input string (including a wide character
    // null). Because a multibyte character can be one or two bytes,
    // you should allot two bytes for each character. Having extra
    // space for the new string is not an error, but having
    // insufficient space is a potential security problem.
    const size_t newsize = origsize * 2;
    // The new string will contain a converted copy of the original
    // string plus the type of string appended to it.
    char* nstring = new char[newsize];

    // Put a copy of the converted string into nstring
    wcstombs_s(&convertedChars, nstring, newsize, define, _TRUNCATE);
    return nstring;
}

/// <summary>
/// Convert BYTE value to readable string value
/// </summary>
/// <param name="devicetype"></param>
/// <returns></returns>
static std::string ConvertDeviceTypeToString(BYTE devicetype)
{
    switch (devicetype)
    {
    case 0:
        return "PCAN_NONE";
    case 1:
        return "PCAN_PEAKCAN";
    case 2:
        return "PCAN_ISA";
    case 3:
        return "PCAN_DNG";
    case 4:
        return "PCAN_PCI";
    case 5:
        return "PCAN_USB";
    case 6:
        return "PCAN_PCC";
    case 7:
        return "PCAN_VIRTUAL";
    case 8:
        return "PCAN_LAN";
    default:
        return "";
    }
}

/// <summary>
/// Convert uint value to readable string value
/// </summary>
/// <param name="value"></param>
/// <returns></returns>
static std::string ConvertToParameterOnOff(UINT32 value)
{
    switch (value)
    {
    case PCAN_PARAMETER_OFF:
        return "PCAN_PARAMETER_OFF";
    case PCAN_PARAMETER_ON:
        return "PCAN_PARAMETER_ON";
    default:
        return "Status unknown: " + std::to_string(value);
    }
}

/// <summary>
/// Convert uint value to readable string value
/// </summary>
/// <param name="value"></param>
/// <returns></returns>
static std::string ConvertToChannelFeatures(UINT32 value)
{
    std::string sFeatures = "";
    if ((value & FEATURE_FD_CAPABLE) == FEATURE_FD_CAPABLE)
        sFeatures += "FEATURE_FD_CAPABLE";
    if ((value & FEATURE_DELAY_CAPABLE) == FEATURE_DELAY_CAPABLE)
        if (sFeatures != "")
            sFeatures += ", FEATURE_DELAY_CAPABLE";
        else
            sFeatures += "FEATURE_DELAY_CAPABLE";
    if ((value & FEATURE_IO_CAPABLE) == FEATURE_IO_CAPABLE)
        if (sFeatures != "")
            sFeatures += ", FEATURE_IO_CAPABLE";
        else
            sFeatures += "FEATURE_IO_CAPABLE";
    return sFeatures;
}

/// <summary>
/// Convert uint value to readable string value
/// </summary>
/// <param name="value"></param>
/// <returns></returns>
static std::string ConvertToChannelCondition(UINT32 value)
{
    switch (value)
    {
    case PCAN_CHANNEL_UNAVAILABLE:
        return "PCAN_CHANNEL_UNAVAILABLE";
    case PCAN_CHANNEL_AVAILABLE:
        return "PCAN_CHANNEL_AVAILABLE";
    case PCAN_CHANNEL_OCCUPIED:
        return "PCAN_CHANNEL_OCCUPIED";
    case PCAN_CHANNEL_PCANVIEW:
        return "PCAN_CHANNEL_PCANVIEW";
    default:
        return "Status unknow: " + std::to_string(value);
    }
}

/// <summary>
/// Convert uint value to readable string value
/// </summary>
/// <param name="value"></param>
/// <returns></returns>
static std::string ConvertToFilterOpenCloseCustom(UINT32 value)
{
    switch (value)
    {
    case PCAN_FILTER_CLOSE:
        return "PCAN_FILTER_CLOSE";
    case PCAN_FILTER_OPEN:
        return "PCAN_FILTER_OPEN";
    case PCAN_FILTER_CUSTOM:
        return "PCAN_FILTER_CUSTOM";
    default:
        return "Status unknown: " + std::to_string(value);
    }
}

/// <summary>
/// Convert bitrate c_short value to readable string
/// </summary>
/// <param name="bitrate">Bitrate to be converted</param>
/// <param name="buffer">A string buffer for the converted bitrate (size MAX_PATH)</param>
static void ConvertBitrateToString(TPCANBaudrate bitrate, LPSTR buffer)
{
    switch (bitrate)
    {
    case PCAN_BAUD_1M:
        strcpy_s(buffer, MAX_PATH, "1 MBit/sec");
        break;
    case PCAN_BAUD_800K:
        strcpy_s(buffer, MAX_PATH, "800 kBit/sec");
        break;
    case PCAN_BAUD_500K:
        strcpy_s(buffer, MAX_PATH, "500 kBit/sec");
        break;
    case PCAN_BAUD_250K:
        strcpy_s(buffer, MAX_PATH, "250 kBit/sec");
        break;
    case PCAN_BAUD_125K:
        strcpy_s(buffer, MAX_PATH, "125 kBit/sec");
        break;
    case PCAN_BAUD_100K:
        strcpy_s(buffer, MAX_PATH, "100 kBit/sec");
        break;
    case PCAN_BAUD_95K:
        strcpy_s(buffer, MAX_PATH, "95,238 kBit/sec");
        break;
    case PCAN_BAUD_83K:
        strcpy_s(buffer, MAX_PATH, "83,333 kBit/sec");
        break;
    case PCAN_BAUD_50K:
        strcpy_s(buffer, MAX_PATH, "50 kBit/sec");
        break;
    case PCAN_BAUD_47K:
        strcpy_s(buffer, MAX_PATH, "47,619 kBit/sec");
        break;
    case PCAN_BAUD_33K:
        strcpy_s(buffer, MAX_PATH, "33,333 kBit/sec");
        break;
    case PCAN_BAUD_20K:
        strcpy_s(buffer, MAX_PATH, "20 kBit/sec");
        break;
    case PCAN_BAUD_10K:
        strcpy_s(buffer, MAX_PATH, "10 kBit/sec");
        break;
    case PCAN_BAUD_5K:
        strcpy_s(buffer, MAX_PATH, "5 kBit/sec");
        break;
    default:
        strcpy_s(buffer, MAX_PATH, "Unknown Bitrate");
        break;
    }
}

/// <summary>
/// Convert bool value to readable string value
/// </summary>
/// <param name="value">Value to be converted</param>
/// <returns>A text with the converted Value</returns>
static std::string ConvertBoolToString(bool value)
{
    switch (value)
    {
    case false:
        return "false";
    case true:
        return "true";
    }
}

#endif
