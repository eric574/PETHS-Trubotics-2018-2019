#pragma config(Motor,  port2,           DriveLeft1,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           DriveLeft2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           DriveRight1,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           DriveRight2,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           Claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           Shooter,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Intake1,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           Intake2,       tmotorVex393_MC29, openLoop)

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//



/*---------------------------------------------------------------------------*/

/*                                                                        */

/*      Description: Competition template for VEX EDR                   */

/*                                                                        */

/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform

#pragma platform(VEX2)

// Select Download method as "competition"

#pragma competitionControl(Competition)

//Main competition background code...do not modify!

#include "Vex_Competition_Includes.c"

#define min(a, b) (a) < (b) ? (a) : (b)

#define max(a, b) (a) < (b) ? (b) : (a)



// Global variables

const int dev = -10; // Global deviation

int con = -1; // Conventional direction

bool stop_intake; // For stopping ball-intake

bool flags; // For when we're on the flags side during autonomous

bool red; // For when we're on the red side during autonomous



/*---------------------------------------------------------------------------*/

/*                        Pre-Autonomous Functions                      */

/*                                                                        */

/*  You may want to perform some actions before the competition starts.   */

/*  Do them in the following function.  You must return from this function   */

/*  or the autonomous and usercontrol tasks will not be started.  This    */

/*  function is only called once after the cortex has been powered on and */

/*  not every time that the robot is disabled.                            */

/*---------------------------------------------------------------------------*/

void pre_auton () {

	// Set bStopTasksBetweenModes to false if you want to keep user created tasks

	// running between Autonomous and Driver controlled modes. You will need to

	// manage all user created tasks if set to false.

	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD

	// used by the competition include file, for example, you might want

	// to display your team name on the LCD in this function.

	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts

	// Example: clearing encoders, setting servo positions, ...

	return;

}



// Global helper functions



// Drive forward

void DriveF (int amount, int time) {

	int tmp = amount;

	motor[DriveLeft1] = tmp * -con;

	motor[DriveRight1] = tmp * -con - dev;

	motor[DriveRight2] = tmp * -con - dev;

	motor[DriveLeft2] = tmp * -con;

	if (time != 0) wait1Msec(time);

}



// Drive backwards

void DriveB (int amount, int time) {

	int tmp = -amount;

	motor[DriveLeft1] = tmp * -con;

	motor[DriveRight1] = tmp * -con - dev;

	motor[DriveRight2] = tmp * -con - dev;

	motor[DriveLeft2] = tmp * -con;

	if (time != 0) wait1Msec(time);

}



// Turn right

void TurnR (int amount, int time) {

	motor[DriveLeft1] = amount * -con;

	motor[DriveRight1] = -amount * -con;

	motor[DriveRight2] = -amount * -con;

	motor[DriveLeft2] = amount * -con;

	if (time != 0) wait1Msec(time);

}



// Turn left

void TurnL (int amount, int time) {

	motor[DriveLeft1] = amount * con;

	motor[DriveRight1] = -amount * con;

	motor[DriveRight2] = -amount * con;

	motor[DriveLeft2] = amount * con;

	if (time != 0) wait1Msec(time);

}



// Rotate the claw to flip the object

void ClawUp (int amount, int time) {

	motor[Claw] = amount * con;

	if (time != 0) wait1Msec(time);

}



void ClawDown (int amount, int time) {

	motor[Claw] = amount * -con;

	if (time != 0) wait1Msec(time);

}



// For taking ball in

void BallIntake1 (int amount, int time) {

	motor[Intake1] = amount * con;

	motor[Intake2] = amount * -con;

	if (time != 0) wait1Msec(time);

}



// For taking ball out

void BallIntake2 (int amount, int time) {

	motor[Intake1] = -amount * con;

	motor[Intake2] = -amount * -con;

	if (time != 0) wait1Msec(time);

}



// For shooting the ball - automate it for now

