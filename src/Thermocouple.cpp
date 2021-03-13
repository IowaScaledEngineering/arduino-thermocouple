/*************************************************************************
Title:    Thermocouple Direct Measurement Library
Authors:  Nathan D. Holmes <maverick@drgw.net>
Authors:  Michael D. Petersen <railfan@drgw.net>
File:     Thermocouple.cpp
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

#include "Thermocouple.h"

float AbstractThermocouple::getTemperature(float millivolts, float Tcj)
{
	return (float)this->getTemperature((double)millivolts, (double)Tcj);
}

double AbstractThermocouple::getTemperature(double millivolts, double Tcj)
{
	double Vcj = this->computeColdJunctionVoltage(Tcj);
	return this->computeTemperature(millivolts + Vcj);
}


double AbstractThermocouple::computeColdJunction(double Tcj, 
	const double T0,
	const double V0,
	const double p1,
	const double p2,
	const double p3,
	const double p4,
	const double q1,
	const double q2)
{
	
#define numerator   ((Tcj - T0)*(p1 + (Tcj - T0)*(p2 + (Tcj - T0) * (p3 + p4*(Tcj - T0)))))
#define denominator (1.0 + (Tcj - T0) * (q1 + q2*(Tcj - T0)))
	return (V0 + (numerator / denominator));
#undef numerator
#undef denominator
}

double AbstractThermocouple::computeTemperatureInternal(double millivolts, 
	const double T0,
	const double V0,
	const double p1,
	const double p2,
	const double p3,
	const double p4,
	const double q1,
	const double q2,
	const double q3)
{
#define numerator ((millivolts - V0)*(p1 + (millivolts - V0)*(p2 + (millivolts - V0)*(p3 + p4*(millivolts-V0)))))
#define denominator (1.0 + (millivolts - V0)*(q1 + (millivolts - V0)*(q2 + q3*(millivolts - V0))))
	return (T0 + (numerator / denominator));
#undef numerator
#undef denominator  
}

/*********************************************************************************************************
Type B Thermocouple Implementation
*********************************************************************************************************/

double TypeB::computeColdJunctionVoltage(double Tcj)
{
	// Type K equations
	// Tcj = temperature in Celsius
	// Returns equivalent voltage in mV

	const double T0 = 4.2000000E+01;
	const double V0 = 3.3933898E-04;
	const double p1 = 2.1196684E-04;
	const double p2 = 3.3801250E-06;
	const double p3 = -1.4793289E-07;
	const double p4 = -3.3571424E-09;
	const double q1 = -1.0920410E-02;
	const double q2 = -4.9782932E-04;

	return this->computeColdJunction(Tcj, T0, V0, p1, p2, p3, p4, q1, q2);
}

double TypeB::computeTemperature(double millivolts)
{
	// Type B equations
	// millivolts = voltage in mV
	// Returns computed temperature in Celsius
	double T0, V0, p1, p2, p3, p4, q1, q2, q3;

	if (0.291 <= millivolts && millivolts< 2.431)
	{
		T0 = 5.0000000E+02;
		V0 = 1.2417900E+00;
		p1 = 1.9858097E+02;
		p2 = 2.4284248E+01;
		p3 = 9.7271640E+01;
		p4 = -1.5701178E+01;
		q1 = 3.1009445E-01;
		q2 = -5.0880251E-01;
		q3 = -1.6163342E-01;
	}
	else if (2.431<=millivolts && millivolts<13.820)
	{
		T0 = 1.2461474E+03;
		V0 = 7.2701221E+00;
		p1 = 9.4321033E+01;
		p2 = 7.3899296E+00;
		p3 = -1.5880987E-01;
		p4 = 1.2681877E-02;
		q1 = 1.0113834E-01;
		q2 = -1.6145962E-03;
		q3 = -4.1086314E-06;
	}
	else
	{
		return (AbstractThermocouple::TCOUPLE_OUT_OF_RANGE);
	}

	return this->computeTemperatureInternal(millivolts, T0, V0, p1, p2, p3, p4, q1, q2, q3);
}

/*********************************************************************************************************
Type E Thermocouple Implementation
*********************************************************************************************************/

