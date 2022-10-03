using namespace vex;

extern brain Brain;

extern controller controller1;

//drivetrain motors
extern motor left1;
extern motor left2;
extern motor left3;

extern motor right1;
extern motor right2;
extern motor right3; 

//intake motors
extern motor intake;

//catapult motor
extern motor thrower;

//motor groups
extern motor_group AllLeft;
extern motor_group AllRight;
extern motor_group AllMotors;

//motor encoders
extern encoder encoder1;
extern encoder encoder2;
extern encoder cataswitch;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
