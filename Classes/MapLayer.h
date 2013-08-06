#ifndef __RABBIT_FIGHT_SHEEP_MAP_LAYER__
#define __RABBIT_FIGHT_SHEEP_MAP_LAYER__

#include "cocos2d.h"
#include "BasicLayer.h"
//#include "Box2dHandler.h"
#include "Hero.h"
#include "Sheep.h"
#include <list>
#include "GLES-Render.h"
using namespace cocos2d;

class MyContact
{
public:
	b2Fixture* fixtureA;
	b2Fixture* fixtureB;
};

class MyContactListener : public b2ContactListener
{
	// Callbacks for derived classes.
	virtual void BeginContact(b2Contact* contact) 
	{ 
		if (contact)
		{
			MyContact mc;
			mc.fixtureA = contact->GetFixtureA();
			mc.fixtureB = contact->GetFixtureB();

			contact_list.push_back(mc);
		}
	}
	virtual void EndContact(b2Contact* contact) 
	{ 
		contact_list.clear();
		B2_NOT_USED(contact); 
	}
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}
	virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}

public:
	std::list<MyContact> contact_list;
};


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
	/** 
	* @brief	physical update
	**/
	void physicalUpdate(float dt);

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
	// Contact event listener
	MyContactListener* m_contactListener;
	GLESDebugDraw* m_debugDraw;

private:
	// touch action
	void onTouchEventSyn(Hero* hero, SheepManager* sheepMgr, CCPoint destination);
	// move action
	void onMoveSyn(Hero* hero, SheepManager* sheepMgr, CCPoint destination);
	// touch ended
	void onTouchEndedEventSyn(Hero* hero, SheepManager* sheepMgr);
};

#endif