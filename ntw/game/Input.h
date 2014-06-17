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

#include "MouseButtonEvent.h"
#include "KeyEvent.h"
#include "InputEnum.h"

class Input {
public:
	
private:

	std::map<Binding, int> keyMap;
	std::map<int, Binding> keyToBindingMap;
	std::deque<KeyEvent> keyInputEvents;
	
	std::map<Binding, int> mouseMap;
	std::map<int, Binding> mouseToBindingMap;
	std::deque<MouseButtonEvent> mouseInputEvents;
	
	char keyPresses[GLFW_KEY_LAST+1];
	
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
	
	void bindMouseAction( MouseButtonEvent fn );
	void bindKeyAction( KeyEvent fn );

	int getAction( Binding act );
	
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
