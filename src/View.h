/*
 * View.h
 *
 *  Created on: Apr 23, 2012
 *      Author: kakus
 */

#ifndef VIEW_H_
#define VIEW_H_

#ifdef WIN32
#include "glut.h"
#include <windows.h>
#else
#include <unistd.h>
#include <GL/glut.h>
#endif

#include <GL/gl.h>
#include <string>
#include "materials.h"
#include <vector>
#include "GameObject.h"

#define WINDOW_NAME "Space invaders by Kakus"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define NEAR_VALUE 10.0
#define FAR_VALUE 2000.0
#define SCALE_FACTOR 11.0
#define INVADERS_FATNESS 1.0

		/*
		 * This is some x value that moves light
		 * so far, player cant see it on scene
		 */
#define LIGHTS_GRAVEYEARD -900

#define SET_MATERIAL(name) glMaterialfv (GL_FRONT,GL_AMBIENT,name##Ambient);\
glMaterialfv (GL_FRONT,GL_DIFFUSE,name##Diffuse);\
glMaterialfv (GL_FRONT,GL_SPECULAR,name##Specular);\
glMaterialf (GL_FRONT,GL_SHININESS,name##Shininess)

class Controller;

enum Perspective { NORMAL, HERO };

/*
 * Because glut is written in C, the View class can't be constructed.
 * So i'am trying to imitate class by namespace.
 * Private members are in View.cpp file and they are defined as globals.
 */
namespace View
{
	void init(int argc, char *argv[]);
	void display();

	void drawNet(float width, float height, float numberOfxLines, float numberOfyLines, float lineWidth);
	void drawLine(float width, float height);
	void drawSquarePlain(int numberOfQuads, float size);
	void setUpLights();
	void displayAliens();
	void displayHero();
	void displayBullets();
	void displayAlienBullets();

	void reshape(int width, int height);
	void idleFunc();
	void initGL();
	void drawString (GLfloat x, GLfloat y, const std::string &string);

	void arrowKeysListener(int key, int x, int y);
	void keyboardListener(unsigned char key, int x, int y);

	void stringToModel(const std::string model, int width, float size);
	void stringToModel2(const std::string model, int width, float cubeSize, float fatness);
	/*
	 * Register controller, all events that coming from gui
	 * will be dispatched by the controller.
	 */
	void registerController(Controller *controller);
};


#endif /* VIEW_H_ */
