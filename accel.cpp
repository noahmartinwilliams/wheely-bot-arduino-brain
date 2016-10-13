#include "Arduino.h"
#include "real.h"
#include "Wire.h"
#include "constants.h"

void setup_accel()
{
	Wire.beginTransmission(MPU_addr);
	Wire.write(0x6B);
	Wire.write(0);
	Wire.endTransmission(true);
}
class real get_y_accel()
{
	int16_t AcX, AcY;
	Wire.beginTransmission(MPU_addr);
	Wire.write(0x3B);

	Wire.endTransmission(false);
	Wire.requestFrom(MPU_addr, 4, true);

	AcX = Wire.read() << 8 | Wire.read();
	AcY = Wire.read() << 8 | Wire.read();

	class real y(double(AcY)*9.8*2.0/16384.0, accel_error);
	return y;
}
