#ifndef __SHEEP__
#define __SHEEP__

#include <string>
#include <vector>
using std::string;
using std::vector;
#include "DataDefine.h"
#include "BasicObject.h"
#include "Hero.h"

enum SheepActionTag
{
	EASswing,
	EASmoveTo
};

class Sheep : public BasicObject
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
	CREATE_FUNC(Sheep);
	
	virtual bool init();

	void setSheepPos(CCPoint pos);

	void moveToDestion(CCPoint destination);

	// attribute
public:
	string m_path;

public:
	CCSprite* m_sheep;
};

class SheepManager : public BasicLayer
{
public:
	virtual bool init();

	CREATE_FUNC(SheepManager);
	/** sheep **/
	CC_SYNTHESIZE_READONLY(CCArray*, m_sheepArr, SheepArr);
	void moveAllSheep(float dt);
	void addSheep(CCPoint point);

	void onDestinationMoved(CCPoint point) { m_destination = point; }

private:
	CCPoint m_destination;
};

#endif