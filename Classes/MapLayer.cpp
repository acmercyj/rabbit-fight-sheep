#include "MapLayer.h"
#include "DataDefine.h"

MapLayer::MapLayer() : m_above(true)
{
	//m_box2dHandler = new Box2dHandler();
}

MapLayer::~MapLayer()
{
	//delete m_box2dHandler;
}

bool MapLayer::init()
{
	bool succeed = false;
	do 
	{
		CC_BREAK_IF(!BasicLayer::init());
		setView();
		this->setTouchEnabled(true);
		succeed = true;
	}while(0);
	
	return succeed;
}

CCScene* MapLayer::scene()
{
	CCScene* MapScene = NULL;
	do 
	{
		CC_BREAK_IF(!(MapScene = CCScene::create()));
		MapLayer* mapLayer = MapLayer::create();
		CC_BREAK_IF(!mapLayer);
		MapScene->addChild(mapLayer);
	}while(0);
	return MapScene;
}

void MapLayer::setViewPointCenter(float dt)
{
	CCPoint pos = m_heroPoint;
	if(m_hero->m_hero)
	{
		pos = m_hero->m_hero->getPosition();
	}
	CCSize winSize = getWinSize();
	float x = StaticMethod::sm_max(pos.x, winSize.width / 2);
	float y = StaticMethod::sm_max(pos.y, winSize.height / 2);
	x = StaticMethod::sm_min(x, (m_tileMap->getMapSize().width * m_tileMap->getTileSize().width) - winSize.width / 2);
	y = StaticMethod::sm_min(y, (m_tileMap->getMapSize().height * m_tileMap->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);
	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}

void MapLayer::setView()
{
	m_tileMap = CCTMXTiledMap::create(TILEMAP_PATH);
	//m_box2dHandler->initBox2D(m_tileMap->getMapSize());
	this->addChild(m_tileMap, 1);
	// add plist
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprite/sprite.plist", "Sprite/sprite.png");
	
	/*this->addChild(m_rabbitManager, 2);
	this->addChild(m_sheepManager, 2);*/

	initBox2dWorld();
	initSpritePosition();
	m_sheepManager = SheepManager::create(this);
	m_sheepManager->setExternalData(m_world, m_sheepPoint);
	m_rabbitManager = SheepManager::create(this);
	m_rabbitManager->setExternalData(m_world, m_rabbitPoint);



	m_hero = Hero::create(this, m_heroPoint);
	m_hero->attachBodyForSprite(m_world);
	m_darkhero = Hero::create(this, m_darkHeroPoint);
	m_darkhero->attachBodyForSprite(m_world);
	//m_hero->m_hero->m_b2Body
	this->schedule(schedule_selector(MapLayer::setViewPointCenter));
	this->schedule(schedule_selector(MapLayer::addSheep), 3.0f);
	this->schedule(schedule_selector(MapLayer::physicalUpdate));
}

bool MapLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	onTouchEventSyn(m_hero, m_sheepManager, convertTouchToNodeSpace(pTouch));
	// TODO:del
	onTouchEventSyn(m_darkhero, m_rabbitManager, convertTouchToNodeSpace(pTouch));
	//  return false to ignore the touch ended event
	return true;
}

void MapLayer::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void MapLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	onTouchEndedEventSyn(m_hero, m_sheepManager);
	// TODO:del
	onTouchEndedEventSyn(m_darkhero, m_rabbitManager);
}

void MapLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	onMoveSyn(m_hero, m_sheepManager, convertTouchToNodeSpace(pTouch));
	// TODO:del
	onMoveSyn(m_darkhero, m_rabbitManager, convertTouchToNodeSpace(pTouch));
}

void MapLayer::initSpritePosition()
{
	CCTMXObjectGroup* objects = m_tileMap->objectGroupNamed("hero");
	CCDictionary* heroPoint;
	CCDictionary* darkheroPoint;
	CCDictionary* rabbit;
	CCDictionary* sheep;
	if(m_above)
	{
		heroPoint = objects->objectNamed("grasshero");
		darkheroPoint = objects->objectNamed("landhero");
		sheep = objects->objectNamed("rabbit");
		rabbit = objects->objectNamed("sheep");
	}
	else
	{
		heroPoint = objects->objectNamed("landhero");
		darkheroPoint = objects->objectNamed("grasshero");
		sheep = objects->objectNamed("sheep");
		rabbit = objects->objectNamed("rabbit");
	}
	m_heroPoint = (ccp(heroPoint->valueForKey("x")->floatValue(), heroPoint->valueForKey("y")->floatValue()));
	m_darkHeroPoint = (ccp(darkheroPoint->valueForKey("x")->floatValue(), darkheroPoint->valueForKey("y")->floatValue()));
	m_rabbitPoint = ccp(rabbit->valueForKey("x")->floatValue(), rabbit->valueForKey("y")->floatValue());
	m_sheepPoint= ccp(sheep->valueForKey("x")->floatValue(), sheep->valueForKey("y")->floatValue());
}

