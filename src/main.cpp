/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Leo Zubiate                                               */
/*    Created:      Fri Sep 02 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "driving-function.h"
#include "routines.h"
#include "RobotFunctions.h"
using namespace vex;

competition Competition;

void usercontrol()
{
  while(1)
  {
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

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.drivercontrol(usercontrol);
  Competition.autonomous(Autonomous);
}
