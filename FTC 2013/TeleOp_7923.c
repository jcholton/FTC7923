#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     controllers,    sensorI2CMuxController)
#pragma config(Sensor, S2,     light,          sensorCOLORNONE)
#pragma config(Sensor, S3,     irSeek,         sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     ultrasonicSensor, sensorSONAR)
#pragma config(Motor,  motorA,          flickMotor1,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          flickMotor2,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     right,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     left,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     hangMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     empty1,        tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     armMotor,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     flagRaiser,    tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    releaseServo,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    pinServo,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    blockServo,           tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    trayR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    trayL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    flagServo,            tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// THIS IS THE NEWEST VERSION OF THIS PROGRAM
// Configuration:
// Flicky motors go into A and B ports on the NXT,
// The right and left motors are on the first controller, m1 is right and m2 i left.
// On the second controller, there is the hanging motor and then an empty motor.
// Controller 3 has m1 as the armMotor and m2 as the flagRaiser
// The servo controller:
// 1 is the release block servo
// 2 is the servo for the pins (not needed on new robot)
// 3 is empty
// 4 is the right tray servo
// 5 is the left tray servo
// 6 is the servo for the flag (which is also no longer needed)

// Sensor config:
// 1 is the controllers
// 2 is the touch sensor for the hanging mechanism. (or the light thingy)
// 3 is the infrared seeker
// 4 is the ultrasonic sensor.




#include "JoystickDriver.c"

bool useTemplate = true;

int minVal = 5;
void updateJoysticks(bool drive)
{

		// For controlling drive
		if(drive)
		{
			if((abs(joystick.joy1_y1) + abs(joystick.joy1_y2)) > minVal)
			{
				motor[right] = joystick.joy1_y1 * -1;

				motor[left] = joystick.joy1_y2;
			}
			else
			{
				motor[right] = 0;
				motor[left] = 0;
			}
		}
		else
		{
			if(abs(joystick.joy1_y1) + abs(joystick.joy1_y2) > minVal)
			{
				motor[right] = joystick.joy1_y2;
				motor[left] = joystick.joy1_y1 * -1;
			}
			else
			{
				motor[right] = 0;
				motor[left] = 0;
			}
		}
}



task main()
{

	SensorType[light] = sensorCOLORRED;

	// Drive is the drive mode, forward or backward
	int initFlagServo = 150;
	bool drive = true;
	int trayPosition = 100;
	int flickMotorOn = 0;
	servo[blockServo] = 0;
	servo[flagServo] = initFlagServo;

	if(useTemplate)
	{
		waitForStart();   // wait for start of tele-op phase
	}
	SensorType[light] = sensorCOLORGREEN;








	// Run until the pigs fly home...
	while(true)
	{
		getJoystickSettings(joystick);


		updateJoysticks(drive);

		// Flip the drive if the START button is pressed
		if(joy1Btn(10) == 1)
		{
			drive = !drive;
			wait1Msec(500);
		}


		// 02
		if(joy1Btn(03) == 0)
			servo[releaseServo] = 140;
		else
			servo[releaseServo] = 0;




		// For controlling the hanging motor power
		int hangPower = 0;
		if(joystick.joy1_TopHat == 0)
		{
			hangPower = -100;
		}
		if(joystick.joy1_TopHat == 4)
		{
			hangPower = 100;
		}
		motor[hangMotor] = hangPower;




		// For controlling the main arm motor power (this is very importanto!)
		// Make sure that the power is (somewhat) low
		int power = 0;
		if(joy1Btn(05) == 1)
			power = 100;
		if(joy1Btn(06) == 1)
			power = -100;
		motor[armMotor] = power;






		// 4 is 3 (3 in controller thingy)
		// For the flag raiser
		int flagPower = 0;
		if(joy1Btn(04) == 1)
		{
			// 30
			flagPower = -100;
		}
		else
		{
			flagPower = 0;
		}
		motor[flagRaiser] = flagPower;








		// Flicky motor
		if(joy1Btn(01) == 1)
		{
			if(flickMotorOn == 1) flickMotorOn = 0;
			else flickMotorOn = 1;

			motor[flickMotor1] = 100;
			motor[flickMotor2] = 100;
			// Improve this because it sucks
			wait1Msec(200);
		}
		if(joy1Btn(02) == 1)
		{
			if(flickMotorOn == -1) flickMotorOn = 0;
			else flickMotorOn = -1;
			motor[flickMotor1] = -100;
			motor[flickMotor2] = -100;
			wait1Msec(200);
		}

		if(flickMotorOn == 1)
		{
			motor[flickMotor1] = 100;
			motor[flickMotor2] = 100;
		}
		else if(flickMotorOn == 0)
		{
			motor[flickMotor1] = 0;
			motor[flickMotor2] = 0;
		}
		else
		{
			motor[flickMotor1] = -100;
			motor[flickMotor2] = -100;
		}






		// 	For arm plate control servos.
		// 6 and 7 on controller
		if(joy1Btn(07) == 1)
		{

			if(trayPosition < 255 && (abs(ServoValue[trayR] - trayPosition) < 5))
			{
				trayPosition++;
				wait1Msec(3);
			}
		}
		if(joy1Btn(08) == 1)
		{
			if(trayPosition > 0 && (abs(ServoValue[trayR] - trayPosition) < 5))
			{
				trayPosition--;
				wait1Msec(3);
			}
		}
		servo[trayR] = trayPosition;
		servo[trayL] = 255 - trayPosition;
	}
}