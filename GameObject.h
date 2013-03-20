/*
 * GameObject.h
 *
 *  Created on: Apr 20, 2012
 *      Author: kakus
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

class Model;

class GameObject
{
private:
	static Model * sModel;

public:
	float x;
	float y;
	const float width;
	const float height;
	float speedXAxis;
	float speedYAxis;
	bool  alive;

	GameObject(float x, float y, float width, float height);

	/*
	 * Check if two object collide with each other.
	 */
	bool collision(const GameObject & otherObject) const;

	/*
	 * Method will be called each new frame,
	 * this is mechanism for doing some calculations
	 * over time for classes implementing this.
	 *
	 *  @param dt time passed since last frame
	 */
	virtual void update(const double dt);

	/*
	 * Getters and setters
	 */
	static Model* getModel();
	static void setModel(Model* model);
};

#endif /* GAMEOBJECT_H_ */
