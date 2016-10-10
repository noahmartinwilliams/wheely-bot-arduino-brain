#ifndef __MOTOR_H__
#define __MOTOR_H__

extern void halt();
extern void control_wheels(double velocity, double turn_rate);
extern void set_angle(double desired_angle);
//extern void turn(double angle);
//extern int goto_goal(double desired_x, double desired_y, int (*exit_func) ());
//extern int forward(double distance, int (*exit_func) ()); //cm
//extern int follow_wall(bool side, double distance, int (*exit_func) ()) ;
//extern void align_with_wall(bool side);
//extern void set_left_direction(bool dir);
//extern void set_right_direction(bool dir);

#endif
