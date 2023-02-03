#include "vex.h"
#include "routines.h"
#include "Autonomous.h"
#include "GPS.h"

using namespace vex;

/*--
Normal auton routine
--*/

void Routine1Auton() {
  //*currently using placeholder values
  moveForward(-10, 70, 1000);
  wait(200, msec);
  IntakeSpitAuto(100, 50, 5000); // roll the roller
  moveForward(30, 10, 5000);    // move forward away from the roller
  wait(800, msec);
  TurninPlace(85, 10, 4000); // turn clockwise towards the basket
  wait(800, msec);
  moveForward(60, 15, 3000); // go towards the basket to shoot
  ShootCatapultAuto(4000);   // shoot the preload disks into low goal
  wait(1000, msec);
  moveForward(40, 10, 3000); // go more forwards to prepare for preloads
  wait(800, msec);
  TurninPlace(85, 15, 4000); // turn clockwise for additional preloads
  wait(800, msec);
  moveForward(50, 10, 5000); // move forwards towards loading zone
}
void Routine1Skills() {
  // currently using placeholder values
  moveForward(-10, 70, 1000);
  wait(200, msec);
  IntakeSpitAuto(240, 70, 5000); // roll the roller
  moveForward(20, 10, 5000);     // move forward away from the roller
  wait(500, msec);
  TurninPlace(90, 15, 4000); // turn clockwise towards the basket
  wait(500, msec);
  moveForward(140, 30, 3000); // go towards the basket to shoot
  ShootCatapultAuto(4000);    // shoot the preload disks into high goal

  // PRELOAD/LOW GOAL PROCEDURE X2
  for (int i = 0; i < 2; i++) {
    wait(500, msec);
    moveForward(-35, 10, 4000); // move backwards towards the loading zone
    wait(500, msec);
    TurninPlace(90, 15, 4000); // turn clockwise for additional preloads
    wait(500, msec);
    moveForward(35 + (i * 5.5), 10, 5000); // move forwards towards loading zone
    wait(3000, msec);
    moveForward(-15, 10, 3000); // move backwards away from the loading zone
    wait(500, msec);
    TurninPlace(-90, 15, 4000); // turn counterclockwise towards goal
    wait(500, msec);
    moveForward(26, 15, 4000); // move forwards towards goal
    wait(500, msec);
    ShootCatapultAuto(3500); // shoot disks into high goal
    wait(500, msec);
  }

  moveForward(-145, 15, 6000); // move backwards to other roller
  wait(400, msec);
  TurninPlace(90, 15, 4000); // turn clockwiseto adjust to the roller position
  wait(400, msec);
  moveForward(-5, 15, 6000); // move backwards to adjust to the roller position
  wait(400, msec);
  TurninPlace(-90, 15,
              4000); // turn counterclockwise to adjust to the roller position
  wait(400, msec);
  moveForward(-73, 15, 6000); // move backwards torwards the roller
  wait(400, msec);
  IntakeSpitAuto(240, 70, 5000); // roll the roller

  moveForward(40, 40, 3000); // move forward for expansion
  TurninPlace(70, 50, 3000); // turn to get the tiles
}

void Routine2Auton() {
  //*currently using placeholder values
  moveForward(-10, 70, 1000);
  wait(200, msec);
  IntakeSpitAuto(45, 50, 5000); // roll the roller
  moveForward(20, 10, 5000);    // move forward away from the roller
  wait(800, msec);
  TurninPlace(85, 10, 4000); // turn clockwise towards the basket
  wait(800, msec);
  moveForward(70, 15, 3000); // go towards the basket to shoot
  wait(800, msec);
  ShootCatapultAuto(4000);   // shoot the preload disks into low goal
  wait(800, msec);
  TurninPlace(85, 10, 4000); // turn clockwise towards the basket
  wait(800, msec);
  moveForward(40, 20, 3000); // go towards the basket to shoot
  wait(800, msec);
  // IntakeSpitAutoTime(10000,100,5000);
  // wait(800, msec);
  intake.spin(reverse, 100, pct);
  moveForward(-80, 10, 3000); // go towards the basket to shoot
  intake.stop();
  wait(800, msec);
  // ShootCatapultAuto(4000);   // shoot the preload disks into low goal
  // TurninPlace(85, 10, 4000); // turn clockwise towards the basket
  // moveForward(40, 20, 3000); // go towards the basket to shoot

  // wait(1000, msec);
  // moveForward(-80, 10, 3000); // go more forwards to prepare for preloads
  // wait(800, msec);
  // TurninPlace(85, 15, 4000); // turn clockwise for additional preloads
  // wait(800, msec);
  // moveForward(50, 10, 5000); // move forwards towards loading zone
  // wait(800, msec);
}

/*--
Skills auton routine
--*/


/*--
TEST GPS ROUTINE
--*/
void GPStest() { DriveToTargetXY(1, 1, 5, 10); }

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

void spinRoller() { IntakeSpitAuto(100, 20, 3); }