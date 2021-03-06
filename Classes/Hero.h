#ifndef __HERO__
#define __HERO__

#include <string>
#include <vector>
using std::string;
using std::vector;
//#include "Box2D/Box2D.h"
#include "DataDefine.h"
#include "BasicObject.h"

enum ActionTag
{
	EArotate,
	EAmoveTo
};

enum SpriteStatus
{
	ESstand,
	ESrotate
};

enum SpriteAnimationID
{
	Erotate
};

class Hero : public BasicObject , public CCObject
{
public:
	Hero();
	~Hero();

public:
	/** 
	* @brief	create rotate action
	* @param	param
	* @return	return val
	**/
	static CCAction* createRotateAction(float timeDelay);
	
	void SetStatus(char status){m_curStatus = status;}
	char GetStatus(){ return m_curStatus;}

	void SetAction(SpriteAnimationID action){m_curAction = action;}
	char GetAction(){ return m_curAction;}
	void setHeroPath(string path) { m_heroPath = path; }

public:
	
	static Hero* create(CCLayer* layer, CCPoint pos);
	void attachBodyForSprite(b2World* world);

	//CREATE_FUNC(Hero);

	bool init(CCPoint pos);

	void setPosition(CCPoint pos);

	void heroRotate();

	void stopRotate();

	void heroMoveTo(CCPoint destination);

	void stopContrl();

	// attribute
public:
	string m_heroPath;

public:
	CCSprite* m_hero;

private:
	/** sprite status -1-invalid��0-small��1-big��2-super **/
	char m_curStatus;
	/** sprite action **/
	SpriteAnimationID m_curAction;
};

#endif