#ifndef __BASIC_OBJECT__
#define __BASIC_OBJECT__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "BasicLayer.h"
using namespace cocos2d;

class BasicObject// : public BasicLayer
{
public:
	BasicObject();
	~BasicObject();

public:
	/** 
	* @ false the attack has been sidesteped!
	**/
	virtual bool onAttacked(int attack, bool continuing = false, float duration = 0);

	/** 
	* @ false the attack has been sidesteped!
	**/
	virtual bool onContinuingInjury(int CIVal, float duration, float interval = 0);

	void continuingInjuryCallBack(float dt);

public:
	void setDefence(int defence) { m_defence = defence; }
	int getDefence() { return m_defence; }
	void setHitPoints(int hp) { m_hitPoints = hp; }
	int setHitPoints() { return m_hitPoints; }
	void setAttack(int attack) { m_attack = attack; }
	int getAttack() { return m_attack; }
	void setSidestep(float sidestep) { m_sidestep = sidestep; }
	float getSidestep() { return m_sidestep; }
	void setDead(bool liveStatus) { m_dead = liveStatus; }
	bool getDead() { return m_dead; }
	void setContinuingInjury(bool CIstatus) { m_continuingInjury = CIstatus; }
	bool getContinuingInjury() { return m_continuingInjury; }
	void setContinuingInjuryVal(int CIVal) { m_continuingInjuryVal = CIVal; }
	int getContinuingInjuryVal() { return m_continuingInjuryVal; }
	void setAttachAttack(int attachVal) { m_attachAttack = attachVal; }
	int getAttachAttack() { return m_attachAttack; }
	void setAttachAttackPercent(float attachPercent) { m_attachPercent = attachPercent; }
	float getAttachAttackPercent() { return m_attachPercent; }
	void setSpeed(float speed) { m_speed = speed; }
	float getSpeed() { return m_speed; }
	void setHorizon(float hrizon) { m_horizon = hrizon; }
	float getHorizon() { return m_horizon; }
	void setPhsicAtkRange(float arrange) { m_phsicAtkRange = arrange; }
	float setPhsicAtkRange() { return m_phsicAtkRange; }

	// basic attribution
protected:
	int m_defence;
	int m_hitPoints;
	int m_attack;
	float m_phsicAtkRange;
	float m_speed;
	float m_horizon;

	// advanced attribution
protected:
	float m_sidestep;
	int m_continuingInjuryVal;
	int m_attachAttack;
	float m_attachPercent;

	// status
protected:
	bool m_dead;
	bool m_continuingInjury;

	// box2d
public:
	/** writehere **/
	CC_SYNTHESIZE(b2Body*, m_b2Body, B2Body);
};

//class B2Sprite : public CCSprite
//{
//	//B2Sprite() { m_b2Body = new b2Body(); }
//	// box2d
//public:
//	/** writehere **/
//	CC_SYNTHESIZE(b2Body*, m_b2Body, B2Body);
//};

#endif