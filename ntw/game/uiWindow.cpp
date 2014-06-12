//
//  uiWindow.cpp
//  ntw
//
//  Created by Gideon on 6/9/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

#include "uiWindow.h"


uiWindow::uiWindow(WebURL _url, asset* _asset, WebCore* core):url(_url),ui_asset(_asset)
{
	view = core->CreateWebView(256, 200);
	view->SetTransparent(true);
	
	//WebURL url(WSLit("file:////Users/gideon/Projects/ntw/ntw/resources/ui/search.html"));
	view->LoadURL(url);
	while (view->IsLoading())
		core->Update();
}

void uiWindow::loadViewIntoAsset()
{
	glGenTextures(1, &(ui_asset->texture));
	// Make sure our surface is not NULL-- it may be NULL if the WebView
	// process has crashed.
	if (getSurface() != 0) {
		// Save our BitmapSurface to a JPEG image in the current
		// working directory.
		if(getSurface()->is_dirty()){
			int w = getSurface()->width();
			int h = getSurface()->height();
			
			unsigned char *buffer = new unsigned char[w * h * 4];
			getSurface()->CopyTo(buffer, w * 4, 4, false, true);
			
			glBindTexture(GL_TEXTURE_2D, ui_asset->texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, buffer);
			glBindTexture(GL_TEXTURE_2D, 0);
			delete[] buffer;
		}
	}
}

void uiWindow::reloadTexture()
{
	if (getSurface() != 0) {
		int w = getSurface()->width();
		int h = getSurface()->height();
		
		unsigned char *buffer = new unsigned char[w * h * 4];
		getSurface()->CopyTo(buffer, w * 4, 4, false, true);
		
		glBindTexture(GL_TEXTURE_2D, ui_asset->texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, buffer);
		glBindTexture(GL_TEXTURE_2D, 0);
		delete[] buffer;
	}
}

BitmapSurface* uiWindow::getSurface()
{
	return (BitmapSurface*)view->surface();
}