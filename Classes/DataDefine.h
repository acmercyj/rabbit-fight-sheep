#ifndef __RABBIT_FIGHT_SHEEP_DATA_DEFINE__
#define __RABBIT_FIGHT_SHEEP_DATA_DEFINE__

#include "cocos2d.h"
using namespace cocos2d;

const char BACKGROUND_IMAGE_PATH[] = {"BackGround/light.jpg"};
static const char TILEMAP_PATH[] = {"Map/rabbit-sheep.tmx"};
static const char TILEMAP_LAYER[] = {"rabbit-sheep.tmx"};

const float PTM_PATIO = 32.0f;

enum ESpriteTag
{
	Ehero,
	Esheep
};

class StaticMethod
{
public:
	static float getDistance(const CCPoint* orin, const CCPoint* destination)
	{
		return sqrt((orin->x - destination->x) * (orin->x - destination->x) + (orin->y - destination->y) * (orin->y - destination->y));
	}
	static float sm_max(float x, float y) 
	{
		return x > y ? x : y;
	}
	static float sm_min(float x, float y)
	{
		return x < y ? x : y;
	}
};

#endif