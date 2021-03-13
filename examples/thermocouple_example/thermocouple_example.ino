/*************************************************************************
Title:    Thermocouple Example Sketch
Authors:  Nathan D. Holmes <maverick@drgw.net>
File:     $Id: $
License:  GNU General Public License v3

ABOUT:
  This is an example use of the Thermocouple library for direct thermocouple
  measurements using an ADC and a cold junction temperature sensor

  Since this example requires no special hardware, two functions are stubbed in
  to simulate having a high-precision ADC and temperature sensor.  To use this with
  real hardware, you'll need to fill these in appropriately.  Instead, the example
  just puts sample values in them to show you how to use the Thermocouple library
  to convert that to a temperature.
  * getThermocoupleMillivolts()
  * getColdJunctionTemp()
  
  The sample sketch just prints the results to the serial console.  Just open your
  console at 9600 baud to see it run. 

  We recommend the Iowa Scaled Engineering ARD-LTC2499 as a potential ADC for this
  application.  Please see the ard2499_thermocouple example under there to see
  how to measure a Type K thermocouple directly using the ARD-LTC2499.

LICENSE:
    Copyright (C) 2021 Nathan D. Holmes & Michael D. Petersen

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

*************************************************************************/

#include <Thermocouple.h>

TypeK typeK;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}


// In a real use case, this function would get the thermocouple voltage from your
// analog to digital converter and return the value in millivolts.  I'm putting in
// 0.349 mV (yes, 349 uV) as a sample value
float getThermocoupleMillivolts()
{
  return 0.349;
}

// In a real use case, this function would get the cold junction temperature in
// degrees C.  I'm putting in 23.2 degrees as a sample value
float getColdJunctionTemp()
{
  return 23.2;
}



void loop() {
  // Get the cold junction temperature
  float Tcj = getColdJunctionTemp();

  // Get the thermocouple voltage measurement in millivolts
  float Vtc = getThermocoupleMillivolts();

  Serial.print("\nCold juct temp = ");
  Serial.print(Tcj, 2);
  Serial.print(" deg C\n");

  Serial.print("Thermocouple voltage = ");
  Serial.print(Vtc, 3);
  Serial.print(" mV\n");

  float Ttc = typeK.getTemperature(Vtc, Tcj);

  Serial.print("Thermocouple temp = ");
  Serial.print(Ttc, 2);
  Serial.print(" deg C\n");
 
  delay(1000);
}
