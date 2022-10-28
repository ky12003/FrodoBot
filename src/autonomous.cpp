#include "vex.h"
#include "autonomous.h"
using namespace vex;

/*----------
MOVEMENT
----------*/
void SetTimeout(int seconds)
{
  AllLeft.setTimeout(seconds, sec);
  AllRight.setTimeout(seconds, sec);
}

void moveForward(int dist, int speed, int timeout)
{
  SetTimeout(timeout);
  AllLeft.spinFor(forward, double (dist/(10.16*M_PI)), rev, double (speed), rpm, false);
  AllRight.spinFor(forward, double (dist/(10.16*M_PI)), rev, double (speed), rpm, true);
  SetTimeout(0);

}

void TurninPlace(int dist, int speed, int timeout) //a postitve number will turn right, a negative number will turn left//
{
  SetTimeout(timeout);
  AllLeft.spinFor(reverse, double (dist/(10.16*M_PI)), rev, double (speed), rpm, false);
  AllRight.spinFor(forward, double (dist/(10.16*M_PI)), rev, double (speed), rpm, true);
  SetTimeout(0);

}

void IntakeAuto(int timeout)
{
  SetTimeout(timeout);
  intake.spin(reverse,100,pct);
  SetTimeout(0);
  intake.stop();
}

void IntakeSpitAuto(int dist, int speed, int timeout)
{
  SetTimeout(timeout);
  intake.spinFor(forward, double (dist), rev, double (speed), rpm, false);
  SetTimeout(0);
}

void catalimit()
{
  
}

void moveForwardPID(int speed) {

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
    AllLeft.spin(forward, speed - modifiedError, pct);
    AllRight.spin(forward, speed + modifiedError, pct);
  }

  // if ((abs(errorPositionLeft) > 5) || (abs(errorPositionRight) > 5)) {
  // }
}