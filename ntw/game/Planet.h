//
//  Planet.h
//  ntw
//
//  Created by Gideon on 6/2/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__Planet__
#define __ntw__Planet__

#include <iostream>
#include <list>
#include <random>

#include "SolarSystemObject.h"
#include "Moon.h"

class Planet : public SolarSystemObject {
	static int idCounter;
	
public:
	int type;
	// in KM
	int radius;
	//in AU
	int orbitRadius;
	int id;
	
	//economy sim info (probably exract for interface, or have the sim point to this object)
	double gdp;
	unsigned long population;
	
public:
	Planet();
	void gen(std::mt19937& eng);
	
};

#endif /* defined(__ntw__Planet__) */
