# Thermocouple Library

## Summary

The Thermocouple library provides an easy way to convert direct thermocouple voltage measurements into a temperature.  You must
have a temperature sensor near or (preferably) thermally coupled to the cold junction in order to make this work.

Originally this library was developed to help users of the Iowa Scaled Engineering [ARD-LTC2499](https://www.iascaled.com/store/ARD-LTC2499)
make direct thermocouple measurements.  The onboard LTC2499 has a built-in temperature sensor, which is close enough to the terminal block to
work as the cold junction temperature sensor.  See the "ard2499_thermocouple" example for how this is used.

The library is heavily based on the work of Mosiac Industries and theirdevelopment of improved rational polynomial functions and coefficients
to model thermocouple systems.  Their work provides significantly lower computational costs and significantly lower error as compared to the
NIST ITS-90 polynomials and coefficients.  Their work is available [on their website here.](http://www.mosaic-industries.com/embedded-systems/microcontroller-projects/temperature-measurement/thermocouple/calibration-table)

## Features

* Support for Type B, E, J, K, N, R, S, and T thermocouples
* Constructed in a way to minimize memory and code space use by automatically removing thermocouple types not used
* Plain C++ so it's usable in Arduino and regular C++ projects

## Classes

There are eight class types, one for each type of thermocouple.  You only need to create one instance of each that you intend to use, as the objects are stateless.
The classes are as follows:
* TypeB
* TypeE
* TypeJ
* TypeK
* TypeN
* TypeR
* TypeS
* TypeT

## Functions

```float TypeX::getTemperature(float millivolts, float Tcj);```
```double TypeX::getTemperature(double millivolts, double Tcj);```

The getTemperature() function will convert a thermocouple measurement (in millivolts) and a cold junction temperature (in degrees Celsius) to a thermocouple temperature (also in degrees Celsius).
The internal calculations are all done as doubles.  On AVRs and most other 8-bit platforms, doubles are 4-bytes, just like a float and offer no additional precision.  However, on larger platforms doubles
provide significantly more precision and may improve accuracy.


Example usage:

```
TypeK tc_k;

// Get millivolts from ADC
float millivolts = getThermocoupleAnalogVoltage();

// Get cold junction temperature
float Tcj = getColdJunctionTemp();

float thermocoupleTemperature = tc_k.getTemperature(millivolts, Tcj);

printf("The thermocouple is at %.2f degrees C\n", thermocoupleTemperature);
```

## Source Releases

The latest source code is always available from our GitHub [arduino-ard2499 repository](https://github.com/IowaScaledEngineering/arduino-thermocouple).

## Open Hardware & Software

Like all public Iowa Scaled Engineering designs, the Thermocouple library is free software, licensed under the GPL v3.


