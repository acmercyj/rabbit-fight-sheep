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
	// initial hero pos
	void init(CCLayer* layer, CCPoint pos);

	void moveToDestion(CCPoint destination);

	//void setDestination(Hero* destination) { m_destination = destination; }
// 	void heroRotate();
// 
// 	void stopRotate();
// 
// 	void heroMoveTo(CCPoint destination);
// 
// 	void stopContrl();

	// attribute
public:
	string m_path;

public:
	CCSprite* m_sheep;
	//ccp* m_destination;

//private:
//	/** sprite status -1-invalid¡¢0-small¡¢1-big¡¢2-super **/
//	char m_curStatus;
//	/** sprite action **/
//	SpriteAnimationID m_curAction;
};

class SheepManager : public BasicLayer
{
public:
	virtual bool init();

	CREATE_FUNC(SheepManager);
	/** sheep **/
	CC_SYNTHESIZE_READONLY(CCArray*, m_sheepArr, SheepArr);
	void moveAllSheep(float dt);
	void addSheep(CCLayer* layer, CCPoint point);

	void onDestinationMoved(CCPoint point) { m_destination = point; }

private:
	//CCSpriteBatchNode* m_sheepBN;
	CCPoint m_destination;
};

#endif