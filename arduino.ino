#include "Arduino.h"

const int battery_pin=A2;
const int left_forward=3;
double get_battery_voltage()
{
	int i=analogRead(battery_pin);
	return double(i)*(20.0/1024.0);
}

void setup()
{
	Serial.begin(9600);
	pinMode(left_forward, OUTPUT);
}

void loop()
{
	if (Serial.available()) {
		String s=Serial.readStringUntil(' ');
		if (s=="?battery" || s=="?battery ") {
			Serial.println(get_battery_voltage());
		}

		if (s=="!lforw" || s=="!lforw ") {
			analogWrite(left_forward, Serial.parseInt());
		}
	}
}
