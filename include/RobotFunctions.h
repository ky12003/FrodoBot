#ifndef ROBOT_FUNCTIONS
#define ROBOT_FUNCTIONS

void intakeToggle();
void reverseIntake();

//logical to handle catapult and intake
void catapultLogic();

// to handle the pneumatic expansion system
void doExpansion();

//manual controls for the robot
// void manualWindUp();
// void manualStopThrower();

// roller w/ optical
void spinRollerOpticalBlue();
void spinRollerOpticalRed();

// helper functions for catapult
void windUp();
void shootDisks();

void printSensor();

#endif 