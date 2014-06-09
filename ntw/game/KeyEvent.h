//
//  KeyEvent.h
//  ntw
//
//  Created by Gideon on 6/8/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__KeyEvent__
#define __ntw__KeyEvent__

#include <iostream>
#include <functional>

class KeyEvent {
	int key;
	std::function< void () > runEvent;
	
public:
	KeyEvent( int _key, std::function< void () > _runEvent );
	void test( int test_key );
};

#endif /* defined(__ntw__KeyEvent__) */
