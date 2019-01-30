#pragma config(Motor,  port2,           DriveLeft1,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port3,           DriveLeft2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           DriveRight1,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           DriveRight2,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           Intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           Indexer,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Loader,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           Flywheel,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,           Descorer,      tmotorNone, openLoop)
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
bool holding;
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



// For stopping the drive

void StopDrive () {

  motor[DriveLeft1] = motor[DriveRight1] = motor[DriveRight2] = motor[DriveLeft2] = 0;

}


// For stopping the shooter

void StopShoot () {

  motor[Flywheel] = 0;

}

// For stopping the claw flipper

void StopDescorer () {

  motor[Descorer] = 0;

}

// For stopping the ball intake

void StopBallIntake () {

  motor[Intake] = 0;

}

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

// For taking ball in

void BallIntake1 (int amount, int time) {

  motor[Intake] = -amount * con;

  if (time != 0) wait1Msec(time);

}

// For taking ball out
void BallIntake2 (int amount, int time) {
  motor[Intake] = amount * con;
  if (time != 0) wait1Msec(time);
}

void Indexer1 (int amount, int time) {
	motor[Indexer] = amount * -con;
	if (time != 0) wait1Msec(time);
}

void Indexer2 (int amount, int time) {
	motor[Indexer] = amount * con;
	if (time != 0) wait1Msec(time);
}

// For shooting the ball up - automate it for now
void Shoot (int amount, int time) {
	Indexer1(127, 500);
  motor[Flywheel] = -amount * -con;
  if (time != 0) wait1Msec(time);
}

// Auto shoots the balls onto the top 2 flags
void autoShoot (int amount) {
	Shoot(127, 500);
	StopShoot();
	DriveF(127, 300);
	StopDrive();
	Shoot(127, 500);
}

// Rotate the claw to flip the object

void DescorerUp (int amount, int time) {

  motor[Descorer] = amount * con;

  if (time != 0) wait1Msec(time);

}

void DescorerDown (int amount, int time) {

  motor[Descorer] = amount * -con;

  if (time != 0) wait1Msec(time);

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

void autoWithFlags (bool red) {

  // Red side

  if (red) {
			// Drive up to get the ball underneath the cap
  			
  		// Load the ball into the intake
  	
  		// Drive back and rotate 90 degrees CCW
  
  		// Shoot the ball onto the top flag
  
  		// Stop flywheel and drive up then stop driev
  
  		// Turn on flywheel to shoot middle flag
  
  		// Turn off flywheel and drive straight to toggle low flag
  
  		// Drive back and turn 90 degrees CW
  
  		// Flip over the cap/drive forwards simultaneously
  
  		// Drive back and turn 90 degrees CW
  
  		// Drive forwards to get onto the platform
  
  		// Turn 90 degrees CCW and drive onto the platform

  }

  // Blue side (left and right are flipped)

  else {

      // Drive up to get the ball underneath the cap
  			
  		// Load the ball into the intake
  	
  		// Drive back and rotate 90 degrees CW
  
  		// Shoot the ball onto the top flag
  
  		// Stop flywheel and drive up then stop driev
  
  		// Turn on flywheel to shoot middle flag
  
  		// Turn off flywheel and drive straight to toggle low flag
  
  		// Drive back and turn 90 degrees CCW
  
  		// Flip over the cap/drive forwards simultaneously
  
  		// Drive back and turn 90 degrees CCW
  
  		// Drive forwards to align with the platform
			
  		// Turn 90 degrees CW and drive onto the platform
  }

}



// For when we are on the side with flags during autonomous

void autoNoFlags (bool red) {

  // Red side

  if (red) {
			// Turn 90 degrees CW and drive forwards to align with the opponent's cap
  		
  		// Turn 90 degrees CCW and drive forwards, while turning on ball intake
  
  		// Now flip over the cap
  
  		// Now drive back and turn 90 degrees CCW
  
  		// Drive forwards and turn 90 degrees CW to align with the platform
  
  		// Now drive forwards to get onto the platform
    
  }

  // Blue side (left and right are flipped)

  else {
			// Turn 90 degrees CCW and drive forwards to align with the opponent's cap
  		
  		// Turn 90 degrees CW and drive forwards, while turning on ball intake
  
  		// Now flip over the cap
  
  		// Now drive back and turn 90 degrees CW
  
  		// Drive forwards and turn 90 degrees CCW to align with the platform
  
  		// Now drive forwards to get onto the platform
    	
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

      tmp = min(vexRT[Ch2], 127);

    }

    else if (vexRT[Ch2] < 0) {
     	tmp = max(vexRT[Ch2], -127);
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
    
    // Make descorer go down
    if (vexRT[Btn7U]) {
      motor[Descorer] = vexRT[Btn7U] * 127 * con;
    }

    // Make descorer go up
    else if (vexRT[Btn7L]) {
      motor[Descorer] = vexRT[Btn7L] * 127 * -con;
    }

    else {
      motor[Descorer] = 0;
    }

    // Turn on the flywheel
    if (vexRT[Btn8L]) {
      int res = vexRT[Btn8L];
      motor[Flywheel] = res * 127 * -con;
    }
    
    // Turn off the flywheel
    if (vexRT[Btn8R]) {
    	StopShoot();	
  	}

    // Ball intake (CW) working
    if (vexRT[Btn6D]) {
      motor[Intake] = vexRT[Btn6D] * -127 * con;
    }

    // Ball intake (CCW) working
    else if (vexRT[Btn5D]) {
      motor[Intake] = vexRT[Btn5D] * 127 * con;
    }

    else {
      StopBallIntake();
    }
    
    // Implement indexer and (maybe) 3rd intake here...
    
  }
}