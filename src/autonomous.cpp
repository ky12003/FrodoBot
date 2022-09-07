#include "vex.h"
#include "autonomous.h"
using namespace vex;

void SetTimeout(int seconds)
{
  AllLeft.setTimeout(seconds, sec);
  AllRight.setTimeout(seconds, sec);
}

void moveFoward(int dist, int speed, int timeout)
{
  SetTimeout(timeout);
  AllLeft.spinFor(forward, double (dist), rev, double (speed), rpm, false);
  AllRight.spinFor(forward, double (dist), rev, double (speed), rpm, true);
  SetTimeout(0);

}

void TurninPlace(int dist, int speed, int timeout)
{
  SetTimeout(timeout);
  AllLeft.spinFor(reverse, double (dist), rev, double (speed), rpm, false);
  AllRight.spinFor(forward, double (dist), rev, double (speed), rpm, true);
  SetTimeout(0);
}