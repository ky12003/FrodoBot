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
using namespace vex;

competition Competition;

void usercontrol()
{
  bool Toggle = false;
  bool ToggleSwitch = false;
  while(1)
  {
    Catapult();
    tankDrive();
  if (controller1.ButtonR2.pressing())
  {
    if (!ToggleSwitch)
    {
      ToggleSwitch = true;
      Toggle = !Toggle;
      if (Toggle)
      {
        intake.spin(reverse,100,pct);
      }
      else 
      {
        intake.stop();
      }
    }
  }
  if (controller1.ButtonR1.pressing())
  {
    if (!ToggleSwitch)
    {
      ToggleSwitch = true;
      Toggle = !Toggle;
      if (Toggle)
      {
        intake.spin(forward,100,pct);
      }
      else 
      {
        intake.stop();
      }
    }
  }
  else 
  {
    ToggleSwitch = false;
  }
  }
}
void Autonomous()
{
  moveinBox();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.drivercontrol(usercontrol);
  Competition.autonomous(Autonomous);
}
