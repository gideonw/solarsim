//
//  Planet.cpp
//  ntw
//
//  Created by Gideon on 6/2/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "Planet.h"

int Planet::idCounter = 0;

Planet::Planet()
{
	type = 0;
	radius = 10000;
	orbitRadius = 10;
	id = idCounter;
	idCounter++;
	population = 0.0;
	gdp = 0.0;
}

void Planet::gen(std::mt19937& eng)
{
	std::uniform_int_distribution<> radii(2439, 69911);
	std::uniform_int_distribution<> gdp_per_cap(4170, 30170);
	std::uniform_int_distribution<> pop_per_rad(5000,100000);

	radius = radii(eng);
	population = ((unsigned long)pop_per_rad(eng)) * ((unsigned long)radius);
	gdp = ((double)(population * (gdp_per_cap(eng)-1000)));
	
}