//
//  Graphics.h
//  ntw
//
//  Created by Gideon on 6/1/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__Graphics__
#define __ntw__Graphics__

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/glfw2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

#include "../tdogl/Camera.h"
#include "../tdogl/Program.h"

#include "util.h"
#include "Env.h"
#include "Assets.h"

class Graphics
{
private:
	glm::vec2 screenSize;
	
public:
	tdogl::Camera camera;
	Awesomium::WebCore* web_core;
	Awesomium::WebView* view;
public:
	Graphics();
	Graphics(int width, int height);
	
	//static methods to load the Opengl libraries
	void initGLFW();
	void openWindow();
	void initGLEW();
	void setOpenGlSettings();
	void checkOpenGlVersion();
	void loadShaders(Assets& as);
	void setUpCamera();
	
	void testLoadAwe();
	
	void render(Env& env, Assets& as);
	
	void exit();
};


#endif /* defined(__ntw__Graphics__) */
