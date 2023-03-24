#include "vex.h"
#include "RobotFunctions.h"
#include "robot-config.h"

#include <string>

#include <iostream>
using namespace vex;

bool intaking = false;
bool intakePosition = false;
bool catapultWind = true;


/*-----------
CATAPULT
------------*/
void catapultLogic() {
  if (catapultWind) {
    windUp();
  }

// roller optical code


  // controller1.ButtonL1.pressed(manualWindUp);
  // controller1.ButtonL2.released(manualStopThrower);
  controller1.ButtonL2.pressed(shootDisks);
  controller1.ButtonR1.pressed(intakeToggle);

  // intake logic
}

void manualWindUp() { thrower.spin(reverse, 100, pct); }

void manualStopThrower() { thrower.stop(); }

void windUp() {

  if (!catapultLimit.pressing()) {
    thrower.spin(reverse, 100, pct);
  } else {
    catapultWind = !catapultWind;
    thrower.stop();
  }
}

void shootDisks() {
  // thrower.setTimeout(800, msec);
  thrower.spinFor(reverse, 800, msec);
  // thrower.setTimeout(0, msec);
  catapultWind = true;
  // prevValue = catapultLimit.value();
}


/*-----------
INTAKE
------------*/

void reverseIntake() { intakePosition = !intakePosition; }

bool doIntakeOut = false;
bool doIntakeIn = false;
bool intakeToggleBuffering = false;
void intakeToggle() {
  if (controller1.ButtonR1.pressing()) {
    if (!intakeToggleBuffering) {

      intakeToggleBuffering = true;
      doIntakeOut = !doIntakeOut;
      doIntakeIn = false;
      if (doIntakeOut) {
        controller1.rumble("-");
      } else {
        controller1.rumble("..");
      }
    }
  } else if (controller1.ButtonR2.pressing()) {
    if (!intakeToggleBuffering) {
      intakeToggleBuffering = true;
      doIntakeIn = !doIntakeIn;
      doIntakeOut = false;
      if (doIntakeIn) {
        controller1.rumble(".");
      } else {
        controller1.rumble("..");
      }
    }
  } else {
    // controller1.rumble(".");
    intakeToggleBuffering = false;
  }

  if (doIntakeOut) {
    intake.spin(fwd, 100, pct);
  } else if (doIntakeIn) {
    intake.spin(directionType::rev, 100, pct);
  } else {
    intake.stop();
  }
}

void spinRollerOpticalBlue() {
  
  if (controller1.ButtonL1.pressing()) {
    OpticalSensor.setLightPower(100, pct);
    do // is going to do 
    {
        intake.spin(fwd, 30, pct); //fwd is going to spin intake roller if the top statement is true
    }
    while (OpticalSensor.color() == blue); // while the 2nd statement is true it is going to changes to opposite color, blue = red, red = blue
    
    intake.stop();// this will stop the roller if the if statement is true and has changed correctly to the opposite color 
    OpticalSensor.setLightPower(0, pct);
  } else if (!doIntakeIn && !doIntakeOut) {
    intake.stop();
    OpticalSensor.setLightPower(0, pct);
  }
  
}

void spinRollerOpticalRed() {
  if (controller1.ButtonL1.pressing()) {
    OpticalSensor.setLightPower(100, pct);
    do // is going to do 
    {
        intake.spin(fwd, 30, pct); //fwd is going to spin intake roller if the top statement is true
    }
    while (OpticalSensor.color() == red); // while the 2nd statement is true it is going to changes to opposite color, blue = red, red = blue
    
    intake.stop();// this will stop the roller if the if statement is true and has changed correctly to the opposite color 
    OpticalSensor.setLightPower(0, pct);
  } else if (!doIntakeIn && !doIntakeOut) {
    intake.stop();
    OpticalSensor.setLightPower(0, pct);
  }
}

/*-----------
EXPANSION
------------*/
// function that is called back to do tasks
void excecuteExpansion() {
  ExpansionLeft.set(1); // activate the pneumatic to activate expansion.
}

// function called into main.cpp that uses a callback.
void doExpansion() {
  controller1.ButtonA.pressed(excecuteExpansion);
}


