#include "vex.h"
#include "routines.h"
#include "Autonomous.h"
#include "GPS.h"

using namespace vex;

/*--
Normal auton routine
--*/

void Routine1Auton() {
  moveForward(-10, 70, 1000, false);
  wait(200, msec);
  IntakeSpitAuto(130, 50, 5000); // roll the roller
  moveForward(20, 10, 5000, false);    // move forward away from the roller
  wait(800, msec);
  TurninPlace(85, 10, 4000); // turn clockwise towards the basket
  wait(800, msec);
  moveForward(50, 15, 3000, false); // go towards the basket to shoot
  ShootCatapultAuto(6000);   // shoot the preload disks into low goal
  wait(1000, msec);
  moveForward(45, 10, 3000, false); // go more forwards to prepare for preloads
  wait(800, msec);
  TurninPlace(90, 15, 4000); // turn clockwise for additional preloads
  wait(800, msec);
  moveForward(50, 10, 5000, false); // move forwards towards loading zone

}

void Routine3Auton() {
  wait(300, msec);
  IntakeSpitAuto(340, 70, 5000); // roll the roller
  moveForward(30, 10, 5000, false);     // move forward away from the roller
  wait(300, msec);
  TurninPlace(50, 15, 4000); // turn clockwise towards the basket
  //TODO: ADD TURN AND SHOOT TO BASKET ON OTHER SIDE.
}

// Routine starting from roller side; ends with shooting into high goal
void Routine2Auton() {
  RollerAuto(blue);                 // roll the roller
  wait(300, msec);                  // buffer
  moveForward(6, 10, 5000);        // move forward away from the roller
  wait(300, msec);                  // buffer
  InertialTurn('r', 15, 42, 3000);  // turn clockwise (right) to get ready to shoot
  wait(300, msec);                  // buffer
  moveForwardPID(310);              // go to the middle of the field to shoot
  waitUntil(pidDone);               // (wait for completion)
  wait(300, msec);                  // buffer
  InertialTurn('l', 15, 82, 4000);  // turn counterclockwise (left) to the basket
  wait(300, msec);                  // buffer
  moveForward(-24, 10, 4000);       // move slightly backwards to shoot
  wait(300, msec);                  // buffer
  ShootCatapultAuto(4000);          // shoot disk into high goal
  wait(300, msec);                  // buffer
  windCatapultAuton();              // wind the catapult up
  wait(300, msec);                  // buffer
  IntakeSpitAuto(2000, 70, 4000);   // intake the other preload disk
  wait(2000, msec);                  // buffer
  ShootCatapultAuto(4000);          // shoot disk into high goal
}

/*--
Skills auton routine
--*/

void Routine1Skills() {
  moveForward(-10, 10, 1000, false);
  wait(300, msec);
  IntakeSpitAuto(340, 70, 5000); // roll the roller
  moveForward(13, 10, 5000, false);     // move forward away from the roller
  wait(300, msec);
  InertialTurn('r', 30, 87, 4000); // Turn clockwise (right) 90 degrees towards the goal
  wait(300, msec);
  moveForward(165, 20, 3000, false); // go towards the basket to shoot
  wait(300, msec);
  InertialTurn('l', 30, 18, 4000); // turn the bot slightly to the left to face the basket
  wait(300, msec);
  windCatapultAuton(); // wind the catapult up
  wait(300, msec);
  ShootCatapultAuto(4000);    // shoot the preload disks into high goal
  wait(300, msec);
  windCatapultAuton();
  wait(300, msec);
  InertialTurn('r', 30, 18, 4000); // turn back to original position
  wait(300, msec);


  // PRELOAD/LOW GOAL PROCEDURE X2
  for (int i = 0; i < 2; i++) {
    wait(300, msec);
    moveForward(-55, 20, 4000, false); // move backwards towards the loading zone
    wait(300, msec);
    InertialTurn('r', 30, 87, 4000); // turn clockwise towards the loading zone
    wait(300, msec);
    moveForward(30 /*+ (i * 3.5)*/, 10, 5000, false); // move forwards towards loading zone
    wait(3000, msec);
    moveForward(-5, 20, 3000, false); // move backwards away from the loading zone
    wait(300, msec);
    InertialTurn('l', 30, 87, 4000); // turn counterclockwise towards goal
    wait(300, msec);
    moveForward(53, 15, 4000, false); // move forwards towards goal
    wait(300, msec);
    InertialTurn('l', 30, 25, 4000); // turn counterclockwise to face basket in order to shoot
    wait(300, msec);
    windCatapultAuton(); // wind the catapult up
    wait(300, msec);
    ShootCatapultAuto(4000);    // shoot the preload disks into high goal
    wait(200, msec);
    windCatapultAuton();
    wait(300, msec);
    InertialTurn('r', 30, 25, 4000); // turn back to original position
  }

  wait(300, msec);
  moveForward(-175, 40, 6000, false); // move backwards to other roller
  wait(300, msec);
  InertialTurn('r', 30, 87, 4000);  // turn clockwise to adjust to the roller position
  wait(300, msec);
  moveForward(-5, 35, 6000, false); // move backwards to adjust to the roller position
  wait(300, msec);
  InertialTurn('l', 30, 87, 4000);  // turn counterclockwise to adjust to the roller position
  wait(300, msec);
  moveForward(-52, 15, 6000, false); // move backwards torwards the roller
  wait(300, msec);
  IntakeSpitAuto(400, 70, 5000); // roll the roller
  wait(300, msec);
  moveForward(40, 40, 3000, false); // move forward for expansion
  wait(300, msec);
  InertialTurn('l', 30, 30, 4000); // turn counterclockwise to get ready for expansion
  wait(300, msec);
  moveForward(-20, 40, 3000, false); // move slightly backwards for more tiles
  wait(300, msec);
  ExpansionLeft.set(1); // shoot expansion
  // wait(200, msec);
  // moveForward(25, 60, 2000); // move forward slightly to get more tiles
}

void Routine2Skills() {
  // -------- 1st Roller and 1st 3-disc shot ---------

  // -------- Diagonal disc pickup and 2nd 3-disk shot -------

  // -------- Red basket (3rd) 3-disk shot ------------
}

/*--
TEST AUTONS
--*/
void testAuton() {
  // printf("test");
  // moveForward(50, 30, 3000);
  // RollerAuto(red);
  // wait(500, msec);

  // moveForwardPID(-50, true);
  // waitUntil(pidDone);
  // wait(300, msec);
  // InertialTurn('r', 20, 90, 6000);
  RollerAuto(blue);
  // moveForwardPID(60.0, fwd);
  // wait(1000, msec);
  // InertialTurn('r', 20, 90, 3000);
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