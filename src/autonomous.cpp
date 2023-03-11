#include "vex.h"
#include "Autonomous.h"
// #include <string>

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
void moveForward(float distanceCM, int speedPct, int timeout) {
  SetTimeout(timeout);
  AllLeft.setVelocity(speedPct, pct);
  AllRight.setVelocity(speedPct, pct);
  // (GEAR RATIO IS ONE-TO-ONE, so the "distance" would be times 1)
  // AllRight.rotateFor(forward, (distanceCM/WHEEL_CIRCUMFERENCE) *
  // DRIVE_GEAR_RATIO, rev, false);
  double distanceToTravel = (distanceCM / WHEEL_CIRCUMFERENCE) * DRIVE_GEAR_RATIO;

  AllMotors.rotateFor(forward, distanceToTravel, rev, true);
  
  //Brain.Screen.printAt(30, 30, "TESTING: %f \n", left1.rotation(deg)*(3.1415926535/180)*(6.985/2));
  SetTimeout(0);
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

////////
// SETTINGS FOR PID
////////
// ------FOR REGULAR LATERAL MOVEMENT-------
// constant values for adjusting error.
double pGain = 0.003;    // proportional gain constant
double iGain = 0.002;    // integral gain constant
double dGain = 0.001;    // derivative gain constant
// setup variables
double desiredDistanceCM; // variable for storing the desired distance to travel (in centimeters)
double error; // current error (Sensor Value - Desired Value)
double prevError; // error 20 milliseconds ago
double errorSum; // cumilative error throughout a given run
double derivative; 
directionType desiredMoveDir; // which way to move (forwards or backwards)

// ------FOR TURNING MOVEMENT------
// constant values for adjusting error
double pGainTurn = 0.003; // proportional gain constant
double iGainTurn = 0.002; // integral gain constant
double dGainTurn = 0.001; // derivative gain constant
// setup variables
double desiredTurn = 0; // desired turn angle (want to drive straight, so 0)
double errorTurn; // current error (Sensor Value - Desired Value)
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
  // while the error is not negligible
  while (error > 0.1) {
    /*--
    LATERAL MOVEMENT
    --*/
    double positionLeft = left1.rotation(deg)*(3.1415926535/180)*(6.985/2);  // get current distance traveled from LEFT encoder
    double positionRight = right1.rotation(deg)*(3.1415926535/180)*(6.985/2);  // get current distance traveled from RIGHT encoder
    double positionAVG = (positionLeft + positionRight)/2; // average of the two encoder positions

    error = desiredDistanceCM - positionAVG; // Potential

    derivative = error - prevError; // Derivative
    errorSum += error; // Integral

    double lateralMotorPower = error*pGain + derivative*dGain + errorSum*iGain;

    /*--
    TURN MOVEMENT
    --*/
    double turnDifference = positionLeft - positionRight;

    errorTurn = turnDifference - desiredTurn; // Potential
    turnDerivative = errorTurn - prevErrorTurn; // Derivative
    errorSumTurn += errorTurn; // Integral

    double turnMotorPower = errorTurn*pGainTurn + turnDerivative*dGainTurn + errorSumTurn*iGainTurn;


    // Brain.Screen.printAt(30, 40, "ERR: %f", error);
    // Brain.Screen.printAt(30, 60, "POWAOOOOONE: %f", lateralMotorPower);
    // Brain.Screen.printAt(30, 80, "POWATWWWWWWO: %f", turnMotorPower);
    /*--
    SETUP FOR NEXT LOOP/SPINNING MOTORS
    --*/
    // spin the motors
    AllLeft.spin(desiredMoveDir, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    AllRight.spin(desiredMoveDir, lateralMotorPower - turnMotorPower, voltageUnits::volt);

    prevError = error;
    prevErrorTurn = errorTurn;

    vex::task::sleep(20);
  }

  AllMotors.stop();
  return 1;
}
////////
// set task up for PID w/ initial variables
///////
void moveForwardPID(double distanceCM, directionType dir) {
  Brain.Screen.printAt(30, 30, "TESTING: %f \n", left1.rotation(deg)*(3.1415926535/180)*(6.985/2));

  // setup
  left1.resetRotation(); // initialize distance travelled as "0"
  right1.resetRotation(); // initialize distance travelled as "0"
  prevError = 0; // initialize prevError
  desiredDistanceCM = distanceCM; // initialize distance goal
  error = desiredDistanceCM; // initialize current error
  desiredMoveDir = dir; //initialize desired direction

  //desiredDistanceCM - left1.rotation(deg)*(3.1415926535/180)*(6.985/2);
  vex::task pidTASK(PIDMove);
}

// Helper function for InertialTurn (*NOTE: in the case 2 inertial sensors get added)
// float inertialAverageDEG()
// {
//   float inertialSum=0;
//   inertialSum=(fabs(Inertial1.rotation(deg))+fabs(Inertial2.rotation(deg)));
//   inertialSum=inertialSum/2;
//   return inertialSum;
// }

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
    while(Inertial1.rotation(deg)<DEGREES)
    {
      AllLeft.spin(reverse, speed, pct);
      AllRight.spin(forward, speed, pct);
    }
        do{
      AllLeft.spin(forward, 3, pct);
      AllRight.spin(reverse, 3, pct);
    }while(Inertial1.rotation(deg)>DEGREES);
  }
  AllLeft.stop(hold);
  AllRight.stop(hold);
}

/*-----
/////////////////////

SCORING

/////////////////////
------*/

void IntakeAuto(int timeout) {
  SetTimeout(timeout);
  intake.spin(reverse, 100, pct);
  SetTimeout(0);
  intake.stop();
}

void IntakeSpitAutoTime(int mTime, int speedPct, int timeout) {
  // SetTimeout(timeout);

  // intake.setVelocity(speedPct, pct);

  intake.spinFor(reverse, mTime, msec);
  // SetTimeout(0);
}

void IntakeSpitAuto(float turnDegree, int speedPct, int timeout) {
  SetTimeout(timeout);

  intake.setVelocity(speedPct, pct);

  intake.rotateFor(forward, turnDegree, deg, false);
  SetTimeout(0);
}

long int prevValueAuton = -1;
bool catapultWindAuton = true;
void windCatapultAuton() {
  while (prevValueAuton == catapultLimit.value()) {
    thrower.spin(reverse, 100, pct);
  }

  thrower.stop();
}

void ShootCatapultAuto(int timeout) {
  thrower.spinFor(reverse, 300, msec);
  prevValueAuton = catapultLimit.value();
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