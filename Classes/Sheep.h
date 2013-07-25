#ifndef __SHEEP__
#define __SHEEP__

#include <string>
#include <vector>
using std::string;
using std::vector;
#include "DataDefine.h"
#include "BasicObject.h"
#include "Hero.h"
//#include "Box2dHandler.h"

enum SheepActionTag
{
	EASswing,
	EASmoveTo
};

class Sheep : public BasicObject , public CCObject
{
public:
	Sheep();
	~Sheep();

public:
	/** 
	* @brief	create rotate action
	* @param	param
	* @return	return val
	**/
	static CCAction* createRotateAction(float timeDelay);
	
	/*void SetStatus(char status){m_curStatus = status;}
	char GetStatus(){ return m_curStatus;}

	void SetAction(SpriteAnimationID action){m_curAction = action;}
	char GetAction(){ return m_curAction;}*/
	void setPath(string path) { m_path = path; }

public:
	//CREATE_FUNC(Sheep);

	static Sheep* create(CCLayer* layer, CCPoint pos);
	void attachBodyForSprite(b2World* world);
	
	bool init(CCPoint pos);

	void setSheepPos(CCPoint pos);

	void moveToDestion(CCPoint destination);

	// attribute
public:
	string m_path;

public:
	CCSprite* m_sheep;
};

class SheepManager : public CCLayer
{
public:
	virtual bool init();

	static SheepManager* create(CCLayer* layer);
	void setExternalData(b2World* world, CCPoint pos);
	//CREATE_FUNC(SheepManager);
	/** sheep **/
	CC_SYNTHESIZE_READONLY(CCArray*, m_sheepArr, SheepArr);
	void moveAllSheep(float dt);
	void addSheep();

	void onDestinationMoved(CCPoint point) { m_destination = point; }

public:
	b2World* m_world;
	CCPoint m_startPos;

private:
	CCPoint m_destination;
};

#endif