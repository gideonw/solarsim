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

#include "Assets.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/BitmapSurface.h>

using namespace Awesomium;

class uiWindow {
	
public:
	//user to update the texture
	asset* ui_asset;
	WebView* view;
	WebURL url;
	
	uiWindow(WebURL url, asset* ui_asset, WebCore* core);
	
	void loadViewIntoAsset();
	void reloadTexture();
	
	BitmapSurface* getSurface();
};

#endif /* defined(__ntw__uiWindow__) */
