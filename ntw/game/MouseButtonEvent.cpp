//
//  MouseButtonEvent.cpp
//  ntw
//
//  Created by Gideon on 6/16/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "MouseButtonEvent.h"

void MouseButtonEvent::setFunction( std::function< void( ) > _func )
{
	func = _func;
}

void MouseButtonEvent::setAction( Action a )
{
	action = a;
}
void MouseButtonEvent::setBinding( Binding b )
{
	gameAction = b;
}

bool MouseButtonEvent::test(Binding b, Action a)
{
	return (action == a && gameAction == b);
}

void MouseButtonEvent::process( )
{
	func();
}