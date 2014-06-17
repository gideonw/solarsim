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
	
	//coords in LY
	double ly2au = 63400.07;
	
	Galaxy galaxy;
	
	bool camLook = false;
	float moveCamForward = 0.0f;
	float moveCamBack = 0.0f;
	float moveCamStrafe_L = 0.0f;
	float moveCamStrafe_R = 0.0f;
};

#endif /* defined(__ntw__Env__) */
