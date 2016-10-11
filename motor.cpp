#include "Arduino.h"
#include "constants.h"
#include "globals.h"

void set_left_direction(bool dir);
void set_right_direction(bool dir);
extern double fix_angle(double input);
void align_with_wall(bool side);
extern volatile bool left_direction, right_direction;

void halt()
{
	analogWrite(left_forward_pin, 0);
	analogWrite(right_forward_pin, 0);
	analogWrite(left_backward_pin, 0);
	analogWrite(right_backward_pin, 0);
}


void control_wheels(double velocity, double turn_rate)
{
        double Vl=(2.0*velocity+turn_rate*body_length)/(2.0*wheel_radius);
        double Vr=(2.0*velocity-turn_rate*body_length)/(2.0*wheel_radius);

	int _right=(int) ((255.0)*Vr/max_speed);
	int _left=(int) ((255.0)*Vl/max_speed);

	set_left_direction(_left > 0 ? true : false);
	set_right_direction(_right > 0 ? true : false);

	halt();
	analogWrite(left_forward_pin, _left > 0 ? _left : 0);
	analogWrite(left_backward_pin, _left <= 0 ? -_left : 0);
	analogWrite(right_forward_pin, _right > 0 ? _right : 0);
	analogWrite(right_backward_pin, _right <= 0 ? -_right : 0);
}


void set_angle(double desired_angle)
{
	double proportional=1.0, integral=1.0, derivative=2.1; 
	double int_angle=0.0;
	double eangle=fix_angle(desired_angle-fix_angle(theta));
	const double wait_time=0.001;//in seconds
	double  prev_angle=eangle;
	double turn_rate;

	while (abs(fix_angle(eangle)) >= max_angle_error) {
		eangle=fix_angle(desired_angle-theta);
		
		turn_rate=proportional*eangle+integral*int_angle+derivative*(eangle-prev_angle)/wait_time;
		prev_angle=eangle;
		int_angle+=wait_time*eangle;
		control_wheels(0.0, turn_rate);
		delay((int) (wait_time*1000.0));
	}
	halt();
}

/* void turn(double angle)
{
	set_angle(fix_angle(current_angle()+angle));
} */


void goto_goal(double desired_x, double desired_y)
{

	double dx=desired_x-_x, dy=desired_y-_y;
	double distance=sqrt(dx*dx+dy*dy);
	const double max_dist=1.0;//cm
	double eangle=fix_angle(atan2(dy, dx)-theta);
	while (distance > max_dist) {
		if (abs(eangle) >= 2.0*max_angle_error) {
			halt();
			set_angle(atan2(dy, dx));
		}
		control_wheels(10.0, 0.0);
		dx=desired_x-_x; dy=desired_y-_y;
		distance=sqrt(dx*dx+dy*dy);
		eangle=fix_angle(atan2(dy, dx)-theta);
		delay(1);
	}
	halt();
}

/* int forward(double distance, int (*exit_func) ()) //cm
{
	return goto_goal(current_x()+distance*cos(current_angle()), current_y()+distance*sin(current_angle()), exit_func);
} */

/* int follow_wall(bool side, double distance, int (*exit_func) ()) 
{
	double distance_traveled=0.0;
	const double increment=5.0;
	while (distance-distance_traveled >= increment)
	{
		int ret=forward(increment, exit_func);
		if (ret!=0)
			return ret;
		align_with_wall(side);
		distance+=increment;
	}

	return forward(distance-distance_traveled, exit_func);
} */


/* void align_with_wall(bool side)
{
	get_left_wall_angle();
	double wall_angle=get_left_wall_angle();
	turn(multiplier*wall_angle);
	while (abs(wall_angle) > high_accuracy_max_angle_error) {
		if (abs(wall_angle) >= max_angle_error) {
			turn(multiplier*wall_angle);
		} else {
			if (wall_angle >= 0.0)
				control_wheels(0.0, multiplier*1.0);
			else
				control_wheels(0.0, -multiplier*1.0);
			delay(int(wall_angle*1000.0));
			halt();
		}
		wall_angle=get_left_wall_angle();
	}
} */

void set_left_direction(bool dir)
{
	left_direction=dir;
}

void set_right_direction(bool dir)
{
	right_direction=dir;
}
