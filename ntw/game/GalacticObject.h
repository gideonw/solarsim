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

enum GOTypes {
	SS = 0,
	NEBULA = 1
	};

class GalacticObject {
public:
	glm::vec3 position;
	GOTypes goType;
};

#endif /* defined(__ntw__GalacticObject__) */
