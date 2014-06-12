//
//  Interface.cpp
//  ntw
//
//  Created by Gideon on 6/9/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "Interface.h"


Interface::Interface()
{
	WebConfig config;
	core = WebCore::Initialize(config);
}

void Interface::loadUiWindows(Assets& as)
{
	//load menu
	WebURL url(WSLit("file:////Users/gideon/Projects/ntw/ntw/resources/ui/search.html"));
	uiWindow* nui = new uiWindow(url, as.loadUiAsset(), core);
	nui->loadViewIntoAsset();
	windows.push_back(nui);
	
}

void Interface::update()
{
	for(auto uiw : windows)
	{
		BitmapSurface* surf = (BitmapSurface*)uiw->getSurface();
		if(surf == 0)
			continue;
		
		//if(surf->is_dirty())
		//{
			core->Update();
			uiw->reloadTexture();
		//}
	}
}