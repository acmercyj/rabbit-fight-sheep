#include "Hero.h"
#include "DataDefine.h"

Hero::Hero()
{
	m_heroPath = "faceKing_0.png";
	setHitPoints(100);
	setAttack(25);
	setSpeed(40.0f);
//	m_hero = new B2Sprite();
}

Hero::~Hero()
{
	/*if(m_hero)
	{
		delete m_hero;
	}*/
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

bool Hero::init(CCPoint pos)
{
	/*if(!BasicLayer::init())
	{
		return false; 
	}*/
	m_hero = CCSprite::createWithSpriteFrameName(m_heroPath.c_str());
	m_hero->setTag(Ehero);
	m_hero->setPosition(pos);
	//m_hero = dynamic_cast<B2Sprite*>(CCSprite::createWithSpriteFrameName(m_heroPath.c_str()));
		//(B2Sprite*)CCSprite::createWithSpriteFrameName(m_heroPath.c_str());
	//addChild(m_hero, 2);
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

Hero* Hero::create(CCLayer* layer, CCPoint pos)
{
	Hero* hero = new Hero();
	if(hero && hero->init(pos))
	{
		layer->addChild(hero->m_hero, 3);
		/*attachBodyForSprite(world);*/
		hero->autorelease();
		hero->retain();
		return hero;
	}
	else
	{
		delete hero;
		hero = NULL;
		return NULL;
	}
}

void Hero::attachBodyForSprite(b2World* world)
{
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.position.Set(m_hero->getPosition().x / PTM_PATIO, m_hero->getPosition().y / PTM_PATIO);
	//spriteBodyDef.userData = sprite;

	setB2Body(world->CreateBody(&spriteBodyDef));
	//m_hero = body->setB2Body(body);
	//m_b2Sprite->m_body = body;
	//m_b2Sprite->m_body(spriteBody);

	b2PolygonShape spriteShape;
	CCSize size = m_hero->getContentSize();

	spriteShape.SetAsBox(size.width / PTM_PATIO / 2, size.height / PTM_PATIO / 2);
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 10.0f;
	//b2Body* spriteBody = m_hero->getB2Body();
	m_b2Body->CreateFixture(&spriteShapeDef);
}
