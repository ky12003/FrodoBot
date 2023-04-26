#include "vex.h"
#include "Autonomous.h"
#include "helper-functions.h"
// #include <string>


//--------- Toggle variables ----------
bool pidDone = false;
bool doIntake = false;

/*----------
/////////////////////

MOVEMENT

////////////////////
----------*/

////////
// Set tmeout for both motors
////////
void SetTimeout(int mSec) {
  AllLeft.setTimeout(mSec, msec);
  AllRight.setTimeout(mSec, msec);
}

// double velocityRightAdjust = 0;
// double velocityLeftAdjust = 0;

////////
// (w/brute force) move forwards or backwards depending on input (positive value: forwards, negative value: backwards)
////////
void moveForward(float distanceCM, int speedPct, int timeout, bool enableIntakeREG) {
  // SetTimeout(timeout);
  AllLeft.setVelocity(speedPct, pct);
  AllRight.setVelocity(speedPct, pct);
  // (GEAR RATIO IS ONE-TO-ONE, so the "distance" would be times 1)
  // AllRight.rotateFor(forward, (distanceCM/WHEEL_CIRCUMFERENCE) *
  // DRIVE_GEAR_RATIO, rev, false);
  double distanceToTravel = (distanceCM / WHEEL_CIRCUMFERENCE) * DRIVE_GEAR_RATIO;

  if (enableIntakeREG) {
    intake.setTimeout(timeout, msec);
    intake.spin(directionType::rev, 70, pct);
  }
  AllMotors.setTimeout(timeout, msec);


  AllMotors.rotateFor(forward, distanceToTravel, rev, true);
  
  //Brain.Screen.printAt(30, 30, "TESTING: %f \n", left1.rotation(deg)*(3.1415926535/180)*(6.985/2));
  intake.setTimeout(0, sec);
  AllMotors.setTimeout(0, sec);
  // SetTimeout(0);
  intake.stop();
  AllMotors.stop();
}

////////
// Brute force turn (positive turn degree: clockwise, negative turn degree: counterclockwise)
////////
void TurninPlace(int turnDegree, int speedPct, int timeout)
{
  SetTimeout(timeout);
  AllLeft.setVelocity(speedPct, pct);
  AllRight.setVelocity(speedPct, pct);

  AllLeft.rotateFor(
      forward,
      ((ROBOT_RADIUS * (turnDegree * (M_PI / 180))) / WHEEL_CIRCUMFERENCE) *
          DRIVE_GEAR_RATIO,
      rev, true);
  AllRight.rotateFor(
      reverse,
      ((ROBOT_RADIUS * (turnDegree * (M_PI / 180))) / WHEEL_CIRCUMFERENCE) *
          DRIVE_GEAR_RATIO,
      rev);
  SetTimeout(0);
}

// Turn with inertial sensor. 
//(dir): "r" or "l" for "right" or "left" respectively. (speed): turning speed in PERCENT. (DEGREES): turn in DEGREES. timeout: timeout in MSEC. 
void InertialTurn(char dir, double speed, double DEGREES, double timeout) {
  Inertial1.resetRotation();
  // Inertial2.setHeading(0.05, deg);
  // Inertial3.setHeading(0.05, deg); 
  if(dir == 'r'){ //Right turning

    while(Inertial1.rotation(deg)<DEGREES)
    {
      AllLeft.spin(forward, speed, pct);
      AllRight.spin(reverse, speed, pct);

    } 
      do{
        AllLeft.spin(reverse, 3, pct);
        AllRight.spin(forward, 3, pct);
      }while(Inertial1.rotation(deg) > DEGREES);
  }
  else if(dir == 'l') {
    while(fabs(Inertial1.rotation(deg))<DEGREES)
    {
      AllLeft.spin(reverse, speed, pct);
      AllRight.spin(forward, speed, pct);
    }
        do{
      AllLeft.spin(forward, 3, pct);
      AllRight.spin(reverse, 3, pct);
    }while(fabs(Inertial1.rotation(deg))>DEGREES);
  }
  AllLeft.stop(hold);
  AllRight.stop(hold);
  // Inertial1.calibrate();
  // waitUntil(!Inertial1.isCalibrating());
}

////////
// SETTINGS FOR PID
////////
// ------FOR REGULAR LATERAL MOVEMENT-------
// constant values for adjusting error.
double pGain = 0.012;    // proportional gain constant
double iGain = 0.002;    // integral gain constant
double dGain = 0.012;    // derivative gain constant
// setup variables
double desiredDistanceCM; // variable for storing the desired distance to travel (in centimeters)
double error = 0; // current error (Sensor Value - Desired Value)
double prevError; // error 20 milliseconds ago
double errorSum; // cumilative error throughout a given run
double derivative; 

