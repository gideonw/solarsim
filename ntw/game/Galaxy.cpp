//
//  Galaxy.cpp
//  ntw
//
//  Created by Gideon on 6/2/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "Galaxy.h"


Galaxy::Galaxy()
{
	verts = nullptr;
}

void Galaxy::gen()
{
	std::random_device rnd;
	std::mt19937 eng(rnd());
	std::uniform_real_distribution<float> xz_dist(-5000, 5000);
	std::uniform_real_distribution<float> y_dist(-2000, 2000);
	std::normal_distribution<> y_dist2(0, 1000);
	std::normal_distribution<> xz_norm_dist(0,5000);
	
	
	//GO object type, right now there are only two, but we are going to only
	// ask for 0 type (SolarSystem)
	std::normal_distribution<> galactic_object_type(0,0);
	
	std::vector<float> a;
	
	int numArms = 4;
	
	double rotateStep = (2 * 3.14156) / numArms;
	
	for( int i = 0; i < numArms; i++ )
	{
		//grab the current rotation for this arm.
		double d = i * rotateStep;
		//generate spiral points
		for(double t = -10.0; t <= 10.0; t += 0.005)
		{
			//double d = 0;
			double radius = 5000;
			std::complex<double> ct(t), paramExp(0.3);
			
			double x = radius * exp(ct * paramExp).real() * cos(t + d);
			double y = 0;
			double z = radius * exp(ct * paramExp).real() * sin(t + d);
			
			int star_count = 500 * exp(-0.25*(t+10.0));
			int y_off = 1200 * exp(-0.2*(t+10.0));
			
			
			if((y_off/2) > 300)
				y_dist2.param(decltype(y_dist2.param())(0, (y_off/2)));
			
			//generate sector around the spiral point
			for(int s = 0; s < star_count; s++)
			{
				GalacticObject* newObj;
				int goType = galactic_object_type(eng);
				//switch later?
				if(goType == GOTypes::SS)
				{
					newObj = new SolarSystem();
					newObj->goType = GOTypes::SS;
					//type sepecific (SolarSystem)
					SolarSystem* ss = (SolarSystem*)newObj;
					ss->gen(eng);
					ss = nullptr;
				} else {
					newObj = new GalacticObject();
					newObj->goType = (GOTypes)goType;
				}
				
				double xg = xz_dist(eng);
				double zg = xz_dist(eng);
				
				double x1;
				double y1 = y + y_dist2(eng);
				double z1;
				
				//making the ball in the middle
				//further from the gen point, the less spread they points should be
				if(t < -4.5)
				{
					x1 = x + (((double)xz_norm_dist(eng)) * exp(-0.00125*(abs(y1))));
					z1 = z + (((double)xz_norm_dist(eng)) * exp(-0.00125*(abs(y1))));
				} else {
					x1 = x + (xg * exp(-0.00125*(abs(y1))));
					z1 = z + (zg * exp(-0.00125*(abs(y1))));
				}
				
				newObj->position.x = x1;
				newObj->position.y = y1;
				newObj->position.z = z1;
				systems.push_back(newObj);
				newObj = nullptr;
			}
		}
	}
}

std::vector<float>* Galaxy::getGalaxyVerticies()
{
	if(verts != nullptr)
		return verts;
	else
		verts = new std::vector<float>();
	
	for (auto go : systems)
	{
		//3 dereference instead of one
		verts->push_back(go->position.x);
		verts->push_back(go->position.y);
		verts->push_back(go->position.z);
		if(go->goType == GOTypes::SS)
			verts->push_back((float)((SolarSystem*)go)->getStarType());
		else
			verts->push_back(0.0f);
	}
	return verts;
}