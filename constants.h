#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

const int num_ticks=19;
const int red=11, green=12, blue=13;
const int right_wheel_encoder=1, left_wheel_encoder=0;
const double body_length=18.0;
const double wheel_radius=3.5;
const double tick_unit=2.0*3.141592*wheel_radius/num_ticks;
const int left_forward_pin=5, left_backward_pin=6;
const int right_forward_pin=10, right_backward_pin=9;
const double max_angle_error=3.141592/38.0;
const double max_speed=10.0;
const int MPU_addr=0x68;
const double accel_error=0.11;

#endif
