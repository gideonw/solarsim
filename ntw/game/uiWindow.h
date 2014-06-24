//
//  uiWindow.h
//  ntw
//
//  Created by Gideon on 6/9/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#ifndef __ntw__uiWindow__
#define __ntw__uiWindow__

#include <iostream>

#include "glm/glm.hpp"
#include "Assets.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/BitmapSurface.h>

using namespace Awesomium;

struct region {
	region(glm::vec2 orig, double _x1, double _y1, double _x2, double _y2)
	{
		origin = orig;
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
	}
	region(region& r)
	{
		origin = r.origin;
		x1 = r.x1;
		y1 = r.y1;
		x2 = r.x2;
		y2 = r.y2;
	}
	double x1, y1, x2, y2;
	glm::vec2 origin;
	bool test(double x, double y)
	{
		return (x > (x1+origin.x) && x < (x2+origin.x) && y > (y1+origin.y) && y < (y2+origin.y));
	}
};

class uiWindow {
	
	
	
public:
	//user to update the texture
	region reg;
	asset* ui_asset;
	WebView* view;
	WebURL url;
	
	bool dirty;
	
	uiWindow(WebURL url, Assets& ui_asset, WebCore* core, region& r);
	
	void loadViewIntoAsset();
	void reloadTexture();
	
	BitmapSurface* getSurface();
};

#endif /* defined(__ntw__uiWindow__) */