double TypeE::computeColdJunctionVoltage(double Tcj)
{
	// Type E equations
	// Tcj = temperature in Celsius
	// Returns equivalent voltage in mV
	const double T0 = 2.5000000E+01;
	const double V0 = 1.4950582E+00;
	const double p1 = 6.0958443E-02;
	const double p2 = -2.7351789E-04;
	const double p3 = -1.9130146E-05;
	const double p4 = -1.3948840E-08;
	const double q1 = -5.2382378E-03;
	const double q2 = -3.0970168E-04;
	return this->computeColdJunction(Tcj, T0, V0, p1, p2, p3, p4, q1, q2);
}

double TypeE::computeTemperature(double millivolts)
{
	// Type E equations
	// millivolts = voltage in mV
	// Returns computed temperature in Celsius
	double T0, V0, p1, p2, p3, p4, q1, q2, q3;

	if (-9.835 <= millivolts && millivolts < -5.237)
	{
		T0 = -1.1721668E+02;
		V0 = -5.9901698E+00;
		p1 = 2.3647275E+01;
		p2 = 1.2807377E+01;
		p3 = 2.0665069E+00;
		p4 = 8.6513472E-02;
		q1 = 5.8995860E-01;
		q2 = 1.0960713E-01;
		q3 = 6.1769588E-03;
	}
	else if (-5.237 <= millivolts && millivolts < 0.591)
	{
		T0 = -5.0000000E+01;
		V0 = -2.7871777E+00;
		p1 = 1.9022736E+01;
		p2 = -1.7042725E+00;
		p3 = -3.5195189E-01;
		p4 = 4.7766102E-03;
		q1 = -6.5379760E-02;
		q2 = -2.1732833E-02;	
		q3 = 0.0;
	}
	else if (0.591 <= millivolts && millivolts < 24.964)
	{
		T0 = 2.5014600E+02;
		V0 = 1.7191713E+01;
		p1 = 1.3115522E+01;
		p2 = 1.1780364E+00;
		p3 = 3.6422433E-02;
		p4 = 3.9584261E-04;
		q1 = 9.3112756E-02;
		q2 = 2.9804232E-03;	
		q3 = 3.3263032E-05;
	}
	else if (24.964 <= millivolts && millivolts < 53.112)
	{
		T0 = 6.0139890E+02;
		V0 = 4.5206167E+01;
		p1 = 1.2399357E+01;
		p2 = 4.3399963E-01;
		p3 = 9.1967085E-03;
		p4 = 1.6901585E-04;
		q1 = 3.4424680E-02;
		q2 = 6.9741215E-04;	
		q3 = 1.2946992E-05;
	}
	else if (53.112 <= millivolts && millivolts < 76.373)
	{
		T0 = 8.0435911E+02;
		V0 = 6.1359178E+01;
		p1 = 1.2759508E+01;
		p2 = -1.1116072E+00;
		p3 = 3.5332536E-02;
		p4 = 3.3080380E-05;
		q1 = -8.8196889E-02;
		q2 = 2.8497415E-03;	
		q3 = 0.0;
	}		
	else 
	{
		return (AbstractThermocouple::TCOUPLE_OUT_OF_RANGE);
	}

	return this->computeTemperatureInternal(millivolts, T0, V0, p1, p2, p3, p4, q1, q2, q3);
}

/*********************************************************************************************************
Type J Thermocouple Implementation
*********************************************************************************************************/

double TypeJ::computeColdJunctionVoltage(double Tcj)
{
	// Type J equations
	// Tcj = temperature in Celsius
	// Returns equivalent voltage in mV
	const double T0 = 2.5000000E+01;
	const double V0 = 1.2773432E+00;
	const double p1 = 5.1744084E-02;
	const double p2 = -5.4138663E-05;
	const double p3 = -2.2895769E-06;
	const double p4 = -7.7947143E-10;
	const double q1 = -1.5173342E-03;
	const double q2 = -4.2314514E-05;

	return this->computeColdJunction(Tcj, T0, V0, p1, p2, p3, p4, q1, q2);
}

