#include "vex.h"
#include "routines.h"
#include "Autonomous.h"
#include "GPS.h"

using namespace vex;

/*--
Normal auton routine
--*/

void Routine1Auton() {
  moveForward(-10, 70, 1000);
  wait(200, msec);
  IntakeSpitAuto(130, 50, 5000); // roll the roller
  moveForward(20, 10, 5000);    // move forward away from the roller
  wait(800, msec);
  TurninPlace(85, 10, 4000); // turn clockwise towards the basket
  wait(800, msec);
  moveForward(50, 15, 3000); // go towards the basket to shoot
  ShootCatapultAuto(6000);   // shoot the preload disks into low goal
  wait(1000, msec);
  moveForward(45, 10, 3000); // go more forwards to prepare for preloads
  wait(800, msec);
  TurninPlace(90, 15, 4000); // turn clockwise for additional preloads
  wait(800, msec);
  moveForward(50, 10, 5000); // move forwards towards loading zone

}

void Routine3Auton() {
  wait(300, msec);
  IntakeSpitAuto(340, 70, 5000); // roll the roller
  moveForward(30, 10, 5000);     // move forward away from the roller
  wait(300, msec);
  TurninPlace(50, 15, 4000); // turn clockwise towards the basket
  //TODO: ADD TURN AND SHOOT TO BASKET ON OTHER SIDE.
}

void Routine2Auton() {
moveForward(-10, 70, 1000);
  wait(200, msec);
  IntakeSpitAuto(130, 50, 5000); // roll the roller
  moveForward(20, 10, 5000);    // move forward away from the roller
  wait(800, msec);
  TurninPlace(85, 10, 4000); // turn clockwise towards the basket
  wait(800, msec);
  moveForward(60, 15, 3000); // go towards the basket
  wait(1000, msec);
  moveForward(45, 10, 3000); // go more forwards to prepare for preloads
  wait(800, msec);
  TurninPlace(90, 15, 4000); // turn clockwise for additional preloads
  wait(800, msec);
  moveForward(50, 10, 5000); // move forwards towards loading zone
}

/*--
Skills auton routine
--*/

void Routine1Skills() {
  moveForward(-10, 10, 1000);
  wait(300, msec);
  IntakeSpitAuto(340, 70, 5000); // roll the roller
  moveForward(10, 10, 5000);     // move forward away from the roller
  wait(300, msec);
  TurninPlace(85, 15, 4000); // turn clockwise towards the basket
  wait(300, msec);
  moveForward(165, 20, 3000); // go towards the basket to shoot
  wait(300, msec);
  TurninPlace(-18, 30, 3000); // turn to face basket
  wait(300, msec);
  windCatapultAuton();
  wait(300, msec);
  ShootCatapultAuto(4000);    // shoot the preload disks into high goal
  wait(300, msec);
  windCatapultAuton();
  wait(300, msec);
  TurninPlace(18, 30, 3000); // turn back to original position
  wait(300, msec);


  // PRELOAD/LOW GOAL PROCEDURE X2
  for (int i = 0; i < 2; i++) {
    wait(300, msec);
    moveForward(-55, 20, 4000); // move backwards towards the loading zone
    wait(300, msec);
    TurninPlace(88, 15, 4000); // turn clockwise for additional preloads
    wait(300, msec);
    moveForward(30 /*+ (i * 3.5)*/, 10, 5000); // move forwards towards loading zone
    wait(3000, msec);
    moveForward(-5, 20, 3000); // move backwards away from the loading zone
    wait(300, msec);
    TurninPlace(-90, 15, 4000); // turn counterclockwise towards goal
    wait(300, msec);
    moveForward(53, 15, 4000); // move forwards towards goal
    wait(300, msec);
    TurninPlace(-25, 30, 3000); // turn to face basket
    wait(300, msec);
    windCatapultAuton();
    wait(300, msec);
    ShootCatapultAuto(4000);    // shoot the preload disks into high goal
    wait(200, msec);
    windCatapultAuton();
    wait(300, msec);
    TurninPlace(24, 30, 3000); // turn back to original position
  }

  wait(300, msec);
  TurninPlace(-5, 30, 2000);
  wait(300, msec);
  moveForward(-175, 40, 6000); // move backwards to other roller
  wait(300, msec);
  TurninPlace(90, 15, 4000); // turn clockwise to adjust to the roller position
  wait(300, msec);
  moveForward(-5, 35, 6000); // move backwards to adjust to the roller position
  wait(300, msec);
  TurninPlace(-90, 15, 4000); // turn counterclockwise to adjust to the roller position
  wait(300, msec);
  moveForward(-52, 15, 6000); // move backwards torwards the roller
  wait(300, msec);
  IntakeSpitAuto(400, 70, 5000); // roll the roller
  wait(300, msec);
  moveForward(40, 40, 3000); // move forward for expansion
  TurninPlace(-70, 50, 3000); // turn to get the tiles
  ExpansionLeft.set(1); // shoot expansion
  // wait(200, msec);
  // moveForward(25, 60, 2000); // move forward slightly to get more tiles
}

void Routine2Skills() {
  moveForward(30, 40, 4000); // move forward towards the basket
  wait(300, msec);
  TurninPlace(-25, 8, 3000); // turn to face basket
  wait(300, msec);
  windCatapultAuton();
  wait(300, msec);
  ShootCatapultAuto(4000);    // shoot the preload disks into high goal
  wait(200, msec);
  windCatapultAuton();
  TurninPlace(20, 8, 3000); // turn back to original position

  for (int i = 0; i < 4; i++) {
    wait(200, msec);
    moveForward(-57 - (i*0.5), 20, 4000); // move backwards towards the loading zone
    wait(200, msec);
    TurninPlace(88, 15, 4000); // turn clockwise for additional preloads
    wait(200, msec);
    moveForward(30 /*+ (i * 3.5)*/, 10, 5000); // move forwards towards loading zone
    wait(3000, msec);
    moveForward(-5, 20, 3000); // move backwards away from the loading zone
    wait(200, msec);
    TurninPlace(-90, 15, 4000); // turn counterclockwise towards goal
    wait(200, msec);
    moveForward(53, 15, 4000); // move forwards towards goal
    wait(200, msec);
    TurninPlace(-25, 30, 3000); // turn to face basket
    wait(200, msec);
    windCatapultAuton();
    wait(200, msec);
    ShootCatapultAuto(4000);    // shoot the preload disks into high goal
    wait(200, msec);
    windCatapultAuton();
    wait(200, msec);
    TurninPlace(20, 30, 3000); // turn back to original position
  }
}

/*--
TEST AUTONS
--*/
void testAuton() {
  // printf("test");
  InertialTurn('r', 40, 90, 6000);
}

void GPStest() { DriveToTargetXY(1, 1, 5, 10); }

// void moveinBox()
// {
//   ////
//   //a postitve number will turn right, a negative number will turn left//
//   ////
//   TurninPlace(30, 80, 1000);
//   wait(1000, msec);
//   moveForward(140, 80, 10000);
//   wait(1000, msec);
//   IntakeSpitAuto(20,600,1000);
//   wait(1000, msec);
// }

void spinRoller() { IntakeSpitAuto(100, 20, 3); }