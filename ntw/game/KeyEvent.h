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

#include "InputEnum.h"

//TODO:: add Modifiers
class KeyEvent {
	Binding gameAction;
	Action action;
	std::function< void( ) > func;
public:
	void setFunction( std::function< void( ) > func );
	void setBinding	( Binding b );
	void setAction	( Action a );
	bool test		( Binding b, Action a );
	void process	( );
};

#endif /* defined(__ntw__KeyEvent__) */
