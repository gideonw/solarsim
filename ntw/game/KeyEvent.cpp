//
//  KeyEvent.cpp
//  ntw
//
//  Created by Gideon on 6/8/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "KeyEvent.h"

KeyEvent::KeyEvent( int _key, std::function< void () > _runEvent )
	:key( _key ),runEvent(_runEvent)
{
	
}

void KeyEvent::test( int test_key )
{
	if(test_key == key)
		runEvent();
}
