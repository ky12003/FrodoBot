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
#include "driving-function.h"
#include "Routines.h"

using namespace vex;
void UserControl() {
  while (true) {
    tankDrive();
    Catapult();
    intakeToggle();
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
