#include "vex.h"
#include "routines.h"
#include "Autonomous.h"
#include "GPS.h"

using namespace vex;

//-------------        Helper function for shooting disks      -----------------
void ShootDisks() {
  ShootCatapultAuto(3000);          // Shoot the disk
  wait(300, msec);                  // Buffer
  windCatapultAuton();              // Wind the catapult up for next shot
}

//------------- Helper function for shooting two disks, one at a time -----------
void DoubleDiskShot() {
  ShootDisks();                      // Shoot the 1st disk
  wait(300, msec);                   // Buffer
  IntakeSpitAuto(-2500, 100, 4000);  // Intake the second disk into the catapult
  wait(400, msec);                   // Buffer
  ShootDisks();                      // Shoot the 2nd disk
}

/////////////////////////
//---------------------
// COMP Routine that starts with roller and shoots 3 low goals
//--------------------
/////////////////////////
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

// Routine starting from roller side; ends with shooting into high goal
void Routine2Auton() {
  RollerAuto(blue);                 // roll the roller (*COLOR CHANGES BASED ON SIDE)
  wait(300, msec);                  // buffer
  moveForward(10, 10, 5000);        // move forward away from the roller
  wait(300, msec);                  // buffer
  InertialTurn('r', 15, 42, 3000);  // turn clockwise (right) to get ready to shoot
  wait(300, msec);                  // buffer
  moveForwardPID(360);              // go to the middle of the field to shoot
  waitUntil(pidDone);               // (wait for completion)
  wait(300, msec);                  // buffer
  InertialTurn('l', 15, 87, 4000);  // turn counterclockwise (left) to the basket
  wait(300, msec);                  // buffer
  ShootCatapultAuto(4000);          // shoot disk into high goal
  wait(300, msec);                  // buffer
  DoubleDiskShot();                 // Shoot both disks into the basket
  wait(300, msec);                  // 
}

// Routine starting
void Routine3Auton() {

}

/////////////////////////
//---------------------
// SKILLS Routine that does not use the intake
//--------------------
/////////////////////////
void Routine1Skills() {
  RollerAuto(red);                      // Roll the roller
  wait(300, msec);                      // Buffer
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

/////////////////////////
//---------------------
// SKILLS Routine starting with roller and not using match loads
//--------------------
/////////////////////////
void Routine2Skills() {
  // -------- 1st Roller and 1st 3-disc shot ---------

  // -------- Diagonal disc pickup and 2nd 3-disk shot -------

  // -------- Red basket (3rd) 3-disk shot ------------
}

/////////////////////////
//---------------------
// SKILLS Routine utilizing match loads and intake, safer for using intake
//--------------------
/////////////////////////
void Routine3Skills() {
  // -----------            Preload disk shots (x2)                  ----------------
  // *steps 1-3 on the diagram
  moveForwardPID(60);               // Move forward to prepare for shot
  waitUntil(pidDone);               // Wait for pid do complete
  wait(300, msec);                  // Buffer
  InertialTurn('l', 10, 20, 4000);  // Turn counterclockwise facing the red basket
  wait(300, msec);                  // Buffer
  DoubleDiskShot();                 // Shoot both disks into red basket
  wait(300, msec);                  // Buffer


  // -----------            Go for extra loads + shoot (x3)          ----------------
  // *steps 4-5 on the diagram
  moveForwardPID(-50);               // Move back towards match load area
  waitUntil(pidDone);                // Wait for pid to complete
  wait(3000, msec);                  // Wait for loader to load disks
  moveForward(20, 20, 4000);         // Move away from the match load area
  wait(300, msec);                   // Buffer
  InertialTurn('l', 10, 10, 2000);   // Turn counterclockwise to align to basket
  wait(300, msec);                   // Buffer
  ShootDisks();                      // Shoot disks
  wait(300, msec);                   // Buffer
  InertialTurn('l', 10, 10, 2000);   // Turn clockwise back to original position
  wait(300, msec);                   // Buffer

  // -----------        Backup + alignment to corner disks           ----------------
  // *steps 6-7 on the diagram
  moveForwardPID(-320, true);        // Move back towards corner while activating intake
  waitUntil(pidDone);                // Wait for pid move to compelte
  wait(300, msec);                   // Buffer
  InertialTurn('r', 40, 135, 4000);  // Turn clockwise facing the corner to allign to pick up disks on the diagonal
  wait(300, msec);                   // Buffer


  // -----------    Intake Corner disks + shoot into red goal (x2)   ----------------
  // *steps 8-10 in the diagram
  moveForward(-50, 20, 5000, true);  // Move back towards center while intaking disk
  wait(300, msec);                   // Buffer
  InertialTurn('r', 10, 70, 4000);   // Turn towards red basket to shoot
  wait(300, msec);                   // Buffer
  DoubleDiskShot();                  // Shoot two disks into red basket
  wait(300, msec);                   // Buffer


  // -----------        1st Roller after shooting the two disks       ----------------
  // *steps 11-12 on the diagram
  InertialTurn('r', 20, 100, 4000);  // Turn clockwise so back faces the roller
  wait(300, msec);                   // Buffer
  RollerAuto(red);                   // Roll the roller
  wait(300, msec);                   // Buffer
  moveForward(10, 10, 2000);         // Slight move forward to have space to turn
  wait(300, msec);                   // Buffer
  InertialTurn('r', 40, 160, 4000);  // Turn to wall (clockwise) to get one of the diagonal disks
  wait(300, msec);                   // Buffer
  moveForwardPID(-60, true);         // Move to diagonal disks while intaking
  waitUntil(pidDone);                // Wait until pid drive is compete
  wait(300, msec);                   // Buffer

  // -----------          2-stack disk shoot into blue goal (x2)     ----------------
  // *steps 13-14 on the diagram
  InertialTurn('l', 30, 160, 5000);  // Turn counterclockwise facing the blue basket
  wait(300, msec);                   // Buffer
  DoubleDiskShot();                  // Shoot both disks (THIS IS A SPECIAL CASE, SO CHANGE THIS LATER)
  wait(300, msec);                   // Buffer

  // -----------            2nd Roller + expansion                   ----------------
  // *steps 15-17 on the diagram
  InertialTurn('l', 20, 100, 4000);  // Turn counterclockwise with the back of the bot facing the roller
  wait(300, msec);                   // Buffer
  moveForwardPID(-60);               // Move towards roller
  waitUntil(pidDone);                // Wait for pid move to complete
  wait(300, msec);                   // Buffer
  InertialTurn('l', 10, 10, 3000);   // Turn to face roller
  wait(300, msec);                   // Buffer
  RollerAuto(blue);                  // Roll the roller
  wait(400, msec);                   // Buffer
  moveForward(30, 80, 2000);         // Move forward for expansion
  wait(200, msec);                   // Buffer
  TurninPlace(40, 60, 4000);         // Turn to expand
  wait(200, msec);                   // Buffer
  ExpansionLeft.set(1);              // Do expansion
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