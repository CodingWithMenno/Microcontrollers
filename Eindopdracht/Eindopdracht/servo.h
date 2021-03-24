#ifndef SERVO_H
#define SERVO_H

// The angle the servo needs to go to, value between 0-180
extern int servo_targetValue;

/*
Inits the servo on port B5 and updates the angle every 20ms (50hz)
*/
void servo1_init();

#endif