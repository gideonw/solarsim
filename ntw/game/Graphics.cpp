//
//  Graphics.cpp
//  ntw
//
//  Created by Gideon on 6/1/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "Graphics.h"

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

Graphics::Graphics()
{
	screenSize.x = 1024;
	screenSize.y = 768;
	wind = nullptr;
}

Graphics::Graphics(int _width, int _height):screenSize(_width, _height)
{
	wind = nullptr;
}

void Graphics::initGLFW()
{
	glfwSetErrorCallback(error_callback);
	if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
}

void Graphics::openWindow()
{
    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 32);
	glfwWindowHint(GLFW_STENCIL_BITS, 0);
	
	wind = glfwCreateWindow((int)screenSize.x, (int)screenSize.y, "NTW", NULL, NULL);
	
    if(wind == nullptr)
        throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 3.2?");
	
	glfwMakeContextCurrent(wind);
}

void Graphics::initGLEW()
{
	// initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
	int error = glewInit();
    if(error != GLEW_OK)
	{
		std::cerr << error << std::endl;
        throw std::runtime_error("glewInit failed");
	}
    
    // GLEW throws some errors, so discard all the errors so far
    while(glGetError() != GL_NO_ERROR) {}
}

void Graphics::checkOpenGlVersion()
{
	// print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	
    // make sure OpenGL version 3.2 API is available
    if(!GLEW_VERSION_3_2)
        throw std::runtime_error("OpenGL 3.2 API is not available.");
}

void Graphics::setOpenGlSettings()
{
	// OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	
	glPointSize(1.0f);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable(GL_BLEND);
}

void Graphics::setUpCamera()
{
	// setup gCamera
    camera.setPosition(glm::vec3(0,0,4));
    camera.setViewportAspectRatio(screenSize.x / screenSize.y);
	camera.setNearAndFarPlanes(camera.nearPlane(), 1000000000000.0f);
}

void Graphics::loadShaders(Assets& as)
{
	std::vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("vertex-shader.vs"), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("fragment-shader.frag"), GL_FRAGMENT_SHADER));
    as.program = new tdogl::Program(shaders);
	
	
	std::vector<tdogl::Shader> uishaders;
    uishaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("ui-vert-shader.vs"), GL_VERTEX_SHADER));
    uishaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("ui-frag-shader.frag"), GL_FRAGMENT_SHADER));
    as.programUi = new tdogl::Program(uishaders);
}

void Graphics::test_awe()
{
	using namespace Awesomium;
	
	WebConfig config;
	core = WebCore::Initialize(config);
	
	view = core->CreateWebView(512, 512);
	view->SetTransparent(true);
	WebURL url(WSLit("data:text/html,<html><body><div style=\"font-color: rgba(0.5, 0.5, 0.5, 1.0)\"><h1>Hello World</h1></div><script type=\"text/javascript\">document.write(\"You are running Awesomium \" + awesomium.version);</script></body></html>"));
	view->LoadURL(url);
	
	// finish loading the page
	while (view->IsLoading())
		core->Update();
	
	
	glGenTextures(1, &texture);
	awe_up();
}

void Graphics::awe_up()
{
	using namespace Awesomium;
	core->Update();
	
	BitmapSurface* surface = (BitmapSurface*)view->surface();
	
	// Make sure our surface is not NULL-- it may be NULL if the WebView
	// process has crashed.
	if (surface != 0) {
		// Save our BitmapSurface to a JPEG image in the current
		// working directory.
		if(surface->is_dirty()){
			int w = surface->width();
			int h = surface->height();
			
			unsigned char *buffer = new unsigned char[w * h * 4];
			surface->CopyTo(buffer, w * 4, 4, false, true);
			
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, buffer);
			glBindTexture(GL_TEXTURE_2D, 0);
			delete[] buffer;
		}
	}
}


void Graphics::render(Env& env, Assets& as) {
    // clear everything
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	///////////////////////////////////////////////////////
	
	std::list<asset*>* drawUs = as.getAssetList();
	
	for (auto draw : *drawUs)
	{
		draw->shaders->use();
		
		////////// Shader specific attributes
		if (as.program == draw->shaders) {
			
			// set the "camera" uniform
			as.program->setUniform("camera", camera.matrix());
			
			// set the "model" uniform in the vertex shader, based on the gDegreesRotated global
			as.program->setUniform("model", glm::rotate(glm::mat4(), env.gDegreesRotated, glm::vec3(0,1,0)));
		} else if (as.programUi == draw->shaders)
		{
			awe_up();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			draw->shaders->setUniform("tex", 0);
		}
		
		////////// Shader Generic operations
		
		glBindVertexArray(draw->vao);
		
		glDrawArrays(draw->drawType, draw->drawStart, draw->drawCount);
		
		glBindVertexArray(0);
		
		glBindTexture(GL_TEXTURE_2D, 0);
		
		draw->shaders->stopUsing();
	}
	
    // swap the display buffers (displays what was just drawn)
    glfwSwapBuffers(wind);
}