double TypeJ::computeTemperature(double millivolts)
{
	// Type J equations
	// millivolts = voltage in mV
	// Returns computed temperature in Celsius
	double T0, V0, p1, p2, p3, p4, q1, q2, q3;

	if (-8.095 <= millivolts && millivolts < 0)
	{
		T0 = -6.4936529E+01;
		V0 = -3.1169773E+00;
		p1 = 2.2133797E+01;
		p2 = 2.0476437E+00;
		p3 = -4.6867532E-01;
		p4 = -3.6673992E-02;
		q1 = 1.1746348E-01;
		q2 = -2.0903413E-02;
		q3 = -2.1823704E-03;
	}
	else if (0 <= millivolts && millivolts < 21.840)
	{
		T0 = 2.5066947E+02;
		V0 = 1.3592329E+01;
		p1 = 1.8014787E+01;
		p2 = -6.5218881E-02;
		p3 = -1.2179108E-02;
		p4 = 2.0061707E-04;
		q1 = -3.9494552E-03;
		q2 = -7.3728206E-04;
		q3 = 1.6679731E-05;
	} 
	else if (21.840 <= millivolts && millivolts < 45.494)
	{
		T0 = 6.4950262E+02;
		V0 = 3.6040848E+01;
		p1 = 1.6593395E+01;
		p2 = 7.3009590E-01;
		p3 = 2.4157343E-02;
		p4 = 1.2787077E-03;
		q1 = 4.9172861E-02;
		q2 = 1.6813810E-03;
		q3 = 7.6067922E-05;
	} 
	else if (45.494 <= millivolts && millivolts < 57.953)
	{
		T0 = 9.2510550E+02;
		V0 = 5.3433832E+01;
		p1 = 1.6243326E+01;
		p2 = 9.2793267E-01;
		p3 = 6.4644193E-03;
		p4 = 2.0464414E-03;
		q1 = 5.2541788E-02;
		q2 = 1.3682959E-04;
		q3 = 1.3454746E-04;
	} 
	else if (57.953 <= millivolts && millivolts < 69.553)
	{
		T0 = 1.0511294E+03;
		V0 = 6.0956091E+01;
		p1 = 1.7156001E+01;
		p2 = -2.5931041E+00;
		p3 = -5.8339803E-02;
		p4 = 1.9954137E-02;
		q1 = -1.5305581E-01;
		q2 = -2.9523967E-03;
		q3 = 1.1340164E-03;
	}
	else
	{
		return (AbstractThermocouple::TCOUPLE_OUT_OF_RANGE);
	}

	return this->computeTemperatureInternal(millivolts, T0, V0, p1, p2, p3, p4, q1, q2, q3);
}



/*********************************************************************************************************
Type K Thermocouple Implementation
*********************************************************************************************************/

double TypeK::computeColdJunctionVoltage(double Tcj)
{
	// Type K equations
	// Tcj = temperature in Celsius
	// Returns equivalent voltage in mV
	const double T0 = 25.0;
	const double V0 = 1.0003453;
	const double p1 = 4.0514854E-02;
	const double p2 = -3.8789638E-05;
	const double p3 = -2.8608478E-06;
	const double p4 = -9.5367041E-10;
	const double q1 = -1.3948675E-03;
	const double q2 = -6.7976627E-05;

	return this->computeColdJunction(Tcj, T0, V0, p1, p2, p3, p4, q1, q2);
}

