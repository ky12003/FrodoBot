#include "vex.h"
#include "robot-config.h"
using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller controller1(primary);

//drivetrain motors (all green motors)
motor left1(PORT14,ratio18_1, true);
motor left2(PORT12,ratio18_1, true);
motor left3(PORT13,ratio18_1, true);

motor right1(PORT1,ratio18_1, false);
motor right2(PORT2,ratio18_1, false);
motor right3(PORT3,ratio18_1,false);

//intake motor (blue motor)
motor intake(PORT19,ratio6_1,false);

//catapult motor (red motor)
motor thrower(PORT18,ratio36_1,false);

//motor groups 
motor_group AllLeft(left1, left2, left3);
motor_group AllRight(right1, right2, right3);
motor_group AllMotors(left1, left2, left3, right1, right2, right3);

//since the encoder has two wires, it needs to be defined by two ports
encoder encoderTop = encoder(Brain.ThreeWirePort.A);
encoder encoderBottom = encoder(Brain.ThreeWirePort.B);
encoder cataswitch = encoder(Brain.ThreeWirePort.H);



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}