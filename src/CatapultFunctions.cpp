#include "vex.h"
#include "CatapultFunctions.h"

using namespace vex;

bool intaking = false;

void catapultLogic() {
controller1.ButtonL2.pressed(windUp);
controller1.ButtonL2.released(windBack);
catapultBumper.pressed(windBack);
controller1.ButtonR2.pressed(intakeOn);
}

void windBack() {
  catapult.stop();

}

void windUp() {
  catapult.spin(forward);
}

void intakeOn() {
if (intaking) {
intakeMotor.stop();
}
else {
  intakeMotor.spin(forward,100,pct);
}
intaking = !intaking;
}