#include "vex.h"
#include "robot-config.h"
#include "RobotFunctions.h"
using namespace vex;

bool intaking = false;

void catapultLogic() {
controller1.ButtonL2.pressed(windUp);
// controller1.ButtonL2.released(windBack);
catapultBumper.pressed(windBack);
controller1.ButtonR1.pressed(intakeToggle);

}

void windUp() {
  thrower.spin(forward);
}

void windBack() {
  thrower.stop();
}


void intakeToggle() {
if (intaking) {
intake.stop();
}
else {
  intake.spin(forward,100,pct);
}
intaking = !intaking;
}
