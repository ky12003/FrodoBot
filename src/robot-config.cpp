#include "vex.h"
#include "robot-config.h"
using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller controller1(primary);

//drivetrain motors (all green motors)
motor left1(PORT3,ratio6_1, false);
motor left2(PORT4,ratio6_1, false);
motor left3(PORT5,ratio6_1, false);

motor right1(PORT6,ratio6_1, true);
motor right2(PORT7,ratio6_1, true);
motor right3(PORT8,ratio6_1, true);


//intake motor (green motor)
motor intake(PORT16,ratio18_1,true);

//catapult motor (red motor)
motor thrower(PORT9,ratio36_1,false);

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