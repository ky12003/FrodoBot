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
#include "CatapultFunctions.h"
#include "DrivingFunctions.h"
#include "Routines.h"

using namespace vex;
void UserControl() {
  while (true) {
    arcadeDrive();
    catapultLogic();
  }
}

void Autonomous() { redStart(); }

competition Competition;
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.drivercontrol(UserControl);
  Competition.autonomous(Autonomous);
}
