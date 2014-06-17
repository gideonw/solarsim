//
//  InputEnum.h
//  ntw
//
//  Created by Gideon on 6/16/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef ntw_InputEnum_h
#define ntw_InputEnum_h

enum Action
{
	PRESSED = 1,
	RELEASED = 2
};
enum Binding
{
	ACT_UNBOUND		= 0,
	//CAMERA
	CAM_STRAFE_L	= 1,
	CAM_STRAFE_R	= 2,
	CAM_FORWARD		= 3,
	CAM_BACK		= 4,
	CAM_ZOOM_OUT	= 5,
	CAM_ZOOM_IN		= 6,
	CAM_MOVE_UP		= 7,
	CAM_MOVE_DOWN	= 8,
	CAM_TOGGLE_LOOK = 9,
	CAM_LOOK_MBTN	= 10,
	
	//OPENGL
	//RELOAD_SHADER	= 70,
	
	//PROGRAM
	PROG_CLOSE		= 9999
};


#endif
