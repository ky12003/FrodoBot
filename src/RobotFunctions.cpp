#include "vex.h"
#include "RobotFunctions.h"
#include "DrivingFunctions.h"
#include "robot-config.h"
#include "helper-functions.h"

#include <string>

#include <iostream>
using namespace vex;

bool intaking = false;
bool intakePosition = false;
bool catapultWind = true;
bool doRollerSpin = false;

double intakeSpeed = 70;

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
/////////////
INTAKE
/////////////
------------*/

//////////////
// Helper function(s) to change the intake speed
//////////////
bool bufferSpeedIntake = false;
// mini function to lower speed
void lowerIntakeSpeed() { ; bufferSpeedIntake = !bufferSpeedIntake;}

// mini function to raise speed
void raiseIntakeSpeed() {  bufferSpeedIntake = !bufferSpeedIntake;}

// MAIN HELPER FUNCTION
void changeIntakeSpeed() {
  printf("TEST: %f\n", intakeSpeed);
  if (controller1.ButtonRight.pressing()) {
    if (!bufferSpeedIntake) {
      intakeSpeed = intakeSpeed + 10;
      bufferSpeedIntake = !bufferSpeedIntake;
    }
    
  } 
  else if (controller1.ButtonLeft.pressing()) 
  {
    if (!bufferSpeedIntake) {
      intakeSpeed = intakeSpeed - 10;
      bufferSpeedIntake = !bufferSpeedIntake;
    }
  }
  else 
  {
    bufferSpeedIntake = false;
  }
  
}

void reverseIntake() { intakePosition = !intakePosition; }

//////////////
// Function for toggling the intake
//////////////
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
    printf("A\n");
    intake.spin(fwd, intakeSpeed, pct);
  } else if (doIntakeIn) {
    printf("B\n");
    intake.spin(directionType::rev, intakeSpeed, pct);
  } else if (!doRollerSpin){
    printf("C\n");
    intake.stop();
  }
}



/////////
// Roller spin functions (for red roller)
////////
void spinRollerOptical(vex::color desiredColor) {
  // ASSUMES OPTICAL IS ATTACHED UNDER THE ROLLER
    printf("TEST: %i", diskInIntake());
  OpticalSensor.setLightPower(100, pct);  // keep light for optical sensor on

  // only check the optical sensor's detected color when it is near the roller
  if (OpticalSensor.isNearObject()) {

    // if the optical sensor detects the desired color:
    if (isColor(desiredColor, OpticalSensor.hue())) 
    {
      // toggle the roller
      doRollerSpin = true;
    } 
    // otherwise (the desired color is now facing upwards, so it is not detected anymore)
    else 
    {
      // untoggle the roller
      doRollerSpin = false;
    }
  } 
  // if the robot is NOT near the roller
  else 
  {
    // don't toggle the roller
    doRollerSpin = false;
  }

  // if the roller toggle is ON, AND the other toggles for the intake are not on
  if (doRollerSpin && !doIntakeIn && !doIntakeOut) 
  {
    // keep the roller spinning
    intake.spin(fwd, 30, pct); 
  } 
  // if the roller toggle is OFF, AND the other toggles for the intake are not on
  else if (!doRollerSpin && !doIntakeIn && !doIntakeOut) 
  {
    // stop the roller
    intake.stop(); 
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


