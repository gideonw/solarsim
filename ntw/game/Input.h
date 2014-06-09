//
//  Input.h
//  ntw
//
//  Created by Gideon on 6/8/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__Input__
#define __ntw__Input__

#include <iostream>
#include <functional>
#include <vector>
#include <map>

#include <GL/glfw.h>

#include "KeyEvent.h"
#include "MouseEvent.h"

class Input {
public:
	enum Actions
	{
		//CAMERA
		CAM_STRAFE_L	= 0,
		CAM_STRAFE_R	= 1,
		CAM_FORWARD		= 2,
		CAM_BACK		= 3,
		CAM_ZOOM_OUT	= 4,
		CAM_ZOOM_IN		= 5,
		CAM_MOVE_UP		= 6,
		CAM_MOVE_DOWN	= 7,
		
		//OPENGL
		//RELOAD_SHADER	= 70,
		
		//PROGRAM
		PROG_CLOSE		= 9999
	};

private:

	std::map<Actions, int> keyMap;
	std::map<Actions, std::function<void(int)>> keyEvents;
	
public:
	static Input* inst;
	Input();
	static Input* init( void );
	void setupGLFWHandlers();
	
	static void keyboardCallBack(int key, int action);
	
	bool bindAction( Actions act, std::function<void(int)> fn );

	int getAction(Actions act);
};

#endif /* defined(__ntw__Input__) */
