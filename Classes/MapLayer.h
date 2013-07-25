#ifndef __RABBIT_FIGHT_SHEEP_MAP_LAYER__
#define __RABBIT_FIGHT_SHEEP_MAP_LAYER__

#include "cocos2d.h"
#include "BasicLayer.h"
//#include "Box2dHandler.h"
#include "Hero.h"
#include "Sheep.h"
using namespace cocos2d;

class MapLayer : public BasicLayer
{
public:
	MapLayer();
	~MapLayer();

public:
	virtual bool init();
	static CCScene* scene();
	CREATE_FUNC(MapLayer);

private:
	void setView();

public:
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher(void);

	// timer callback
private:
	void setViewPointCenter(float dt);
	void addSheep(float dt);

public:
	/** game map **/
	CCTMXTiledMap* m_tileMap;
	/** the map layer **/
	CCTMXLayer* m_tmxMap;
	/** grass hero **/
	Hero* m_hero;
	/** land hero **/
	Hero* m_darkhero;
	/** sheep mgr **/
	SheepManager* m_sheepManager;
	/** rabbit mgr **/
	SheepManager* m_rabbitManager;
	//Box2dHandler* m_box2dHandler;

public:
	// hero side
	void setHeroSide(bool isGrass = false) { m_above = isGrass; }
	bool getHeroSide() { return m_above; }
	// initial hero pos
	void initSpritePosition();
	void initBox2dWorld();

private:
	/** pos flag **/
	bool m_above;
	CCPoint m_heroPoint;
	CCPoint m_darkHeroPoint;
	CCPoint m_rabbitPoint;
	CCPoint m_sheepPoint;

protected:
	/** writehere **/
	b2World* m_world;

private:
	// touch action
	void onTouchEventSyn(Hero* hero, SheepManager* sheepMgr, CCPoint destination);
	// move action
	void onMoveSyn(Hero* hero, SheepManager* sheepMgr, CCPoint destination);
	// touch ended
	void onTouchEndedEventSyn(Hero* hero, SheepManager* sheepMgr);
};

#endif