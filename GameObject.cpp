/*
 * GameObject.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: kakus
 */

#include "GameObject.h"

Model *GameObject::sModel = nullptr;

GameObject::GameObject(float x, float y, float width, float height) :
						height(height), width(width)
{
	this->x = x;
	this->y = y;
	speedXAxis = 0;
	speedYAxis = 0;
	alive = false;
}

bool GameObject::collision(const GameObject & otherObject) const
{
	/*
	 * Analysis only on x axis
	 * A------B
	 *   C------D
	 *
	 * they will collide only if
	 *   C < B && D > A
	 */
	if ( otherObject.x < (this->x + this->width) &&
		(otherObject.x + otherObject.width) > this->x )
	{
		/*
		 * Same on Y axis.
		 */
		if ( otherObject.y < (this->y + this->height) &&
			 (otherObject.y + otherObject.height) > this->y)
		{
			return true;
		}
	}

	return false;
}

Model* GameObject::getModel()
{
	return sModel;
}

void GameObject::setModel(Model* model)
{
	sModel = model;
}

void GameObject::update(const double dt)
{
	this->x += speedXAxis*dt/1000.0;
	this->y += speedYAxis*dt/1000.0;
}


