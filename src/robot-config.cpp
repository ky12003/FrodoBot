#include "vex.h"
#include "robot-config.h"
using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller controller1(primary);

//drivetrain motors (all blue motors)
motor left1(PORT3,ratio6_1, false);
motor left2(PORT4,ratio6_1, false);
motor left3(PORT5,ratio6_1, false);

motor right1(PORT6,ratio6_1, true);
motor right2(PORT7,ratio6_1, true);
motor right3(PORT8,ratio6_1, true);


//intake motor (green motor) also serves as our roller
motor intake(PORT15,ratio18_1,true);

//catapult motor (red motor)
motor thrower(PORT9,ratio36_1,false);

//motor groups 
motor_group AllLeft(left1, left2, left3);
motor_group AllRight(right1, right2, right3);
motor_group AllMotors(left1, left2, left3, right1, right2, right3);


// GPS
gps DrivetrainGPS = gps(PORT10, 118, 10, mm, 90); //port, x, y, units, angle offset

smartdrive Drivetrain = smartdrive(AllLeft, AllRight, DrivetrainGPS, 319.19, 265, 255, mm, 1);
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//since the encoder has two wires, it needs to be defined by two ports
encoder encoderTop = encoder(Brain.ThreeWirePort.A);
encoder encoderBottom = encoder(Brain.ThreeWirePort.B);
encoder cataswitch = encoder(Brain.ThreeWirePort.H);

// CONSTANTS
const float WHEEL_CIRCUMFERENCE = 6.72*(3.1415926535);
const float WHEEL_BASE = 26.5;
const float DRIVE_GEAR_RATIO = 1;
const float TRACK_WIDTH = 7.5;
const float ROBOT_RADIUS = sqrtf( powf( (TRACK_WIDTH/2), 2) + powf( (WHEEL_BASE/2), 2) );


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  Brain.setTimer(0, msec);
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain GPS
  wait(200, msec);
  DrivetrainGPS.calibrate();
  Brain.Screen.print("Calibrating GPS for Drivetrain");
  // wait for the GPS calibration process to finish
  while (DrivetrainGPS.isCalibrating()) {
    wait(25, msec);
  }

  //Set Drivetrain Velocity
  Drivetrain.setHeading(DrivetrainGPS.heading(), degrees);

  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}