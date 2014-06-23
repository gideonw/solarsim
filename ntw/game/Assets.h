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

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../tdogl/Program.h"

struct asset {
    tdogl::Program* shaders;
	GLuint texture;
    GLuint vbo;
    GLuint vao;
	GLuint vio;
    GLenum drawType;
    GLint drawStart;
    GLint drawCount;
	glm::mat4 transform;
	asset() :
		shaders(nullptr),
		texture(0),
		vbo(0),
		vao(0),
		vio(0),
		drawType(GL_POINTS),
		drawStart(0),
		drawCount(0)
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
	
	void loadGalaxy(std::vector<float>* verts);
	void loadOctree(std::vector<glm::vec3>& v, std::vector<unsigned int>& inds);
	
	asset* loadUiAsset();
	asset* loadUiAsset(glm::vec2 orig, GLfloat h, GLfloat w);
	
	tdogl::Program* program;
	tdogl::Program* programUi;
	tdogl::Program* programOt;
	tdogl::Program* programPl;
	
};

#endif /* defined(__ntw__Assets__) */
