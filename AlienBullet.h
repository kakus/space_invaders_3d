/*
 * AlienBullet.h
 *
 *  Created on: May 6, 2012
 *      Author: kakus
 */

#ifndef ALIENBULLET_H_
#define ALIENBULLET_H_

#include "GameObject.h"

class AlienBullet: public GameObject
{
public:
	AlienBullet(float x, float y):GameObject(x, y, 0.1, 0.5) {}
};

#endif /* ALIENBULLET_H_ */
