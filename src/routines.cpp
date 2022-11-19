#include "vex.h"
#include "Routines.h"
#include "Autonomous.h"

void redStart() {
moveForward(-25,50,2);
spinRoller();
moveForward(10,25,2);
}