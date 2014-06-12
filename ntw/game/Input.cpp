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
void keyboardCallBack_w( GLFWwindow* wind, int key, int action, int a, int b )
{
	Input::keyboardCallBack(key, action);
}

void scrollCallBack_w( GLFWwindow* wind, double xoff, int yoff )
{
	Input::scrollCallBack(xoff, yoff);
}

void cursorPosCallBack_w( GLFWwindow* wind, double x, double y )
{
	//std::cout << x << "," << y << std::endl;
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
}

void Input::cursorPosCB(double x, double y)
{
	//
	inst->xp = x;
	inst->yp = y;
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

void Input::keyboardCallBack(int key, int action)
{
	//
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

int Input::getAction( Actions act )
{
	return glfwGetKey( wind, keyMap[act] );
}
