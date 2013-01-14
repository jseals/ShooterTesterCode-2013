/*
 * @file Gamepad.hpp
 * 
 * @brief A wrapper class for the Logitech F310 game controller
 */

#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP

#include "Joystick.h"

class Gamepad : public Joystick
{
public:
	
	// Enums for the axes, sticks, and buttons
	typedef enum
	{
		kLeftStick,
		kRightStick,
	} StickType;
	
	typedef enum
	{
		kLeftXAxis,
		kLeftYAxis,
		kRightXAxis,
		kRightYAxis,
	} AxisType;
	
	typedef enum
	{
		kXButton,
		kAButton,
		kBButton,
		kYButton,
		kLeftBumper,
		kRightBumper,
		kLeftTrigger,
		kRightTrigger,
		kBackButton,
		kStartButton,
		kLeftStickButton,
		kRightStickButton,
	} ButtonType;
	
	Gamepad(UINT32 port) : Joystick(port) {}
	virtual ~Gamepad() {};
	
	float GetX(StickType stick)
	{
		switch(stick)
		{
		case kRightStick:
			return GetRawAxis(kRightXAxisNum);
		case kLeftStick:
			return GetRawAxis(kLeftXAxisNum);
		default:
			return 0.0;
		}
	}
	
	float GetY(StickType stick)
	{
		switch(stick)
		{
		case kRightStick:
			return GetRawAxis(kRightYAxisNum);
		case kLeftStick:
			return GetRawAxis(kLeftYAxisNum);
		default:
			return 0.0;
		}
	}
	
	float GetAxis(AxisType axis)
	{
		switch(axis)
		{
		    case kLeftXAxis: return GetX(kLeftStick);
		    case kLeftYAxis: return GetY(kLeftStick);
		    case kRightXAxis: return GetX(kRightStick);
		    case kRightYAxis: return GetY(kRightStick);
		    default: return 0.0;
		}
	}
	
	float GetDPadX(void)
	{
		return GetRawAxis(kDPadXAxisNum);
	}
	
	float GetDPadY(void)
	{
		return GetRawAxis(kDPadYAxisNum);
	}
	
	bool GetButton(ButtonType button)
	{
		switch(button)
		{
		case kXButton:
			return GetRawButton(kXButtonNum);
		case kAButton:
			return GetRawButton(kAButtonNum);
		case kBButton:
			return GetRawButton(kBButtonNum);
		case kYButton:
			return GetRawButton(kYButtonNum);
		case kLeftBumper:
			return GetRawButton(kLeftBumperNum);
		case kRightBumper:
			return GetRawButton(kRightBumperNum);
		case kLeftTrigger:
			return GetRawButton(kLeftTriggerNum);
		case kRightTrigger:
			return GetRawButton(kRightTriggerNum);
		case kBackButton:
			return GetRawButton(kBackButtonNum);
		case kStartButton:
			return GetRawButton(kStartButtonNum);
		case kLeftStickButton:
			return GetRawButton(kLeftStickButtonNum);
		case kRightStickButton:
			return GetRawButton(kRightStickButtonNum);
		default:
			return false;
		}
	}
	
private:
	
	// Button definitions
	static const UINT32 kLeftXAxisNum = 1;
	static const UINT32 kLeftYAxisNum = 2;
	static const UINT32 kRightXAxisNum = 3;
	static const UINT32 kRightYAxisNum = 4;
	static const UINT32 kDPadXAxisNum = 5;
	static const UINT32 kDPadYAxisNum = 6;
	
	static const UINT32 kXButtonNum = 1;
	static const UINT32 kAButtonNum = 2;
	static const UINT32 kBButtonNum = 3;
	static const UINT32 kYButtonNum = 4;
	static const UINT32 kLeftBumperNum = 5;
	static const UINT32 kRightBumperNum = 6;
	static const UINT32 kLeftTriggerNum = 7;
	static const UINT32 kRightTriggerNum = 8;
	static const UINT32 kBackButtonNum = 9;
	static const UINT32 kStartButtonNum = 10;
	static const UINT32 kLeftStickButtonNum = 11;
	static const UINT32 kRightStickButtonNum = 12;
};

#endif
