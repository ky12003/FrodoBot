#include "driving-function.h"
#include "vex.h"
#include "robot-config.h"
using namespace vex;


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