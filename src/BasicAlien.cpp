/*
 * BasicAlien.cpp
 *
 *  Created on: Apr 22, 2012
 *      Author: kakus
 */

#include "BasicAlien.h"
#include <cstdlib>

BasicAlien::BasicAlien(float x = 0.0, float y = 0.0, float width = 1.0, float height = 1.0, int id = 0, AlienType alienType = CLASSIC_ALIEN):
GameObject(x, y, width, height), id(id), alienType(alienType)
{
	lifeTime = 0;
	tryingToFireBullet = false;
}

void BasicAlien::operator=(const BasicAlien &basicAlien)
{
	BasicAlien(basicAlien.x, basicAlien.y, basicAlien.width, basicAlien.height,
				basicAlien.id, basicAlien.alienType);
}

void BasicAlien::update(const double dt)
{
	GameObject::update(dt);

	lifeTime += dt;
	if(lifeTime > 3000.0)
	{
		tryingToFireBullet = rand()%5==4;
		lifeTime = 0.0;
	}
}
