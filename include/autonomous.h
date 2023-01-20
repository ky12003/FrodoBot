#ifndef AUTONOMOUS
#define AUTONOMOUS

void SetTimeout(int);
void moveForward(float distanceCM, int speedPct, int timeout); //(int dist, int speed, int timeout(seconds))//
void TurninPlace(int turnDegree, int speedPct, int timeout); //(int dist, int speed, int timeout(seconds))//
void IntakeSpitAuto(float turnDegree, int speedPct, int timeout);
void IntakeAuto(int dist, int speed, int timeout);
void ShootCatapultAuto(int timeout);

// void catalimit(int dist, int speed, int timeout);
void moveForwardPID(int speed);


#endif 