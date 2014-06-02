//
//  Graphics.cpp
//  ntw
//
//  Created by Gideon on 6/1/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "Graphics.h"

Graphics::Graphics()
{
	screenSize.x = 800;
	screenSize.y = 600;
}

Graphics::Graphics(int _width, int _height):screenSize(_width, _height)
{
}

void Graphics::initGLFW()
{
	if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
}

void Graphics::openWindow()
{
    // open a window with GLFW
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    if(!glfwOpenWindow((int)screenSize.x, (int)screenSize.y, 8, 8, 8, 8, 24, 0, GLFW_WINDOW))
        throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 3.2?");
}

void Graphics::initGLEW()
{
	// initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    
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
}

void Graphics::setUpCamera()
{
	// setup gCamera
    camera.setPosition(glm::vec3(0,0,4));
    camera.setViewportAspectRatio(screenSize.x / screenSize.y);
}

void Graphics::loadShaders(Assets& as)
{
	std::vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("vertex-shader.txt"), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("fragment-shader.txt"), GL_FRAGMENT_SHADER));
    as.program = new tdogl::Program(shaders);
	
	
	std::vector<tdogl::Shader> uishaders;
    uishaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("ui-vert-shader.txt"), GL_VERTEX_SHADER));
    uishaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("ui-frag-shader.txt"), GL_FRAGMENT_SHADER));
    as.programUi = new tdogl::Program(uishaders);
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
		}
		
		////////// Shader Generic operations
		
		
		glBindVertexArray(draw->vao);
		
		glDrawArrays(draw->drawType, draw->drawStart, draw->drawCount);
		
		glBindVertexArray(0);
		
		draw->shaders->stopUsing();
	}
	
	/*
    // bind the program (the shaders)
	
    as.program->use();
	
    // set the "camera" uniform
    as.program->setUniform("camera", camera.matrix());
	
    // set the "model" uniform in the vertex shader, based on the gDegreesRotated global
    as.program->setUniform("model", glm::rotate(glm::mat4(), env.gDegreesRotated, glm::vec3(0,1,0)));
	
    // bind the texture and set the "tex" uniform in the fragment shader
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, gTexture->object());
    //gProgram->setUniform("tex", 0); //set to 0 because the texture is bound to GL_TEXTURE0
	
    // bind the VAO (the triangle)
    glBindVertexArray(gVAO);
    
    // draw the VAO
	if(!glfwGetKey('Q')){
		glDrawArrays(GL_POINTS, 0, env.numStars);
	} else {
		glDrawArrays(GL_TRIANGLES, 0, env.numStars);
	}
    
    // unbind the VAO, the program and the texture
    glBindVertexArray(0);
    //glBindTexture(GL_TEXTURE_2D, 0);
    program->stopUsing();
	
	
	///////////////////////////////////////////////////////
	
	programUi->use();
	
	glBindVertexArray(gVAOUI);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
	
	glBindVertexArray(0);
	
	programUi->stopUsing();
	*/
	
	///////////////////////////////////////////////////////
    // swap the display buffers (displays what was just drawn)
    glfwSwapBuffers();
}
