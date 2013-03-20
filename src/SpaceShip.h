/*
 * SpaceShip.h
 *
 *  Created on: Apr 20, 2012
 *      Author: kakus
 */

#ifndef SPACESHIP_H_
#define SPACESHIP_H_

#include "GameObject.h"

class SpaceShip//: public GameObject
{
public:
	SpaceShip();

	void moveLeft();
	void moveRight();
	void fire();
	int lifeCount() const;

};

#endif /* SPACESHIP_H_ */
