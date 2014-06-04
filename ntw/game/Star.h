//
//  Star.h
//  ntw
//
//  Created by Gideon on 6/2/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__Star__
#define __ntw__Star__

#include <iostream>

#include "SolarSystemObject.h"

class Star : public SolarSystemObject {
	int type;
	
public:
	Star();
	Star(int type);
	
	int getType();
};

#endif /* defined(__ntw__Star__) */
