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
#include <deque>

#include "Interface.h"

#include <GL/glfw3.h>

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
		CAM_TOGGLE_LOOK = 8,
		
		//OPENGL
		//RELOAD_SHADER	= 70,
		
		//PROGRAM
		PROG_CLOSE		= 9999
	};

private:

	std::map<Actions, int> keyMap;
	std::map<Actions, std::function<void(int)>> keyEvents;
		
	double xoff;
	
public:
	//pointer to interface for mouse handling
	Interface* interface;
	bool uiHasFocus;
	unsigned int cursorMode;
	
	std::function<void(double, double)> cursor;
	
	GLFWwindow* wind;
	static Input* inst;
	Input();
	static Input* init( void );
	void setupGLFWHandlers();
	
	static void keyboardCallBack( int key, int scanCode, int action, int mods );
	static void mouseButtonCallBack( int key, int action, int mods );
	static void scrollCallBack(double xoff, double yoff);
	static void cursorPosCB(double x, double y);
	
	bool bindAction( Actions act, std::function<void(int)> fn );

	int getAction(Actions act);
	
	double getScrollWheelPos();
	void setScrollWheelPos(double pos);
	
	//cursor
	volatile double xp;
	volatile double yp;
	
	void getCursorPos(double* xo, double* yo);
	void setCursorPos(double xi, double yi);
	
	void disableCursor();
	void hideCursor();
	void showCursor();
	unsigned int getCursorMode();
};

#endif /* defined(__ntw__Input__) */