double TypeK::computeTemperature(double millivolts)
{
	// Type K equations
	// millivolts = voltage in mV
	// Returns computed temperature in Celsius
	double T0, V0, p1, p2, p3, p4, q1, q2, q3;

	if( (-6.404 < millivolts) && (millivolts <= -3.554) )
	{
		T0 = -1.2147164E+02;
		V0 = -4.1790858E+00;
		p1 = 3.6069513E+01;
		p2 = 3.0722076E+01;
		p3 = 7.7913860E+00;
		p4 = 5.2593991E-01;
		q1 = 9.3939547E-01;
		q2 = 2.7791285E-01;
		q3 = 2.5163349E-02;
	}
	else if( (-3.554 < millivolts) && (millivolts <= 4.096) )
	{
		T0 = -8.7935962E+00;
		V0 = -3.4489914E-01;
		p1 = 2.5678719E+01;
		p2 = -4.9887904E-01;
		p3 = -4.4705222E-01;
		p4 = -4.4869203E-02;
		q1 = 2.3893439E-04;
		q2 = -2.0397750E-02;
		q3 = -1.8424107E-03;
	}
	else if( (4.096 < millivolts) && (millivolts <= 16.397) )
	{
		T0 = 3.1018976E+02;
		V0 = 1.2631386E+01;
		p1 = 2.4061949E+01;
		p2 = 4.0158622E+00;
		p3 = 2.6853917E-01;
		p4 = -9.7188544E-03;
		q1 = 1.6995872E-01;
		q2 = 1.1413069E-02;
		q3 = -3.9275155E-04;
	}
	else if( (16.397 < millivolts) && (millivolts <= 33.275) )
	{
		T0 = 6.0572562E+02;
		V0 = 2.5148718E+01;
		p1 = 2.3539401E+01;
		p2 = 4.6547228E-02;
		p3 = 1.3444400E-02;
		p4 = 5.9236853E-04;
		q1 = 8.3445513E-04;
		q2 = 4.6121445E-04;
		q3 = 2.5488122E-05;
	}
	else if( (33.275 < millivolts) && (millivolts <= 69.553) )
	{
		T0 = 1.0184705E+03;
		V0 = 4.1993851E+01;
		p1 = 2.5783239E+01;
		p2 = -1.8363403E+00;
		p3 = 5.6176662E-02;
		p4 = 1.8532400E-04;
		q1 = -7.4803355E-02;
		q2 = 2.3841860E-03;
		q3 = 0.0000000E+00;
	}
	else
	{
		return (AbstractThermocouple::TCOUPLE_OUT_OF_RANGE);
	}

	return this->computeTemperatureInternal(millivolts, T0, V0, p1, p2, p3, p4, q1, q2, q3);
}


/*********************************************************************************************************
Type N Thermocouple Implementation
*********************************************************************************************************/

double TypeN::computeColdJunctionVoltage(double Tcj)
{
	// Type N equations
	// Tcj = temperature in Celsius
	// Returns equivalent voltage in mV

	const double T0 = 7.0000000E+00;
	const double V0 = 1.8210024E-01;
	const double p1 = 2.6228256E-02;
	const double p2 = -1.5485539E-04;
	const double p3 = 2.1366031E-06;
	const double p4 = 9.2047105E-10;
	const double q1 = -6.4070932E-03;
	const double q2 = 8.2161781E-05;

	return this->computeColdJunction(Tcj, T0, V0, p1, p2, p3, p4, q1, q2);
}

double TypeN::computeTemperature(double millivolts)
{
	// Type N equations
	// millivolts = voltage in mV
	// Returns computed temperature in Celsius
	double T0, V0, p1, p2, p3, p4, q1, q2, q3;

	if (-4.313 <= millivolts && millivolts < 0.0)
	{
		T0 = -5.9610511E+01;
		V0 = -1.5000000E+00;
		p1 = 4.2021322E+01;
		p2 = 4.7244037E+00;
		p3 = -6.1153213E+00;
		p4 = -9.9980337E-01;
		q1 = 1.6385664E-01;
		q2 = -1.4994026E-01;
		q3 = -3.0810372E-02;
	}
	else if (0.0 <= millivolts && millivolts < 20.613)
	{
		T0 = 3.1534505E+02;
		V0 = 9.8870997E+00;
		p1 = 2.7988676E+01;
		p2 = 1.5417343E+00;
		p3 = -1.4689457E-01;
		p4 = -6.8322712E-03;
		q1 = 6.2600036E-02;
		q2 = -5.1489572E-03;	
		q3 = -2.8835863E-04;
	}
	else if (20.613 <= millivolts && millivolts < 47.513)
	{
		T0 = 1.0340172E+03;
		V0 = 3.7565475E+01;
		p1 = 2.6029492E+01;
		p2 = -6.0783095E-01;
		p3 = -9.7742562E-03;
		p4 = -3.3148813E-06;
		q1 = -2.5351881E-02;
		q2 = -3.8746827E-04;	
		q3 = 1.7088177E-06;
	}
	else
	{
		return (AbstractThermocouple::TCOUPLE_OUT_OF_RANGE);
	}

	return this->computeTemperatureInternal(millivolts, T0, V0, p1, p2, p3, p4, q1, q2, q3);
}

/*********************************************************************************************************
Type R Thermocouple Implementation
*********************************************************************************************************/