void MapLayer::onTouchEventSyn(Hero* hero, SheepManager* sheepMgr, CCPoint destination)
{
	hero->heroRotate();
	onMoveSyn(hero, sheepMgr, destination);
}

void MapLayer::onMoveSyn(Hero* hero, SheepManager* sheepMgr, CCPoint destination)
{
	sheepMgr->onDestinationMoved(destination);
	hero->heroMoveTo(destination);
}

void MapLayer::onTouchEndedEventSyn(Hero* hero, SheepManager* sheepMgr)
{
	sheepMgr->onDestinationMoved(hero->m_hero->getPosition());
	hero->stopContrl();
}

void MapLayer::addSheep(float dt)
{
	m_sheepManager->addSheep();
	m_rabbitManager->addSheep();
	m_sheepManager->onDestinationMoved(m_hero->m_hero->getPosition());
	m_rabbitManager->onDestinationMoved(m_darkhero->m_hero->getPosition());
}

void MapLayer::initBox2dWorld()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	m_world = new b2World(gravity);
	//m_world->set
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);
	m_debugDraw = new GLESDebugDraw(PTM_PATIO);
	m_world->SetDebugDraw(m_debugDraw);
	// collision detect
	m_contactListener = new MyContactListener();
	m_world->SetContactListener(m_contactListener);


	//uint32 flags = 0;
	//flags += b2Draw::e_shapeBit;
	////        flags += b2Draw::e_jointBit;
	////        flags += b2Draw::e_aabbBit;
	////        flags += b2Draw::e_pairBit;
	////        flags += b2Draw::e_centerOfMassBit;
	////m_debugDraw->SetFlags(flags);


	//// Define the ground body.
	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0, 0); // bottom-left corner

	//// Call the body factory which allocates memory for the ground body
	//// from a pool and creates the ground box shape (also from a pool).
	//// The body is also added to the world.
	//b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	////// Define the ground box shape.
	//b2EdgeShape groundBox;
}

void MapLayer::physicalUpdate(float dt)
{
	if (m_world)
		m_world->Step(dt, 10, 10);

	// 基于cocos2d的精灵位置来更新box2d的body位置
	for(b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			CCSprite* sprite = (CCSprite*)b->GetUserData();
			if (sprite)
			{
				b2Vec2 pt = b2Vec2((float)(sprite->getPosition().x / PTM_PATIO), (float)(sprite->getPosition().y / PTM_PATIO));
				float angle = (float)CC_DEGREES_TO_RADIANS(sprite->getRotation());
				b->SetTransform(pt, angle);
			}
		}
	}

	std::list<b2Body*> toDestroy_list;

	for( std::list<MyContact>::iterator it = m_contactListener->contact_list.begin(); 
		it != m_contactListener->contact_list.end();
		++it)
	{
		MyContact& contact = *it;

		b2Body* bodyA = contact.fixtureA->GetBody();
		b2Body* bodyB = contact.fixtureB->GetBody();

		CCSprite* sa = (CCSprite*)bodyA->GetUserData();
		CCSprite* sb = (CCSprite*)bodyB->GetUserData();
		if (sa && sb)
		{
			if (sa->getTag() == Ehero && sb->getTag() == Esheep)
				toDestroy_list.push_back(bodyB);
			else if (sa->getTag() == Esheep && sa->getTag() == Ehero)
				toDestroy_list.push_back(bodyA);
		}
	}

	// Destroy contact item.
	std::list<b2Body*>::iterator it = toDestroy_list.begin();
	while(it != toDestroy_list.end())
	{
		if ((*it)->GetUserData() != NULL)
		{
			CCSprite* sprite = (CCSprite*)((*it)->GetUserData());
			if (sprite)
			{
				//sprite->stopActionByTag(EASmoveTo);
				removeChild(sprite, true);
			}
			m_world->DestroyBody(*it);
		}

		++it;
	}

	toDestroy_list.clear();
}
