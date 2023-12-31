/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  inertialSensor.calibrate();
  while(inertialSensor.isCalibrating()){
    wait(100,msec);
  }
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
// ALL VARIABLES FOR PID DEFINED HERE //
double ratio = 0.1;
double destination = 90;
double error = destination - inertialSensor.rotation(degrees);
void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // Turns robot right 45 degrees
  LeftMotor.spin(forward,error * ratio, voltageUnits::volt);
  RightMotor.spin(reverse,error*ratio,voltageUnits::volt);
  printf("error is %f\n", inertialSensor.rotation(degrees));
  waitUntil((inertialSensor.rotation(degrees)) >= 90);
  LeftMotor.stop();
  RightMotor.stop();
  wait(400, msec);
  // Move 14 inches
  // driveDistanceInches(14);
  // Turn left 45 degrees
  LeftMotor.spin(reverse,error*ratio,voltageUnits::volt);
  RightMotor.spin(forward,error*ratio,voltageUnits::volt);
  waitUntil((inertialSensor.rotation(degrees)) <= 90);
  LeftMotor.stop();
  RightMotor.stop();
  
  // Move 17 inches
  // DriveDistanceInches(17);
  // ..........................................................................
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
int deadband = 5;
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}
//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}