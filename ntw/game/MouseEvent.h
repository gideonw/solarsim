//
//  MouseEvent.h
//  ntw
//
//  Created by Gideon on 6/9/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__MouseEvent__
#define __ntw__MouseEvent__

#include <iostream>

class MouseEvent {
	int x1, y1;
	int x2, y2;
	std::function< void () > runEvent;
	
public:
	MouseEvent( int _x1, int _y1,
				int _x2, int _y2, std::function< void () > _runEvent );
	void test( int x, int y );
};

#endif /* defined(__ntw__MouseEvent__) */
