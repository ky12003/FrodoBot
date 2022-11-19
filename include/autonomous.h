#ifndef AUTONOMOUS
#define AUTONOMOUS

void moveForwardPID(int);
void spinRoller();
void timeout(int);
void moveForward(float dist, int speed, int timeout);

#endif
