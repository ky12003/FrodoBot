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
using namespace vex;

competition Competition;

void usercontrol()
{
  while(1)
  {
  arcadeDrive();
  //tankDrive();
  // if needed, switch between the two drive modes here
  }
}
  
void Autonomous()
{
 //placeholder for the code that does not exist yet :^)
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.drivercontrol(usercontrol);
  Competition.autonomous(Autonomous);
}
