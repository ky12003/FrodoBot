#include "driving-function.h"
#include "vex.h"
#include "robot-config.h"
using namespace vex;

void arcadeDrive()
{
  if (abs(controller1.Axis3.value()) > 5 || abs(controller1.Axis1.value()) > 5)
  {
    AllRight.spin(forward, (controller1.Axis3.value() + controller1.Axis1.value()) * 0.8, pct);
    AllLeft.spin(forward, (controller1.Axis3.value() - controller1.Axis1.value()) * 0.8, pct);
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
    AllRight.spin(forward, (controller1.Axis3.value()) * 0.05, pct);
    AllLeft.spin(forward, (controller1.Axis2.value()) * 0.05, pct); 
    printf("\nleftside: %n", controller1.Axis2.value());
    printf("\nrightside: %n", controller1.Axis3.value());
  }
  else
  {
    printf("\npaused");
    AllRight.stop();
    AllLeft.stop();
  } 
}

bool catapultDown = true;
void Catapult()
{
  if (controller1.ButtonL1.pressing())
  {
    thrower.spin(reverse, 100, pct);
    catapultDown = false;
  }
  else
  {
    if (catapultDown == true) {
      thrower.stop();
    } else {
      thrower.spin(forward, 100, pct);
      if (thrower.velocity(pct) < 0.5) {
        catapultDown = true;
      }
    }
    
  }
}

void windBack() {
  thrower.stop();

}

void windUp() {
  thrower.spin(forward);
}

//intake wheel control
bool doIntakeOut = false;
bool doIntakeIn = false;
bool intakeToggleBuffering = false;
void intakeToggle(){
  if(controller1.ButtonR1.pressing())
  {
    if (!intakeToggleBuffering) {
      
      intakeToggleBuffering = true;
      doIntakeOut = !doIntakeOut;
      doIntakeIn = false;
      if (doIntakeOut) {
        controller1.rumble("-");
      } else {
        controller1.rumble("..");
      }
    }
  } 
  else if (controller1.ButtonR2.pressing()) {
    if (!intakeToggleBuffering) {
      intakeToggleBuffering = true;
      doIntakeIn = !doIntakeIn;
      doIntakeOut = false;
      if (doIntakeIn) {
        controller1.rumble(".");
      } else {
        controller1.rumble("..");
      }
    }
  }
  else {
    // controller1.rumble(".");
    intakeToggleBuffering = false;
  }

  if (doIntakeOut) {
    intake.spin(fwd, 100, pct);
  } else if (doIntakeIn) {
    intake.spin(directionType::rev, 100, pct);
  } else {
    intake.stop();
  }
}