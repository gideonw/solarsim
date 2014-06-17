//
//  Input.cpp
//  ntw
//
//  Created by Gideon on 6/8/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "Input.h"

Input* Input::inst = nullptr;

//sets up the Input module by registering the callback with GLFW
void keyboardCallBack_w( GLFWwindow* wind, int key, int scanCode, int action, int mods )
{
	Input::keyboardCallBack( key, scanCode, action, mods );
}

void mouseButtonCallBack_w( GLFWwindow* wind, int button, int action, int mods )
{
	Input::mouseButtonCallBack( button, action, mods );
}

void scrollCallBack_w( GLFWwindow* wind, double xoff, int yoff )
{
	Input::scrollCallBack( xoff, yoff );
}

void cursorPosCallBack_w( GLFWwindow* wind, double x, double y )
{
	//std::cout << x << "," << y << std::endl;
	x *= 2;
	y *= 2;
	Input::cursorPosCB( x, y );
}

Input::Input()
{
	wind = nullptr;
	//default Key to Action mapping
	
	keyMap[PROG_CLOSE]		=	GLFW_KEY_ESCAPE;
	keyMap[CAM_FORWARD]		=	'W';
	keyMap[CAM_BACK]		=	'S';
	keyMap[CAM_STRAFE_L]	=	'A';
	keyMap[CAM_STRAFE_R]	=	'D';
	keyMap[CAM_MOVE_UP]		=	'Z';
	keyMap[CAM_MOVE_DOWN]	=	'X';
	keyMap[CAM_TOGGLE_LOOK]	=	'C';
	
	mouseMap[CAM_LOOK_MBTN] =	GLFW_MOUSE_BUTTON_RIGHT;
	mouseToBindingMap[GLFW_MOUSE_BUTTON_RIGHT] = CAM_LOOK_MBTN;

	//later:: load from file
}

Input* Input::init()
{
	if(inst == nullptr)
		inst = new Input();
	return inst;
}

void Input::setupGLFWHandlers()
{
	//setup the conrols callbacks.
	glfwSetKeyCallback( wind, keyboardCallBack_w );
	glfwSetCursorPosCallback( wind, cursorPosCallBack_w );
	glfwSetMouseButtonCallback( wind, mouseButtonCallBack_w );
	glfwSetKeyCallback( wind, keyboardCallBack_w );
}

void Input::cursorPosCB(double x, double y)
{
	if (inst->cursorMode != GLFW_CURSOR_DISABLED && inst->interface->handleCursor(x, y)) {
		//cursor handled in ui, set focus
		inst->uiHasFocus = true;
	} else {
		//pass to the cursor to the game, but it doesn't have to use it
		inst->uiHasFocus = false;
		inst->xp = x;
		inst->yp = y;
		inst->cursor(x,y);
		//std::cout << x << "," << y << std::endl;
	}
}

unsigned int Input::getCursorMode()
{
	return cursorMode;
}

void Input::getCursorPos(double* xo, double* yo)
{
	(*xo) = xp;
	(*yo) = yp;
}

void Input::setCursorPos(double xi, double yi)
{
	xp = xi;
	yp = yi;
	glfwSetCursorPos(wind, xp, yp);
}

void Input::disableCursor()
{
	cursorMode = GLFW_CURSOR_DISABLED;
	glfwSetInputMode( inst->wind, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Input::hideCursor()
{
	cursorMode = GLFW_CURSOR_HIDDEN;
	glfwSetInputMode( inst->wind, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Input::showCursor()
{
	cursorMode = GLFW_CURSOR_NORMAL;
	glfwSetInputMode( inst->wind, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Input::keyboardCallBack( int key, int scanCode, int action, int mods )
{
	//if they didn't use the key then we will pass it to everyone else
	//TODO: certain keys we want to pass to the game ragardless and never send
	//		to the ui
	if(inst->uiHasFocus && !inst->interface->passKeyToFocus( key, scanCode, action, mods ))
	{
		//this means that we didn't use the key in the interface so mark it as pressed
		
	}
	Action a = (action == GLFW_PRESS) ? Action::PRESSED : Action::RELEASED;
	
	for (auto var : inst->keyInputEvents)
	{
		if(var.test(inst->keyToBindingMap[key], a))
		{
			var.process();
			break;
		}
	}
}

void Input::mouseButtonCallBack( int button, int action, int mods )
{
	std::cout << button << std::endl;
	if( inst->interface->passMouseButtonToFocus( button, action, mods ) )
	{
		
	}
	Action a = (action == GLFW_PRESS) ? Action::PRESSED : Action::RELEASED;

	for (auto var : inst->mouseInputEvents)
	{
		if(var.test(inst->mouseToBindingMap[button], a))
		{
			var.process();
			break;
		}
	}
}

void Input::bindMouseAction( MouseButtonEvent fn )
{
	mouseInputEvents.push_back(fn);
}

void Input::bindKeyAction( KeyEvent fn )
{
	keyInputEvents.push_back(fn);
}

void Input::scrollCallBack(double xoff, double yoff)
{
	inst->xoff += xoff;
	if(inst->xoff > 100.0)
		inst->xoff = 0.0;
	
	if(inst->xoff < 0.0)
		inst->xoff = 0.0;
}

double Input::getScrollWheelPos()
{
	return xoff;
}

void Input::setScrollWheelPos(double pos)
{
	xoff = pos;
}

int Input::getAction( Binding act )
{
	if(uiHasFocus)
		return GLFW_RELEASE;
	return glfwGetKey( wind, keyMap[act] );
}
