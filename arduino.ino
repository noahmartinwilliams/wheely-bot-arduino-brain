#include "Arduino.h"

const int battery_pin=A2;
const int left_forward=3, left_backward=5;
const int right_forward=6, right_backward=9;;
double get_battery_voltage()
{
	int i=analogRead(battery_pin);
	return double(i)*(20.0/1024.0);
}

void setup()
{
	Serial.begin(9600);
	pinMode(left_forward, OUTPUT);
	pinMode(left_backward, OUTPUT);
	pinMode(right_backward, OUTPUT);
	pinMode(right_forward, OUTPUT);
}

void loop()
{
	if (Serial.available()) {
		String s=Serial.readStringUntil(' ');
		if (s=="?battery" || s=="?battery ") {
			Serial.println(get_battery_voltage());
		} else if (s=="!lforw" || s=="!lforw ") {
			analogWrite(left_backward, 0);
			analogWrite(left_forward, Serial.parseInt());
		} else if (s=="!lback" || s=="!lback ") {
			analogWrite(left_forward, 0);
			analogWrite(left_backward, Serial.parseInt());
		} else if (s=="!rforw" || s=="!rforw ") {
			analogWrite(right_backward, 0);
			analogWrite(right_forward, Serial.parseInt());
		} else if (s=="!rback" || s=="!rback ") {
			analogWrite(right_forward, 0);
			analogWrite(right_backward, Serial.parseInt());
		}
	}
}
