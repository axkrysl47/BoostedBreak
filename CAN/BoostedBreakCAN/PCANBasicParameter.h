/***
 *  BoostedBreak - BoostedBreakCAN Program
 *
 *  PCANBasicParameter.h
 *
 *  Author: Alexander Krysl (axkrysl47)
 *  Date:   2022/04/03
 **/

#pragma once
#include "stdafx.h"
#include "PCANBasic.h"
#include "PCANBasicUtility.h"

#ifndef __PCANBASICPARAMETERH__
#define __PCANBASICPARAMETERH__

/// <summary>
/// Shows device identifier parameter
/// </summary>
void GetPCAN_DEVICE_ID(TPCANHandle handle);

/// <summary>
/// Sets device identifier parameter
/// </summary>
/// <param name="iDeviceID"></param>
void SetPCAN_DEVICE_ID(TPCANHandle handle, UINT32 iDeviceID);

/// <summary>
/// Shows all information about attached channels
/// </summary>
void GetPCAN_ATTACHED_CHANNELS(bool isFD);

/// <summary>
/// Shows the status of selected PCAN-Channel
/// </summary>
void GetPCAN_CHANNEL_CONDITION(TPCANHandle handle);

/// <summary>
///  Shows the status from the status LED of the USB devices
/// </summary>
void GetPCAN_CHANNEL_IDENTIFYING(TPCANHandle handle);

/// <summary>
/// De/Activates the status LED of the USB devices
/// </summary>
/// <param name="value">True to turn on; False to turn off</param>
void SetPCAN_CHANNEL_IDENTIFYING(TPCANHandle handle, bool value);

/// <summary>
/// Shows information about features
/// </summary>
void GetPCAN_CHANNEL_FEATURES(TPCANHandle handle);

/// <summary>
/// Shows the status from Bitrate-Adapting mode
/// </summary>
void GetPCAN_BITRATE_ADAPTING(TPCANHandle handle);

/// <summary>
/// De/Activates the Bitrate-Adapting mode
/// </summary>
/// <param name="value">True to turn on; False to turn off</param>
void SetPCAN_BITRATE_ADAPTING(TPCANHandle handle, bool isFD, TPCANBaudrate bitrate, TPCANBitrateFD bitrateFD, bool value);

/// <summary>
/// Shows the status from the reception of status frames
/// </summary>
void GetPCAN_ALLOW_STATUS_FRAMES(TPCANHandle handle);

/// <summary>
/// De/Activates the reception of status frames
/// </summary>
/// <param name="value">True to turn on; False to turn off</param>
void SetPCAN_ALLOW_STATUS_FRAMES(TPCANHandle handle, bool value);

/// <summary>
/// Shows the status from the reception of RTR frames
/// </summary>
void GetPCAN_ALLOW_RTR_FRAMES(TPCANHandle handle);

/// <summary>
/// De/Activates the reception of RTR frames
/// </summary>
/// <param name="value">True to turn on; False to turn off</param>
void SetPCAN_ALLOW_RTR_FRAMES(TPCANHandle handle, bool value);

/// <summary>
/// Shows the status from the reception of CAN error frames
/// </summary>
void GetPCAN_ALLOW_ERROR_FRAMES(TPCANHandle handle);

/// <summary>
/// De/Activates the reception of CAN error frames
/// </summary>
/// <param name="value">True to turn on; False to turn off</param>
void SetPCAN_ALLOW_ERROR_FRAMES(TPCANHandle handle, bool value);

/// <summary>
/// Shows the status from the reception of Echo frames
/// </summary>
void GetPCAN_ALLOW_ECHO_FRAMES(TPCANHandle handle);

/// <summary>
/// De/Activates the reception of Echo frames
/// </summary>
/// <param name="value">True to turn on; False to turn off</param>
void SetPCAN_ALLOW_ECHO_FRAMES(TPCANHandle handle, bool value);

/// <summary>
/// Shows the reception filter with a specific 11-bit acceptance code and mask
/// </summary>
void GetPCAN_ACCEPTANCE_FILTER_11BIT(TPCANHandle handle);

/// <summary>
/// Sets the reception filter with a specific 11-bit acceptance code and mask
/// </summary>
/// <param name="iacceptancefilter11bit">Acceptance code and mask</param>
void SetPCAN_ACCEPTANCE_FILTER_11BIT(TPCANHandle handle, UINT64 iacceptancefilter11bit);

/// <summary>
/// Shows the reception filter with a specific 29-bit acceptance code and mask
/// </summary>
void GetPCAN_ACCEPTANCE_FILTER_29BIT(TPCANHandle handle);

/// <summary>
/// Sets the reception filter with a specific 29-bit acceptance code and mask
/// </summary>
/// <param name="iacceptancefilter29bit">Acceptance code and mask</param>
void SetPCAN_ACCEPTANCE_FILTER_29BIT(TPCANHandle handle, UINT64 iacceptancefilter29bit);

/// <summary>
/// Shows the status of the reception filter
/// </summary>
void GetPCAN_MESSAGE_FILTER(TPCANHandle handle);

/// <summary>
/// De/Activates the reception filter
/// </summary>
/// <param name="imessagefilter">Configure reception filter</param>
void SetPCAN_MESSAGE_FILTER(TPCANHandle handle, UINT32 imessagefilter);

#endif
