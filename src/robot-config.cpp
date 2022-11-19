#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller controller1(primary);

motor leftFront(PORT3, ratio18_1, false);
motor leftMiddle(PORT4, ratio18_1, false);
motor leftBack(PORT5, ratio18_1, false);

motor rightFront(PORT6, ratio18_1, true);
motor rightMiddle(PORT7, ratio18_1, true);
motor rightBack(PORT8, ratio18_1, true);

bumper catapultBumper(Brain.ThreeWirePort.A);

motor_group leftWheels(leftFront, leftMiddle, leftBack);
motor_group rightWheels(rightFront, rightMiddle, rightBack);

motor catapult(PORT9, ratio36_1, true);
// motor intake(PORT16, ratio18_1, true);

motor intakeMotor(PORT16, ratio18_1, false);
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}