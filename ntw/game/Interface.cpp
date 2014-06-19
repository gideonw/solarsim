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
	region r2(glm::vec2(512.0, 368.0), 0, 0, 350, 220);
	nui = new uiWindow(url2, as, core, r2);
	nui->loadViewIntoAsset();
	windows.push_back(nui);
	
	//load menu
	WebURL url3(WSLit("file:////Users/gideon/Projects/ntw/ntw/resources/ui/dev.html"));
	region r3(glm::vec2(2048-350, 0.0), 0, 0, 350, 220);
	nui = new uiWindow(url3, as, core, r3);
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
			lastFocus = win->view;
			return true;
		}
	}
	if(lastFocus != nullptr)
		lastFocus->Unfocus();
	return false;
}

bool Interface::passKeyToFocus( int key, int scanCode, int action, int mods )
{
	if(lastFocus != nullptr)
	{
		WebKeyboardEvent e;
		e.text[0] = (wchar16)key;
		
		e.type = WebKeyboardEvent::kTypeChar;
		lastFocus->InjectKeyboardEvent(e);
		
		//e.type = WebKeyboardEvent::kTypeKeyUp;
		//lastFocus->InjectKeyboardEvent(e);
		return true;
	}
	return false;
}

bool Interface::passMouseButtonToFocus( int button, int action, int mods )
{
	if(lastFocus != nullptr)
	{
		if(action == 1)
			lastFocus->InjectMouseDown(Awesomium::MouseButton::kMouseButton_Left);
		else
			lastFocus->InjectMouseUp(Awesomium::MouseButton::kMouseButton_Left);

		return true;
	}
	return false;
}

void Interface::update()
{
	for(auto uiw : windows)
	{
		JSValue v = uiw->view->ExecuteJavascriptWithResult(WSLit("rotateClicked"), WSLit(""));
		//std::cout << v.ToBoolean() << std::endl;
		
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