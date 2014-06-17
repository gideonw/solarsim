//
//  Game.h
//  ntw
//
//  Created by Gideon on 6/1/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__Game__
#define __ntw__Game__

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ftgl/ftgl.h>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <list>
#include <complex>
#include <random>
#include <sstream>
#include <iomanip>
#include <locale>
#include <functional>

// tdogl classes
#include "../tdogl/Program.h"
#include "../tdogl/Texture.h"
#include "../tdogl/Camera.h"

//my classes
#include "Graphics.h"
#include "Env.h"
#include "Assets.h"
#include "Input.h"
#include "Interface.h"
#include "InputEnum.h"
#include "MouseButtonEvent.h"

class Game
{
public:
	static Game* inst;
	
private:
	Env env;
	Assets as;
	Graphics graphics;
	Interface ui;
	Input* inp;
	
	Game();
	
public:
	static void start();
	
	void gameLoop();
	
	void update(float secondsElapsed);
	
	void updateCamera(double x, double y);
	
	void enableCamLook();
	void disableCamLook();
	
	GLFWwindow* wind;
	
};

#endif /* defined(__ntw__Game__) */