double TypeR::computeColdJunctionVoltage(double Tcj)
{
	// Type R equations
	// Tcj = temperature in Celsius
	// Returns equivalent voltage in mV

	const double T0 = 2.5000000E+01;
	const double V0 = 1.4067016E-01;
	const double p1 = 5.9330356E-03;
	const double p2 = 2.7736904E-05;
	const double p3 = -1.0819644E-06;
	const double p4 = -2.3098349E-09;
	const double q1 = 2.6146871E-03;
	const double q2 = -1.8621487E-04;

	return this->computeColdJunction(Tcj, T0, V0, p1, p2, p3, p4, q1, q2);
}

double TypeR::computeTemperature(double millivolts)
{
	// Type R equations
	// millivolts = voltage in mV
	// Returns computed temperature in Celsius
	double T0, V0, p1, p2, p3, p4, q1, q2, q3;

	if (-0.226 <= millivolts && millivolts < 1.469)
	{
		T0 = 1.3054315E+02;
		V0 = 8.8333090E-01;
		p1 = 1.2557377E+02;
		p2 = 1.3900275E+02;
		p3 = 3.3035469E+01;
		p4 = -8.5195924E-01;
		q1 = 1.2232896E+00;
		q2 = 3.5603023E-01;
		q3 = 0.0;
	}
	else if (1.469 <= millivolts && millivolts < 7.461)
	{
		T0 = 5.4188181E+02;
		V0 = 4.9312886E+00;
		p1 = 9.0208190E+01;
		p2 = 6.1762254E+00;
		p3 = -1.2279323E+00;
		p4 = 1.4873153E-02;
		q1 = 8.7670455E-02;
		q2 = -1.2906694E-02;	
		q3 = 0.0;
	}
	else if (7.461 <= millivolts && millivolts < 14.277)
	{
		T0 = 1.0382132E+03;
		V0 = 1.1014763E+01;
		p1 = 7.4669343E+01;
		p2 = 3.4090711E+00;
		p3 = -1.4511205E-01;
		p4 = 6.3077387E-03;
		q1 = 5.6880253E-02;
		q2 = -2.0512736E-03;	
		q3 = 0.0;
	}
	else if (14.277 <= millivolts && millivolts < 21.101)
	{
		T0 = 1.5676133E+03;
		V0 = 1.8397910E+01;
		p1 = 7.1646299E+01;
		p2 = -1.0866763E+00;
		p3 = -2.0968371E+00;
		p4 = -7.6741168E-01;
		q1 = -1.9712341E-02;
		q2 = -2.9903595E-02;	
		q3 = -1.0766878E-02;
	}
	else
	{
		return (AbstractThermocouple::TCOUPLE_OUT_OF_RANGE);
	}

	return this->computeTemperatureInternal(millivolts, T0, V0, p1, p2, p3, p4, q1, q2, q3);
}

/*********************************************************************************************************
Type S Thermocouple Implementation
*********************************************************************************************************/

double TypeS::computeColdJunctionVoltage(double Tcj)
{
	// Type S equations
	// Tcj = temperature in Celsius
	// Returns equivalent voltage in mV
	const double T0 = 2.5000000E+01;
	const double V0 = 1.4269163E-01;
	const double p1 = 5.9829057E-03;
	const double p2 = 4.5292259E-06;
	const double p3 = -1.3380281E-06;
	const double p4 = -2.3742577E-09;
	const double q1 = -1.0650446E-03;
	const double q2 = -2.2042420E-04;

	return this->computeColdJunction(Tcj, T0, V0, p1, p2, p3, p4, q1, q2);
}

