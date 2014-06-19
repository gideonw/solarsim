/*
*  Octree.h
*  ntw
*
*  Created by Gideon on 6/18/14.
*   Copyright (c) 2014 Gideon. All rights reserved.
*/
#ifndef __ntw__Octree__
#define __ntw__Octree__

#include <iostream>
#include <glm/glm.hpp>

#include "Node.h"

class Octree {
	public:
	Node* root;
	glm::vec3 dimension;
	
	public:
	Octree(int size);
};


#endif /* defined(__ntw__Octree__) */
