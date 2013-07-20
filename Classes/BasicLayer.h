#ifndef __RABBIT_FIGHT_SHEEP_BasicLayer__
#define __RABBIT_FIGHT_SHEEP_BasicLayer__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

using namespace CocosDenshion;

class BasicLayer : public CCLayer
{
public:
	BasicLayer();
	~BasicLayer();

	virtual bool init();

	CCSize getWinSize();

	CREATE_FUNC(BasicLayer);

	void setBackgroundImage(const char* back_image_name);
};

#endif /* defined(__MyMoonWarrior__BasicLayer__) */
