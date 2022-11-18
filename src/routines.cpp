#include "vex.h"
#include "autonomous.h"
#include "routines.h"
using namespace vex;

void moveinBox()
{
  ////
  //a postitve number will turn right, a negative number will turn left//
  //// 
  TurninPlace(25, 80, 1);
  wait(1000, msec);
  moveForward(140, 80, 10);
  wait(1000, msec);
  IntakeSpitAuto(20,600,10);
  wait(1000, msec);
}

void spinRoller() {
IntakeSpitAuto(100,20,3);
}