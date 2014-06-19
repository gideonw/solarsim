/*
*  Octree.cpp
*  ntw
*
*  Created by Gideon on 6/18/14.
*   Copyright (c) 2014 Gideon. All rights reserved.
*/

#include "Octree.h"

Octree::Octree(int size)
{
	glm::vec3 dim(1.0,1.0,1.0);
	root = new Node(glm::vec3(0.0,0.0,0.0), dim*(float)size);
}