void Shoot (int amount) {

	motor[Shooter] = amount * -con;

	wait1Msec(1500);

	motor[Shooter] = 0;

	// if (time != 0) wait1Msec(time);

}



// For stopping the drive

void StopDrive () {

	motor[DriveLeft1] = motor[DriveRight1] = motor[DriveRight2] = motor[DriveLeft2] = 0;

}



// For stopping the claw flipper

void StopClaw () {

	motor[Claw] = 0;

}



// For stopping the shooter

void StopShoot () {

	motor[Shooter] = 0;

}



// For stopping the ball intake

void StopBallIntake () {

	motor[Intake1] = motor[Intake2] = 0;

}





/*---------------------------------------------------------------------------*/

/*                                                                        */

/*                            Autonomous Task                           */

/*                                                                        */

/*  This task is used to control your robot during the autonomous phase of   */

/*  a VEX Competition.                                                    */

/*                                                                        */

/*  You must modify the code to add your own robot specific commands here.   */

/*---------------------------------------------------------------------------*/



// Autonomous Functions



// For when we are on the side with no flags during autonomous

void autoNoFlags (bool red) {

	// Red side

	if (red) {

		// Collect ball underneath the mobile goal first

		BallIntake1(127, 0);

		DriveF(127, 1500);

		StopDrive();

		StopBallIntake();

		// Now flip the mobile goal over

		TurnL(127, 500);

		StopDrive();

		DriveB(127, 1000);

		StopDrive();

		ClawUp(127, 500);

		StopClaw();

		ClawDown(127, 500);

		StopClaw();

		// Now park on the nearest platform

		TurnL(127, 200);

		StopDrive();

		DriveF(127, 2000);

		StopDrive();

		TurnR(127, 400);

		StopDrive();

		DriveF(127, 150);

		StopDrive();

	}

	// Blue side (left and right are flipped)

	else {

		// Collect ball underneath the mobile goal first

		BallIntake1(127, 0);

		DriveF(127, 1500);

		StopDrive();

		StopBallIntake();

		// Now flip the mobile goal over

		TurnR(127, 500);

		StopDrive();

		DriveB(127, 1000);

		StopDrive();

		ClawUp(127, 500);

		StopClaw();

		ClawDown(127, 500);

		StopClaw();

		// Now park on the nearest platform

		TurnR(127, 200);

		StopDrive();

		DriveF(127, 2000);

		StopDrive();

		TurnL(127, 400);

		StopDrive();

		DriveF(127, 150);

		StopDrive();

	}

}



// For when we are on the side with flags during autonomous

void autoWithFlags (bool red) {

	// Red side

	if (red) {

		// Collect the ball underneath the mobile goal first

		BallIntake1(127, 0);

		DriveF(127, 1500);

		StopDrive();

		StopBallIntake();

		// Now shoot the 2 balls onto the top 2 flags

		DriveB(127, 1500);

		StopDrive();

		TurnL(127, 500);

		StopDrive();

		DriveF(127, 500);

		StopDrive();

		Shoot(127);

		// Now flip the mobile goal over

		TurnL(127, 500);

		StopDrive();

		DriveF(127, 150);

		StopDrive();

		ClawUp(127, 500);

		StopClaw();

		ClawDown(127, 500);

		StopClaw();

		// Turn around after

		TurnR(127, 1500);

		StopDrive();

	}

	// Blue side (left and right are flipped)

	else {

		// Collect the ball underneath the mobile goal first

		BallIntake1(127, 0);

		DriveF(127, 1500);

		StopDrive();

		StopBallIntake();

		// Now shoot the 2 balls onto the top 2 flags

		DriveB(127, 1500);

		StopDrive();

		TurnR(127, 500);

		StopDrive();

		DriveF(127, 500);

		StopDrive();

		Shoot(127);

		// Now flip the mobile goal over

		TurnR(127, 500);

		StopDrive();

		DriveF(127, 150);

		StopDrive();

		ClawUp(127, 500);

		StopClaw();

		ClawDown(127, 500);

		StopClaw();

		// Turn around after

		TurnL(127, 1500);

		StopDrive();

	}

}



