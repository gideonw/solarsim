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
	lastFocus = nullptr;
}

void Interface::loadUiWindows(Assets& as)
{
	//load menu
	WebURL url(WSLit("file:////Users/gideon/Projects/ntw/ntw/resources/ui/search.html"));
	region r(glm::vec2(0.0,0.0), 0, 0, 220, 220);
	uiWindow* nui = new uiWindow(url, as, core, r);
	nui->loadViewIntoAsset();
	windows.push_back(nui);
	
	//load menu
	WebURL url2(WSLit("file:////Users/gideon/Projects/ntw/ntw/resources/ui/menu.html"));
	region r2(glm::vec2(512.0, 368.0), 0, 0, 310, 220);
	nui = new uiWindow(url2, as, core, r2);
	nui->loadViewIntoAsset();
	windows.push_back(nui);
	
}

bool Interface::handleCursor(double x, double y)
{
	for (auto win : windows)
	{
		if(win->reg.test(x, y))
		{
			win->view->InjectMouseMove( std::floor(x-win->reg.origin.x) , std::floor(y-win->reg.origin.y) );
			win->view->Focus();
			return true;
		}
	}
	if(lastFocus != nullptr)
		lastFocus->Unfocus();
	return false;
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