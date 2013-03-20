/*
 * Bullet.h
 *
 *  Created on: Apr 22, 2012
 *      Author: kakus
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "GameObject.h"

class Bullet: public GameObject
{
public:
	Bullet(float x, float y):GameObject(x, y, 0.1, 0.5) {}
	void operator=(const Bullet & bullet)
	{
		Bullet(bullet.x, bullet.y);
	}
};

#endif /* BULLET_H_ */
