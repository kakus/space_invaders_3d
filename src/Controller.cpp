/*
 * Controller.cpp
 *
 *  Created on: Apr 23, 2012
 *      Author: kakus
 */

#include "Controller.h"
#include "View.h"
#include <iostream>

void Controller::init()
{
    clock_gettime(CLOCK_MONOTONIC, &timeOfLastFrame);

	model = new Model();
	model->initNewGame();
	GameObject::setModel(model);
}

std::vector<BasicAlien>& Controller::getAliens() const
{
	return model->aliens;
}

Hero& Controller::getHero() const
{
	return model->hero;
}

void Controller::leftKeyPressed()
{
	model->moveHeroLeft();
}

void Controller::rightKeyPressed()
{
	model->moveHeroRight();
}

void Controller::spaceKeyPressed()
{
	model->fireBullet();
}

std::vector<Bullet>& Controller::getBullets() const
{
	return model->bullets;
}

std::vector<Bullet>& Controller::getAlienBullets() const
{
	return model->alienBullets;
}

Controller::~Controller()
{
	if(model != nullptr)
		delete model;
}


//Help function to calculate time diff
timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

void Controller::mainLoop()
{
	if ( model == nullptr)
	{
		std::cerr<<"Erro model doesnt exist."<<std::endl;
		exit(1);
	}

	timespec timeOfCurrentFrame;
    clock_gettime(CLOCK_MONOTONIC, &timeOfCurrentFrame);

    timespec dt = diff(timeOfLastFrame, timeOfCurrentFrame);
	model->update(dt.tv_nsec/1000000);
    timeOfLastFrame = timeOfCurrentFrame;
}


