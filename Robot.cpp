/*
 * @file Robot.cpp
 */

#include "Robot.hpp"

using namespace nr::main;

/*
 * This define is usually off since we do not have an encoder on the shaft
 * Uncomment if we do have encoder
 * If uncommented, the speed from the Jaguar will be retrieved directly
 * Now, it is getting the last value from the user (the "outputValue" as called in WPI)
 */

//#define WITH_ENCODER


float Robot::snap_value(float snapVal, float threshold, float actualVal )
{
	// If the joystick axis is greater than 0 minus the threshold
	float final = (( actualVal > (snapVal - threshold) )
			
	&& 
	
	// and if the joystick axis is less than 0 plus the threshold
	( actualVal < (snapVal + threshold) ))  
	
	?
	
	// make it equal 0 
	snapVal 
	:
	// Else, make it equal the joystick axis
	actualVal;	
	
	return final;
}

/*
 * @brief The Robot constructor
 * @param pad The gamepad we are using in place of joysticks
 */
Robot::Robot() : 	pad(1),
					jag(1)
{
	ResetMotorState();
	SmartDashboard::init();
	lw = LiveWindow::GetInstance();
	lw->AddActuator("Shoot", "Motor", &jag);
}

Motor_State Robot::GetMotorState()
{
	return state;
}

void Robot::ResetMotorState()
{
	state = JSM_OFF_STATE;
}

void Robot::Drive(float magn, float dir, float rot)
{
	// invert the y axis
	dir *= -1;
	
	// motor enum
	typedef enum
	{
		frontLeftMot = 0,
		frontRightMot = 1,
		rearLeftMot = 2,
		rearRightMot = 3
	} MotorType;
	
	// Maximum motors
	static const INT32 maxMots = 4;
	
	// wheel speeds array 
	double _wheelSpeeds[maxMots];
	
	// Calculate wheel speeds of each motor based on x, y, and z axes 
	_wheelSpeeds[frontLeftMot] = magn + dir + rot;
	_wheelSpeeds[frontRightMot] = -magn + dir - rot;
	_wheelSpeeds[rearLeftMot] = -magn + dir + rot;
	_wheelSpeeds[rearRightMot] = magn + dir - rot;
	
	// A Sync Group for the Jaguar Set() function
	UINT8 syncG = 0;
	
	// Set the speed for each motor based on calculations above
	jag.Set (_wheelSpeeds[frontLeftMot], syncG);
}


void Robot::GamepadDrive(float driveX, float driveY, float driveZ)
{
	if( snap_value(0.0, threshold, driveX) != 0 ||
		snap_value(0.0, threshold, driveY) != 0 ||
		snap_value(0.0, threshold, driveZ) != 0)
	{
		Drive(	snap_value(0.0, threshold, driveX),
				snap_value(0.0, threshold, driveY),
				snap_value(0.0, threshold, driveZ)
					);	
	}
}

/*
 * @brief The joystick driving goes here
 */

