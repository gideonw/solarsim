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
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <list>
#include <sstream>

// tdogl classes
#include "../tdogl/Program.h"
#include "../tdogl/Texture.h"
#include "../tdogl/Camera.h"

//my classes
#include "Graphics.h"
#include "Env.h"
#include "Assets.h"

class Game
{
public:
	static Game* inst;
	
private:
	Env env;
	Assets as;
	Graphics graphics;

	Game();
	
public:
	static void start();
	
	void gameLoop();
	
	void update(float secondsElapsed);
	
};

#endif /* defined(__ntw__Game__) */
