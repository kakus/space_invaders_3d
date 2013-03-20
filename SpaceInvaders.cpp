//============================================================================
// Name        : SpaceInvaders.cpp
// Author      : Kamil Misiowiec
// Version     : 0.1b
// Description : Space invaders in C++ and openGL
//============================================================================

/*
 * 			Orginalnie invadersow jest 11 x 5 (w x h)
 * 			sa 4 bunkry
 *
 * 			* * * * * * * * * * * <- 11
 * 			# # # # # # # # # # #
 * 			# # # # # # # # # # #
 * 			& & & & & & & & & & &
 * 			& & & & & & & & & & &
 *
 * 				^	^	^	^
 * 				_/\_  <- ty
 *
 * 			x x <-zycia
 *
 */
#include <iostream>
#include "View.h"
#include "Controller.h"

using namespace std;

int main(int argc, char *argv[])
{
 	Controller controller;
	/*
	 * Ugly construction where view register controller, it is
	 * forced by glut. Can't register class members as function
	 * callbacks in glut api.
	 */
	View::registerController(&controller);
	controller.init();
	View::init(argc, argv);
	return 0;
}
