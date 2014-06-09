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
void GLFWCALL keyboardCallBack_w( int key, int action )
{
	Input::keyboardCallBack(key, action);
}

Input::Input()
{
	//default Key to Action mapping
	
	keyMap[PROG_CLOSE]		=	GLFW_KEY_ESC;
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
	glfwSetKeyCallback( keyboardCallBack_w );
}

void Input::keyboardCallBack(int key, int action)
{
	//
}

int Input::getAction( Actions act )
{
	return glfwGetKey(keyMap[act]);
}