task autonomous () {

	// ..........................................................................

	// Insert user code here.

	// ..........................................................................

	// Still needs TESTING

	if (flags) {

		autoWithFlags(red);

	}

	else {

		autoNoFlags(red);

	}

}



/*---------------------------------------------------------------------------*/

/*                                                                        */

/*                            User Control Task                         */

/*                                                                        */

/*  This task is used to control your robot during the user control phase of */

/*  a VEX Competition.                                                    */

/*                                                                        */

/*  You must modify the code to add your own robot specific commands here.   */

/*---------------------------------------------------------------------------*/

task usercontrol () {

	// User control code here, inside the loop

	while (1) {

		// FORWARD AND BACKWARD

		int tmp;

		if (vexRT[Ch2] > 0) {

			tmp = min(vexRT[Ch2], 100);

		}

		else if (vexRT[Ch2] < 0) {

			tmp = max(vexRT[Ch2], -100);

		}

		motor[DriveLeft1] = tmp * -con;

		motor[DriveRight1] = tmp * -con - dev;

		motor[DriveRight2] = tmp * -con - dev;

		motor[DriveLeft2] = tmp * -con;

		// Left axle turn

		if (vexRT[Btn5U]) {

			motor[DriveLeft1] = vexRT[Btn5U] * 127 * con;

			motor[DriveRight1] = vexRT[Btn5U] * -127 * con;

			motor[DriveRight2] = vexRT[Btn5U] * -127 * con;

			motor[DriveLeft2] = vexRT[Btn5U] * 127 * con;

		}

		// Right axle turn

		if (vexRT[Btn6U]) {

			motor[DriveLeft1] = vexRT[Btn6U] * 127 * -con;

			motor[DriveRight1] = vexRT[Btn6U] * -127 * -con;

			motor[DriveRight2] = vexRT[Btn6U] * -127 * -con;

			motor[DriveLeft2] = vexRT[Btn6U] * 127 * -con;

		}

		// Claw angle rotation (to go up) not working - need to replace motor most likely

		if (vexRT[Btn7U]) {

			motor[Claw] = vexRT[Btn7U] * 127 * -con;

		}

		if (!vexRT[Btn7U]) {

			motor[Claw] = 0;

		}

		// Claw angle rotation (to go down) working

		if (vexRT[Btn7L]) {

			motor[Claw] = vexRT[Btn7L] * 127 * con;

		}

		if (!vexRT[Btn7L]) {

			motor[Claw] = 0;

		}

		/* Need to make sure catapult arm stays in place for ball intake - Use a potentiometer!!! */

		// Shooter working CCW (make sure it goes back down again after shooting up)

		if (vexRT[Btn8L]) {

			int res = vexRT[Btn8L];

			motor[Shooter] = res * 127 * -con;

			wait1Msec(1500);

			motor[Shooter] = 0;

			// motor[Shooter] = res*30*con;

		}

		// Shooter working CW (not really necessary)

		if (vexRT[Btn8R]) {

			int res = vexRT[Btn8R];

			motor[Shooter] = res * -127 * -con;

			wait1Msec(1500);

			// motor[Shooter] = res*30*-con;

		}

		// Ball intake (CW) working

		if (vexRT[Btn6D]) {

			motor[Intake1] = vexRT[Btn6D] * -127 * con;

			motor[Intake2] = vexRT[Btn6D] * -127 * -con;

			stop_intake = 1;

		}

		if (!vexRT[Btn6D]) {

			motor[Intake1] = motor[Intake2] = 0;

		}

		// Ball intake (CCW) not working - hardware problem

		if (vexRT[Btn5D]) {

			motor[Intake1] = vexRT[Btn5D] * 127 * con;

			motor[Intake2] = vexRT[Btn5D] * 127 * -con;

			stop_intake = 1;

		}

		if (!vexRT[Btn5D]) {

			motor[Intake1] = motor[Intake2] = 0;

		}

	}

}
