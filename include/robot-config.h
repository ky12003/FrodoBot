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

//catapult motor
extern motor thrower;
extern limit catapultBumper;

//motor groups
extern motor_group AllLeft;
extern motor_group AllRight;
extern motor_group AllMotors;


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
