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
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("fragment-shader.fs"), GL_FRAGMENT_SHADER));
    as.program = new tdogl::Program(shaders);
	
	
	std::vector<tdogl::Shader> uishaders;
    uishaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("ui-vert-shader.vs"), GL_VERTEX_SHADER));
    uishaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("ui-frag-shader.fs"), GL_FRAGMENT_SHADER));
    as.programUi = new tdogl::Program(uishaders);
	
	std::vector<tdogl::Shader> otshaders;
    otshaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("octree-debug.vs"), GL_VERTEX_SHADER));
    otshaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("octree-debug.fs"), GL_FRAGMENT_SHADER));
    as.programOt = new tdogl::Program(otshaders);
	
	std::vector<tdogl::Shader> plshaders;
    plshaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("planet-vert.vs"), GL_VERTEX_SHADER));
    plshaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("planet-frag.fs"), GL_FRAGMENT_SHADER));
    as.programPl = new tdogl::Program(plshaders);
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
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, draw->texture);
			draw->shaders->setUniform("tex", 0);
		} else if (as.programOt == draw->shaders)
		{
			// set the "camera" uniform
			as.programOt->setUniform("camera", camera.matrix());
			
			// set the "model" uniform in the vertex shader, based on the gDegreesRotated global
			as.programOt->setUniform("model", glm::rotate(glm::mat4(), env.gDegreesRotated, glm::vec3(0,1,0)));
			
			glBindVertexArray(draw->vao);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, draw->vio);
			
			glDrawElements(draw->drawType, draw->drawCount, GL_UNSIGNED_INT, 0);
			
			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			
			draw->shaders->stopUsing();
			
			continue;
			
		}
		
		//use instanced drawing for the stars, then gather a list of the indicies of the ones to draw as stars and the ones to draw as spheres, only change it if the number of stars within a certain distance changes.
		
		//draw stars:: 1, 3, 5
		//draw sphere: 2, 4, 6, 7
		//move, use a range cube in front of the camera location. (look into frustrum culling method from videos)
		
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