void Robot::OperatorControl() 
{	
	GetWatchdog().SetEnabled(false);
	
	while( IsOperatorControl() ) 
	{
		// The shooter button state machine
		switch(state)
		{
		case JSM_OFF_STATE:
			if( pad.GetButton(pad.kYButton) )
			{
				jag.Set(0.50);
				state = JSM_FFW_STATE;
			}
			
			else if ( pad.GetButton(pad.kAButton) )
			{
				jag.Set(-0.5);
				state = JSM_REV_STATE;
			}
			
			else if ( pad.GetButton(pad.kLeftBumper) )
			{
#ifdef WITH_ENCODER
				float curr = jag.GetSpeed();
#else
				float curr = jag.Get();
#endif
				float wanted = curr + 0.10;
				jag.Set(wanted);
				state = JSM_INC_STATE;
			}
			
			else if ( pad.GetButton(pad.kRightBumper) )
			{
#ifdef WITH_ENCODER
				float curr = jag.GetSpeed();
#else
				float curr = jag.Get();
#endif
				float wanted = curr - 0.10;
				jag.Set(wanted);
				state = JSM_DEC_STATE;
			}
			
			break;
		
		case JSM_FFW_STATE:
			if(!pad.GetButton(pad.kLeftBumper))
				kLeftBumperIncrementSpeed = 0;
			if( pad.GetButton(pad.kAButton) )
			{
				jag.Set(-0.5);
				state = JSM_REV_STATE;
			}
			
			else if( pad.GetButton(pad.kBButton) )
			{
				jag.Set(0.0);
				state = JSM_OFF_STATE;
			}
			
			else if ( pad.GetButton(pad.kLeftBumper) )
			{			
#ifdef WITH_ENCODER
				float curr = jag.GetSpeed();
#else
				float curr = jag.Get();
#endif
				float wanted = curr + 0.10;
				jag.Set(wanted);
				state = JSM_INC_STATE;
			}
			
			else if ( pad.GetButton(pad.kRightBumper) )
			{
#ifdef WITH_ENCODER
				float curr = jag.GetSpeed();
#else
				float curr = jag.Get();
#endif
				float wanted = curr - 0.10;
				jag.Set(wanted);
				state = JSM_DEC_STATE;
			}
			
			break;
			
		case JSM_REV_STATE:
			if( pad.GetButton(pad.kYButton) )
			{
				jag.Set(0.50);
				state = JSM_FFW_STATE;
			}
			
			else if( pad.GetButton(pad.kBButton) )
			{
				jag.Set(0.0);
				state = JSM_OFF_STATE;
			}
			
			else if ( pad.GetButton(pad.kLeftBumper) )
			{
#ifdef WITH_ENCODER
				float curr = jag.GetSpeed();
#else
				float curr = jag.Get();
#endif
				float wanted = curr + 0.10;
				jag.Set(wanted);
				state = JSM_INC_STATE;
			}
			
			else if ( pad.GetButton(pad.kRightBumper) )
			{
#ifdef WITH_ENCODER
				float curr = jag.GetSpeed();
#else
				float curr = jag.Get();
#endif
				float wanted = curr - 0.10;
				jag.Set(wanted);
				state = JSM_DEC_STATE;
			}
			
			break;
		
		case JSM_INC_STATE:
			if ( pad.GetButton(pad.kRightBumper) )
			{
#ifdef WITH_ENCODER
				float curr = jag.GetSpeed();
#else
				float curr = jag.Get();
#endif
				float wanted = curr - 0.10;
				jag.Set(wanted);
				state = JSM_DEC_STATE;
			}
			//NEW STUFF 11/15
			//Catches the left bumper press to increase the speed by 0.1, then remains in the INC state
			else if(pad.GetButton(pad.kLeftBumper))
			{
#ifdef WITH_ENCODER
				float curr = jag.GetSpeed();
#else
				float curr = jag.Get();
				float wanted = curr + .10;
				jag.set(wanted);
			}
			
			else if( pad.GetButton(pad.kLeftBumper) )
			{
#ifdef WITH_ENCODER
				float curr = jag.GetSpeed();
#else
				float curr = jag.Get();
#endif
				float wanted = curr + 0.10;
				jag.Set(wanted);
				state = JSM_INC_STATE;
			}
			
			else if( pad.GetButton(pad.kYButton) )
			{
				jag.Set(0.50);
				state = JSM_FFW_STATE;
			}
			
			else if( pad.GetButton(pad.kBButton) )
			{
				jag.Set(0.0);
				state = JSM_OFF_STATE;
			}
			
			else if( pad.GetButton(pad.kAButton) )
			{
				jag.Set(-0.50);
				state = JSM_REV_STATE;
			}
			
			break;
			
		case JSM_DEC_STATE:
			if ( pad.GetButton(pad.kLeftBumper) )
			{
#ifdef WITH_ENCODER
				float curr = jag.GetSpeed();
#else
				float curr = jag.Get();
#endif
				float wanted = curr + 0.10;
				jag.Set(wanted);
				state = JSM_INC_STATE;
			}
			
<<<<<<< HEAD
			//NEW STUFF
			//Catches the right bumper press to decrease the speed by 0.1, then stays in the same DEC state
			else if ( pad.GetButton(pad.kRightBumper) )
=======
			else if( pad.GetButton(pad.kRightBumper) )
>>>>>>> 994500dcb3d7142b3379aa2efee83eaf47b8ff53
			{
#ifdef WITH_ENCODER
				float curr = jag.GetSpeed();
#else
				float curr = jag.Get();
#endif
				float wanted = curr - 0.10;
				jag.Set(wanted);
<<<<<<< HEAD
			}
=======
				state = JSM_DEC_STATE;
			}
			
>>>>>>> 994500dcb3d7142b3379aa2efee83eaf47b8ff53
			else if( pad.GetButton(pad.kYButton) )
			{
				jag.Set(0.50);
				state = JSM_FFW_STATE;
			}
			
			else if( pad.GetButton(pad.kBButton) )
			{
				jag.Set(0.0);
				state = JSM_OFF_STATE;
			}
			
			else if( pad.GetButton(pad.kAButton) )
			{
				jag.Set(-0.50);
				state = JSM_REV_STATE;
			}
			
			break;
		}
	}
}

/*
 * @brief Run everything here in loops
 */
void Robot::StartCompetition() 
{
	OperatorControl();
}

START_ROBOT_CLASS(Robot);
