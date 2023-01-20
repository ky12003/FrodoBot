#include "vex.h"
#include "autonomous.h"
#include "routines.h"
#include "GPS.h"
using namespace vex;

/*--
Normal auton routine
--*/

void Routine1Auton() {
  //*currently using placeholder values
  moveForward(-10, 70, 1000);
  wait(200, msec);
  IntakeSpitAuto(200,70,5000); // roll the roller
  moveForward(25, 10, 5000); // move forward away from the roller
  wait(800, msec);
  TurninPlace(90, 15, 4000); // turn clockwise towards the basket
  wait(800, msec);
  moveForward(105, 30, 3000); // go towards the basket to shoot
  ShootCatapultAuto(4000); // shoot the preload disks into low goal
  wait(1000, msec);
  TurninPlace(90, 15, 4000); // turn clockwise for additional preloads
  wait(800, msec);
  moveForward(35, 10, 5000); // move forwards towards loading zone
  wait(800, msec);
 

  // *PRELOAD/LOW GOAL PROCEDURE X3
  // for (int i = 0; i < 3; i++) {
  //   wait(1000, msec);
  //   TurninPlace(90, 15, 4000); // turn clockwise for additional preloads
  //   wait(800, msec);
  //   moveForward(35 + (i*5.5), 10, 5000); // move forwards towards loading zone
  //   wait(2500, msec);
  //   moveForward(-25, 10, 3000); // move backwards away from the loading zone
  //   wait(800, msec);
  //   TurninPlace(-90, 15, 4000); // turn counterclockwise towards goal
  //   controller1.rumble("."); // TEMP NOTICE FOR SHOOTING DISKS
  //   // ShootCatapultAuto(1500) // shoot in low goal
  //   wait(800, msec);
  //   moveForward(-8, 10, 1000); // move slightly backwards to reposition
  // }
  
}

/*--
Skills auton routine
--*/
void Routine1Skills() {
  // *currently using placeholder values

  IntakeSpitAuto(20,600,10000); // roll the roller
  moveForward(30, 80, 1000); // move forward away from the roller
  TurninPlace(25, 80, 1000); // turn clockwise towards the basket
  moveForward(200, 80, 1000); // go towards the basket to shoot
  ShootCatapultAuto(1500); // shoot the preload disks into the basket
  moveForward(1, 1, 1); // move forward to start positioning for the other roller (should be near the basket in the low goal area)
  TurninPlace(25, 1, 1); // turn clockwise (90 deg) to start heading towards the other roller
  moveForward(1, 1, 1); // move fowards towards the other roller
  TurninPlace(25, 1, 1); // turn clockwise (90 deg) towards roller
  moveForward(-1, 1, 1); // move backwards towards the roller
  IntakeSpitAuto(20,600,10); // roll the roller
}

/*--
TEST GPS ROUTINE
--*/
void GPStest() {
  DriveToTargetXY(1, 1, 5, 10);
}



// void moveinBox()
// {
//   ////
//   //a postitve number will turn right, a negative number will turn left//
//   //// 
//   TurninPlace(25, 80, 1000);
//   wait(1000, msec);
//   moveForward(140, 80, 10000);
//   wait(1000, msec);
//   IntakeSpitAuto(20,600,1000);
//   wait(1000, msec);
// }

void spinRoller() {
IntakeSpitAuto(100,20,3);
}