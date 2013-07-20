#include "MapLayer.h"
#include "DataDefine.h"

MapLayer::MapLayer() : m_grass(false)
{
	m_hero = new Hero();
	m_darkhero = new Hero();
	//m_sheepManager = new SheepManager();
}

MapLayer::~MapLayer()
{
	delete m_hero;
	delete m_darkhero;
	//delete m_sheepManager;
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
	CCPoint pos = m_hero->m_hero->getPosition();
	CCSize winSize = getWinSize();
	int x = max(pos.x, winSize.width / 2);
	int y = max(pos.y, winSize.height / 2);
	x = min(x, (m_tileMap->getMapSize().width * m_tileMap->getTileSize().width) - winSize.width / 2);
	y = min(y, (m_tileMap->getMapSize().height * m_tileMap->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);
	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}

void MapLayer::setView()
{
	m_tileMap = CCTMXTiledMap::create(TILEMAP_PATH);
	this->addChild(m_tileMap, 1);
	// add plist
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprite/sprite.plist", "Sprite/sprite.png");
	m_sheepManager = SheepManager::create();
	this->addChild(m_sheepManager, 2);
	initHero();
	this->schedule(schedule_selector(MapLayer::setViewPointCenter));
//	this->schedule(schedule_selector(SheepManager::addSheep), 1.0f);
}

bool MapLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	onTouchEventSyn(m_hero, convertTouchToNodeSpace(pTouch));
	// TODO:del
	onTouchEventSyn(m_darkhero, convertTouchToNodeSpace(pTouch));
	//  return false to ignore the touch ended event
	return true;
}

void MapLayer::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void MapLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	m_sheepManager->onDestinationMoved(m_hero->m_hero->getPosition());
	onTouchEndedEventSyn(m_hero);
	// TODO:del
	onTouchEndedEventSyn(m_darkhero);
}

void MapLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	onMoveSyn(m_hero, convertTouchToNodeSpace(pTouch));
	// TODO:del
	onMoveSyn(m_darkhero, convertTouchToNodeSpace(pTouch));
}

void MapLayer::initHero()
{
	/*m_hero = Hero::create();
	m_darkhero = Hero::create();*/
	CCTMXObjectGroup* objects = m_tileMap->objectGroupNamed("hero");
	CCDictionary* heroPoint;
	CCDictionary* darkheroPoint;
	if(m_grass)
	{
		heroPoint = objects->objectNamed("grasshero");
		darkheroPoint = objects->objectNamed("landhero");
	}
	else
	{
		heroPoint = objects->objectNamed("landhero");
		darkheroPoint = objects->objectNamed("grasshero");
	}
	
	float x = heroPoint->valueForKey("x")->floatValue();
	float y = heroPoint->valueForKey("y")->floatValue();
	m_hero->init(this, ccp(x, y));

	m_sheepManager->addSheep(this, ccp(x + 30, y +30));
	m_sheepManager->addSheep(this, ccp(x + 20, y +20));
	m_sheepManager->addSheep(this, ccp(40, 40));

	x = darkheroPoint->valueForKey("x")->floatValue();
	y = darkheroPoint->valueForKey("y")->floatValue();
	m_darkhero->init(this, ccp(x, y));
}

void MapLayer::onTouchEventSyn(Hero* hero, CCPoint destination)
{
	hero->heroRotate();
	onMoveSyn(hero, destination);
}

void MapLayer::onMoveSyn(Hero* hero, CCPoint destination)
{
	m_sheepManager->onDestinationMoved(destination);
	hero->heroMoveTo(destination);
}

void MapLayer::onTouchEndedEventSyn(Hero* hero)
{
	hero->stopContrl();
}
