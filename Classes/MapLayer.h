#ifndef __RABBIT_FIGHT_SHEEP_MAP_LAYER__
#define __RABBIT_FIGHT_SHEEP_MAP_LAYER__

#include "cocos2d.h"
#include "BasicLayer.h"
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

	//
private:
	void setViewPointCenter(float dt);

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

public:
	// hero side
	void setHeroSide(bool isGrass = false) { m_grass = isGrass; }
	bool getHeroSide() { return m_grass; }
	// initial hero pos
	void setHeroPosition();

private:
	/** pos flag **/
	bool m_grass;

protected:
private:
	// touch action
	void onTouchEventSyn(Hero* hero, CCPoint destination);
	// move action
	void onMoveSyn(Hero* hero, CCPoint destination);
	// touch ended
	void onTouchEndedEventSyn(Hero* hero);
};

#endif