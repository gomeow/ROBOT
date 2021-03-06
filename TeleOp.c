#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

//----------------------------- Initialization ------------------------------

int motorSlow = 1;
bool toggleArm = false;
bool toggleSpool = false;
bool toggleClaw = false;
int motorSpeedA = 0;
int motorSpeedD = 0;
int motorSpeedE = 0;
int motorSpeedF = 0;
int motorSpeedG = 0;

void initializeRobot() { //Initialize, setting all motors to a speed of 0.
	motor[motorD] = 0;
	motor[motorE] = 0;
	motor[motorF] = 0;
	motor[motorG] = 0;
}

//--------------------  Joystick 1 (Driver) Controls --------------------------

int getJoy1y1() { //Get the left side movement.
	if(joystick.joy1_y1 > 10 || joystick.joy1_y1 < -10) return joystick.joy1_y1 / 3;
	else return 0;
}
int getJoy1y2() {  //Get the right side movement.
	if(joystick.joy1_y2 > 10 || joystick.joy1_y2 < -10) return joystick.joy1_y2 / 3;
	else return 0;
}

int getMotorSlow() { //Returns which speed to go at
  if (joy1Btn(1) == 1) return 1; //fast X Button
  else if (joy1Btn(2) == 1) return 2; //medium A position
  else if (joy1Btn(3) == 1) return 4; //slow B position
  else return 0;
}

void joy1Controls() {
	getJoystickSettings(joystick);
	motorSpeedD = getJoy1y2();
	motorSpeedE = getJoy1y1();
	if(getMotorSlow() != 0)	{
		motorSlow = getMotorSlow();
	}
	if(joy1Btn(8) == 1) {
		motor[motorD] = 10;
		motor[motorE] = 10;
	}
	else if(joy1Btn(7) == 1) {
		motor[motorD] = -10;
		motor[motorE] = -10;
	}
	else if(joy1Btn(5) == 1) {
		motor[motorD] = 17;
		motor[motorE] = -17;
	}
	else if(joy1Btn(6) == 1) {
		motor[motorD] = -17;
		motor[motorE] = 17;
	}
	else {
  	motor[motorD] = motorSpeedD / motorSlow;
  	motor[motorE] = motorSpeedE / motorSlow;
	}
}

// ------------------- Joystick 2 (Gunner) Controls ------------------------

int getArmMovement() {  //Gets Arm movement
	if (joy2Btn(7) == 1) {
		return 100;
	}
	else if(joy2Btn(8) == 1) {
		return -15;
	}
	else return 0;
}



int getSpoolMovement() {  //Gets Spool Movement
	if(joystick.joy2_y1 > 10 || joystick.joy2_y1 < -10) return joystick.joy2_y1;
	else return 0;
}

int getClawMovement() { //Gets Claw Movement
	if(joystick.joy2_y2 > 10 || joystick.joy2_y2 < -10) return joystick.joy2_y2/4;
	else return 0;
}

void joy2Controls() {
	motorSpeedF = getArmMovement();
	motorSpeedG = getSpoolMovement();
	motorSpeedA = getClawMovement();

	motor[motorA] = motorSpeedA;
	motor[motorF] = motorSpeedF;
	motor[motorG] = motorSpeedG;

	//This motor controls the arm, moving it up and down.
}

//--------------------------------- Main --------------------------------

task main() {
    initializeRobot();
    waitForStart();

    while(true) {
	    joy1Controls();
	    joy2Controls();
    }
}
