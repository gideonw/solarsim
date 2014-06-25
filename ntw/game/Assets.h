//
//  Assets.h
//  ntw
//
//  Created by Gideon on 6/1/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__Assets__
#define __ntw__Assets__

#include <iostream>
#include <list>
#include <complex>
#include <random>
#include <deque>
#include <unordered_map>
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../tdogl/Program.h"

struct asset {
    tdogl::Program* shaders;
	GLuint texture;
    GLuint vbo;
	GLuint pos_vbo;
    GLuint vao;
	GLuint vio;
    GLenum drawType;
    GLint drawStart;
    GLint drawCount;
	bool wireframe;
	glm::mat4 transform;
	asset() :
		shaders(nullptr),
		texture(0),
		vbo(0),
		pos_vbo(0),
		vao(0),
		vio(0),
		drawType(GL_POINTS),
		drawStart(0),
		drawCount(0),
		wireframe(false)
    {
	}
};

//factory
class Assets
{
private:
	std::list<asset*> assets;
public:
	Assets();
	
	std::list<asset*>* getAssetList();
	void addAsset(asset* a);
	
	void loadGalaxy(std::vector<glm::vec4>& v, std::vector<unsigned int>& inds);
	void loadOctree(std::vector<glm::vec3>& v, std::vector<unsigned int>& inds);
	
	void loadSphere();
	
	asset* loadUiAsset();
	asset* loadUiAsset(glm::vec2 orig, GLfloat h, GLfloat w);
	
	tdogl::Program* program;
	tdogl::Program* programUi;
	tdogl::Program* programOt;
	tdogl::Program* programPl;
	
};

class GeometryProvider
{
public:
	static void Icosahedron(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices)
    {
		indices = {
			1,    5,    2,
			2,    5,    3,
			3,    5,    4,
			4,    5,    1,
			1,    0,    4,
			4,    0,    3,
			3,    0,    2,
			2,    0,    1
		};
		float X = 1.0f;
		float Z = 1.0f;
		float Y = Z;
		
		vertices = {
			glm::vec3(0.0f,		0.0f,	Z),
			glm::vec3(X,		0.0f,	0.0f),
			glm::vec3(0.0f,		Y,		0.0f),
			glm::vec3(-X,		0.0f,	0.0f),
			glm::vec3(0.0f,		-Y,		0.0f),
			glm::vec3(0.0f,		0.0f,	-Z)
		};
	}
	
	static void rec(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices, int level)
	{
		struct KeyFuncs
		{
			size_t operator()(const glm::vec3& k)const
			{
				using std::size_t;
				using std::hash;
				using std::string;
				
				size_t seed = 0;
				
				hash<float> hasher;
				seed ^= hasher(k.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
				seed ^= hasher(k.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
				seed ^= hasher(k.z) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
				
				return seed;
				// Compute individual hash values for first,
				// second and third and combine them using XOR
				// and bit shifting:
				
				//return ((hash<float>()() ^ (hash<float>()(k.y) << 1)) >> 1) ^ (hash<float>()(k.z) << 1);
			}
			
			bool operator()(const glm::vec3& a, const glm::vec3& b)const
			{
				return a.x == b.x && a.y == b.y && a.z == b.z;
			}
		};
		std::vector<glm::vec3> nVerts;
		std::vector<unsigned int> nInds;
		
		std::unordered_map<glm::vec3, unsigned int, KeyFuncs, KeyFuncs> indMap;
		
		//split the passed in geometry
		int index = 0;
		for (int i = 0; i < indices.size()-2; i+=3) {
			//split it!
			glm::vec3 v0 = vertices[indices[i]];
			glm::vec3 v1 = vertices[indices[i+1]];
			glm::vec3 v2 = vertices[indices[i+2]];
			//      v0
			//     /  \
			//    w1 - w0
			//   /  \ /  \
			// v2---w2---v1
			
			//calculate the mid points for our points
			glm::vec3 w0 = glm::vec3( (v0.x + v1.x)/2.0f, (v0.y + v1.y)/2.0f, (v0.z + v1.z)/2.0f);
			glm::vec3 w1 = glm::vec3( (v1.x + v2.x)/2.0f, (v1.y + v2.y)/2.0f, (v1.z + v2.z)/2.0f);
			glm::vec3 w2 = glm::vec3( (v0.x + v2.x)/2.0f, (v0.y + v2.y)/2.0f, (v0.z + v2.z)/2.0f);
			
			int cnt = indMap.count(v0);
			if(!(cnt > 0))
			{
				indMap[v0] = index;
				index++;
				nVerts.push_back(v0);
			}
			cnt = indMap.count(v1);
			if(!(cnt > 0))
			{
				indMap[v1] = index;
				index++;
				nVerts.push_back(v1);
			}
			if(!(indMap.count(v2) > 0))
			{
				indMap[v2] = index;
				index++;
				nVerts.push_back(v2);
			}
			if(!(indMap.count(w0) > 0))
			{
				indMap[w0] = index;
				index++;
				nVerts.push_back(w0);
			}
			if(!(indMap.count(w1) > 0))
			{
				indMap[w1] = index;
				index++;
				nVerts.push_back(w1);
			}
			if(!(indMap.count(w2) > 0))
			{
				indMap[w2] = index;
				index++;
				nVerts.push_back(w2);
			}
			//tri 0
			nInds.push_back(indMap[v0]);
			nInds.push_back(indMap[w0]);
			nInds.push_back(indMap[w2]);
			
			//tri 1
			nInds.push_back(indMap[v1]);
			nInds.push_back(indMap[w1]);
			nInds.push_back(indMap[w0]);
			
			//tri 2
			nInds.push_back(indMap[v2]);
			nInds.push_back(indMap[w2]);
			nInds.push_back(indMap[w1]);
			
			//tri 3
			nInds.push_back(indMap[w0]);
			nInds.push_back(indMap[w1]);
			nInds.push_back(indMap[w2]);
			
		}
		
		for (int i = 0; i < nVerts.size(); i++)
			nVerts[i]= glm::normalize(nVerts[i]);
		
		//if we have more levels to go then recurse
		if(level > 0)
			rec(nVerts, nInds, level-1);
		
		//return the new set
		vertices = nVerts;
		indices = nInds;
	}
};

#endif /* defined(__ntw__Assets__) */
