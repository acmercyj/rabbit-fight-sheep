#ifndef __RABBIT_FIGHT_SHEEP_MENU_LAYER__
#define __RABBIT_FIGHT_SHEEP_MENU_LAYER__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include "BasicLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

class MenuLayer : public CCLayer// : public BasicLayer
{
public:
	// initialize
	virtual bool init();
	// get scene
	static CCScene* scene();
	// create function
	CREATE_FUNC(MenuLayer);
	// set layer view
	void setView();
	// add menu
	void addMenu();
	// play music
	void PlayMusic(const char* musicPath);
	// get windows size
	CCSize getWinSize();
	// set back ground view
	void setBackgroundImage(const char* back_image_name);

public:
	//
	void onClickStart(CCObject* pSender);
	//
	void onClickAbout(CCObject* pSender);
	//
	void onClickOption(CCObject* pSender);
};

class AboutLayer : public BasicLayer
{
public:
	virtual bool init();
	static CCScene* scene();
	CREATE_FUNC(AboutLayer);
	void setupViews();
	void back_callback(CCObject* pSender);
};

#endif
