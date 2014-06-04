//
//  Env.h
//  ntw
//
//  Created by Gideon on 6/1/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__Env__
#define __ntw__Env__

#include <iostream>

#include "Galaxy.h"

// meant to keep any game variables or data/data structures
class Env
{
public:
	Env();
	
	void initializeEnv();
	
	//Variables!!!
	float gDegreesRotated = 10.0f;
	float degreesPerSecond = 0.0f;
	
	float moveSpeed = 2000.0f;
	
	int numStars = 1200000;
	
	Galaxy galaxy;
};

#endif /* defined(__ntw__Env__) */
