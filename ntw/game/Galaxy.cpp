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

void Galaxy::makeGraph()
{
	oct = new Octree(75000);
	for (int i = 0; i < systems.size(); i++) {
		oct->root->insert(systems[i]);
	}
}

void Galaxy::printGalaxyStats()
{
	double max = 0.0;
	double min = 100000;
	double max_gdp = 0.0;
	double min_gdp = std::numeric_limits<double>::max();
	double avg_gdp = 0.0;
	unsigned long max_pop = 0;
	unsigned long min_pop = std::numeric_limits<unsigned long>::max();
	unsigned long avg_pop = 0;
	double sys_max_gdp = 0.0;
	double sys_min_gdp = std::numeric_limits<double>::max();
	double sys_avg_gdp = 0.0;
	unsigned long sys_max_pop = 0.0;
	unsigned long sys_min_pop = std::numeric_limits<unsigned long>::max();
	unsigned long sys_avg_pop = 0.0;
	int sys_cnt = 0;
	int cnt = 0;
	
	for (auto var : systems)
	{
		double a = glm::distance(var->position, glm::vec3(0.0,0.0,0.0));
		max = std::max(max, a);
		min = std::min(min, a);
		
		for (auto pl : ((SolarSystem*)var)->objects)
		{
			sys_avg_gdp += ((Planet*)pl)->gdp;
			sys_max_gdp = std::max(((Planet*)pl)->gdp, sys_max_gdp);
			sys_min_gdp = std::min(((Planet*)pl)->gdp, sys_min_gdp);
			
			sys_avg_pop += ((Planet*)pl)->population;
			sys_max_pop = std::max(((Planet*)pl)->population, sys_max_pop);
			sys_min_pop = std::min(((Planet*)pl)->population, sys_min_pop);
			
			sys_cnt++;
		}
		
		if (sys_cnt == 0)
			
			continue;
		
		sys_avg_gdp = sys_avg_gdp/ (double)sys_cnt;
		sys_avg_pop = sys_avg_pop/ (unsigned long)sys_cnt;
		
		max_gdp = std::max(sys_max_gdp, max_gdp);
		min_gdp = std::min(sys_min_gdp, min_gdp);
		avg_gdp += sys_avg_gdp;
		
		max_pop = std::max(sys_max_pop, max_pop);
		min_pop = std::min(sys_min_pop, min_pop);
		avg_pop += sys_avg_pop;
		
		sys_cnt = 0;
		sys_max_gdp = 0;
		sys_min_gdp = std::numeric_limits<double>::max();
		sys_avg_gdp = 0;
		sys_max_pop = 0;
		sys_min_pop = std::numeric_limits<unsigned long>::max();
		sys_avg_pop = 0;
		
		cnt++;
	}
	
	avg_gdp = avg_gdp / (double)cnt;
	avg_pop = avg_pop / (double)cnt;
	
	std::cout.imbue(std::locale("en_US.UTF-8"));
	
	std::cout
	<< std::fixed << std::endl
	<< "Gal Seed: \t" << seed << std::endl
	<< "SS Count: \t" << cnt << std::endl
	<< "Max GDP: \t" << max_gdp << std::endl
	<< "Min GDP: \t" << min_gdp << std::endl
	<< "Avg GDP: \t" << avg_gdp << std::endl << std::endl
	<< "Max Pop: \t" << max_pop << std::endl
	<< "Min Pop: \t" << min_pop << std::endl
	<< "Avg Pop: \t" << avg_pop << std::endl << std::endl;
	
	std::cout	<< "Max Dist: \t" << max << std::endl
				<< "Min Dist: \t" << min << std::endl;
	//////////////////////////////////////////////////
	/*
	typedef std::chrono::steady_clock::time_point time_p;
	typedef std::chrono::duration<int,std::milli> millisecs_t ;
	typedef std::chrono::duration<int,std::micro> microsecs_t ;
	namespace chro = std::chrono;
	
	time_p start = chro::steady_clock::now();
	
	makeGraph();
	
	time_p end = chro::steady_clock::now();
    millisecs_t duration( chro::duration_cast<millisecs_t>(end-start) ) ;
	int lcnt = 0;
	oct->root->leaf_count(lcnt);
	int ncnt = 0;
	oct->root->node_count(ncnt);
    std::cout << duration.count() << " ms.\n\t Leafs: \t " << lcnt << std::endl << "\t Nodes: \t"  << ncnt << std::endl;
	
	start = chro::steady_clock::now() ;
	for(int i = 0; i < 1; i++)
	{
		std::deque<Obj*> res;
		Obj* r = oct->root->nearest_neighbor(systems[i]);
	}
	
	end = chro::steady_clock::now();
    microsecs_t duration2( chro::duration_cast<microsecs_t>(end-start) ) ;
	
    std::cout << duration2.count() << " micros.\n" ;
	
	start = chro::steady_clock::now() ;
	for(int i = 0; i < 10; i++)
	{
		//std::cout << "3 Nearest to " << ((SolarSystem*)systems[i*100])->id << std::endl;
		std::deque<Obj*> res;
		oct->root->nearest_neighbors(systems[i*100], 3, res);
		//for_each(res.begin(), res.end(), [](Obj* o) { std::cout << "\t " << ((SolarSystem*)o)->id << std::endl;});
	}
	
	end = chro::steady_clock::now();
	duration2 = chro::duration_cast<microsecs_t>(end-start);
	
    std::cout << duration2.count() << " micros.\n" ;
	//std::cout << glm::distance(r->position, systems[0]->position) << std::endl;
	std::cout <<  (ncnt * sizeof(float) * 3 * 16) * ((float)std::mega::den / (float)std::mega::num) << "MB" << std::endl;
	//size of octree debug lines, its tiny just draw all of them
	 */
}

