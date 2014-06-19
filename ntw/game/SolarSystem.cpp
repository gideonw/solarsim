//
//  SolarSystem.cpp
//  ntw
//
//  Created by Gideon on 6/2/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "SolarSystem.h"

int SolarSystem::nextId = 0;

SolarSystem::SolarSystem()
{
	star = nullptr;
	objects = {};
	id = nextId;
	nextId++;
}

void SolarSystem::gen(std::mt19937 &eng)
{
	//generate the solar system
	std::normal_distribution<> star_type(7,3.5);
	std::uniform_int_distribution<> num_planets(0, 7);
	
	int t = star_type(eng);
	Star* newStar = new Star(t);
	star = newStar;
	newStar = nullptr;
	
	//based on star type select the types of planets and number of planets
	
	int np = num_planets(eng);
	for (int i = 0; i < np; i++) {
		Planet* so = new Planet();
		so->gen(eng);
		objects.push_back(so);
		so = nullptr;
	}
	
}

int SolarSystem::getStarType()
{
	return star->getType();
}