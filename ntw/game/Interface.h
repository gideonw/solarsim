//
//  Interface.h
//  ntw
//
//  Created by Gideon on 6/9/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__Interface__
#define __ntw__Interface__

#include <iostream>
#include <vector>


#include "uiWindow.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/BitmapSurface.h>

using namespace Awesomium;


class Interface {
	std::vector<uiWindow*> windows;
	WebCore* core;
public:
	Interface();
	
	void update();
	void loadUiWindows( Assets& as );
	
};

#endif /* defined(__ntw__Interface__) */
