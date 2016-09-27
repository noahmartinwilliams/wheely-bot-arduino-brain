#include "Arduino.h"
#include "constants.h"
#include "motor.h"

double fix_angle(double input)
{
	return atan2(cos(input), sin(input));
}
const int battery_pin=A2;
double get_battery_voltage()
{
	int i=analogRead(battery_pin);
	return double(i)*(20.0/1024.0);
}

void setup()
{
	Serial.begin(9600);
	pinMode(left_forward_pin, OUTPUT);
	pinMode(left_backward_pin, OUTPUT);
	pinMode(right_backward_pin, OUTPUT);
	pinMode(right_forward_pin, OUTPUT);
}

void loop()
{
	if (Serial.available()) {
		String s=Serial.readStringUntil(' ');
		if (s=="?battery" || s=="?battery ") {
			Serial.println(get_battery_voltage());
		} else if (s=="!lforw" || s=="!lforw ") {
			analogWrite(left_backward_pin, 0);
			analogWrite(left_forward_pin, Serial.parseInt());
		} else if (s=="!lback" || s=="!lback ") {
			analogWrite(left_forward_pin, 0);
			analogWrite(left_backward_pin, Serial.parseInt());
		} else if (s=="!rforw" || s=="!rforw ") {
			analogWrite(right_backward_pin, 0);
			analogWrite(right_forward_pin, Serial.parseInt());
		} else if (s=="!rback" || s=="!rback ") {
			analogWrite(right_forward_pin, 0);
			analogWrite(right_backward_pin, Serial.parseInt());
		} else if (s=="!steer " || s=="!steer") {
			control_wheels(Serial.parseFloat(), Serial.parseFloat());
		} else if (s=="!halt" || s=="!halt ") {
			halt();
		}
	}
}