// ------FOR TURNING MOVEMENT------
// constant values for adjusting error
double pGainTurn = 0.03; // proportional gain constant
double iGainTurn = 0.02; // integral gain constant
double dGainTurn = 0.01; // derivative gain constant
// setup variables
double desiredTurnDEG; // desired turn angle (want to drive straight, so 0)
double errorTurn = 0; // current error (Sensor Value - Desired Value)
double prevErrorTurn; // error 20 milliseconds ago
double errorSumTurn; // cumilative error throughout a given run
double turnDerivative;

// ------ MISC --------
// bool doPID = false;


/////////
// CALLBACK PID FUNCTION/PID SETTINGS (*USED REFERENCE FROM: https://www.youtube.com/watch?v=D0H4t4n5J6k AND https://www.youtube.com/watch?v=_Itn-0d340g)
/////////
int PIDMove() {
  
  //------------ PID LOOP --------------
  if (doIntake) {
    intake.spin(directionType::rev, 50, pct);
  }

  // while the error is not negligible
  while ((error > 0.3 && desiredDistanceCM > 0) || (error < -0.3 && desiredDistanceCM < 0)) {
    /*--
    LATERAL MOVEMENT
    --*/
    
    float positionLeft = left1.rotation(deg)*(3.1415926535/180)*(6.82625);  // get current distance traveled from LEFT encoder (in centimeters)
    float positionRight = right1.rotation(deg)*(3.1415926535/180)*(6.82625);  // get current distance traveled from RIGHT encoder (in centimeters)
    float positionAVG = (positionLeft + positionRight)/2; // average of the two encoder positions

    error = desiredDistanceCM - positionAVG; // Potential
    derivative = error - prevError; // Derivative
    errorSum += error; // Integral

    float lateralMotorPower = error*pGain + derivative*dGain + errorSum*iGain; // PID calculation

    /*--
    TURN MOVEMENT
    --*/
    float currTurn = Inertial1.rotation(deg); // get the current rotation angle

    errorTurn = currTurn - desiredTurnDEG; // Potential
    turnDerivative = errorTurn - prevErrorTurn; // Derivative
    errorSumTurn += errorTurn; // Integral

    float turnMotorPower = errorTurn*pGainTurn + turnDerivative*dGainTurn + errorSumTurn*iGainTurn; // PID calculation

    Brain.Screen.printAt(30, 30, "TEST");
    /*--
    SETUP FOR NEXT LOOP/SPINNING MOTORS
    --*/
    // spin the motors
    AllLeft.spin(fwd, lateralMotorPower - turnMotorPower, voltageUnits::volt);
    AllRight.spin(fwd, lateralMotorPower + turnMotorPower, voltageUnits::volt);

    prevError = error;
    prevErrorTurn = errorTurn;

    vex::task::sleep(20);
  } 
  
  AllMotors.stop();
  intake.stop();
  wait(500, msec);        // buffer

  float remainingTurnErr = Inertial1.rotation(deg); // remaining turn error
    
  // if remaining turn error is positive (too far clockwise) (*WITHIN MARGIN)
  if (remainingTurnErr > 3) 
  {
    InertialTurn('l', 7, fabs(remainingTurnErr), 4000); // correct remaining turn error counterclockwise
  }
  // otherwise, if remaining turn error is negative (too far counterclockwise) (*WITHIN MARGIN)
  else if (remainingTurnErr < -3)
  {
    InertialTurn('r', 7, fabs(remainingTurnErr), 4000); // correct remaining turn error clockwise
  }

  pidDone = true;
  return 1;
}

void resetValuesPID() {
  pidDone = false;
  left1.resetRotation(); // initialize distance travelled as "0"
  right1.resetRotation(); // initialize distance travelled as "0"
  Inertial1.resetRotation(); // initialize turn angle as "0"
  // reset proportional error
  error = 0;
  errorTurn = 0;
  // reset integral error
  errorSum = 0;
  errorSumTurn = 0;
  // reset derivative error
  prevError = 0; 
  prevErrorTurn = 0; 


}

////////
// set task up for MOVE PID w/ initial variables
///////
void moveForwardPID(float distanceCM, bool enableIntakePID) {
  Brain.Screen.printAt(30, 30, "TESTING: %f \n", left1.rotation(deg)*(3.1415926535/180)*(6.985/2));

  // setup
  resetValuesPID();
  desiredDistanceCM = distanceCM; // initialize distance goal
  desiredTurnDEG = 0; // initialize turn goal (as 0 since goal is straight movement)
  error = desiredDistanceCM; // initialize current error
  doIntake = enableIntakePID; // initialize switch for enabling/disabling intake during drive
  
  // callback
  vex::task pidTASK(PIDMove);
}

