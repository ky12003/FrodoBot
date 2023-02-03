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
    tankDrive();
    catapultLogic();
    // printf("\ntest: %li", catapultBumper.value());
  }
}
void Autonomous()
{
  // Routine1Auton();
  Routine1Skills();
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
