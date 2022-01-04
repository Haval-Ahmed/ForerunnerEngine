//////////////////////////////////////////////////////////////////////////
/// @File:
///     FileUtilities.cpp
/// @Notes:
///     File Utilties for Forerunner Engine
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     See attached license 
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <cmath>

//////////////////////////////////////////////////////////////////////////
/// Windows Libraries
//////////////////////////////////////////////////////////////////////////
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "XInputController.h"

namespace ForerunnerEngine
{
    XInputController::XInputController()
		: leftThumbStickDeadzone(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		, rightThumbStickDeadzone(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		, triggerAnalogDeadzone(XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
    {
		// Indentify controller capabilities
		XINPUT_CAPABILITIES xinputCapabilities;

		// Clean them out
		ZeroMemory(&xinputCapabilities, sizeof(XINPUT_CAPABILITIES));

		// Check if a game pad is connected
		XInputGetCapabilities(0, XINPUT_FLAG_GAMEPAD, &xinputCapabilities);

		// Check the capabilities 
		if (xinputCapabilities.Type != XINPUT_DEVTYPE_GAMEPAD)
		{

		}

		switch (xinputCapabilities.SubType)
		{
			case XINPUT_DEVSUBTYPE_UNKNOWN:
				break;

			case XINPUT_DEVSUBTYPE_GAMEPAD:
				break;

			case XINPUT_DEVSUBTYPE_WHEEL:
				break;

			case XINPUT_DEVSUBTYPE_ARCADE_STICK:
				break;

			case XINPUT_DEVSUBTYPE_FLIGHT_STICK:
				break;

			case XINPUT_DEVSUBTYPE_DANCE_PAD:
				break;

			case XINPUT_DEVSUBTYPE_GUITAR:
			case XINPUT_DEVSUBTYPE_GUITAR_ALTERNATE:
			case XINPUT_DEVSUBTYPE_GUITAR_BASS:
				break;

			case XINPUT_DEVSUBTYPE_DRUM_KIT:
				break;

			case XINPUT_DEVSUBTYPE_ARCADE_PAD:
				break;

			default:
				break;
		}

		switch (xinputCapabilities.Flags)
		{
			// Device has an integrated voice device.
			case XINPUT_CAPS_VOICE_SUPPORTED:
				break;

			// Device supports force feedback functionality. 
			// Note that these force-feedback features beyond rumble 
			// are not currently supported through XINPUT on Windows.
			case XINPUT_CAPS_FFB_SUPPORTED:
				break;

				// Device is wireless.
			case XINPUT_CAPS_WIRELESS:
				break;

			// Device supports plug-in modules. 
			// Note that plug-in modules like the text input device (TID) 
			// are not supported currently through XINPUT on Windows.
			case XINPUT_CAPS_PMD_SUPPORTED:
				break;

			// Device lacks menu navigation buttons(START, BACK, DPAD).
			case XINPUT_CAPS_NO_NAVIGATION:
				break;

			default:
				break;
		}
    }

	XInputController::~XInputController()
	{

	}

	void XInputController::getControllerState(void)
	{
		// Iterator through max possible devices
		for (int i = 0; i < 4; i++)
		{
			// Clear controller state
			ZeroMemory(&xinputControllers[i], sizeof(XINPUT_STATE));

			// Get controller state
			XINPUT_STATE controllerState;
			DWORD deviceConnected = XInputGetState(i, &controllerState);

			// Ensure device is connected
			if (deviceConnected == ERROR_SUCCESS)
			{
				// Store state in member controllers array
				xinputControllers[i] = controllerState.Gamepad;
			}
			else
			{
				// Device not connected
			}
		}
	}
				
	void XInputController::setVibration(uint8_t leftMotorPercentage, uint8_t rightMotorPercentage)
	{
		/*
			wLeftMotorSpeed: Speed of the left motor. Valid values are in the range 0 to 65,535. Zero signifies no motor use; 65,535 signifies 100 percent motor use.
			wRightMotorSpeed: Speed of the right motor. Valid values are in the range 0 to 65,535. Zero signifies no motor use; 65,535 signifies 100 percent motor use.
			The left motor is the low-frequency rumble motor. The right motor is the high-frequency rumble motor. The two motors are not the same, and they create different vibration effects.
		*/
		// Create a vibration packet
		XINPUT_VIBRATION controllerVibration;

		// Clear packet
		ZeroMemory(&controllerVibration, sizeof(XINPUT_VIBRATION));

		// Set vibration values
		controllerVibration.wLeftMotorSpeed		= (leftMotorPercentage  * (65535) / (100));
		controllerVibration.wRightMotorSpeed	= (rightMotorPercentage * (65535) / (100));

		// Set controller state
		XInputSetState(0, &controllerVibration);
	}

	void ForerunnerEngine::XInputController::getLeftStickValue(void)
	{
		/*
			XINPUT_GAMEPAD_DPAD_UP 			0x0001
			XINPUT_GAMEPAD_DPAD_DOWN 		0x0002
			XINPUT_GAMEPAD_DPAD_LEFT 		0x0004
			XINPUT_GAMEPAD_DPAD_RIGHT 		0x0008
			XINPUT_GAMEPAD_START 			0x0010
			XINPUT_GAMEPAD_BACK 			0x0020
			XINPUT_GAMEPAD_LEFT_THUMB 		0x0040
			XINPUT_GAMEPAD_RIGHT_THUMB 		0x0080
			XINPUT_GAMEPAD_LEFT_SHOULDER 	0x0100
			XINPUT_GAMEPAD_RIGHT_SHOULDER 	0x0200
			XINPUT_GAMEPAD_A 				0x1000
			XINPUT_GAMEPAD_B 				0x2000
			XINPUT_GAMEPAD_X 				0x4000
			XINPUT_GAMEPAD_Y 				0x8000

			bLeftTrigger:	The current value of the left trigger analog control. The value is between 0 and 255.
			bRightTrigger:	The current value of the right trigger analog control. The value is between 0 and 255.

			sThumbLX: Left thumbstick x-axis value. Each of the thumbstick axis members is a signed value between -32768 and 32767 describing the position of the thumbstick. A value of 0 is centered. Negative values signify down or to the left. Positive values signify up or to the right. The constants XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE or XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE can be used as a positive and negative value to filter a thumbstick input.
			sThumbLY: Left thumbstick y-axis value. The value is between -32768 and 32767.
			sThumbRX: Right thumbstick x-axis value. The value is between -32768 and 32767.
			sThumbRY: Right thumbstick y-axis value. The value is between -32768 and 32767.

			*/
		// Iterator through max possible devices
		for (int i = 0; i < 4; i++)
		{
			float leftStickX = xinputControllers[i].sThumbLX;
			float leftStickY = xinputControllers[i].sThumbLY;


			// Determine how far the controller is pushed
			float magnitude = sqrt(leftStickX * leftStickX + leftStickY * leftStickY);

			// Determine the direction the controller is pushed
			float normalizedLX = leftStickX / magnitude;
			float normalizedLY = leftStickY / magnitude;

			float normalizedMagnitude = 0;

			//check if the controller is outside a circular dead zone
			if (magnitude > leftThumbStickDeadzone)
			{
				// clip the magnitude at its expected maximum value
				if (magnitude > 32767) 
					magnitude = 32767;

				//adjust magnitude relative to the end of the dead zone
				magnitude -= leftThumbStickDeadzone;

				//optionally normalize the magnitude with respect to its expected range
				//giving a magnitude value of 0.0 to 1.0
				normalizedMagnitude = magnitude / (32767 - leftThumbStickDeadzone);
			}
			else //if the controller is in the deadzone zero out the magnitude
			{
				magnitude = 0.0;
				normalizedMagnitude = 0.0;
			}
		}
	}

	void ForerunnerEngine::XInputController::getRightStickValue(void)
	{

	}

	void XInputController::getBatteryConnectionType(void)
	{
		/*
		BatteryType
			BATTERY_TYPE_DISCONNECTED 	The device is not connected.
			BATTERY_TYPE_WIRED 	The device is a wired device and does not have a battery.
			BATTERY_TYPE_ALKALINE 	The device has an alkaline battery.
			BATTERY_TYPE_NIMH 	The device has a nickel metal hydride battery.
			BATTERY_TYPE_UNKNOWN 	The device has an unknown battery type.
		*/

		XINPUT_BATTERY_INFORMATION bInformation;
		//auto res =  XInputGetBatteryInformation(0, BATTERY_DEVTYPE_GAMEPAD, &XInputGetBatteryInformation);

		// if res == ERROR_SUCCESS


	}

	void XInputController::getBatteryLevel(void)
	{
		/*
		BatteryLevel
			BATTERY_LEVEL_EMPTY
			BATTERY_LEVEL_LOW
			BATTERY_LEVEL_MEDIUM
			BATTERY_LEVEL_FULL
		*/

		XINPUT_BATTERY_INFORMATION bInformation;
		//auto res =  XInputGetBatteryInformation(0, BATTERY_DEVTYPE_GAMEPAD, &XInputGetBatteryInformation);

		// if res == ERROR_SUCCESS
	}
}


/*
DWORD XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeystroke)
XINPUT_KEYSTROKE keyStroke

VirtualKey: Virtual-key code of the key, button, or stick movement. See XInput.h for a list of valid virtual-key (VK_xxx) codes. Also, see Remarks.
Unicode: This member is unused and the value is zero.

Flags: Flags that indicate the keyboard state at the time of the input event. This member can be any combination of the following flags:

XINPUT_KEYSTROKE_KEYDOWN 	The key was pressed.
XINPUT_KEYSTROKE_KEYUP 	The key was released.
XINPUT_KEYSTROKE_REPEAT 	A repeat of a held key.

UserIndex: Index of the signed-in gamer associated with the device. Can be a value in the range 0�3.

HidCode: HID code corresponding to the input. If there is no corresponding HID code, this value is zero.

VK_PAD_A 	A button
VK_PAD_B 	B button
VK_PAD_X 	X button
VK_PAD_Y 	Y button
VK_PAD_RSHOULDER 	Right shoulder button
VK_PAD_LSHOULDER 	Left shoulder button
VK_PAD_LTRIGGER 	Left trigger
VK_PAD_RTRIGGER 	Right trigger
VK_PAD_DPAD_UP 	Directional pad up
VK_PAD_DPAD_DOWN 	Directional pad down
VK_PAD_DPAD_LEFT 	Directional pad left
VK_PAD_DPAD_RIGHT 	Directional pad right
VK_PAD_START 	START button
VK_PAD_BACK 	BACK button
VK_PAD_LTHUMB_PRESS 	Left thumbstick click
VK_PAD_RTHUMB_PRESS 	Right thumbstick click
VK_PAD_LTHUMB_UP 	Left thumbstick up
VK_PAD_LTHUMB_DOWN 	Left thumbstick down
VK_PAD_LTHUMB_RIGHT 	Left thumbstick right
VK_PAD_LTHUMB_LEFT 	Left thumbstick left
VK_PAD_LTHUMB_UPLEFT 	Left thumbstick up and left
VK_PAD_LTHUMB_UPRIGHT 	Left thumbstick up and right
VK_PAD_LTHUMB_DOWNRIGHT 	Left thumbstick down and right
VK_PAD_LTHUMB_DOWNLEFT 	Left thumbstick down and left
VK_PAD_RTHUMB_UP 	Right thumbstick up
VK_PAD_RTHUMB_DOWN 	Right thumbstick down
VK_PAD_RTHUMB_RIGHT 	Right thumbstick right
VK_PAD_RTHUMB_LEFT 	Right thumbstick left
VK_PAD_RTHUMB_UPLEFT 	Right thumbstick up and left
VK_PAD_RTHUMB_UPRIGHT 	Right thumbstick up and right
VK_PAD_RTHUMB_DOWNRIGHT 	Right thumbstick down and right
VK_PAD_RTHUMB_DOWNLEFT 	Right thumbstick down and left
*/