#include "vex.h"
#include "autonomous.h"
using namespace vex;

/*----------
MOVEMENT
----------*/
void SetTimeout(int mSec)
{
  AllLeft.setTimeout(mSec, msec);
  AllRight.setTimeout(mSec, msec);
}

void moveForward(float distanceCM, int speedPct, int timeout)
{
  SetTimeout(timeout);
  AllLeft.setVelocity(speedPct, pct);
  AllRight.setVelocity(speedPct, pct);
  // (GEAR RATIO IS ONE-TO-ONE, so the "distance" would be times 1)
  // AllRight.rotateFor(forward, (distanceCM/WHEEL_CIRCUMFERENCE) * DRIVE_GEAR_RATIO, rev, false);
  AllMotors.rotateFor(forward, (distanceCM/WHEEL_CIRCUMFERENCE) * DRIVE_GEAR_RATIO, rev, true);
  SetTimeout(0);

}

void TurninPlace(int turnDegree, int speedPct, int timeout) //a postitve number will turn right, a negative number will turn left//
{
  SetTimeout(timeout);
  AllLeft.setVelocity(speedPct, pct);
  AllRight.setVelocity(speedPct, pct);

  

  AllLeft.rotateFor(forward, ((ROBOT_RADIUS * (turnDegree* (M_PI/180) ) ) / WHEEL_CIRCUMFERENCE) * DRIVE_GEAR_RATIO  , rev, true);
  AllRight.rotateFor(reverse, ((ROBOT_RADIUS * (turnDegree * (M_PI/180) ) ) / WHEEL_CIRCUMFERENCE) * DRIVE_GEAR_RATIO, rev); 
  SetTimeout(0);

}

void IntakeAuto(int timeout)
{
  SetTimeout(timeout);
  intake.spin(reverse,100,pct);
  SetTimeout(0);
  intake.stop();
}

void IntakeSpitAuto(float turnDegree, int speedPct, int timeout)
{
  SetTimeout(timeout);

  intake.setVelocity(speedPct, pct);

  intake.rotateFor(forward, turnDegree, deg, true);
  SetTimeout(0);
}

void ShootCatapultAuto(int timeout) {
  SetTimeout(timeout);
  while (true) {
    thrower.spin(forward, 100, pct);
    if (thrower.velocity(pct) < 0.5) {
      break;
    }
  }
  thrower.spin(forward, 100, pct);

  SetTimeout(0);
}

// void catapultLogic() {
// controller1.ButtonL2.pressed(windUp);
// catapultBumper.pressed(windBack);
// controller1.ButtonR2.pressed(intakeOn);
// }

// void windBack() {
//   catapult.stop();

// }

// void windUp() {
//   catapult.spin(forward);
// }

void moveForwardPID(int speedPct) {

  int encPositionLeft;
  int encPositionRight;
  int error =0;
  int modifiedError;
  float kp = 0.1;

  AllLeft.resetPosition();
  AllRight.resetPosition();
  // double errorPositionLeft = targetPosition- encPositionLeft;
  // double errorPositionRight = targetPosition - encPositionRight;
  while (true) {
    
    encPositionLeft = AllLeft.position(deg);
    encPositionRight = AllRight.position(deg);
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
    AllLeft.spin(forward, speedPct - modifiedError, pct);
    AllRight.spin(forward, speedPct + modifiedError, pct);
  }

  // if ((abs(errorPositionLeft) > 5) || (abs(errorPositionRight) > 5)) {
  // }
}