/*
*  Node.h
*  ntw
*
*  Created by Gideon on 6/18/14.
*   Copyright (c) 2014 Gideon. All rights reserved.
*/
#ifndef __ntw__Node__
#define __ntw__Node__

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

#include <glm/glm.hpp>

#include "Obj.h"

using namespace std;

class Node {
	
	glm::vec3 center;
	glm::vec3 halfDimension;
	
	deque<Node*> children;
	Obj* data = nullptr;
	
	int get_instert_octant(const glm::vec3& p) const;
	
public:
	Node(glm::vec3 center, glm::vec3 size);
	void split();
	void split_and_ins(int child, Obj* ins);
	bool is_leaf_w_data() const;
	bool is_leaf() const;
	void set_data(Obj*);
	void insert(Obj*);
	void get_points_inside_box(const glm::vec3& bmin, const glm::vec3& bmax, std::deque<Obj*>& results);
	//bad algo, there is a real one out there taht will be faster
	Obj* nearest_neighbor( Obj* o );
	void nearest_neighbors(Obj* o, int minCount, std::deque<Obj*>& results);
	void node_count(int& count);
	void leaf_count(int& count);
	void accum_verts(std::vector<glm::vec3>& v, std::vector<unsigned int>& inds );
};

#endif /* defined(__ntw__Node__) */
