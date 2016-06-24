void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial.begin(19200);
}

boolean battConnected = false;
static float DIODE_DROP = 0.48; // experimentally determined for 6/24/16's setup

/**
 * Battery voltage is run through a protection diode and then halved for measurement.
 * To correct this, we map the analog input value (from 0 to 1023) to nine volts, and
 * then add the voltage drop of our diode.
 * 
 * After processing, we then output it to serial.  When the battery is disconnected,
 * we output one blank line and wait for voltage to be applied again.
 */
void loop() {
  float rawIn = (float) analogRead(0);
  float vIn = fMap(rawIn, 0, 1023, 0, 9) + DIODE_DROP;
  
  if (vIn<=DIODE_DROP) {
    if (battConnected) {
      Serial.println();
      battConnected = false;
    }
  } else {
    Serial.print(vIn);
    Serial.println(" V");
    battConnected = true;
  }
  
  delay(100);
}

/**
 * This is the code behind the built-in map(), changed to work with floats.
 */
float fMap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
