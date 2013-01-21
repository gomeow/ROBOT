#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int motorSlow = 1;
bool toogleArm = false;
bool toogleSpool = false;
int motorSpeedD = 0;
int motorSpeedE = 0;
int motorSpeedF = 0;
int motorSpeedG = 0;


//Get the left side movement.
int getJoy1y1() {
	return joystick.joy1_y1;
}
//Get the right side movement.
int getJoy1y2() {
	return joystick.joy1_y2;
}

//Returns which speed to go at
int getMotorSlow() {
  if (joy1Btn(1) == 1) //X position
	  return 1; //fast
	else if (joy1Btn(2) == 1) //A position
    return 2; //medium
	else if (joy1Btn(3) == 1) //B position
		return 4; //slow
	else {
		return 0;
	}
}

//Initialize, setting all motors to a speed of 0.
void initializeRobot() {
	motor[motorD] = 0;
	motor[motorE] = 0;
}

void joy1Controls() {
	getJoystickSettings(joystick);
	motorSpeedD = getJoy1y1();
	motorSpeedE = getJoy1y2();
	if(getMotorSlow() != 0)	{
		motorSlow = getMotorSlow();
	}
  motor[motorD] = motorSpeedD / motorSlow;
  motor[motorE] = motorSpeedE / motorSlow;
}

/*
 * Get Joystick 2 (Guunner) Controls
 */

int getArmMovement() {
	if (joy2Btn(7) == 1) {
		return 50;
	}
	else if(joy2Btn(8) == 1) {
		return -20;
	}
	else return 0;
}

int getSpoolMovement() {
	return joystick.joy2_y1;
}

int getClawMovement() {
	return joystick.joy2_y2;
}

int getToggleSpool() {
	toggleArm = (joy2Btn(2) == 1) ? true : false;
}

int getToggleArm() {
	toggleArm = (joy2Btn(3) == 1) ? true : false;
}

void joy2Controls() {
	motorSpeedF = getArmMovement();
	motorSpeedG = getSpoolMovement();

	getToggleSpool();
	getToggleArm();

	motor[motorF] = (toggleArm) ? motorSpeedF : motorSpeedF - 20;
	motor[motorG] = (toggleSpool) ? motorSpeedG : motorSpeedG - 20;

	//This motor controls the arm, moving it up and down.
	//May need editing later, probably just changing it to negative.
}

task main() {
    initializeRobot();
    waitForStart();

    while(true) {
	    joy1Controls();
	    joy2Controls();
    }
}
