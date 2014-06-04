//
//  Galaxy.h
//  ntw
//
//  Created by Gideon on 6/2/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__Galaxy__
#define __ntw__Galaxy__

#include <iostream>
#include <list>
#include <complex>
#include <random>
#include <vector>

#include "GalacticObject.h"
#include "SolarSystem.h"


class Galaxy {
	std::list<GalacticObject*> systems;
	std::vector<float>* verts;
	
public:
	
	Galaxy();
	void gen();
	std::vector<float>* getGalaxyVerticies();
};

#endif /* defined(__ntw__Galaxy__) */
