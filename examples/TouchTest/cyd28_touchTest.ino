#include <CYD28_Touchscreen.h>

CYD28_TouchR ts = CYD28_TouchR(320, 240);

void setup()
{
	Serial.begin(115200);
	ts.begin();
	while (!Serial && (millis() <= 1000));
}

void loop()
{
	if (ts.touched())
	{
		CYD28_TS_Point p = ts.getPointScaled();
		CYD28_TS_Point p_raw = ts.getPointRaw();
		Serial.printf("Raw:\t\tx=%d, y=%d, z=%d\r\n", p_raw.x, p_raw.y, p_raw.z);
		Serial.printf("Scaled:\t\t x=%d, y=%d, z=%d\r\n", p.x, p.y, p.z);	
		delay(30);
	}
}