/*
 * AlienOne.h
 *
 *  Created on: Apr 26, 2012
 *      Author: kakus
 */

#ifndef ALIENONE_H_
#define ALIENONE_H_

#include "BasicAlien.h"

class ClassicALien: public BasicAlien
{
public:
	ClassicALien(const float x, const float y, int id): BasicAlien(x, y, 1.0, 1.0, id, CLASSIC_ALIEN) {}
};

#endif /* ALIENONE_H_ */
