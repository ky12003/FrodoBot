/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\gobin                                            */
/*    Created:      Thu Oct 06 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"

#include "Autonomous.h"
#include "RobotFunctions.h"
#include "DrivingFunctions.h"
#include "Routines.h"
#include "robot-config.h"
#include <iostream>


using namespace vex;
void UserControl() {
  thrower.setVelocity(100, pct);
  while (true) {
    // printf("\ntest: %li", catapultLimit.pressing());
    tankDrive();
    catapultLogic();
    intakeToggle();
    doExpansion();
    spinRollerOpticalBlue();
    // spinRollerOpticalRed();
    // printf("\ntest: %li", catapultBumper.value());
  }
}

void preAuton() {
  Inertial1.resetHeading();
  Inertial1.startCalibration();
  do  { } while (Inertial1.isCalibrating());
}

void Autonomous()
{
  // preAuton();

  // Routine1Auton();
  Routine2Auton(blue);
  // Routine1Skills();
  // Routine2Skills();
  // Routine3Skills();
  // testAuton();
  // GPStest();
  // moveinBox();
}

competition Competition;
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.drivercontrol(UserControl);
  Competition.autonomous(Autonomous);
}
