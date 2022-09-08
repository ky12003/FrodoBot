#include "driving-function.h"
#include "vex.h"
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
  if (abs(controller1.Axis2.value()) > 5 && abs(controller1.Axis3.value()) > 5)
  {
    AllLeft.spin(forward, controller1.Axis3.value(), pct);
    AllRight.spin(forward, controller1.Axis2.value(), pct); 
  }
  else
  {
    AllRight.stop();
    AllLeft.stop();
  }  
}

