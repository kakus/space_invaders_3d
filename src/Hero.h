#ifndef HERO_H_
#define HERO_H_

#include "GameObject.h"

class Hero: public GameObject
{
public:
	Hero(float x = 1.0, float y = 14.0):
        GameObject(x, y, 1.0, 1.0) {}
};
#endif
