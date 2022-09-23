#include "driving-function.h"
#include "vex.h"
#include "robot-config.h"
using namespace vex;

void arcadeDrive()
{
  if (abs(controller1.Axis3.value()) > 5 || abs(controller1.Axis1.value()) > 5)
  {
    AllRight.spin(forward, (controller1.Axis3.value() + controller1.Axis1.value() ), pct);
    AllLeft.spin(forward, (controller1.Axis3.value() - controller1.Axis1.value() ), pct);
  }

  // arcade drive function, 
  //Axis 3 on controller controls foward and reverse. 
  //Axis 1 on controllers controls left and right turns
  else
  {
    AllRight.stop();
    AllLeft.stop();
  }
}

void tankDrive()
{
  if (abs(controller1.Axis2.value()) > 5 || abs(controller1.Axis3.value()) > 5)
  {
    AllRight.spin(forward, controller1.Axis3.value(), pct);
    AllLeft.spin(forward, controller1.Axis2.value(), pct); 
  }
  else
  {
    AllRight.stop();
    AllLeft.stop();
  } 
}

void Intake()
  {
    bool Toggle = false;
    bool ToggleSwitch = false;
    if (controller1.ButtonR1.pressing())
  {
    if (!ToggleSwitch)
    {
      ToggleSwitch = true;
      Toggle = !Toggle;
      if (Toggle)
      {
        intake.spin(reverse);
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

void Catapult()
{
  bool CatapultToggle = false;
  bool CatapultSwitch = false;
  if (controller1.ButtonX.pressing())
  {
    if (!CatapultSwitch)
    {
      CatapultToggle = true;
      CatapultToggle = !CatapultToggle;
      if (CatapultToggle)
      {
        thrower.spinFor(forward, 1.5, seconds);
      }
      else 
      {
        thrower.stop();
      }
    }
  }
}
