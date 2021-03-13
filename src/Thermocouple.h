/*************************************************************************
Title:    Thermocouple Direct Measurement Library
Authors:  Nathan D. Holmes <maverick@drgw.net>
Authors:  Michael D. Petersen <railfan@drgw.net>
File:     Thermocouple.h
License:  GNU General Public License v3

CREDITS:
    This library was hugely based on the work of Mosiac Industries and their
    development of improved rational polynomial functions and coefficients
    to model thermocouple systems.  Their work provides significantly lower
    computational costs and significantly lower error as compared to the 
    NIST ITS-90 polynomials and coefficients.  See their work here:
    http://www.mosaic-industries.com/embedded-systems/microcontroller-projects/temperature-measurement/thermocouple/calibration-table

LICENSE:
    Copyright (C) 2021 Nathan D. Holmes & Michael D. Petersen

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

*************************************************************************/

#ifndef _THERMOCOUPLE_H_
#define _THERMOCOUPLE_H_

#define TC_OUT_OF_RANGE (AbstractThermocouple::TCOUPLE_OUT_OF_RANGE)

class AbstractThermocouple {
	public:
		float getTemperature(float millivolts, float Tcj);
		double getTemperature(double millivolts, double Tcj);
		const double TCOUPLE_OUT_OF_RANGE = -1000.0;
	protected:
		double computeColdJunction(double Tcj, const double T0, const double V0, const double p1, const double p2, const double p3, const double p4, const double q1, const double q2);
		double computeTemperatureInternal(double millivolts, const double T0, const double V0, const double p1, const double p2, const double p3, const double p4, const double q1, const double q2, const double q3);
		virtual double computeTemperature(double millivolts) = 0;
		virtual double computeColdJunctionVoltage(double Tcj) = 0;
};

class TypeB : public AbstractThermocouple {
	protected:
		double computeTemperature(double millivolts);
		double computeColdJunctionVoltage(double Tcj);
};

class TypeE : public AbstractThermocouple {
	protected:
		double computeTemperature(double millivolts);
		double computeColdJunctionVoltage(double Tcj);
};

class TypeJ : public AbstractThermocouple {
	protected:
		double computeTemperature(double millivolts);
		double computeColdJunctionVoltage(double Tcj);
};

class TypeK : public AbstractThermocouple {
	protected:
		double computeTemperature(double millivolts);
		double computeColdJunctionVoltage(double Tcj);
};

class TypeN : public AbstractThermocouple {
	protected:
		double computeTemperature(double millivolts);
		double computeColdJunctionVoltage(double Tcj);
};

class TypeR : public AbstractThermocouple {
	protected:
		double computeTemperature(double millivolts);
		double computeColdJunctionVoltage(double Tcj);
};

class TypeS : public AbstractThermocouple {
	protected:
		double computeTemperature(double millivolts);
		double computeColdJunctionVoltage(double Tcj);
};

class TypeT : public AbstractThermocouple {
	protected:
		double computeTemperature(double millivolts);
		double computeColdJunctionVoltage(double Tcj);
};



#endif