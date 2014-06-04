//
//  Star.cpp
//  ntw
//
//  Created by Gideon on 6/2/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "Star.h"

Star::Star():type(0)
{
}

Star::Star(int _type):type(_type)
{
}

int Star::getType()
{
	return type;
}