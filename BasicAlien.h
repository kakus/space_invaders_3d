/*
 * BasicAlien.h
 *
 *  Created on: Apr 22, 2012
 *      Author: kakus
 */

#ifndef BASICALIEN_H_
#define BASICALIEN_H_

#include "GameObject.h"

enum AlienType { CLASSIC_ALIEN, BIG_HEAD_ALIEN, SMALL_HEAD_ALIEN };

class BasicAlien: public GameObject
{
private:
	double lifeTime;

public:
	const AlienType alienType;
	bool tryingToFireBullet;
	const int id;

	BasicAlien(const float x, const float y,const float width, const float height, int id, AlienType alienType);
	void operator=(const BasicAlien &basicAlien);

	void hit();
	void update(const double dt);
};

#endif /* BASICALIEN_H_ */
