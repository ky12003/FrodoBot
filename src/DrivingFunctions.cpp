#include "vex.h"
#include "DrivingFunctions.h"
#include "robot-config.h"

using namespace vex;

void arcadeDrive()
{
  if (abs(controller1.Axis3.value()) > 5 || abs(controller1.Axis1.value()) > 5)
  {
    AllRight.spin(forward, (controller1.Axis3.value() + controller1.Axis1.value()) * 0.9, pct);
    AllLeft.spin(forward, (controller1.Axis3.value() - controller1.Axis1.value()) * 0.9, pct);
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
  // printf("test: %f", Inertial1.rotation(deg));
  if (abs(controller1.Axis2.value()) > 10 || abs(controller1.Axis3.value()) > 10)
  {
    AllRight.spin(forward, (controller1.Axis2.value()) * 0.5, pct);
    AllLeft.spin(forward, (controller1.Axis3.value()) * 0.5, pct); 
    // printf("\nleftside: %n", controller1.Axis2.value());
    // printf("\nrightside: %n", controller1.Axis3.value());
  }
  else
  {
    AllRight.stop();
    AllLeft.stop();
  } 
}

