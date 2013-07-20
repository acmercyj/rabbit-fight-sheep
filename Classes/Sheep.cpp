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

void Sheep::init(CCLayer* layer, CCPoint pos)
{
	m_sheep = CCSprite::createWithSpriteFrameName(m_path.c_str());
	CCAction* action = createRotateAction(0.2f);
	action->setTag(EASswing);
	m_sheep->runAction(action);
	m_sheep->setPosition(pos);
	layer->addChild(m_sheep, 2);
	//setDestination(((MapLayer*)layer)->m_hero);
	//aiContrlCallBack(0.0f);
}

void Sheep::moveToDestion(CCPoint destination)
{
	m_sheep->stopActionByTag(EASmoveTo);
	//CCPoint destination = m_destination->getPosition();
	float distance = StaticMethod::getDistance(&destination, &m_sheep->getPosition());
	float duration = distance / getSpeed();
	CCMoveTo* moveToAction = CCMoveTo::create(duration, destination);
	moveToAction->setTag(EASmoveTo);
	m_sheep->runAction(moveToAction);
}

bool SheepManager::init()
{
	if(!BasicLayer::init())
	{
		return false;
	}
	//m_sheepBN = new CCSpriteBatchNode();
		//CCSpriteBatchNode::create("sheep_1.png" );
	//this->addChild(m_sheepBN);
	//  4.初始化数组
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

void SheepManager::addSheep(CCLayer* layer, CCPoint point)
{
	Sheep* sheep = new Sheep();
	sheep->init(layer, point);
	m_sheepArr->addObject(sheep);
	//m_sheepBN->addChild(sheep);
}
