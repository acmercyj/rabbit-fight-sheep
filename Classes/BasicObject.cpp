#include "BasicObject.h"

BasicObject::BasicObject()
{
	m_dead = 0;
	m_sidestep = 0;
	m_attachPercent = 0;
	m_attachAttack = 0;
	m_continuingInjury = false;
	m_continuingInjuryVal = 0;
}

BasicObject::~BasicObject()
{

}

bool BasicObject::onAttacked(int attack, bool continuing, float duration)
{
	if(getDead()) return false;
	// sides step calculation
	if(m_sidestep < 0 && CCRANDOM_0_1() <= m_sidestep)
	{
		return false;
	}
	if(continuing)
	{
		onContinuingInjury(attack, duration, 1);
	}
	else
	{
		int realAttack = attack - m_defence;
		if(realAttack > 0)
		{
			m_hitPoints -= realAttack;
			if(m_hitPoints <= 0)
			{
				this->unscheduleAllSelectors();
				setDead(true);
			}
		}
	}
	return true;
}

bool BasicObject::onContinuingInjury(int CIVal, float duration, float interval)
{
	if(getContinuingInjury())
	{
		setContinuingInjuryVal(CIVal + m_continuingInjuryVal);
	}
	else
	{
		setContinuingInjury(true);
		setContinuingInjuryVal(CIVal);
	}
	this->schedule(schedule_selector(BasicObject::continuingInjuryCallBack), interval, (int)(duration / interval), 0.1f);
	return true;
}

void BasicObject::continuingInjuryCallBack(float dt)
{
	onAttacked(m_continuingInjuryVal);
}
