/*
*  Node.cpp
*  ntw
*
*  Created by Gideon on 6/18/14.
*   Copyright (c) 2014 Gideon. All rights reserved.
*/

#include "Node.h"

Node::Node(glm::vec3 _center, glm::vec3 size)
{
	center = _center;
	halfDimension = size;
	children.resize(8, nullptr);
}

bool Node::is_leaf_w_data() const
{
	return is_leaf() && data != nullptr;
}

bool Node::is_leaf() const
{
	bool leaf = true;
	for(int i = 0; i < 8; i++)
	{
		leaf &= children[i] == nullptr;
	}
	return leaf;
}

void Node::insert(Obj* ins)
{
	if (is_leaf()) {
		if(data == nullptr) {
			data = ins;
		} else {
			//split and insert
			split();
			split_and_ins(get_instert_octant(ins->position), ins);
		}
	} else {
		split_and_ins(get_instert_octant(ins->position), ins);
	}
}

void Node::set_data(Obj * d)
{
	data = d;
}

void Node::split()
{
	Obj* oldData = data;
	data = nullptr;
	int i = get_instert_octant(oldData->position);
	glm::vec3 newCenter = center;
	newCenter.x += halfDimension.x * (i&4 ? .5f : -.5f);
	newCenter.y += halfDimension.y * (i&2 ? .5f : -.5f);
	newCenter.z += halfDimension.z * (i&1 ? .5f : -.5f);
	children[i] = new Node(newCenter, halfDimension*0.5f); //change
	children[i]->set_data(oldData);
}

void Node::split_and_ins(int child, Obj* ins)
{
	if(children[child] == nullptr)
	{
		glm::vec3 newCenter = center;
		newCenter.x += halfDimension.x * (child&4 ? .5f : -.5f);
		newCenter.y += halfDimension.y * (child&2 ? .5f : -.5f);
		newCenter.z += halfDimension.z * (child&1 ? .5f : -.5f);
		children[child] = new Node(newCenter, halfDimension*0.5f);
	}
	children[child]->insert(ins);
}

int Node::get_instert_octant(const glm::vec3& point) const {
	int oct = 0;
	if(point.x >= center.x) oct |= 4;
	if(point.y >= center.y) oct |= 2;
	if(point.z >= center.z) oct |= 1;
	return oct;
}

void Node::get_points_inside_box(const glm::vec3& bmin, const glm::vec3& bmax, std::deque<Obj*>& results) {
	// If we're at a leaf node, just see if the current data point is inside
	// the query bounding box
	if(is_leaf()) {
		if(data != nullptr) {
			const glm::vec3& p = data->position;
			if(p.x>bmax.x || p.y>bmax.y || p.z>bmax.z) return;
			if(p.x<bmin.x || p.y<bmin.y || p.z<bmin.z) return;
			results.push_back(data);
		}
	} else {
		// We're at an interior node of the tree. We will check to see if
		// the query bounding box lies outside the octants of this node.
		for(int i=0; i<8; ++i) {
			if (children[i] !=nullptr) {
				// Compute the min/max corners of this child octant
				glm::vec3 cmax = children[i]->center + children[i]->halfDimension;
				glm::vec3 cmin = children[i]->center - children[i]->halfDimension;
				
				// If the query rectangle is outside the child's bounding box,
				// then continue
				if(cmax.x<bmin.x || cmax.y<bmin.y || cmax.z<bmin.z) continue;
				if(cmin.x>bmax.x || cmin.y>bmax.y || cmin.z>bmax.z) continue;
				
				// At this point, we've determined that this child is intersecting
				// the query bounding box
				children[i]->get_points_inside_box(bmin,bmax,results);
			}
		}
	}
}

Obj* Node::nearest_neighbor(Obj* o)
{
	glm::vec3 bmin(-100,-100,-100);
	glm::vec3 bmax(100,100,100);
	bmin += o->position;
	bmax += o->position;
	
	std::deque<Obj*> res;
	do {
		res.clear();
		get_points_inside_box(bmin, bmax, res);
	} while (res.size() > 100);

	std::sort(res.begin(), res.end(), [o](Obj* a, Obj* b){
		double d1 = glm::distance(a->position, o->position);
		double d2 = glm::distance(b->position, o->position);
		return d1 < d2;
	});
	//remove myself
	res.pop_front();

	return res[0];
}


void Node::nearest_neighbors(Obj *o, int minCount, std::deque<Obj *> &results)
{
	glm::vec3 bmin(0,0,0);
	glm::vec3 bmax(0,0,0);
	bmin += o->position;
	bmax += o->position;
	
	do {
		bmin -= glm::vec3(100, 100, 100);
		bmax += glm::vec3(100, 100, 100);
		results.clear();
		get_points_inside_box(bmin, bmax, results);
	} while (results.size() < minCount);
	
	std::sort(results.begin(), results.end(), [o](Obj* a, Obj* b){
		double d1 = glm::distance(a->position, o->position);
		double d2 = glm::distance(b->position, o->position);
		return d1 < d2;
	});
	//remove myself
	results.pop_front();
	
}

void Node::node_count(int &count)
{
	count++;
	for(int i = 0; i < 8; i++)
	{
		if(children[i] != nullptr){
			children[i]->node_count(count);
		}
	}
}

void Node::leaf_count(int &count)
{
	if (is_leaf_w_data()) {
		count++;
	} else {
		for(int i = 0; i < 8; i++)
		{
			if(children[i] != nullptr){
				children[i]->leaf_count(count);
			}
		}
	}
}

void Node::accum_verts(std::vector<glm::vec3>& v, std::vector<unsigned int>& inds )
{
	glm::vec3 hd = halfDimension;
	glm::vec3 v1( center.x - hd.x, center.y + hd.y, center.z + hd.z );
	glm::vec3 v2( center.x + hd.x, center.y + hd.y, center.z + hd.z );
	glm::vec3 v3( center.x + hd.x, center.y + hd.y, center.z - hd.z );
	glm::vec3 v4( center.x - hd.x, center.y + hd.y, center.z - hd.z );
	
	glm::vec3 v5( center.x - hd.x, center.y - hd.y, center.z + hd.z );
	glm::vec3 v6( center.x + hd.x, center.y - hd.y, center.z + hd.z );
	glm::vec3 v7( center.x + hd.x, center.y - hd.y, center.z - hd.z );
	glm::vec3 v8( center.x - hd.x, center.y - hd.y, center.z - hd.z );
	
	unsigned int first = v.size();
	//verts
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	v.push_back(v4);
	v.push_back(v5);
	v.push_back(v6);
	v.push_back(v7);
	v.push_back(v8);
	
	//top
	inds.push_back(first);
	inds.push_back(first+1);
	
	inds.push_back(first+1);
	inds.push_back(first+2);
	
	inds.push_back(first+2);
	inds.push_back(first+3);
	
	inds.push_back(first+3);
	inds.push_back(first);
	
	//bottom
	inds.push_back(first+4);
	inds.push_back(first+5);
	
	inds.push_back(first+5);
	inds.push_back(first+6);
	
	inds.push_back(first+6);
	inds.push_back(first+7);
	
	inds.push_back(first+7);
	inds.push_back(first+4);
	
	//sides
	inds.push_back(first);
	inds.push_back(first+4);
	
	inds.push_back(first+1);
	inds.push_back(first+5);
	
	inds.push_back(first+2);
	inds.push_back(first+6);
	
	inds.push_back(first+3);
	inds.push_back(first+7);
	
	for(int i = 0; i < 8; i++)
	{
		if(children[i] != nullptr){
			children[i]->accum_verts(v, inds);
		}
	}
}

