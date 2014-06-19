//
//  Assets.cpp
//  ntw
//
//  Created by Gideon on 6/1/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "Assets.h"

Assets::Assets()
{
}

void Assets::addAsset(asset *a)
{
	assets.push_back(a);
}

std::list<asset*>* Assets::getAssetList()
{
	return &assets;
}

asset* Assets::loadUiAsset()
{
	return loadUiAsset(glm::vec2(0.0,0.0), 512.0f, 512.0f);
}

asset* Assets::loadUiAsset(glm::vec2 orig, GLfloat h, GLfloat w)
{
	asset* tmp = new asset();
	
	tmp->shaders = programUi;
	tmp->drawType = GL_TRIANGLE_STRIP;
	
	// make and bind the VAO
    glGenVertexArrays(1, &(tmp->vao));
    glBindVertexArray(tmp->vao);
    
    // make and bind the VBO
    glGenBuffers(1, &(tmp->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, tmp->vbo);
	/*
	GLfloat vertexData[] = {
		//  X			Y				Z		U		V
		
		
		
		orig.x + 0.0f,	orig.y + 0.0f,	0.0f,	0.0f,	0.0f,
		orig.x + h,		orig.y + 0.0f,	0.0f,	1.0f,	0.0f,
		orig.x + h,		orig.y + w,		0.0f,	1.0f,	1.0f,
		orig.x + h,		orig.y + w,		0.0f,	1.0f,	1.0f,
		orig.x + 0.0f,	orig.y + 0.0f,	0.0f,	0.0f,	0.0f,
		orig.x + 0.0f,	orig.y + w,		0.0f,	0.0f,	1.0f,
		orig.x + h,		orig.y + w,		0.0f,	1.0f,	1.0f,
	};*/
	
	GLfloat vertexData[] = {
		//  X			Y				Z		U		V
		orig.x + h,		orig.y + w,		0.0f,	1.0f,	1.0f,
		orig.x + 0.0f,	orig.y + w,		0.0f,	0.0f,	1.0f,
		orig.x + 0.0f,	orig.y + 0.0f,	0.0f,	0.0f,	0.0f,
		orig.x + h,		orig.y + w,		0.0f,	1.0f,	1.0f,
		orig.x + h,		orig.y + 0.0f,	0.0f,	1.0f,	0.0f,
		orig.x + 0.0f,	orig.y + 0.0f,	0.0f,	0.0f,	0.0f
	};
	//set the draw count for gl_draw arrays
	tmp->drawCount = 6;
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(tmp->shaders->attrib("vert"));
	glVertexAttribPointer(tmp->shaders->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
	
	glEnableVertexAttribArray(tmp->shaders->attrib("vertTexCoord"));
	glVertexAttribPointer(tmp->shaders->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
	
    glBindVertexArray(0);
	
	addAsset(tmp);
	return tmp;
}

void Assets::loadGalaxy(std::vector<float>* verts)
{
	asset* tmp = new asset();
	
	tmp->shaders = program;
	tmp->drawType = GL_POINTS;
	
	// make and bind the VAO
    glGenVertexArrays(1, &(tmp->vao));
    glBindVertexArray((tmp->vao));
    
    // make and bind the VBO
    glGenBuffers(1, &(tmp->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, tmp->vbo);

	tmp->drawCount = (GLint)(verts->size()/3);
	
	glBufferData(GL_ARRAY_BUFFER, verts->size() * sizeof(float), &(*verts)[0], GL_STATIC_DRAW);
	
    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(tmp->shaders->attrib("vert"));
    glVertexAttribPointer(tmp->shaders->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), NULL);
	
    // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
	
    glEnableVertexAttribArray(tmp->shaders->attrib("starType"));
    glVertexAttribPointer(tmp->shaders->attrib("starType"), 1, GL_FLOAT, GL_TRUE,  4*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
	
    // unbind the VAO
    glBindVertexArray(0);
	
	addAsset(tmp);
	
}

void Assets::loadOctree(std::vector<glm::vec3>& v, std::vector<unsigned int>& inds)
{
	std::vector<float>* verts = new std::vector<float>();
	asset* tmp = new asset();
	
	for (auto var : v)
	{
		verts->push_back(var.x);
		verts->push_back(var.y);
		verts->push_back(var.z);
	}
	
	tmp->shaders = programOt;
	tmp->drawType = GL_LINES;
	
	// make and bind the VAO
    glGenVertexArrays(1, &(tmp->vao));
    glBindVertexArray((tmp->vao));
    
    // make and bind the VBO
    glGenBuffers(1, &(tmp->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, tmp->vbo);
	
	glGenBuffers(1, &(tmp->vio));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmp->vio);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(unsigned int), &inds[0], GL_STATIC_DRAW);
	
	tmp->drawCount = (GLint)(inds.size());
	
	glBufferData(GL_ARRAY_BUFFER, verts->size() * sizeof(float), &(*verts)[0], GL_STATIC_DRAW);
	
    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(tmp->shaders->attrib("vert"));
    glVertexAttribPointer(tmp->shaders->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), NULL);
	
    // unbind the VAO
    glBindVertexArray(0);
	
	addAsset(tmp);
	delete verts;
}
