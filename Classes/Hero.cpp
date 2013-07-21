#include "Hero.h"
#include "DataDefine.h"

Hero::Hero()
{
	m_heroPath = "faceKing_0.png";
	setHitPoints(100);
	setAttack(25);
	setSpeed(40.0f);
}

Hero::~Hero()
{

}

CCAction* Hero::createRotateAction(float timeDelay)
{
	vector<string> frameName;
	frameName.push_back("faceKing_1.png");
	frameName.push_back("faceKing_2.png");
	frameName.push_back("faceKing_3.png");
	frameName.push_back("faceKing_4.png");
	frameName.push_back("faceKing_5.png");
	frameName.push_back("faceKing_6.png");

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

bool Hero::init()
{
	if(!BasicLayer::init())
	{
		return false; 
	}
	m_hero = CCSprite::createWithSpriteFrameName(m_heroPath.c_str());
	addChild(m_hero, 2);
	return true;
}

void Hero::heroRotate()
{
	if(GetStatus() != ESrotate)
	{
		SetStatus(ESrotate);
		CCAction* rotate = createRotateAction(0.1f);
		rotate->setTag(EArotate);
		m_hero->runAction(rotate);
	}
}

void Hero::stopRotate()
{
	m_hero->stopActionByTag(EArotate);
}

void Hero::heroMoveTo(CCPoint destination)
{
	m_hero->stopActionByTag(EAmoveTo);
	float distance = StaticMethod::getDistance(&destination, &m_hero->getPosition());
	float duration = distance / getSpeed();
	CCMoveTo* moveToAction = CCMoveTo::create(duration, destination);
	moveToAction->setTag(EAmoveTo);
	m_hero->runAction(moveToAction);
}

void Hero::stopContrl()
{
	m_hero->stopAllActions();
	if(GetStatus() != ESstand)
	{
		SetStatus(ESstand);
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_heroPath.c_str());
		m_hero->setDisplayFrame(pFrame);
	}
}

void Hero::setPosition(CCPoint pos)
{
	m_hero->setPosition(pos);
	SetStatus(ESstand);
}
