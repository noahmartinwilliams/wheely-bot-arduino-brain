#include "Arduino.h"
#include "globals.h"
#include "constants.h"

extern double fix_angle(double input);
void left_interrupt()
{
	noInterrupts();
	int left=ticks_left;
	if (left_direction)
		ticks_left++;
	else
		ticks_left--;

	double dist_left=(left-ticks_left)*tick_unit;
	theta=fix_angle(theta-dist_left/body_length);
	_x=_x+cos(theta)*dist_left;
	_y=_y+sin(theta)*dist_left;
	interrupts();
}

void right_interrupt()
{
	noInterrupts();
	int right=ticks_right;
	if (right_direction)
		ticks_right++;
	else
		ticks_right--;

	double dist_right=(right-ticks_right)*tick_unit;
	theta=fix_angle(theta-dist_right/body_length);
	_x=_x+cos(theta)*dist_right;
	_y=_y+sin(theta)*dist_right;
	interrupts();
}
