/*
 * Model.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: kakus
 */

#include "Model.h"

void Model::initNewGame()
{
	#define ALIEN_ID alienRows*ALIEN_COLS+alienCols

	alienStepTime = 0;
	alienMoveDirection = RIGHT;
	aliens.clear();

	AlienType alienType = CLASSIC_ALIEN;
	for (int alienRows = 0; alienRows < ALIEN_ROWS; ++alienRows)
	{
		switch(alienRows)
		{
			case 0:
				alienType = SMALL_HEAD_ALIEN;
				break;

			case 1:
				alienType = CLASSIC_ALIEN;
				break;

			case 2:
				alienType = CLASSIC_ALIEN;
				break;

			default:
				alienType = BIG_HEAD_ALIEN;
				break;
		}

		for (int alienCols = 0; alienCols < ALIEN_COLS; ++alienCols) {
			auto alien = BasicAlien(alienCols*1.5, alienRows*1.5, 1, 1, ALIEN_ID, alienType);
			alien.alive = true;
			aliens.push_back(alien);
			aliensArray[alienCols][alienRows]=true;
		}
	}

	bullets = vector<Bullet>(NUMBER_OF_BULLETS_THAT_HERO_CAN_FIRE, Bullet(0, 0));
	alienBullets = vector<Bullet>(NUMBER_OF_BULLETS_THAT_ALIEN_CAN_FIRE, Bullet(0, 0));
}

void Model::nextStage()
{
}

bool Model::isAlienInFirstLine(const int id) const
{
	return id >= (ALIEN_ROWS-1)*ALIEN_COLS;
}

void Model::update(const miliseconds dt)
{
	alienStepTime += dt;
	if(alienStepTime > ALIEN_STEP_TIME)
	{
			switch(alienMoveDirection)
			{
				case LEFT:
					alienMoveDirection = RIGHT;
				break;

				case RIGHT:
					alienMoveDirection = LEFT;
				break;
			}
			alienStepTime = 0;
	}

    /*
     * Update hero
     */
    if(hero.x > GAME_LEFT_EDGE && hero.x < GAME_RIGHT_EDGE)
    {
        hero.speedXAxis *= 0.9;
        hero.update(dt);
    }
    
	/*
	 * Update aliens
	 */
	auto alienIt = aliens.begin();
	for(; alienIt != aliens.end(); ++alienIt)
	{
		auto &alien = *alienIt;
		if(alien.alive)
		{

			switch(alienMoveDirection)
			{
				case LEFT:
					alien.speedXAxis=-ALIEN_MOVE_SPEED;
				break;

				case RIGHT:
					alien.speedXAxis=ALIEN_MOVE_SPEED;
				break;
			}

			alien.update(dt);
			if(alien.tryingToFireBullet && (isAlienInFirstLine(alien.id) || noAlienUnder(alien.id)))
			{
				auto bulletIt = alienBullets.begin();
				for(; bulletIt != alienBullets.end(); ++bulletIt)
				{
					auto &bullet = *bulletIt;
					if(bullet.alive == false)
					{
						bullet.x = alien.x+alien.width/2;
						bullet.y = alien.y;
						bullet.speedYAxis = ALIEN_BULLET_SPEED;
						bullet.alive = true;
						alien.tryingToFireBullet = false;
						break;
					}
				}
			}
		}
	}

	/*
	 * Update alien bullets and check if they didnt went off screen
	 */
	auto bulletIt = alienBullets.begin();
	for(; bulletIt != alienBullets.end(); ++bulletIt)
	{
		auto &bullet = *bulletIt;
		if(bullet.alive)
		{
			bullet.update(dt);
			if(bullet.y > GAME_DOWN_EDGE)
				bullet.alive = false;
		}
	}


	/*
	 * Update hero bullets and check if they didnt went off screen
	 */
	bulletIt = bullets.begin();
	for(; bulletIt != bullets.end(); ++bulletIt)
	{
		auto &bullet = *bulletIt;
		if(bullet.alive)
		{
			bullet.update(dt);
			if(bullet.y < 0)
				bullet.alive = false;
		}
	}

	/*
	 * Check if aliens bullets collide with hero bullets
	 */
	auto alienBulletIt = alienBullets.begin();
	for(; alienBulletIt != alienBullets.end(); ++alienBulletIt)
	{
		auto &alienBullet = *alienBulletIt;
		if(alienBullet.alive == false) continue;

		auto bulletIt = bullets.begin();
		for(; bulletIt != bullets.end(); ++bulletIt)
		{
			auto &bullet = *bulletIt;
			if(bullet.alive == false) continue;
			if(alienBullet.collision(bullet))
			{
				alienBullet.alive = false;
				bullet.alive = false;
			}
		}
	}

	/*
	 * check if alien was hit by hero bullet
	 */
	alienIt = aliens.begin();
	for(; alienIt != aliens.end(); ++alienIt)
	{
		auto &alien = *alienIt;
		if(alien.alive == false) continue;
		auto bulletIt = bullets.begin();

		for(; bulletIt != bullets.end(); ++bulletIt)
		{
			auto &bullet = *bulletIt;
			if(bullet.alive == false) continue;
			if(alien.collision(bullet))
			{
				bullet.alive = false;
				alien.alive = false;
				updateAliensArray(alien.id);
			}
		}
	}

	/*
	 * check if hero was hit by alien bullet
	 */
	bulletIt = alienBullets.begin();
	for(; bulletIt != alienBullets.end(); ++bulletIt)
	{
		auto &bullet = *bulletIt;
		if(bullet.collision(hero))
		{

			//TODO GAME END STATE
			initNewGame();
			break;
		}
	}

}

void Model::moveHeroRight()
{
    hero.speedXAxis = 4.0;
}

void Model::moveHeroLeft()
{
    hero.speedXAxis = -4.0;
}

void Model::fireBullet()
{
	auto bulletIt = bullets.begin();
	for(; bulletIt != bullets.end(); ++bulletIt)
	{
		auto &bullet = *bulletIt;
		if(bullet.alive == false)
		{
			bullet.x = hero.x+hero.width/2;
			bullet.y = hero.y;
			bullet.alive = true;
			bullet.speedYAxis = HERO_BULLET_SPEED;
			break;
		}
	}
}

bool Model::noAlienUnder(const int id) const
{
	if((id/ALIEN_COLS) < ALIEN_ROWS )
		return !aliensArray[id%ALIEN_COLS][(id/ALIEN_COLS)+1];
	else
		return false;
}

void Model::updateAliensArray(const int id)
{
	aliensArray[id%ALIEN_COLS][(id/ALIEN_COLS)]=false;
}




