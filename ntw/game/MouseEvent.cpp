//
//  MouseEvent.cpp
//  ntw
//
//  Created by Gideon on 6/9/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "MouseEvent.h"

MouseEvent::MouseEvent( int _x1, int _y1,
		   int _x2, int _y2, std::function< void () > _runEvent )
{
	
}

void MouseEvent::test( int x, int y )
{
	/*
		(x1, y1)
			.-----------+
			|	(x,y)	|
			|	.		|
			+-----------.
					(x2, y2)
	 */
	if( ( x < x1 && x > x2 ) &&
		( y < y1 && y < y2 ) )
	{
		runEvent();
	}
}
