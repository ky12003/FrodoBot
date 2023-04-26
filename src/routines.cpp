#include "vex.h"
#include "routines.h"
#include "Autonomous.h"
#include "GPS.h"

using namespace vex;

/*----------
////////////
// COMPETITION AUTONOMOUS
////////////
-----------*/


/////////
// Helper function for shooting disks
////////
void shootAllDisks() {
  ShootCatapultAuto(4000);            // shoot disks  
  wait(800, msec);                    // buffer
  windCatapultAuton();                // wind the catapult up   
}


/////////
// Routine shooting low goals starting from the roller
////////
void Routine1Auton(vex::color desiredColor) {
  // ------------- Rolling the roller + turn towards basket ------------------
  RollerAuto(desiredColor);           // roll the roller to the desired color
  wait(300, msec);                    // buffer
  moveForward(20, 10, 5000);          // move forward away from the roller
  wait(300, msec);                    // buffer
  InertialTurn('r', 10, 87, 4000);    // turn clockwise towards the basket


  // -------------- Movement towards basket + shoot to low goal --------------
  wait(800, msec);                    // buffer
  moveForwardPID(80);                 // move towards basket to shoot
  waitUntil(pidDone);                 // wait until pid completes
  wait(300, msec);                    // buffer
  controller1.rumble(".");
  shootAllDisks();                    // shoot disks into low goal
  wait(300, msec);                    // buffer


  // --------------   Prep to get disks on rim near basket      --------------
  InertialTurn('r', 15, 177, 5000);   // turn around with back facing the opponent's basket
  wait(300, msec);                    // buffer
  moveForward(-25, 15, 4000);         // move back slightly for positioning
  wait(300, msec);                    // buffer
  InertialTurn('l', 10, 87, 4000);    // face the wall where driver is (for positioning)
  wait(300, msec);                    // buffer
  moveForward(-30, 15, 4000);         // move slightly backwards for positioning
  wait(300, msec);                    // buffer
  InertialTurn('r', 10, 87, 4000);    // face the other wall so that back is facing basket
  wait(300, msec);                    // buffer
  moveForwardPID(-86);               // move backwards towards disks near opponent basket
  waitUntil(pidDone);                 // wait until the pid is done
  wait(300, msec);                    // buffer
  moveForward(-25, 8, 4000, true);   // move backwards torwards the disks while intaking
  wait(500, msec);                    // buffer 


  // --------------   Get first disk on rim + position for 2nd       ----------------
  // StoreDisk(5000, true);              // store a disk in the catapult
  // wait(300, msec);                    // buffer
  moveForward(27, 25, 5000);          // move fowards for the other 2 disks
  wait(300, msec);                    // buffer
  InertialTurn('r', 10, 87, 4000);    // turn 90 degrees clockwise 
  wait(300, msec);                    // buffer
  moveForward(55, 20, 4000);          // move forwards to position for more disks
  wait(300, msec);                    // buffer
  InertialTurn('l', 10, 87, 4000);    // position for other disks
  wait(300, msec);                    // buffer

  // --------------          Get second (last) disk on rim + shoot      ----------------
  moveForward(-25, 8, 4000, true);   // move backwards towards 2nd disk while intaking
  wait(500, msec);                    // buffer      
  IntakeSpitAutoTime(1500, 70);             // store a disk in the catapult
  wait(300, msec);                    // buffer
  moveForwardPID(80);                 // move fowards towards center field to prepare   
  waitUntil(pidDone);                 // wait until pid is done
  wait(500, msec);                    // buffer
  InertialTurn('l', 15, 177, 5000);   // turn around towards low goal to shoot
  wait(300, msec);                    // buffer
  shootAllDisks();                 // shoot disks
  wait(300, msec);                    // buffer 

}


