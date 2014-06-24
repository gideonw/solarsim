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
	std::vector<GalacticObject*> systems;

private:
	unsigned int seed;
	
public:

	Galaxy();
	void gen();
	void gen2();
	void getGalaxyVerticies(std::vector<glm::vec4>& v, std::vector<unsigned int>& inds);
	
	void printGalaxyStats();
	void makeGraph();
	Octree* oct;
};

#endif /* defined(__ntw__Galaxy__) */
