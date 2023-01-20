#include "math.h"

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


//motor encoders
extern encoder encoder1;
extern encoder encoder2;
extern encoder cataswitch;

// GPS
extern gps DrivetrainGPS;
long map(long x, long in_min, long in_max, long out_min, long out_max);

// constants
extern const float WHEEL_CIRCUMFERENCE;
extern const float WHEEL_BASE;
extern const float DRIVE_GEAR_RATIO;
extern const float TRACK_WIDTH;
extern const float ROBOT_RADIUS;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
