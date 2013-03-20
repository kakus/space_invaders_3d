/*
 * Model.h
 *
 *  Created on: Apr 20, 2012
 *      Author: kakus
 */

#ifndef MODEL_H_
#define MODEL_H_
#include <vector>
#include <algorithm>

#include "BasicAlien.h"
#include "AlienOne.h"
#include "Hero.h"
#include "Bullet.h"

#define ALIEN_ROWS 5
#define ALIEN_COLS 11
#define GAME_RIGHT_EDGE 15.0
#define GAME_LEFT_EDGE 0
#define GAME_DOWN_EDGE 16.0
#define HERO_STEP_SIZE 0.25f
#define ALIEN_BULLET_SPEED 5.0
#define HERO_BULLET_SPEED -15.0
#define NUMBER_OF_BULLETS_THAT_HERO_CAN_FIRE 2
#define NUMBER_OF_BULLETS_THAT_ALIEN_CAN_FIRE 5
#define ALIEN_STEP_TIME 2000.0
#define ALIEN_MOVE_SPEED 1.0

typedef double miliseconds;

using namespace std;

class Model
{
private:
	enum MoveDirection { LEFT, RIGHT };
	MoveDirection alienMoveDirection;
	double alienStepTime;
public:
	vector<Bullet> alienBullets;
	vector<BasicAlien> aliens;
	vector<Bullet> bullets;
	Hero hero;

	int gameScore;
	int heroLives;

	bool aliensArray[ALIEN_COLS][ALIEN_ROWS];

	/*
	 * Setup new game, alines, players, score, etc ...
	 */
	void initNewGame();
	void nextStage();
	/*
	 * Updates game state
	 *
	 * @param dt time passed since last frame
	 */
	void update(const miliseconds dt);

	void moveHeroRight();
	void moveHeroLeft();
	void fireBullet();
private:
	bool isAlienInFirstLine(const int id) const;
	bool noAlienUnder(const int id) const;
	void updateAliensArray(const int id);
};

#endif /* MODEL_H_ */
