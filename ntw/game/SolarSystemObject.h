//
//  SolarSystemObject.h
//  ntw
//
//  Created by Gideon on 6/2/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__SolarSystemObject__
#define __ntw__SolarSystemObject__

#include <iostream>
#include <vector>

class SolarSystemObject {

public:
	// THings currently orbiting me
	std::vector<SolarSystemObject*> orbitalBodies;
};

#endif /* defined(__ntw__SolarSystemObject__) */
