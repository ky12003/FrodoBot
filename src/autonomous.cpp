#include "vex.h"
#include "autonomous.h"
using namespace vex;

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