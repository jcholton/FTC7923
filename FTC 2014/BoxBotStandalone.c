#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     touchmux1,      sensorHiTechnicTouchMux)
#pragma config(Motor,  mtr_S1_C1_1,     l1,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     l2,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     r1,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     r2,            tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

//Bit map definitions
#define mux_button1 0x01
#define mux_button2 0x02
#define mux_button3 0x04
#define mux_button4 0x08

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  initializeRobot();

  //waitForStart();   // wait for start of tele-op phase

  while (true)
	{
		getJoystickSettings(joystick);


		int left = 0;
		int right = 0;

		if(SensorValue(touchmux1) & mux_button1)
		{
			left = -100;
		}
		else if(SensorValue(touchmux1) & mux_button2)
		{
			left = 100;
		}
		else
		{
			left = 0;
		}


		if(SensorValue(touchmux1) & mux_button3)
		{
			right = -100;
		}
		else if(SensorValue(touchmux1) & mux_button4)
		{
			right = 100;
		}
		else
		{
			right = 0;
		}


		left = joystick.joy1_y1;
		right = joystick.joy1_y2;

		if(abs(left) < 10) left = 0;
		if(abs(right) < 10) right = 0;

		motor[l1] = left;
		motor[l2] = left;
		motor[r1] = right;
		motor[r2] = right;

	  wait1Msec(50);
  }
}
