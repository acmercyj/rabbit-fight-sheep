#include "Sheep.h"
#include "MapLayer.h"
#include "DataDefine.h"

Sheep::Sheep()
{
	m_path = "sheep_1.png";
	setHitPoints(60);
	setAttack(5);
	setSpeed(15.0f);
}

Sheep::~Sheep()
{

}

CCAction* Sheep::createRotateAction(float timeDelay)
{
	vector<string> frameName;
	frameName.push_back("sheep_1.png");
	frameName.push_back("sheep_2.png");

	CCAnimation* animation = CCAnimation::create();
	animation->setDelayPerUnit(timeDelay);
	for(char i = 0; i < (char)frameName.size(); ++i)
	{
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName[i].c_str()));
	}
	CCAnimate* animate = CCAnimate::create(animation);
	CCAction* action = CCRepeatForever::create(animate);
	return action;
}

bool Sheep::init()
{
	if(!BasicLayer::init())
	{
		return false;
	}
	m_sheep = CCSprite::createWithSpriteFrameName(m_path.c_str());
	CCAction* action = createRotateAction(0.2f);
	action->setTag(EASswing);
	m_sheep->runAction(action);
	addChild(m_sheep, 2);
	return true;
}

void Sheep::moveToDestion(CCPoint destination)
{
	m_sheep->stopActionByTag(EASmoveTo);
	float distance = StaticMethod::getDistance(&destination, &m_sheep->getPosition());
	float duration = distance / getSpeed();
	CCMoveTo* moveToAction = CCMoveTo::create(duration, destination);
	moveToAction->setTag(EASmoveTo);
	m_sheep->runAction(moveToAction);
}

void Sheep::setSheepPos(CCPoint pos)
{
	m_sheep->setPosition(pos);
}

bool SheepManager::init()
{
	if(!BasicLayer::init())
	{
		return false;
	}
	m_sheepArr = CCArray::create();
	m_sheepArr->retain();
	this->schedule(schedule_selector(SheepManager::moveAllSheep), 2.0f);

	return true;
}

void SheepManager::moveAllSheep(float dt)
{
	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_sheepArr, obj)
	{
		Sheep* sheep = (Sheep*)obj;
		sheep->moveToDestion(m_destination);
	}
}

void SheepManager::addSheep(CCPoint point)
{
	Sheep* sheep = Sheep::create();
	sheep->setSheepPos(point);
	this->addChild(sheep, 2);
	m_sheepArr->addObject(sheep);
}
