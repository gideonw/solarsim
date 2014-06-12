//
//  Game.cpp
//  ntw
//
//  Created by Gideon on 6/1/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//


#include "Game.h"

void print_step(int& step, std::string s)
{
	step++;
	std::cout << step << " - " << s << std::endl;
}

Game* Game::inst = nullptr;

Game::Game()
{
	
}

void Game::start()
{
	inst = new Game();
	int instep = 0;
	
	// initialise GLFW
	
	print_step(instep, "Init GLFW");
	inst->graphics.initGLFW();
	
    print_step(instep, "Open Window");
	inst->graphics.openWindow();
	
	print_step(instep, "Send Window Handler to Graphics");
	inst->wind = inst->graphics.wind;
	
	print_step(instep, "Init Input");
	inst->inp = Input::init();
	
	print_step(instep, "Send Input to Graphics");
	inst->inp->wind = inst->graphics.wind;
	
	print_step(instep, "Init GLEW");
	inst->graphics.initGLEW();
	
	print_step(instep, "Set OpenGL Settings");
	inst->graphics.setOpenGlSettings();
	
	print_step(instep, "Check OpenGL Version");
	inst->graphics.checkOpenGlVersion();
	
	print_step(instep, "GLFW Settings");
	// GLFW settings
	//glfwWindowHint( GLFW_CURSOR_HIDDEN, GL_TRUE );
	glfwSetInputMode( inst->wind, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos( inst->wind, 0, 0 );
	inst->inp->setScrollWheelPos( 0.0 );
	
	print_step(instep, "Setup GLFWHandlers");
	inst->inp->setupGLFWHandlers();
	
    print_step(instep, "Load Shaders");
    // load vertex and fragment shaders into opengl
    inst->graphics.loadShaders(inst->as);
	
	print_step(instep, "Initialize Env");
	//initialize the environment
	inst->env.initializeEnv();
	
	print_step(instep, "Load Galaxy");
    // Load Assets
	inst->as.loadGalaxy(inst->env.galaxy.getGalaxyVerticies());
	
	print_step(instep, "Load UI Windows");
	inst->ui.loadUiWindows(inst->as);
	
	print_step(instep, "Setup Camera");
	inst->graphics.setUpCamera();
	
    print_step(instep, "Game Loop");
    inst->gameLoop();
	
	print_step(instep, "End");
    // clean up and exit
    glfwTerminate();
	
}

void Game::gameLoop()
{
	
	std::random_device rnd;
	std::mt19937 eng(rnd());
	std::uniform_int_distribution<> pick_two(0, (int)env.galaxy.systems.size());
	
	env.galaxy.printGalaxyStats();
	
	// run while the window is open
	double lastTime = glfwGetTime();
    while(!glfwWindowShouldClose(wind)){
        // update the scene based on the time elapsed since last update
        double thisTime = glfwGetTime();
		
        update(thisTime - lastTime);
        lastTime = thisTime;
		// check for errors
        GLenum error = glGetError();
        if(error != GL_NO_ERROR)
            std::cerr << "OpenGL Error Update " << error << ": " << (const char*)gluErrorString(error) << std::endl;
		
		
        // draw one frame
		graphics.render(env, as);
		
        glfwPollEvents();
		
        // check for errors
        error = glGetError();
        if(error != GL_NO_ERROR)
            std::cerr << "OpenGL Error Render" << error << ": " << (const char*)gluErrorString(error) << std::endl;
		
        //exit program if escape key is pressed
        if(glfwGetKey(wind, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(wind, GL_TRUE);
    }
	glfwDestroyWindow(wind);
}

void Game::update(float secondsElapsed)
{
	ui.update();
	
	env.gDegreesRotated += secondsElapsed * env.degreesPerSecond;
    while(env.gDegreesRotated > 360.0f) env.gDegreesRotated -= 360.0f;
	
	if(glfwGetKey(wind, 'R')){
		env.degreesPerSecond = 10.0f;
	} else if(glfwGetKey(wind, 'T')){
		env.degreesPerSecond = 0.0f;
	}
	
    //move position of camera based on WASD keys, and XZ keys for up and down
	
	
	if(glfwGetKey(wind, '[')){
		env.moveSpeed += 10.0f;
		std::cout << env.moveSpeed << std::endl;
	} else if (glfwGetKey(wind, ']')){
		env.moveSpeed -= 10.0f;
		while (env.moveSpeed < 0.0f) {
			env.moveSpeed = 10.0f;
		}
	}
	
	if(glfwGetKey(wind, '\\')){
		env.moveSpeed = 0.5f;
	}
		
	//if(glfwGetKey('J'))
		//LoadCloud();

	
    if(inp->getAction(Input::Actions::CAM_BACK)){
        graphics.camera.offsetPosition(secondsElapsed * env.moveSpeed * -graphics.camera.forward());
    } else if(inp->getAction(Input::Actions::CAM_FORWARD)){
        graphics.camera.offsetPosition(secondsElapsed * env.moveSpeed * graphics.camera.forward());
    }
    if(inp->getAction(Input::Actions::CAM_STRAFE_L)){
        graphics.camera.offsetPosition(secondsElapsed * env.moveSpeed * -graphics.camera.right());
    } else if(inp->getAction(Input::Actions::CAM_STRAFE_R)){
        graphics.camera.offsetPosition(secondsElapsed * env.moveSpeed * graphics.camera.right());
    }
    if(inp->getAction(Input::Actions::CAM_MOVE_UP)){
        graphics.camera.offsetPosition(secondsElapsed * env.moveSpeed * -glm::vec3(0,1,0));
    } else if(inp->getAction(Input::Actions::CAM_MOVE_DOWN)){
        graphics.camera.offsetPosition(secondsElapsed * env.moveSpeed * glm::vec3(0,1,0));
    }
	
    //rotate camera based on mouse movement
    const float mouseSensitivity = 0.1;
    double mouseXo, mouseYo;
    glfwGetCursorPos(wind, &mouseXo, &mouseYo);
	int mouseX, mouseY;
	mouseX = std::floor(mouseXo);
	mouseY = std::floor(mouseYo);
	
	//std::cout << "(" << mouseX << "," << mouseY << ")" << std::endl;
	
    graphics.camera.offsetOrientation(mouseSensitivity * mouseY, mouseSensitivity * mouseX);
    glfwSetCursorPos(wind, 0, 0); //reset the mouse, so it doesn't go out of the window
	
    //increase or decrease field of view based on mouse wheel
    const float zoomSensitivity = -0.2;
    float fieldOfView = graphics.camera.fieldOfView() + zoomSensitivity * (float)(inp->getScrollWheelPos());
    if(fieldOfView < 5.0f) fieldOfView = 5.0f;
    if(fieldOfView > 130.0f) fieldOfView = 130.0f;
    graphics.camera.setFieldOfView(fieldOfView);
    inp->setScrollWheelPos(0);

}


