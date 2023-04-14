#ifndef AUTONOMOUS
#define AUTONOMOUS

void SetTimeout(int);

extern bool pidDone;

/*----------
MOVEMENT
----------*/

void moveForward(float distanceCM, int speedPct, int timeout, bool enableIntakeREG = false); //(int dist, int speed, int timeout(seconds))//

void TurninPlace(int turnDegree, int speedPct, int timeout); //(int dist, int speed, int timeout(seconds))//

// move forwards/backwards with PID.
void moveForwardPID(float distanceCM, bool enableIntakePID = false);

// Turn with inertial sensor. 
//(dir): "r" or "l" for "right" or "left" respectively. (speed): turning speed in PERCENT. (DEGREES): turn in DEGREES. timeout: timeout in MSEC. 
void InertialTurn(char dir, double speed, double DEGREES, double timeout);


/*----------
SCORING
----------*/
void StoreDisk(int timeout);
void IntakeSpitAutoTime(int mTime, int speedPct, int timeout);
void IntakeSpitAuto(float turnDegree, int speedPct, int timeout);
void IntakeAuto(int timeout);
void RollerAuto(vex::color desiredColor);
void windCatapultAuton();
void ShootCatapultAuto(int timeout);

// void catalimit(int dist, int speed, int timeout);
// void moveForwardPID(int speed);

#endif
