#include "vex.h"
#include "autonomous.h"
#include "routines.h"
using namespace vex;

void moveinBox()
{
  ////
  // 
  ////
  moveForward(60,60,10);
  wait(1000, msec);
  TurninPlace(-19,60,1);
  wait(1000, msec);
  TurninPlace(-19,60,1);
  wait(1000, msec);
  moveForward(60,60,10);
  wait(1000, msec);
  TurninPlace(19,60,1);
  wait(1000, msec);
  moveForward(60,60,10);

}