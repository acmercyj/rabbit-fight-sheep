#include "Sheep.h"
#include "MapLayer.h"
#include "DataDefine.h"

Sheep::Sheep()
{
	m_path = "sheep_1.png";
	setHitPoints(60);
	setAttack(5);
	setSpeed(15.0f);
	//m_sheep = new B2Sprite();
}

Sheep::~Sheep()
{
	if(m_sheep)
	{
		delete m_sheep;
	}
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

bool Sheep::init(CCPoint pos)
{
	/*if(!BasicLayer::init())
	{
	return false;
	}*/
	m_sheep = CCSprite::createWithSpriteFrameName(m_path.c_str());
	m_sheep->setPosition(pos);
	m_sheep->setTag(Esheep);
	CCAction* action = createRotateAction(0.2f);
	action->setTag(EASswing);
	m_sheep->runAction(action);
	//addChild(m_sheep, 2);
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

Sheep* Sheep::create(CCLayer* layer, CCPoint pos)
{
	Sheep* sheep = new Sheep();
	if(sheep && sheep->init(pos))
	{
		layer->addChild(sheep->m_sheep, 3);
		//attachBodyForSprite(world);
		sheep->autorelease();
		//sheep->retain();

		return sheep;
	}
	else
	{
		delete sheep;
		sheep = NULL;
		return NULL;
	}
}

void Sheep::attachBodyForSprite( b2World* world )
{
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.position.Set(m_sheep->getPosition().x / PTM_PATIO, m_sheep->getPosition().y / PTM_PATIO);
	//spriteBodyDef.userData = sprite;

	setB2Body(world->CreateBody(&spriteBodyDef));
	//m_sheep = body->setB2Body(body);
	//m_b2Sprite->m_body = body;
	//m_b2Sprite->m_body(spriteBody);

	b2PolygonShape spriteShape;
	CCSize size = m_sheep->getContentSize();

	spriteShape.SetAsBox(size.width / PTM_PATIO / 2, size.height / PTM_PATIO / 2);
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 10.0f;
	//b2Body* spriteBody = m_sheep->getB2Body();
	m_b2Body->CreateFixture(&spriteShapeDef);
}

bool SheepManager::init()
{
	if(!CCLayer::init())
	{
		return 0;
	}
	m_sheepArr = CCArray::create();
	m_sheepArr->retain();
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

void SheepManager::addSheep()
{
	Sheep* sheep = Sheep::create(this, m_startPos);
	sheep->attachBodyForSprite(m_world);
	//bh->addBodyForSprite(sheep->m_sheep);
	//sheep->setSheepPos(point);
	//this->addChild(sheep, 2);
	m_sheepArr->addObject(sheep);
}

SheepManager* SheepManager::create(CCLayer* layer)
{
	SheepManager* sheepMgr = new SheepManager();
	if(sheepMgr && sheepMgr->init())
	{
		layer->addChild(sheepMgr, 3);
		sheepMgr->autorelease();
		return sheepMgr;
	}
	else
	{
		delete sheepMgr;
		sheepMgr = NULL;
		return NULL;
	}
}

void SheepManager::setExternalData(b2World* world, CCPoint pos)
{
	m_world = world;
	m_startPos = pos;
	schedule(schedule_selector(SheepManager::moveAllSheep), 2.0f);
}
