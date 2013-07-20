#ifndef __RABBIT_FIGHT_SHEEP_DATA_DEFINE__
#define __RABBIT_FIGHT_SHEEP_DATA_DEFINE__

#include "cocos2d.h"
using namespace cocos2d;

const char BACKGROUND_IMAGE_PATH[] = {"BackGround/light.jpg"};
static const char TILEMAP_PATH[] = {"Map/rabbit-sheep.tmx"};
static const char TILEMAP_LAYER[] = {"rabbit-sheep.tmx"};

class StaticMethod
{
public:
	static float getDistance(const CCPoint* orin, const CCPoint* destination)
	{
		return sqrt((orin->x - destination->x) * (orin->x - destination->x) + (orin->y - destination->y) * (orin->y - destination->y));
	}
};

#endif