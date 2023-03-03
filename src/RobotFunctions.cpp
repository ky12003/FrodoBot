#include "vex.h"
#include "RobotFunctions.h"
#include "robot-config.h"

#include <string>

#include <iostream>
using namespace vex;

bool intaking = false;
bool intakePosition = false;
bool catapultWind = true;
long int prevValue = -1;


void catapultLogic() {
  if (catapultWind) {
    windUp();
  }

// roller optical code
// std::string s = "red";
  // if (rollerOptical.isNearObject()) {
  //   while (rollerOptical.color()) {
  //     intake.spin(fwd, 10, pct);
  //   }
  // }

  // controller1.ButtonL1.pressed(manualWindUp);
  // controller1.ButtonL2.released(manualStopThrower);
  controller1.ButtonL2.pressed(shootDisks);
  controller1.ButtonR1.pressed(intakeToggle);

  // intake logic
}

void manualWindUp() { thrower.spin(reverse, 100, pct); }

void manualStopThrower() { thrower.stop(); }

void windUp() {

  if (catapultLimit.value() == prevValue) {
    thrower.spin(reverse, 100, pct);
  } else {
    catapultWind = !catapultWind;
    thrower.stop();
  }
}

void shootDisks() {
  // thrower.setTimeout(800, msec);
  thrower.spinFor(reverse, 800, msec);
  // thrower.setTimeout(0, msec);
  catapultWind = true;
  prevValue = catapultLimit.value();
}

// void intakeToggle() {
//   if (intaking) {
//     intake.stop();
//   } else {
//     if (intakePosition) {
//       intake.spin(forward, 80, pct);
//     }
//     else {
//         { intake.spin(reverse, 100, pct); }
//       }
//     }
//     intaking = !intaking;
//   }

void reverseIntake() { intakePosition = !intakePosition; }

bool doIntakeOut = false;
bool doIntakeIn = false;
bool intakeToggleBuffering = false;
void intakeToggle() {
  if (controller1.ButtonR1.pressing()) {
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
  } else if (controller1.ButtonR2.pressing()) {
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
  } else {
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
