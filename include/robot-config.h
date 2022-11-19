using namespace vex;

extern brain Brain;

extern controller controller1; 

extern motor leftFront;
extern motor leftMiddle;
extern motor leftBack;

extern motor rightFront;
extern motor rightMiddle;
extern motor rightBack;

extern motor_group leftWheels;
extern motor_group rightWheels;

extern bumper catapultBumper;
extern motor intakeMotor;

extern motor catapult;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
