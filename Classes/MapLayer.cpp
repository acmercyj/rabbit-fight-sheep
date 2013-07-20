#include "MapLayer.h"
#include "DataDefine.h"

MapLayer::MapLayer() : m_above(true)
{
}

MapLayer::~MapLayer()
{
}

bool MapLayer::init()
{
	bool succeed = false;
	do 
	{
		CC_BREAK_IF(!__super::init());
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
	m_rabbitManager = SheepManager::create();
	this->addChild(m_rabbitManager, 2);
	this->addChild(m_sheepManager, 2);
	m_hero = Hero::create();
	m_darkhero = Hero::create();
	setHeroPosition();
	this->addChild(m_hero, 2);
	this->addChild(m_darkhero, 2);
	this->schedule(schedule_selector(MapLayer::setViewPointCenter));
	this->schedule(schedule_selector(MapLayer::addSheep), 3.0f);
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

void MapLayer::setHeroPosition()
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
	m_hero->setPosition(ccp(heroPoint->valueForKey("x")->floatValue(), heroPoint->valueForKey("y")->floatValue()));
	m_darkhero->setPosition(ccp(darkheroPoint->valueForKey("x")->floatValue(), darkheroPoint->valueForKey("y")->floatValue()));
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
	m_sheepManager->addSheep(m_sheepPoint);
	m_rabbitManager->addSheep(m_rabbitPoint);
	m_sheepManager->onDestinationMoved(m_hero->m_hero->getPosition());
	m_rabbitManager->onDestinationMoved(m_darkhero->m_hero->getPosition());
}
