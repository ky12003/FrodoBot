#include "vex.h"
#include "robot-config.h"
#include "RobotFunctions.h"
using namespace vex;

bool intaking = false;
bool catapultWind = true;
long int prevValue = -1;

void catapultLogic() {
  if (catapultWind) {
    windUp();
  }
  controller1.ButtonL2.pressed(shootDisks);
  controller1.ButtonR1.pressed(intakeToggle);
}

void windUp() {
   
  if (catapultBumper.value() == prevValue) {
    thrower.spin(reverse, 100, pct);
  } else {
    catapultWind = !catapultWind;
    thrower.stop();
  }
}

void windBack() {
  // if (catapultBumper.value() != prevValue) {
  //   thrower.stop();
  //   prevValue = catapultBumper.value();
    thrower.stop();
}

void shootDisks() {
  thrower.setTimeout(1200, msec);
  thrower.spinFor(reverse, 1200, msec);
  thrower.setTimeout(0, msec);
  catapultWind = true;
  prevValue = catapultBumper.value();
}

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

// void intakeToggle() {
// if (intaking) {
// intake.stop();
// }
// else {
//   intake.spin(forward,100,pct);
// }
// intaking = !intaking;
// }
