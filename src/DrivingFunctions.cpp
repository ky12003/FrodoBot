#include "vex.h"
#include "DrivingFunctions.h"

using namespace vex;

void arcadeDrive() {
  double speed = 0.7;

  if ((abs(controller1.Axis3.value()) > 25) ||
      (abs(controller1.Axis1.value()) > 25)) {
    leftWheels.spin(
        forward,
        ((controller1.Axis3.value() + (controller1.Axis1.value() / 2)) * speed),
        pct);
    rightWheels.spin(
        forward,
        ((controller1.Axis3.value() - (controller1.Axis1.value() / 2)) * speed),
        pct);
  } else {
    leftWheels.stop();
    rightWheels.stop();
  }
}

  void tankDrive()
{
  if (abs(controller1.Axis2.value()) > 5 || abs(controller1.Axis3.value()) > 5)
  {
    leftWheels.spin(forward, (controller1.Axis3.value()) * 0.8, pct);
    rightWheels.spin(forward, (controller1.Axis2.value()) * 0.8, pct); 
  }
  else
  {
   leftWheels.stop();
    rightWheels.stop();
  } 
}