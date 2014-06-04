//
//  Planet.h
//  ntw
//
//  Created by Gideon on 6/2/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__Planet__
#define __ntw__Planet__

#include <iostream>
#include <list>

#include "SolarSystemObject.h"
#include "Moon.h"

class Planet : public SolarSystemObject {
	int type;
	std::list<Moon> moons;
	
public:
	
};

#endif /* defined(__ntw__Planet__) */
