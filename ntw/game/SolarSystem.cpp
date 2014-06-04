//
//  SolarSystem.cpp
//  ntw
//
//  Created by Gideon on 6/2/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "SolarSystem.h"

SolarSystem::SolarSystem()
{
	star = nullptr;
	objects = {};
}

void SolarSystem::gen(std::mt19937 &eng)
{
	//generate the solar system
	std::normal_distribution<> star_type(7,3.5);
	int t = star_type(eng);
	Star* newStar = new Star(t);
	star = newStar;
	objects.push_back((SolarSystemObject*)newStar);
}

int SolarSystem::getStarType()
{
	return star->getType();
}