#include "vex.h"
#include "Autonomous.h"

void setMotorTimeout(int timeSeconds){

  leftWheels.setTimeout(timeSeconds, sec);
  rightWheels.setTimeout(timeSeconds, sec);
}

void spinRoller() {
  setMotorTimeout(2);
  intakeMotor.spin(reverse,100,pct);
  wait(750, msec);
  intakeMotor.stop();
  
}

void moveForward(float distanceCM, int speedPCT, int timeSec){
  setMotorTimeout(timeSec);

//public bool vex::motor::spinFor(directionType dir, double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true)

  leftWheels.spinFor(fwd, double(distanceCM/(10.16 * M_PI)), rev, double(speedPCT), velocityUnits::pct, false);
  rightWheels.spinFor(fwd, double(distanceCM/(10.16 * M_PI)), rev, double(speedPCT), velocityUnits::pct, false);

  setMotorTimeout(0);
}


void moveForwardPID(int speed) {

  int encPositionLeft;
  int encPositionRight;
  int error =0;
  int modifiedError;
  float kp = 0.1;

  leftWheels.resetPosition();
  rightWheels.resetPosition();
  // double errorPositionLeft = targetPosition- encPositionLeft;
  // double errorPositionRight = targetPosition - encPositionRight;
  while (true) {
    
    encPositionLeft = leftWheels.position(deg);
    encPositionRight = rightWheels.position(deg);
    error = encPositionLeft - encPositionRight;
    modifiedError = int (kp*error);
    printf("%d %d \n", encPositionLeft, encPositionRight);
    wait(50,msec);

if (error > 100) {
  error = 100;
}
else if(error < -100){
  error = -100;
}
    leftWheels.spin(forward, speed - modifiedError, pct);
    rightWheels.spin(forward, speed + modifiedError, pct);
  }

  // if ((abs(errorPositionLeft) > 5) || (abs(errorPositionRight) > 5)) {
  // }
}

// void moveForwardPID() {

//   double targetVelocity = 25;
//   double encVelocityLeft = leftWheels.velocity(pct);
//   double encVelocityRight = rightWheels.velocity(pct);
//   double errorVelocityLeft = targetVelocity - encVelocityLeft;
//   double errorVelocityRight = targetVelocity - encVelocityRight;

// if ((abs(errorVelocityLeft) > 5) || (abs(errorVelocityRight) > 5)) {
//    leftWheels.spin(forward, encVelocityLeft + errorVelocityLeft, pct);
//    rightWheels.spin(forward, encVelocityRight + errorVelocityRight, pct);
// }

// }