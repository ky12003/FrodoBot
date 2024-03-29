#ifndef ROBOTCONF_H
#define ROBOTCONF_H

using namespace vex;

//control device setup
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
extern optical rollerOptical;

//catapult motor
extern motor thrower;
extern limit catapultLimit;
extern optical OpticalSensor;
// extern bumper catapultBumper;
// extern sonar throwerSonar;

//motor groups
extern motor_group AllLeft;
extern motor_group AllRight;
extern motor_group AllMotors;


//motor encoders
// extern encoder encoder1;
// extern encoder encoder2;
// extern encoder cataswitch;

// pneumatics
extern digital_out ExpansionLeft;
extern digital_out ExpansionRight;

// GPS
extern gps DrivetrainGPS;
long map(long x, long in_min, long in_max, long out_min, long out_max);

// sonar
extern sonar SonarSensor;

// Inertial
extern inertial Inertial1; // Under the catapult near the front of the bot
// extern inertial Inertial2; // 

// constants
extern const float WHEEL_CIRCUMFERENCE;
extern const float WHEEL_BASE;
extern const float DRIVE_GEAR_RATIO;
extern const float TRACK_WIDTH;
extern const float ROBOT_RADIUS;

extern const float redMIN;
extern const float redMAX;
extern const float blueMIN;
extern const float blueMAX;

extern const float diskBoundMAX;
extern const float diskBoundMIN;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);

#endif