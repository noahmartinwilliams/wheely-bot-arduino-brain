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
	Serial.begin(115200);
	pinMode(left_forward_pin, OUTPUT);
	pinMode(left_backward_pin, OUTPUT);
	pinMode(right_backward_pin, OUTPUT);
	pinMode(right_forward_pin, OUTPUT);
	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
}

double readFloat()
{
	double ret, mul=1.0;
	while (Serial.peek()==' ') {
		Serial.read();
	}
	if (Serial.peek()=='-') {
		mul=-1.0;
	}
	ret=(double) Serial.parseFloat();
	return ret*mul;
}

void loop()
{
	if (Serial.available()) {
		String s=Serial.readStringUntil(' ');
		if (s=="?battery" || s=="?battery ")
			Serial.println(get_battery_voltage());
		else if (s=="!steer " || s=="!steer") {
			double a=readFloat();
			double b=-readFloat();
			control_wheels(a, b);
		} else if (s=="!halt" || s=="!halt ")
			halt();
		else if (s=="!ron" || s=="!ron ") 
			digitalWrite(red, HIGH);
		else if (s=="!bon" || s=="!bon ")
			digitalWrite(blue, HIGH);
		else if (s=="!gon" || s=="!gon ")
			digitalWrite(green, HIGH);

		else if (s=="!roff" || s=="!roff ")
			digitalWrite(red, LOW);

		else if (s=="!goff" || s=="!goff ")
			digitalWrite(green, LOW);

		else if (s=="!boff" || s=="!boff ") 
			digitalWrite(blue, LOW);
		Serial.readStringUntil('\n');
	}
}
