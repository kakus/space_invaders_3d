/*
 * Controller.h
 *
 *  Created on: Apr 23, 2012
 *      Author: kakus
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "Model.h"
#include <time.h>

class Controller
{
private:
	Model *model;
    timespec timeOfLastFrame;

public:
	Controller():model(nullptr) {}
	void init();
	void mainLoop();
	std::vector<BasicAlien>& getAliens() const;
	Hero& getHero() const;
	std::vector<Bullet>& getBullets() const;
	std::vector<Bullet>& getAlienBullets() const;

	void leftKeyPressed();
	void rightKeyPressed();
	void spaceKeyPressed();

	~Controller();
};

#endif /* CONTROLLER_H_ */
