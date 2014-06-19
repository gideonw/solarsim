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

void Assets::loadGalaxy(std::deque<float>* verts)
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

/*
 void Assets::loadSquare()
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
 
 GLfloat vertexData[] = {
 //  X     Y     Z		U		V
 512.0f,	512.0f,	0.0f,	1.0f,	1.0f,
 0.0f,	512.0f,	0.0f,	0.0f,	1.0f,
 0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
 512.0f,	512.0f,	0.0f,	1.0f,	1.0f,
 512.0f,	0.0f,	0.0f,	1.0f,	0.0f,
 0.0f,	0.0f,	0.0f,	0.0f,	0.0f
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
 
 }

 
void Assets::loadCloud()
{
	std::random_device rnd;
	std::mt19937 eng(rnd());
	std::uniform_real_distribution<float> xz_dist(-5000, 5000);
	std::uniform_real_distribution<float> y_dist(-2000, 2000);
	std::normal_distribution<> y_dist2(0, 1000);
	std::normal_distribution<> xz_norm_dist(0,5000);
	std::normal_distribution<> star_type(7,3.5);
	
	asset* tmp = new asset();
	
	tmp->shaders = program;
	tmp->drawType = GL_POINTS;
	
	// make and bind the VAO
    glGenVertexArrays(1, &(tmp->vao));
    glBindVertexArray((tmp->vao));
    
    // make and bind the VBO
    glGenBuffers(1, &(tmp->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, tmp->vbo);
	
	//todo: start using hte new env galaxy!!!! dont forget tmp!!!!
	
	std::vector<float> a;
	
	int numArms = 4;
	
	double rotateStep = (2 * 3.14156) / numArms;
	
	for( int i = 0; i < numArms; i++ )
	{
		//grab the current rotation for this arm.
		double d = i * rotateStep;
		for(double t = -10.0; t <= 10.0; t += 0.005)
		{
			//double d = 0;
			double radius = 5000;
			std::complex<double> ct(t), paramExp(0.3);
			
			double x = radius * exp(ct * paramExp).real() * cos(t + d);
			double y = 0;
			double z = radius * exp(ct * paramExp).real() * sin(t + d);
			
			int star_count = 500 * exp(-0.25*(t+10.0));
			int y_off = 1200 * exp(-0.2*(t+10.0));
			
			
			if((y_off/2) > 300)
				y_dist2.param(decltype(y_dist2.param())(0, (y_off/2)));
				
				
				for(int s = 0; s < star_count; s++)
				{
					
					double xg = xz_dist(eng);
					double zg = xz_dist(eng);
					
					double x1;
					double y1 = y + y_dist2(eng);
					double z1;
					
					//making the ball in the middle
					//further from the gen point, the less spread they points should be
					if(t < -4.5)
					{
						x1 = x + (((double)xz_norm_dist(eng)) * exp(-0.00125*(abs(y1))));
						z1 = z + (((double)xz_norm_dist(eng)) * exp(-0.00125*(abs(y1))));
					} else {
						x1 = x + (xg * exp(-0.00125*(abs(y1))));
						z1 = z + (zg * exp(-0.00125*(abs(y1))));
					}
					a.push_back((float)x1);
					a.push_back((float)y1);
					a.push_back((float)z1);
					int st =  star_type(eng);
					//a.push_back((float) (star_dist(eng)));
					a.push_back((float)st);
				}
			
			
			
			//std::cout << a[i] << ", ";
			//if(i % 3 == 2)
			//	std::cout << std::endl;
		}
	}
	
	tmp->drawCount = (GLint)(a.size()/3);
	std::cout << tmp->drawCount << std::endl;
	
	glBufferData(GL_ARRAY_BUFFER, a.size() * sizeof(float), &a[0], GL_STATIC_DRAW);
	
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
 */
