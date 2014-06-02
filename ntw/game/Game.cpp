//
//  Game.cpp
//  ntw
//
//  Created by Gideon on 6/1/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//


#include "Game.h"

Game* Game::inst = nullptr;

Game::Game()
{
}

void Game::start()
{
	inst = new Game();
	
	// initialise GLFW
	inst->graphics.initGLFW();
    
	inst->graphics.openWindow();
	
    // GLFW settings
    glfwDisable(GLFW_MOUSE_CURSOR);
    glfwSetMousePos(0, 0);
    glfwSetMouseWheel(0);
	
	inst->graphics.initGLEW();
	
	inst->graphics.setOpenGlSettings();
	
	inst->graphics.checkOpenGlVersion();
    
    // load vertex and fragment shaders into opengl
    inst->graphics.loadShaders(inst->as);
	
    // load the texture
    //LoadTexture();
	
    // create buffer and fill it with the points of the triangle
	
	inst->as.loadCloud();
	
	inst->as.loadSquare();
	
	//LoadTriangle();
	
	inst->graphics.setUpCamera();
    
    
    inst->gameLoop();
	
    // clean up and exit
    glfwTerminate();
	
}

void Game::gameLoop()
{
	
	// run while the window is open
	double lastTime = glfwGetTime();
    while(glfwGetWindowParam(GLFW_OPENED)){
        // update the scene based on the time elapsed since last update
        double thisTime = glfwGetTime();
        update(thisTime - lastTime);
        lastTime = thisTime;
        
        // draw one frame
        //Render();
		graphics.render(env, as);
		
        // check for errors
        GLenum error = glGetError();
        if(error != GL_NO_ERROR)
            std::cerr << "OpenGL Error " << error << ": " << (const char*)gluErrorString(error) << std::endl;
		
        //exit program if escape key is pressed
        if(glfwGetKey(GLFW_KEY_ESC))
            glfwCloseWindow();
    }
	
}

void Game::update(float secondsElapsed)
{
	
	env.gDegreesRotated += secondsElapsed * env.degreesPerSecond;
    while(env.gDegreesRotated > 360.0f) env.gDegreesRotated -= 360.0f;
	
	if(glfwGetKey('R')){
		env.degreesPerSecond = 10.0f;
	} else if(glfwGetKey('T')){
		env.degreesPerSecond = 0.0f;
	}
	
    //move position of camera based on WASD keys, and XZ keys for up and down
	
	
	if(glfwGetKey('[')){
		env.moveSpeed += 5.0f;
		std::cout << env.moveSpeed << std::endl;
	} else if (glfwGetKey(']')){
		env.moveSpeed -= 5.0f;
		while (env.moveSpeed < 0.0f) {
			env.moveSpeed = 5.0f;
		}
	}
	
	//if(glfwGetKey('J'))
		//LoadCloud();
	
    if(glfwGetKey('S')){
        graphics.camera.offsetPosition(secondsElapsed * env.moveSpeed * -graphics.camera.forward());
    } else if(glfwGetKey('W')){
        graphics.camera.offsetPosition(secondsElapsed * env.moveSpeed * graphics.camera.forward());
    }
    if(glfwGetKey('A')){
        graphics.camera.offsetPosition(secondsElapsed * env.moveSpeed * -graphics.camera.right());
    } else if(glfwGetKey('D')){
        graphics.camera.offsetPosition(secondsElapsed * env.moveSpeed * graphics.camera.right());
    }
    if(glfwGetKey('Z')){
        graphics.camera.offsetPosition(secondsElapsed * env.moveSpeed * -glm::vec3(0,1,0));
    } else if(glfwGetKey('X')){
        graphics.camera.offsetPosition(secondsElapsed * env.moveSpeed * glm::vec3(0,1,0));
    }
	
    //rotate camera based on mouse movement
    const float mouseSensitivity = 0.1;
    int mouseX, mouseY;
    glfwGetMousePos(&mouseX, &mouseY);
    graphics.camera.offsetOrientation(mouseSensitivity * mouseY, mouseSensitivity * mouseX);
    glfwSetMousePos(0, 0); //reset the mouse, so it doesn't go out of the window
	
    //increase or decrease field of view based on mouse wheel
    const float zoomSensitivity = -0.2;
    float fieldOfView = graphics.camera.fieldOfView() + zoomSensitivity * (float)glfwGetMouseWheel();
    if(fieldOfView < 5.0f) fieldOfView = 5.0f;
    if(fieldOfView > 130.0f) fieldOfView = 130.0f;
    graphics.camera.setFieldOfView(fieldOfView);
    glfwSetMouseWheel(0);

}

