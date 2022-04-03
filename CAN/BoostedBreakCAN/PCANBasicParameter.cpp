/***
 *  BoostedBreak - BoostedBreakCAN Program
 *
 *  PCANBasicParameter.cpp
 *
 *  Author: Alexander Krysl (axkrysl47)
 *  Date:   2022/04/03
 **/

#include "PCANBasicParameter.h"

void GetPCAN_DEVICE_ID(TPCANHandle handle)
{
    UINT32 iDeviceID;
    TPCANStatus stsResult = CAN_GetValue(handle, PCAN_DEVICE_ID, &iDeviceID, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Get PCAN_DEVICE_ID: ");
        PCANDebugOutput(std::to_string(iDeviceID));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void SetPCAN_DEVICE_ID(TPCANHandle handle, UINT32 iDeviceID)
{
    TPCANStatus stsResult = CAN_SetValue(handle, PCAN_DEVICE_ID, &iDeviceID, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Set PCAN_DEVICE_ID: ");
        PCANDebugOutput(std::to_string(iDeviceID));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}


void GetPCAN_ATTACHED_CHANNELS(bool isFD)
{
    UINT32 iChannelsCount;
    TPCANStatus stsResult = CAN_GetValue(PCAN_NONEBUS, PCAN_ATTACHED_CHANNELS_COUNT, &iChannelsCount, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        TPCANChannelInformation* ciChannelInformation = new TPCANChannelInformation[iChannelsCount];

        stsResult = CAN_GetValue(PCAN_NONEBUS, PCAN_ATTACHED_CHANNELS, ciChannelInformation, iChannelsCount * sizeof(TPCANChannelInformation));

        if (stsResult == PCAN_ERROR_OK)
        {
            PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
            PCANDebugOutput("Get PCAN_ATTACHED_CHANNELS:\n");

            for (int i = 0; i < (int)iChannelsCount; i++)
            {
                PCANDebugOutput("---------------------------\n");
                char buffer[MAX_PATH];
                GetTPCANHandleName(ciChannelInformation[i].channel_handle, buffer);
                if (isFD)
                {
                    PCANDebugOutput("channel_handle:      ");
                    PCANDebugOutput(buffer);
                    PCANDebugOutput("BUS");
                    PCANDebugOutput(std::to_string(ciChannelInformation[i].channel_handle & 0xFF));
                    PCANDebugOutput("\n");

                }
                else
                {
                    PCANDebugOutput("channel_handle:      ");
                    PCANDebugOutput(buffer);
                    PCANDebugOutput("BUS");
                    PCANDebugOutput(std::to_string(ciChannelInformation[i].channel_handle & 0xF));
                    PCANDebugOutput("\n");

                }
                PCANDebugOutput("device_type:         "); 
                PCANDebugOutput(ConvertDeviceTypeToString(ciChannelInformation[i].device_type));
                PCANDebugOutput("\n");
                PCANDebugOutput("controller_number:   ");
                PCANDebugOutput(std::to_string((int)ciChannelInformation[i].controller_number)); 
                PCANDebugOutput("\n");
                PCANDebugOutput("device_features:     ");
                PCANDebugOutput(ConvertToChannelFeatures(ciChannelInformation[i].device_features));
                PCANDebugOutput("\n");
                PCANDebugOutput("device_name:         ");
                PCANDebugOutput(ciChannelInformation[i].device_name);
                PCANDebugOutput("\n");
                PCANDebugOutput("device_id:           ");
                PCANDebugOutput(std::to_string(ciChannelInformation[i].device_id));
                PCANDebugOutput("\n");
                PCANDebugOutput("channel_condition:   ");
                PCANDebugOutput(ConvertToChannelCondition(ciChannelInformation[i].channel_condition));
                PCANDebugOutput("\n");
            }
            PCANDebugOutput("\n");
        }
        delete[] ciChannelInformation;
    }
    if (stsResult != PCAN_ERROR_OK)
        ShowStatus(stsResult);

}

void GetPCAN_CHANNEL_CONDITION(TPCANHandle handle)
{
    UINT32 iChannelCondition;
    TPCANStatus stsResult = CAN_GetValue(handle, PCAN_CHANNEL_CONDITION, &iChannelCondition, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Get PCAN_CHANNEL_CONDITION: ");
        PCANDebugOutput(ConvertToChannelCondition(iChannelCondition));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void GetPCAN_CHANNEL_IDENTIFYING(TPCANHandle handle)
{
    UINT32 iChannelIdentifying;
    TPCANStatus stsResult = CAN_GetValue(handle, PCAN_CHANNEL_IDENTIFYING, &iChannelIdentifying, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Get PCAN_CHANNEL_IDENTIFYING: ");
        PCANDebugOutput(ConvertToParameterOnOff(iChannelIdentifying));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void SetPCAN_CHANNEL_IDENTIFYING(TPCANHandle handle, bool value)
{
    UINT32 ciChannelIdentifying;
    if (value)
        ciChannelIdentifying = PCAN_PARAMETER_ON;
    else
        ciChannelIdentifying = PCAN_PARAMETER_OFF;

    TPCANStatus stsResult = CAN_SetValue(handle, PCAN_CHANNEL_IDENTIFYING, &ciChannelIdentifying, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {

        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Set PCAN_CHANNEL_IDENTIFYING: ");
        PCANDebugOutput(ConvertToParameterOnOff(ciChannelIdentifying));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void GetPCAN_CHANNEL_FEATURES(TPCANHandle handle)
{
    UINT32 iChannelFeatures;
    TPCANStatus stsResult = CAN_GetValue(handle, PCAN_CHANNEL_FEATURES, &iChannelFeatures, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Get PCAN_CHANNEL_FEATURES: ");
        PCANDebugOutput(ConvertToChannelFeatures(iChannelFeatures));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void GetPCAN_BITRATE_ADAPTING(TPCANHandle handle)
{
    UINT32 iBitrateAdapting;
    TPCANStatus stsResult = CAN_GetValue(handle, PCAN_BITRATE_ADAPTING, &iBitrateAdapting, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Get PCAN_BITRATE_ADAPTING: ");
        PCANDebugOutput(ConvertToParameterOnOff(iBitrateAdapting));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void SetPCAN_BITRATE_ADAPTING(TPCANHandle handle, bool isFD, TPCANBaudrate bitrate, TPCANBitrateFD bitrateFD, bool value)
{
    UINT32 iBitrateAdapting;

    // Note: SetPCAN_BITRATE_ADAPTING requires an uninitialized channel, 
    //
    CAN_Uninitialize(PCAN_NONEBUS);

    if (value)
        iBitrateAdapting = PCAN_PARAMETER_ON;
    else
        iBitrateAdapting = PCAN_PARAMETER_OFF;

    TPCANStatus stsResult = CAN_SetValue(handle, PCAN_BITRATE_ADAPTING, &iBitrateAdapting, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Set PCAN_BITRATE_ADAPTING: ");
        PCANDebugOutput(ConvertToParameterOnOff(iBitrateAdapting));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);

    // Channel will be connected again
    if (isFD)
        stsResult = CAN_InitializeFD(handle, bitrateFD);
    else
        stsResult = CAN_Initialize(handle, bitrate);

    if (stsResult != PCAN_ERROR_OK)
    {
        std::cout << "Error while re-initializing the channel.\n";
        ShowStatus(stsResult);
    }
}

void GetPCAN_ALLOW_STATUS_FRAMES(TPCANHandle handle)
{
    UINT32 iAllowStatusFrames;
    TPCANStatus stsResult = CAN_GetValue(handle, PCAN_ALLOW_STATUS_FRAMES, &iAllowStatusFrames, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Get PCAN_ALLOW_STATUS_FRAMES: ");
        PCANDebugOutput(ConvertToParameterOnOff(iAllowStatusFrames));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void SetPCAN_ALLOW_STATUS_FRAMES(TPCANHandle handle, bool value)
{
    UINT32 iAllowStatusFrames;

    if (value)
        iAllowStatusFrames = PCAN_PARAMETER_ON;
    else
        iAllowStatusFrames = PCAN_PARAMETER_OFF;

    TPCANStatus stsResult = CAN_SetValue(handle, PCAN_ALLOW_STATUS_FRAMES, &iAllowStatusFrames, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Set PCAN_ALLOW_STATUS_FRAMES: ");
        PCANDebugOutput(ConvertToParameterOnOff(iAllowStatusFrames));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void GetPCAN_ALLOW_RTR_FRAMES(TPCANHandle handle)
{
    UINT32 iAllowRTRFrames;
    TPCANStatus stsResult = CAN_GetValue(handle, PCAN_ALLOW_RTR_FRAMES, &iAllowRTRFrames, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Get PCAN_ALLOW_RTR_FRAMES: ");
        PCANDebugOutput(ConvertToParameterOnOff(iAllowRTRFrames));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void SetPCAN_ALLOW_RTR_FRAMES(TPCANHandle handle, bool value)
{
    UINT32 iAllowRTRFrames;

    if (value)
        iAllowRTRFrames = PCAN_PARAMETER_ON;
    else
        iAllowRTRFrames = PCAN_PARAMETER_OFF;

    TPCANStatus stsResult = CAN_SetValue(handle, PCAN_ALLOW_RTR_FRAMES, &iAllowRTRFrames, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Set PCAN_ALLOW_RTR_FRAMES: ");
        PCANDebugOutput(ConvertToParameterOnOff(iAllowRTRFrames));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void GetPCAN_ALLOW_ERROR_FRAMES(TPCANHandle handle)
{
    UINT32 iAllowErrorFrames;
    TPCANStatus stsResult = CAN_GetValue(handle, PCAN_ALLOW_ERROR_FRAMES, &iAllowErrorFrames, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Get PCAN_ALLOW_ERROR_FRAMES: ");
        PCANDebugOutput(ConvertToParameterOnOff(iAllowErrorFrames));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void SetPCAN_ALLOW_ERROR_FRAMES(TPCANHandle handle, bool value)
{
    UINT32 iAllowErrorFrames;

    if (value)
        iAllowErrorFrames = PCAN_PARAMETER_ON;
    else
        iAllowErrorFrames = PCAN_PARAMETER_OFF;

    TPCANStatus stsResult = CAN_SetValue(handle, PCAN_ALLOW_ERROR_FRAMES, &iAllowErrorFrames, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Set PCAN_ALLOW_ERROR_FRAMES: ");
        PCANDebugOutput(ConvertToParameterOnOff(iAllowErrorFrames));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void GetPCAN_ALLOW_ECHO_FRAMES(TPCANHandle handle)
{
    UINT32 iAllowEchoFrames;
    TPCANStatus stsResult = CAN_GetValue(handle, PCAN_ALLOW_ECHO_FRAMES, &iAllowEchoFrames, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Get PCAN_ALLOW_ECHO_FRAMES: ");
        PCANDebugOutput(ConvertToParameterOnOff(iAllowEchoFrames));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void SetPCAN_ALLOW_ECHO_FRAMES(TPCANHandle handle, bool value)
{
    UINT32 iAllowEchoFrames;

    if (value)
        iAllowEchoFrames = PCAN_PARAMETER_ON;
    else
        iAllowEchoFrames = PCAN_PARAMETER_OFF;

    TPCANStatus stsResult = CAN_SetValue(handle, PCAN_ALLOW_ECHO_FRAMES, &iAllowEchoFrames, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Set PCAN_ALLOW_ECHO_FRAMES: ");
        PCANDebugOutput(ConvertToParameterOnOff(iAllowEchoFrames));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void GetPCAN_ACCEPTANCE_FILTER_11BIT(TPCANHandle handle)
{
    UINT64 iAcceptanceFilter11Bit;
    TPCANStatus stsResult = CAN_GetValue(handle, PCAN_ACCEPTANCE_FILTER_11BIT, &iAcceptanceFilter11Bit, sizeof(UINT64));

    if (stsResult == PCAN_ERROR_OK)
    {
        char result[MAX_PATH];
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        sprintf_s(result, sizeof(result), "%16llx", iAcceptanceFilter11Bit);
        PCANDebugOutput("Get PCAN_ACCEPTANCE_FILTER_11BIT: "); // << std::setfill('0') << std::setw(16) << std::hex << result << "h\n";
        PCANDebugOutput(result);
        PCANDebugOutput("h\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void SetPCAN_ACCEPTANCE_FILTER_11BIT(TPCANHandle handle, UINT64 iacceptancefilter11bit)
{
    TPCANStatus stsResult = CAN_SetValue(handle, PCAN_ACCEPTANCE_FILTER_11BIT, &iacceptancefilter11bit, sizeof(UINT64));

    if (stsResult == PCAN_ERROR_OK)
    {
        char result[MAX_PATH];
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        sprintf_s(result, sizeof(result), "%16llx", iacceptancefilter11bit);
        PCANDebugOutput("Set PCAN_ACCEPTANCE_FILTER_11BIT: ");
        PCANDebugOutput(result);
        PCANDebugOutput("h\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void GetPCAN_ACCEPTANCE_FILTER_29BIT(TPCANHandle handle)
{
    UINT64 iAcceptanceFilter29Bit;
    TPCANStatus stsResult = CAN_GetValue(handle, PCAN_ACCEPTANCE_FILTER_29BIT, &iAcceptanceFilter29Bit, sizeof(UINT64));

    if (stsResult == PCAN_ERROR_OK)
    {
        char result[MAX_PATH];
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        sprintf_s(result, sizeof(result), "%16llx", iAcceptanceFilter29Bit);
        PCANDebugOutput("Get PCAN_ACCEPTANCE_FILTER_29BIT: ");
        PCANDebugOutput(result);
        PCANDebugOutput("h\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void SetPCAN_ACCEPTANCE_FILTER_29BIT(TPCANHandle handle, UINT64 iacceptancefilter29bit)
{
    TPCANStatus stsResult = CAN_SetValue(handle, PCAN_ACCEPTANCE_FILTER_29BIT, &iacceptancefilter29bit, sizeof(UINT64));

    if (stsResult == PCAN_ERROR_OK)
    {
        char result[MAX_PATH];
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        sprintf_s(result, sizeof(result), "%16llx", iacceptancefilter29bit);
        PCANDebugOutput("Set PCAN_ACCEPTANCE_FILTER_29BIT: ");
        PCANDebugOutput(result);
        PCANDebugOutput("h\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void GetPCAN_MESSAGE_FILTER(TPCANHandle handle)
{
    UINT32 iMessageFilter;
    TPCANStatus stsResult = CAN_GetValue(handle, PCAN_MESSAGE_FILTER, &iMessageFilter, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Get PCAN_MESSAGE_FILTER: ");
        PCANDebugOutput(ConvertToFilterOpenCloseCustom(iMessageFilter));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}

void SetPCAN_MESSAGE_FILTER(TPCANHandle handle, UINT32 imessagefilter)
{
    TPCANStatus stsResult = CAN_SetValue(handle, PCAN_MESSAGE_FILTER, &imessagefilter, sizeof(UINT32));

    if (stsResult == PCAN_ERROR_OK)
    {
        PCANDebugOutput("-----------------------------------------------------------------------------------------\n");
        PCANDebugOutput("Set PCAN_MESSAGE_FILTER: ");
        PCANDebugOutput(ConvertToFilterOpenCloseCustom(imessagefilter));
        PCANDebugOutput("\n");
        PCANDebugOutput("\n");
    }
    else
        ShowStatus(stsResult);
}