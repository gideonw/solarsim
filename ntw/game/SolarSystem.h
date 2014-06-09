//
//  SolarSystem.h
//  ntw
//
//  Created by Gideon on 6/2/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__SolarSystem__
#define __ntw__SolarSystem__

#include <iostream>
#include <vector>
#include <random>

#include "Star.h"
#include "SolarSystemObject.h"
#include "GalacticObject.h"
#include "Planet.h"

class SolarSystem : public GalacticObject {
	Star* star;
public://temp pub, need get
	std::vector<SolarSystemObject*> objects;
	
	//inheirits position from galacticObject, this is the center of the system
	
	int id;
	
public:
	
	SolarSystem();
	void gen(std::mt19937& eng);
	int getStarType();
	
};

#endif /* defined(__ntw__SolarSystem__) */
