//
//  GalacticObject.h
//  ntw
//
//  Created by Gideon on 6/2/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__GalacticObject__
#define __ntw__GalacticObject__

#include <iostream>
#include <glm/glm.hpp>

#include "Obj.h"

enum GOTypes {
	SS = 0,
	NEBULA = 1
	};

class GalacticObject : public Obj {
public:
	GOTypes goType;
};

#endif /* defined(__ntw__GalacticObject__) */
