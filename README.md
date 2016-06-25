A quick arduino device I threw together to measure 9V batteries when I couldn't find a meter.

/**
 * Battery voltage is run through a protection diode and then halved for measurement.
 * To correct this, we map the analog input value (from 0 to 1023) to nine volts, and
 * then add the voltage drop of our diode.
 * 
 * After processing, we then output it to serial.  When the battery is disconnected,
 * we output one blank line and wait for voltage to be applied again.
 */