////////
// set task up for TURN PID w/ initial variables
///////
// void turnPID(float rotationDEG) {
//   // setup
//   resetValuesPID();
//   desiredDistanceCM = 0; // initialize distance goal (as 0 since turning in place)
//   desiredTurnDEG = rotationDEG; // initialize turn goal 
//   errorTurn = desiredTurnDEG; // initialize current error
  
//   // callback
//   vex::task pidTASK(PIDMove);
// }


// Helper function for InertialTurn (*NOTE: in the case 2 inertial sensors get added)
// float inertialAverageDEG()
// {
//   float inertialSum=0;
//   inertialSum=(fabs(Inertial1.rotation(deg))+fabs(Inertial2.rotation(deg)));
//   inertialSum=inertialSum/2;
//   return inertialSum;
// }

/*-----
/////////////////////

SCORING

/////////////////////
------*/

// void IntakeAuto(int timeout) {
//   SetTimeout(timeout);
//   intake.spin(reverse, 100, pct);
//   SetTimeout(0);
//   intake.stop();
// }

//////////
// AUTONOMOUS FUNCTION FOR INTAKE (with time input)
///////////
void IntakeSpitAutoTime(int mTime, int speedPct) {
  // SetTimeout(timeout);

  intake.spinFor(reverse, mTime, msec, speedPct, velocityUnits::pct);

  // SetTimeout(0);
}

//////////
// AUTONOMOUS FUNCTION FOR INTAKE (with degree input)
///////////
void IntakeSpitAuto(float turnDegree, int speedPct, int timeout) {
  SetTimeout(timeout);

  intake.setVelocity(speedPct, pct);

  intake.rotateFor(forward, turnDegree, deg, false);
  SetTimeout(0);
}

//////////
// AUTONOMOUS INTAKE FUNCTION TO INTAKE WHILE THERE IS NO DISK IN THE INTAKE
///////////
void StoreDisk(int timeout, bool storeInCatapult) {
  SetTimeout(timeout);

  // while there is no disk fully in the intake...
  while (!diskInIntake()) 
  {
    intake.spin(reverse, 30, pct);
  }

  // if the user wants to store the disk in the catapult instead of the intake...
  if (storeInCatapult) 
  {
    intake.spin(reverse, 70, pct);    // raise the speed to put in the catapult
    wait(1500, msec);     // keep spinning until the disk is fully in the catapult
  }

  intake.stop();        // stop the intake
  SetTimeout(0);
}

////////
// AUTONOMOUS ROLLER FUNCTION W/ OPTICAL
////////
void RollerAuto(vex::color desiredColor) {
  // ASSUMES OPTICAL SENSOR IS FACING THE BOTTOM OF THE ROLLER

  OpticalSensor.setLightPower(100, pct); // turn the light on

  // keep driving backwards towards the roller until it is near the roller
  while (!OpticalSensor.isNearObject())
  {
    AllMotors.spin(reverse, 5, pct);
  } 

  // give it a bit of extra time to go near the roller
  wait(300, msec);

  // stop the drive
  AllMotors.stop();

  // LOOP
  do 
  {
    // keep spinning the roller...
    intake.spin(fwd, 30, pct);
  }
  while (isColor(desiredColor, OpticalSensor.hue())); // ...while the optical sensor still detects the desired color
  
  intake.stop(); // stop the intake once the loop is over

  OpticalSensor.setLightPower(0, pct); // turn off the light

}

// A function that winds the catapult up and stops after the limit switch is hit.
bool catapultWindAuton = true;
void windCatapultAuton() {
  do {
    thrower.spin(reverse, 100, pct);
  } while (catapultLimit.pressing());

  thrower.stop();
}

// A function that shoots the catapult
void ShootCatapultAuto(int timeout) {
  thrower.spinFor(reverse, 300, msec);
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

// void moveForwardPID(int speedPct) {

//   int encPositionLeft;
//   int encPositionRight;
//   int error = 0;
//   int modifiedError;
//   float kp = 0.1;

//   AllLeft.resetPosition();
//   AllRight.resetPosition();
//   // double errorPositionLeft = targetPosition- encPositionLeft;
//   // double errorPositionRight = targetPosition - encPositionRight;
//   while (true) {

//     encPositionLeft = AllLeft.position(deg);
//     encPositionRight = AllRight.position(deg);
//     error = encPositionLeft - encPositionRight;
//     modifiedError = int(kp * error);
//     printf("%d %d \n", encPositionLeft, encPositionRight);
//     wait(50, msec);

//     if (error > 100) {
//       error = 100;
//     } else if (error < -100) {
//       error = -100;
//     }
//     AllLeft.spin(forward, speedPct - modifiedError, pct);
//     AllRight.spin(forward, speedPct + modifiedError, pct);
//   }

//   // if ((abs(errorPositionLeft) > 5) || (abs(errorPositionRight) > 5)) {
//   // }
// }

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