#ifndef SERVO_H
#define SERVO_H

// The angle the servo needs to go to, value between 250-1500
extern int servo1_targetValue;
// The angle the servo needs to go to, value between 250-2500
extern int servo2_targetValue;


/*
Inits the servo on port B5 and updates the angle every 20ms (50hz)
*/
void servo_init();

#endif