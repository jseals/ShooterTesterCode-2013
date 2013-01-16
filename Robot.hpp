/*
 * @file Robot.h
 * 
 * @brief The main robot files. This model uses RobotBase directly to avoid Command-based Robot stupidity
 * 
 */
#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "RobotBase.h"
#include "Joystick.h"
#include "Timer.h"
#include "CANJaguar.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"

#include "Gamepad.hpp"	

namespace nr
{
	namespace main
	{
	
	/*
	 * @class Robot
	 */
	
		typedef enum jag_state
		{
			JSM_OFF_STATE,
			JSM_FFW_STATE,
			JSM_REV_STATE,
			JSM_INC_STATE,
			JSM_DEC_STATE
		} Motor_State;
		
		class Robot : public RobotBase
		{
		public:		
			Gamepad pad;
			
			CANJaguar jag;
			
			/*
			 * @details Robot() is the constructor for this class 
			 */
			Robot();
			
			
			Motor_State state;
			
			Motor_State GetMotorState();
			
			void ResetMotorState();
	
			/*
			 * @details The functions that would normally be automated for us. I decided to spice things up and implement my own
			 */
			void Autonomous();
			void OperatorControl();

			/*
			 * @details The StartCompetition() function will run autonomous and teleop when required
			 */
			void StartCompetition();

			/*
			 * @brief The drive function that takes in joystick positions
			 * @param driveX The X axis of the joystick
			 * @param driveY The Y axis of the joystick
			 * @param driveZ The Z axis of the joystick
			 */
			
			void Drive( float magn, float dir, float rot);
			void GamepadDrive( float driveX, float driveY, float driveZ );
		private:	
			static const double threshold = 0.0;
			float snap_value( float snapVal, float threshold, float actualVal );
			
			LiveWindow* lw;
		};
	}	
}
#endif
