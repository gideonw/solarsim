//
//  util.cpp
//  ntw
//
//  Created by Gideon on 6/1/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "util.h"

std::string ResourcePath(std::string fileName)
{
	return std::string("/Users/gideon/Projects/ntw/ntw/resources/").append(fileName);
}