/////////
// Routine starting with intaking disks on the diagonal, shooting low goals, then finally rolling the roller
/////////
void Routine2Auton(vex::color desiredColor) {
  RollerAuto(red);             // roll
  moveForward(20, 10, 5000, false);    // move forward away from the roller
  wait(800, msec);
  TurninPlace(85, 10, 4000); // turn clockwise towards the basket
  wait(800, msec);
  moveForward(60, 15, 3000, false); // go towards the basket
  wait(1000, msec);
  moveForward(45, 10, 3000, false); // go more forwards to prepare for preloads
  wait(800, msec);
  TurninPlace(90, 15, 4000); // turn clockwise for additional preloads
  wait(800, msec);
  moveForward(50, 10, 5000, false); // move forwards towards loading zone
}


void Routine3Auton(vex::color desiredColor) {
  wait(300, msec);
  IntakeSpitAuto(340, 70, 5000); // roll the roller
  moveForward(30, 10, 5000, false);     // move forward away from the roller
  wait(300, msec);
  TurninPlace(50, 15, 4000); // turn clockwise towards the basket
  //TODO: ADD TURN AND SHOOT TO BASKET ON OTHER SIDE.
}



/*----------
////////////
// SKILLS AUTONOMOUS
////////////
-----------*/

//////////
// Skills routine that makes use of match loads to shoot 2 preloads and 2 triple-disk shots and rolls both rollers in the corner
/////////
void Routine1Skills(vex::color desiredColor) {
  // ---------------    Roll the roller + turn to prepare      ----------------
  RollerAuto(desiredColor);             // roll the roller
  wait(300, msec);                      // buffer
  moveForward(13, 10, 5000, false);     // move forward away from the roller
  wait(300, msec);                      // buffer
  InertialTurn('r', 30, 87, 4000);      // Turn clockwise (right) 90 degrees towards the goal
  wait(300, msec);

  // ------------  Move to basket and shoot preloads into high basket  --------
  moveForwardPID(200);                  // go towards the basket to shoot
  waitUntil(pidDone);                   // wait for PID completion
  wait(300, msec);                      // buffer
  InertialTurn('l', 30, 18, 4000);      // turn the bot slightly to the left to face the basket
  wait(300, msec);                      // buffer
  shootAllDisks();                      // shoot all disks into high goal
  wait(300, msec);                      // buffer
  InertialTurn('r', 30, 18, 4000);      // turn back to original position                


  // ------------------- PRELOAD/LOW GOAL PROCEDURE X2 --------------------
  for (int i = 0; i < 2; i++) {
    // ------------- Match-load disk retrieval + turn positioning --------------
    wait(300, msec);                      // buffer
    moveForwardPID(-55);                  // move backwards towards the loading zone
    waitUntil(pidDone);                   // wait for PID completion
    wait(300, msec);                      // buffer
    InertialTurn('r', 30, 87, 4000);      // turn clockwise towards the loading zone
    wait(300, msec);                      // buffer
    moveForward(30, 10, 5000);            // move forwards towards loading zone
    wait(3000, msec);                     // wait for person to load disks
    moveForward(-5, 20, 3000, false);     // move backwards away from the loading zone
    wait(300, msec);                      // buffer
    InertialTurn('l', 30, 87, 4000);      // turn counterclockwise towards goal

    // -----------------        Go to basket + shoot    ------------------------
    wait(300, msec);                      // buffer
    moveForwardPID(55);                   // move forwards towards goal
    waitUntil(pidDone);                   // wait until PID completion
    wait(300, msec);                      // buffer
    InertialTurn('l', 30, 15, 4000);      // turn counterclockwise to face basket in order to shoot
    wait(300, msec);                      // buffer
    shootAllDisks();                      // shoot all disks into high goal
    wait(300, msec);                      // buffer
    InertialTurn('r', 30, 15, 4000);      // turn back to original position
  }

  // -------------------      Get roller         -----------------------
  wait(300, msec);                      // buffer
  moveForwardPID(-175);                 // move backwards to other roller
  waitUntil(pidDone);                   // wait for PID completion
  wait(300, msec);                      // buffer
  InertialTurn('r', 30, 87, 4000);      // turn clockwise to adjust to the roller position
  wait(300, msec);                      // buffer
  moveForward(-5, 35, 6000, false);     // move backwards to adjust to the roller position
  wait(300, msec);                      // buffer
  InertialTurn('l', 30, 87, 4000);      // turn counterclockwise to adjust to the roller position
  wait(300, msec);                      // buffer
  RollerAuto(desiredColor);             // roll the roller
  wait(300, msec);                      // buffer

  // ----------------       Expansion            -----------------------
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

void Routine2Skills(vex::color desiredColor) {
  RollerAuto(red);                 // roll the roller
  wait(200, msec);
  moveForward(13, 10, 5000, false);       // move forward away from the roller
  wait(300, msec);
  InertialTurn('r', 20, 90, 4000); // Turn clockwise (right) 90 degrees towards the goal
  wait(300, msec);
  moveForwardPID(185, false);             // go towards the basket to shoot (OLD: // moveForward(165, 20, 3000);)
  waitUntil(pidDone);
  wait(200, msec);
  InertialTurn('l', 20, 18, 4000); // turn the bot slightly to the left to face the basket
  wait(300, msec);
  windCatapultAuton();             // wind the catapult up
  wait(300, msec);
  ShootCatapultAuto(4000);         // shoot the preload disks into high goal
  wait(300, msec);
  windCatapultAuton();
  wait(300, msec);
  InertialTurn('r', 20, 18, 4000); // turn back to original position
  wait(300, msec);


  // PRELOAD/LOW GOAL PROCEDURE X2
  for (int i = 0; i < 2; i++) {
    wait(300, msec);
    moveForwardPID(-45, false);             // move backwards towards the loading zone (OLD: moveForward(-55, 20, 4000); )
    waitUntil(pidDone);
    wait(200, msec);
    InertialTurn('r', 20, 90, 4000); // turn clockwise towards the loading zone
    wait(300, msec);
    moveForward(30 /*+ (i * 3.5)*/, 10, 5000, false); // move forwards towards loading zone
    wait(3000, msec);
    moveForward(-5, 20, 3000, false);       // move backwards away from the loading zone
    wait(300, msec);
    InertialTurn('l', 20, 90, 4000); // turn counterclockwise towards goal
    wait(300, msec);
    moveForwardPID(45, false);              // move forwards towards goal (OLD: moveForward(53, 15, 4000); )
    waitUntil(pidDone);
    wait(200, msec);
    InertialTurn('l', 20, 25, 4000); // turn counterclockwise to face basket in order to shoot
    wait(300, msec);
    windCatapultAuton(); // wind the catapult up
    wait(300, msec);
    ShootCatapultAuto(4000);    // shoot the preload disks into high goal
    wait(200, msec);
    windCatapultAuton();
    wait(300, msec);
    InertialTurn('r', 20, 25, 4000); // turn back to original position
  }

  wait(300, msec);
  moveForwardPID(-160, true);            // move backwards to other roller (OLD: moveForward(-175, 40, 6000);)
  waitUntil(pidDone);
  wait(200, msec);
  InertialTurn('r', 20, 90, 4000); // turn clockwise to adjust to the roller position
  wait(300, msec);
  moveForward(-5, 35, 6000, false);       // move backwards to adjust to the roller position
  wait(300, msec);
  InertialTurn('l', 20, 90, 4000); // turn counterclockwise to adjust to the roller position
  wait(300, msec);
  RollerAuto(red);                // roll the roller
  wait(300, msec);
  moveForwardPID(40, false);              // move forward for expansion (OLD: moveForward(40, 40, 3000);)
  waitUntil(pidDone);
  wait(200, msec);
  InertialTurn('l', 20, 30, 4000); // turn counterclockwise to get ready for expansion
  wait(300, msec);
  moveForward(-20, 40, 3000, false);      // move slightly backwards for more tiles
  wait(300, msec);
  ExpansionLeft.set(1);            // shoot expansion
}

/*--
TEST AUTONS
--*/
void testAuton() {
  // printf("test");
  // moveForward(50, 30, 3000);
  // RollerAuto(red);
  // wait(500, msec);

  // StoreDisk(4000);
  moveForwardPID(-100);
  // moveForwardPID(-50, true);
  // waitUntil(pidDone);
  // wait(300, msec);
  // RollerAuto(blue);
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