void Galaxy::gen2()
{
	double au2ly = 1/64000;
	
	std::random_device rnd;
	std::mt19937 eng(rnd());
	GalacticObject* newObj;
	int goType = GOTypes::SS;
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
	
	//making the ball in the middle
	//further from the gen point, the less spread they points should be
		
	newObj->position.x = 0.0;
	newObj->position.y = 0.0;
	newObj->position.z = 0.0;
	systems.push_back(newObj);
	newObj = nullptr;

	
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
	
	//making the ball in the middle
	//further from the gen point, the less spread they points should be
	
	newObj->position.x = 50000;
	newObj->position.y = 0.0;
	newObj->position.z = 0.0;
	systems.push_back(newObj);
	newObj = nullptr;
	
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
	
	//making the ball in the middle
	//further from the gen point, the less spread they points should be
	
	newObj->position.x = 50.0 * au2ly;
	newObj->position.y = 0.0;
	newObj->position.z = 0.0;
	systems.push_back(newObj);
	newObj = nullptr;
	
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
	
	//making the ball in the middle
	//further from the gen point, the less spread they points should be
	
	newObj->position.x = 30.0*au2ly;
	newObj->position.y = 0.0;
	newObj->position.z = 0.0;
	systems.push_back(newObj);
	newObj = nullptr;
	
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
	
	//making the ball in the middle
	//further from the gen point, the less spread they points should be
	
	newObj->position.x = 1.8*au2ly;
	newObj->position.y = 0.0;
	newObj->position.z = 0.0;
	systems.push_back(newObj);
	newObj = nullptr;
	
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
	
	//making the ball in the middle
	//further from the gen point, the less spread they points should be
	
	newObj->position.x = 4.3;
	newObj->position.y = 0.0;
	newObj->position.z = 0.0;
	systems.push_back(newObj);
	newObj = nullptr;
	
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
	
	//making the ball in the middle
	//further from the gen point, the less spread they points should be
	
	newObj->position.x = 4.3 + (3*au2ly);
	newObj->position.y = 0.0;
	newObj->position.z = 0.0;
	systems.push_back(newObj);
	newObj = nullptr;
	
	
}

void Galaxy::gen()
{
	std::random_device rnd;
	seed = rnd();
	std::mt19937 eng(seed);
	std::uniform_real_distribution<float> xz_dist(-5000, 5000);
	std::uniform_real_distribution<float> y_dist(-2000, 2000);
	std::normal_distribution<> y_dist2(0, 1000);
	std::normal_distribution<> xz_norm_dist(0,5000);
	
	
	//GO object type, right now there are only two, but we are going to only
	// ask for 0 type (SolarSystem)
	std::normal_distribution<> galactic_object_type(0,0);
	
	std::vector<float> a;
	
	int numArms = 3;
	
	double rotateStep = (2 * 3.14156) / numArms;
	
	for( int i = 0; i < numArms; i++ )
	{
		//grab the current rotation for this arm.
		double d = i * rotateStep;
		//generate spiral points
		for(double t = -10.0; t <= 10.0; t += 0.005)
		{
			//double d = 0;
			double radius = 2500;//old:5000 new:2500
			double scale_it = 1;
			std::complex<double> ct(t), paramExp(0.3);
			
			double x = radius * exp(ct * paramExp).real() * cos(t + d);
			double y = 0;
			double z = radius * exp(ct * paramExp).real() * sin(t + d);
			
			int star_count = 75 * exp(-0.25*(t+10.0));//old:500, new:250 (75, 0.17)
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
				
				newObj->position.x = x1*scale_it;
				newObj->position.y = y1*scale_it;
				newObj->position.z = z1*scale_it;
				systems.push_back(newObj);
				newObj = nullptr;
			}
		}
	}
	makeGraph();
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