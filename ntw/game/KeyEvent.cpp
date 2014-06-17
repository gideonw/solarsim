//
//  KeyEvent.cpp
//  ntw
//
//  Created by Gideon on 6/8/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "KeyEvent.h"

void KeyEvent::setAction( Action a )
{
	action = a;
}
void KeyEvent::setBinding( Binding b )
{
	gameAction = b;
}

bool KeyEvent::test(Binding b, Action a)
{
	return (action == a && gameAction == b);
}

void KeyEvent::process( )
{
	func();
}