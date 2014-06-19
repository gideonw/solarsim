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
#include <locale>
#include <limits>
#include <chrono>
#include <deque>

#include <glm/glm.hpp>

#include "GalacticObject.h"
#include "SolarSystem.h"

#include "Octree.h"

class Galaxy {
public: //temp
	std::deque<GalacticObject*> systems;
	std::deque<float>* verts;

private:
	unsigned int seed;
	
public:

	Galaxy();
	void gen();
	void gen2();
	std::deque<float>* getGalaxyVerticies();
	
	void printGalaxyStats();
	void makeGraph();
	Octree* oct;
};

#endif /* defined(__ntw__Galaxy__) */