double TypeS::computeTemperature(double millivolts)
{
	// Type T equations
	// millivolts = voltage in mV
	// Returns computed temperature in Celsius
	double T0, V0, p1, p2, p3, p4, q1, q2, q3;

	if (-0.236 <= millivolts && millivolts < 1.441)
	{
		T0 = 1.3792630E+02;
		V0 = 9.3395024E-01;
		p1 = 1.2761836E+02;
		p2 = 1.1089050E+02;
		p3 = 1.9898457E+01;
		p4 = 9.6152996E-02;
		q1 = 9.6545918E-01;
		q2 = 2.0813850E-01;
		q3 = 0.0;
	}
	else if (1.441 <= millivolts && millivolts < 6.913)
	{
		T0 = 4.7673468E+02;
		V0 = 4.0037367E+00;
		p1 = 1.0174512E+02;
		p2 = -8.9306371E+00;
		p3 = -4.2942435E+00;
		p4 = 2.0453847E-01;
		q1 = -7.1227776E-02;
		q2 = -4.4618306E-02;	
		q3 = 1.6822887E-03;
	}
	else if (6.913 <= millivolts && millivolts < 12.856)
	{
		T0 = 9.7946589E+02;
		V0 = 9.3508283E+00;
		p1 = 8.7126730E+01;
		p2 = -2.3139202E+00;
		p3 = -3.2682118E-02;
		p4 = 4.6090022E-03;
		q1 = -1.4299790E-02;
		q2 = -1.2289882E-03;	
		q3 = 0.0;
	}
	else if (12.856 <= millivolts && millivolts < 18.693)
	{
		T0 = 1.6010461E+03;
		V0 = 1.6789315E+01;
		p1 = 8.4315871E+01;
		p2 = -1.0185043E+01;
		p3 = -4.6283954E+00;
		p4 = -1.0158749E+00;
		q1 = -1.2877783E-01;
		q2 = -5.5802216E-02;	
		q3 = -1.2146518E-02;
	}
	else
	{
		return (AbstractThermocouple::TCOUPLE_OUT_OF_RANGE);
	}

	return this->computeTemperatureInternal(millivolts, T0, V0, p1, p2, p3, p4, q1, q2, q3);
}

/*********************************************************************************************************
Type T Thermocouple Implementation
*********************************************************************************************************/

double TypeT::computeColdJunctionVoltage(double Tcj)
{
	// Type T equations
	// Tcj = temperature in Celsius
	// Returns equivalent voltage in mV
	const double T0 = 2.5000000E+01;
	const double V0 = 9.9198279E-01;
	const double p1 = 4.0716564E-02;
	const double p2 = 7.1170297E-04;
	const double p3 = 6.8782631E-07;
	const double p4 = 4.3295061E-11;
	const double q1 = 1.6458102E-02;
	const double q2 = 0.0;

	return this->computeColdJunction(Tcj, T0, V0, p1, p2, p3, p4, q1, q2);
}

double TypeT::computeTemperature(double millivolts)
{
	// Type T equations
	// millivolts = voltage in mV
	// Returns computed temperature in Celsius
	double T0, V0, p1, p2, p3, p4, q1, q2, q3;
	if (-6.18 <= millivolts && millivolts < -4.648)
	{
		T0 = -1.9243000E+02;
		V0 = -5.4798963E+00;
		p1 = 5.9572141E+01;
		p2 = 1.9675733E+00;
		p3 = -7.8176011E+01;
		p4 = -1.0963280E+01;
		q1 = 2.7498092E-01;
		q2 = -1.3768944E+00;
		q3 = -4.5209805E-01;
	}
	else if (-4.648 <= millivolts && millivolts < 0.0)
	{
		T0 = -6.0000000E+01;
		V0 = -2.1528350E+00;
		p1 = 3.0449332E+01;
		p2 = -1.2946560E+00;
		p3 = -3.0500735E+00;
		p4 = -1.9226856E-01;
		q1 = 6.9877863E-03;
		q2 = -1.0596207E-01;  
		q3 = -1.0774995E-02;
	}
	else if (0.0 <= millivolts && millivolts < 9.288)
	{
		T0 = 1.3500000E+02;
		V0 = 5.9588600E+00;
		p1 = 2.0325591E+01;
		p2 = 3.3013079E+00;
		p3 = 1.2638462E-01;
		p4 = -8.2883695E-04;
		q1 = 1.7595577E-01;
		q2 = 7.9740521E-03; 
		q3 = 0.0;
	}
	else if (9.288 <= millivolts && millivolts < 20.872)
	{
		T0 = 3.0000000E+02;
		V0 = 1.4861780E+01;
		p1 = 1.7214707E+01;
		p2 = -9.3862713E-01;
		p3 = -7.3509066E-02;
		p4 = 2.9576140E-04;
		q1 = -4.8095795E-02;
		q2 = -4.7352054E-03;  
		q3 = -1.2146518E-02;
	}
	else
	{
		return (AbstractThermocouple::TCOUPLE_OUT_OF_RANGE);
	}

	return this->computeTemperatureInternal(millivolts, T0, V0, p1, p2, p3, p4, q1, q2, q3);
}
