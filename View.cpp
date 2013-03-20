/*
 * View.cpp
 *
 *  Created on: Apr 23, 2012
 *      Author: kakus
 */

#include "View.h"
#include "ClassicInvader.h"
#include "HeroModel.h"
#include "BulletModel.h"
#include "AlienBulletModel.h"
#include "StartTextModel.h"
#include "BigHeadInvaderModel.h"
#include "SmallHeadInvaderModel.h"

#include "Controller.h"
#include <iostream>

/*
 * PRIVATE VARIABLES
 */

static Controller *pController = nullptr;
static GLfloat rotation = 0.0;
static Perspective perspective = NORMAL;

#define NUMBER_OF_AVAILABLE_LIGHT_FOR_ALIENS 5
static int availableAlienLights[NUMBER_OF_AVAILABLE_LIGHT_FOR_ALIENS] = { -1, -1, -1, -1, -1 };
static int availableHeroLights[] = {-1, -1};
//GLfloat ambientLightSettings[4] = { 0.6, 0.6, 0.6, 1.0 };
static GLfloat ambientLightSettings[4] = { 3, 3, 3, 1.0 };
static GLfloat light0Direction[3] = { 0.0, 1.0, 0.0 };
static GLfloat light0Position[4] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat light0Position2[4] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat light1Position[4] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat light2Position[4] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat light3Position[4] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat light4Position[4] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat light5Position[4] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat light6Position[4] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat light7Position[4] = { 0.0, 0.0, 10.0, 1.0 };
static GLfloat* lightPositionArray[] = {
		light0Position,
		light1Position,
		light2Position,
		light3Position,
		light4Position,
		light5Position,
		light6Position,
		light7Position
};
static GLfloat laserConstantAttenuation = 1.0;
static GLfloat laserQuadraticAttenuation = 0.0025;
static bool mirror = false;




/*
 * METHODS
 */

void View::registerController(Controller *controller)
{
	pController = controller;
}

void View::arrowKeysListener(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			pController->leftKeyPressed();
		break;

		case GLUT_KEY_RIGHT:
			pController->rightKeyPressed();
		break;

		case GLUT_KEY_UP:
			rotation+=2.1;
		break;

		case GLUT_KEY_DOWN:
			rotation-=2.1;
		break;

	}
}

void View::keyboardListener(unsigned char key, int x, int y)
{
	switch(key)
	{
		case ' ':
			pController->spaceKeyPressed();
		break;

		case '1':
			perspective = NORMAL;
		break;

		case '2':
			perspective = HERO;
		break;

		case '3':
			mirror != mirror;
		break;
	}
}

void View::idleFunc()
{
	if(pController == nullptr)
	{
		std::cerr <<"Error controller doesn't exist." <<std::endl;
		exit(1);
	}

	pController->mainLoop();
	display();
}

void View::init(int argc, char *argv[])
{
	/*
	 * Setting up window
	 */
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow(WINDOW_NAME);

	/*
	 * Initialize of openGl features
	 */
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	initGL();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(arrowKeysListener);

	glutIdleFunc(idleFunc);
	glutMainLoop();
}

void View::reshape(int width, int height)
{
	/*
	 * Full window render
	 */
	glViewport(0, 0, width, height);

	/*
	 * Makes that rendered image always will be in 1:1 ratio
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0, float(width)/height, NEAR_VALUE, FAR_VALUE);
}

void View::display()
{
	static int frame = 0;
	static GLfloat rot = 0;

#ifdef WIN32
	Sleep(10.0);
#else
	usleep(10*1000);
    //sleep(1);
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	 * Turn on lights
	 */
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLightSettings);
//
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(perspective == HERO)
	{
		GLfloat canerax = pController->getHero().x*SCALE_FACTOR-88;
		gluLookAt(canerax, -100, -160, 	//eye
				  canerax, 0.0, -180, 	//center
				  0, 1, 0);				//up
	}

//	glTranslatef(-20.0, 20.0, -40.0);
  glTranslatef(-90.0, 90.0, -180.0);
//	glRotatef(rotation, 0.0, 1.0, 0.0);


//	glDisable(GL_LIGHTING);
//	glPushMatrix();
//		glColor3f(0.6, 0.6, 0.6);
//		glTranslatef(-800, -200-frame, -5);
//		drawNet(2000, 2000, 30, 30, 0.5);
//	glPopMatrix();
//
//	glPushMatrix();
//		glColor3f(0.6, 0.6, 0.6);
//		glTranslatef(-800, -200-(frame+=20), 40);
//		drawNet(2000, 2000, 30, 30, 0.5);
//	glPopMatrix();

	if(frame > 800)
		frame = 0;
	//glEnable(GL_LIGHTING);

	glColorMask(0,0,0,0);								// Set Color Mask
	glEnable(GL_STENCIL_TEST);							// Enable Stencil Buffer For "marking" The Floor
	glStencilFunc(GL_ALWAYS, 1, 1);						// Always Passes, 1 Bit Plane, 1 As Mask
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);			// We Set The Stencil Buffer To 1 Where We Draw Any Polygon
														// Keep If Test Fails, Keep If Test Passes But Buffer Test Fails
														// Replace If Test Passes
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glPushMatrix();
			glTranslatef(-80, 200, -10);
			glRotatef(90, 1, 0, 0);
			drawSquarePlain(100, 4);
	glPopMatrix();								// Draw The Floor (Draws To The Stencil Buffer)
														// We Only Want To Mark It In The Stencil Buffer
	glEnable(GL_DEPTH_TEST);							// Enable Depth Testing
	glColorMask(1,1,1,1);								// Set Color Mask to TRUE, TRUE, TRUE, TRUE
	glStencilFunc(GL_EQUAL, 1, 1);						// We Draw Only Where The Stencil Is 1
														// (I.E. Where The Floor Was Drawn)
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);				// Don't Change The Stencil Buffer
	glEnable(GL_CLIP_PLANE0);							// Enable Clip Plane For Removing Artifacts
	
	double eqr[] = {0.0f, -1.0f, 0.0f, 0.0f};			// (When The Object Crosses The Floor)
	glClipPlane(GL_CLIP_PLANE0, eqr);					// Equation For Reflected Objects
	glPushMatrix();
		glTranslatef(0, 0, -20);
		glScalef(1.0f, 1.0f, -1.0f);					// Mirror Y Axis
		setUpLights();	// Set Up Light0
		displayAliens();
		displayHero();
		displayBullets();
		displayAlienBullets();
	glPopMatrix();										// Pop The Matrix Off The Stack
	glDisable(GL_CLIP_PLANE0);							// Disable Clip Plane For Drawing The Floor
	glDisable(GL_STENCIL_TEST);							// We Don't Need The Stencil Buffer Any More (Disable)
	glEnable(GL_BLEND);

	//if(mirror)// Enable Blending (Otherwise The Reflected Object Wont Show)
	//	glDisable(GL_LIGHTING);								// Since We Use Blending, We Disable Lighting
	glColor4f(0.0f, 0.0f, 0.0f, 0.4f);					// Set Color To White With 80% Alpha
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blending Based On Source Alpha And 1 Minus Dest Alpha

	glPushMatrix();
		SET_MATERIAL(BlackPlastic);
		glTranslatef(-80, 140, -10);
		glRotatef(90, 1, 0, 0);
		drawSquarePlain(100, 4);
	glPopMatrix();										// Draw The Floor To The Screen

	glEnable(GL_LIGHTING);								// Enable Lighting
	glDisable(GL_BLEND);

    setUpLights();
	displayAliens();
	displayHero();
	displayBullets();
	displayAlienBullets();

	//glFlush();
	glutSwapBuffers();
}

void View::drawNet(float width, float height, float numberOfxLines, float numberOfyLines, float lineWidth)
{
	/*
	 * here we draw:
	 * -------------
	 * --------------
	 * ------------
	 */
	glLineWidth(lineWidth);
	for (int x = 0; x < numberOfxLines; ++x)
	{
		glBegin(GL_LINES);
			glVertex3f(0, x*height/numberOfxLines, 0);
			glVertex3f(width, x*height/numberOfxLines, 0);
		glEnd();
	}
	/*
	 * and there
	 * | | | | |
	 * | | | | |
	 * | | | | |
	 */
	for (int y = 0; y < numberOfyLines; ++y)
	{
		glBegin(GL_LINES);
			glVertex3f(y*width/numberOfyLines, 0, 0);
			glVertex3f(y*width/numberOfyLines, height, 0);
		glEnd();
	}
}

void View::drawSquarePlain(int numberOfQuads, float size)
{
	glBegin(GL_QUADS);
		for(int x=0; x<numberOfQuads; ++x)
		{
			for(int y=0; y<numberOfQuads; ++y)
			{
				float fx = x*size;
				float fz = y*size;

				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f(fx, 0.0, fz);		//topleft
				glVertex3f(fx+size, 0.0, fz);	//topright
				glVertex3f(fx+size, 0.0, fz+size);	//bottomright
				glVertex3f(fx, 0.0, fz+size);	//bottomleft
			}
		}
	glEnd();
}

void View::drawLine(float width, float height)
{
	glBegin(GL_QUADS);
		glVertex3f(0, 0.0, 0);		//topleft
		glVertex3f(width, 0, 0);	//topright
		glVertex3f(width, height, 0);	//bottomright
		glVertex3f(0, height, 0);	//bottomleft
	glEnd();
}

void View::setUpLights()
{

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);

	glLightfv(GL_LIGHT0,GL_POSITION,light0Position);
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,light0Direction);
//	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);    	// set cutoff angle
//	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT,20.0);

	glLightfv(GL_LIGHT1,GL_POSITION,light1Position);
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,light0Direction);

	glLightfv(GL_LIGHT2,GL_POSITION,light2Position);
	glLightfv(GL_LIGHT3,GL_POSITION,light3Position);
	glLightfv(GL_LIGHT4,GL_POSITION,light4Position);
	glLightfv(GL_LIGHT5,GL_POSITION,light5Position);
	glLightfv(GL_LIGHT6,GL_POSITION,light6Position);
	glLightfv(GL_LIGHT7,GL_POSITION,light7Position);

	glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION, laserConstantAttenuation);
	glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,laserQuadraticAttenuation);

	glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION, laserConstantAttenuation);
	glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,laserQuadraticAttenuation);

	glLightf(GL_LIGHT2,GL_CONSTANT_ATTENUATION, laserConstantAttenuation);
	glLightf(GL_LIGHT2,GL_QUADRATIC_ATTENUATION,laserQuadraticAttenuation);

	glLightf(GL_LIGHT3,GL_CONSTANT_ATTENUATION, laserConstantAttenuation);
	glLightf(GL_LIGHT3,GL_QUADRATIC_ATTENUATION,laserQuadraticAttenuation);

	glLightf(GL_LIGHT4,GL_CONSTANT_ATTENUATION, laserConstantAttenuation);
	glLightf(GL_LIGHT4,GL_QUADRATIC_ATTENUATION,laserQuadraticAttenuation);

	glLightf(GL_LIGHT5,GL_CONSTANT_ATTENUATION, laserConstantAttenuation);
	glLightf(GL_LIGHT5,GL_QUADRATIC_ATTENUATION,laserQuadraticAttenuation);

	glLightf(GL_LIGHT6,GL_CONSTANT_ATTENUATION, laserConstantAttenuation);
	glLightf(GL_LIGHT6,GL_QUADRATIC_ATTENUATION,laserQuadraticAttenuation);

	glLightf(GL_LIGHT7,GL_CONSTANT_ATTENUATION, laserConstantAttenuation);
	glLightf(GL_LIGHT7,GL_QUADRATIC_ATTENUATION,laserQuadraticAttenuation);

	GLfloat whiteLaser[] = { 1, 1, 1, 1};
	glLightfv(GL_LIGHT1,GL_SPECULAR, whiteLaser);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteLaser);

	GLfloat redLaser[] = { 1, 0, 0, 1};
	glLightfv(GL_LIGHT2,GL_SPECULAR,redLaser);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, redLaser);

	glLightfv(GL_LIGHT3,GL_SPECULAR,redLaser);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, redLaser);

	glLightfv(GL_LIGHT3,GL_SPECULAR,redLaser);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, redLaser);

	glLightfv(GL_LIGHT4,GL_SPECULAR,redLaser);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, redLaser);

	glLightfv(GL_LIGHT5,GL_SPECULAR,redLaser);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, redLaser);

	glLightfv(GL_LIGHT6,GL_SPECULAR,redLaser);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, redLaser);

	GLfloat blueLaser[] = { 0, 0, 1, 1};
	glLightfv(GL_LIGHT7,GL_SPECULAR, blueLaser);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, blueLaser);
}

void View::drawString (GLfloat x, GLfloat y, const string& string)
{
    //glRasterPos2f (x,y);
    //for (auto c : string)
    //    glutBitmapCharacter (GLUT_BITMAP_9_BY_15, c);
}

void View::displayAlienBullets()
{
	glDisable(GL_LIGHTING);
	glColor3f(1, 0, 0);
	static int frame = 0;

	/*
	 * Remove unused lights from scene
	 */
	light2Position[0] = LIGHTS_GRAVEYEARD;
	light3Position[0] = LIGHTS_GRAVEYEARD;
	light4Position[0] = LIGHTS_GRAVEYEARD;
	light5Position[0] = LIGHTS_GRAVEYEARD;
	light6Position[0] = LIGHTS_GRAVEYEARD;

	auto &bullets = pController->getAlienBullets();
	for(int i=0; i<bullets.size(); ++i)
	{
		if(bullets[i].alive == false) continue;

		for(int light=0; light<NUMBER_OF_AVAILABLE_LIGHT_FOR_ALIENS; ++light)
		{
			if(availableAlienLights[light]==-1  ||
			   availableAlienLights[light]==i   ||
			   bullets[availableAlienLights[light]].alive == false)
			{
				lightPositionArray[2+light][0]=bullets[i].x*SCALE_FACTOR;
				lightPositionArray[2+light][1]=-bullets[i].y*SCALE_FACTOR-2*SCALE_FACTOR;
				availableAlienLights[light]=i;
				break;
			}
		}

		glPushMatrix();
			glTranslatef(bullets[i].x*SCALE_FACTOR, -bullets[i].y*SCALE_FACTOR, 0.0);
			if(frame%30<15)
				stringToModel2(std::string(ALIEN_BULLET_MODEL_FRAME1), ALIEN_BULLET_MODEL_WIDTH, 1.0, 1);
			else
				stringToModel2(std::string(ALIEN_BULLET_MODEL_FRAME2), ALIEN_BULLET_MODEL_WIDTH, 1.0, 1);
		glPopMatrix();
	}

	frame++;
	glEnable(GL_LIGHTING);
}

void View::displayBullets()
{
	glDisable(GL_LIGHTING);
	//TODO trasnparent laser
//	glDisable(GL_DEPTH_TEST);
	glColor4f(1, 1, 1, 1);

	/*
	 * Remove unused light from scene
	 */
	light0Position[0] = LIGHTS_GRAVEYEARD;
	light1Position[0] = LIGHTS_GRAVEYEARD;

	auto bullets = pController->getBullets();
	for(int i=0; i<bullets.size(); ++i)
	{
		if(bullets[i].alive == false) continue;

		if(availableHeroLights[0] == -1 || availableHeroLights[0] == i || bullets[availableHeroLights[0]].alive == false)
		{
			light0Position[0]=bullets[i].x*SCALE_FACTOR;
			light0Position[1]=-bullets[i].y*SCALE_FACTOR-SCALE_FACTOR;
			availableHeroLights[0] = i;
		}
		else if(availableHeroLights[1] == -1 || availableHeroLights[1] == i || bullets[availableHeroLights[1]].alive == false)
		{
			light1Position[0]=bullets[i].x*SCALE_FACTOR;
			light1Position[1]=-bullets[i].y*SCALE_FACTOR-SCALE_FACTOR;
			availableHeroLights[1] = i;
		}

		glPushMatrix();
			glTranslatef(bullets[i].x*SCALE_FACTOR, -bullets[i].y*SCALE_FACTOR, 0.0);
			stringToModel2(std::string(BULLET_MODEL_FRAME1), BULLET_MODEL_WIDTH, 1.0, 1);
		glPopMatrix();
	}

//	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void View::displayHero()
{
	auto &hero = pController->getHero();

	SET_MATERIAL(Emerald);
	glPushMatrix();
		light7Position[0] = hero.x*SCALE_FACTOR;
		light7Position[1] = -hero.y*SCALE_FACTOR-20;
		glTranslatef(hero.x*SCALE_FACTOR, -hero.y*SCALE_FACTOR, 0.0);
//		glTranslatef(-5.0, -2.0, 0.0);
		stringToModel2(std::string(HERO_MODEL_FRAME1), HERO_MODEL_WIDTH, 1.0, 1);
	glPopMatrix();
}

void View::displayAliens()
{
	static int frame = 0;
	auto aliens = pController->getAliens();
	auto alienIt = aliens.begin();
	for(;alienIt != aliens.end(); ++alienIt)
	{
		auto &alien = *alienIt;
		if(alien.alive == false) continue;
		glPushMatrix();
			glTranslatef(alien.x*SCALE_FACTOR, -alien.y*SCALE_FACTOR, 0.0);
			if(perspective == HERO)
			{
				glTranslatef(SCALE_FACTOR/2, SCALE_FACTOR/2, SCALE_FACTOR/2);
				glRotatef(90, 1, 0, 0);
				glTranslatef(-SCALE_FACTOR/2, -SCALE_FACTOR/2, 0);
			}
			switch(alien.alienType)
			{
				case BIG_HEAD_ALIEN:
					SET_MATERIAL(Pearl);
					if(frame%30>15)
                        stringToModel2(std::string(BIGHEAD_INVADER_FRAME1),
                                BIGHEAD_INVADER_WIDTH, 1.0, INVADERS_FATNESS);
					else
                        stringToModel2(std::string(BIGHEAD_INVADER_FRAME2),
                                BIGHEAD_INVADER_WIDTH, 1.0, INVADERS_FATNESS);
					break;

				case SMALL_HEAD_ALIEN:
					SET_MATERIAL(Emerald);
					if(frame%30>15)
                        stringToModel2(std::string(SMALLHEAD_INVADER_FRAME1),
                                SMALLHEAD_INVADER_WIDTH, 1.0, INVADERS_FATNESS);
					else
                        stringToModel2(std::string(SMALLHEAD_INVADER_FRAME2),
                                SMALLHEAD_INVADER_WIDTH, 1.0, INVADERS_FATNESS);
					break;

				default:
					SET_MATERIAL(Jade);
					if(frame%30>15)
                        stringToModel2(std::string(CLASSIC_INVADER_FRAME1),
                                CLASSIC_INVADER_WIDTH, 1.0, INVADERS_FATNESS);
					else
                        stringToModel2(std::string(CLASSIC_INVADER_FRAME2),
                                CLASSIC_INVADER_WIDTH, 1.0, INVADERS_FATNESS);
					break;
			}
		glPopMatrix();
	}
	frame++;
}

void View::initGL()
{
//	glClearColor(1.0, 1.0, 1.0, 1.0);
	/*
	 * Set background color to black
	 */
	glClearColor(0.0, 0.0, 0.0, 1.0);

	/*
	 * Turn on depth buffer
	 */
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glClearStencil(0);

	glEnable (GL_NORMALIZE);
	//glEnable (GL_BLEND);
//	glShadeModel(GL_FLAT);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void View::stringToModel2(const std::string model, int width, float cubeSize, float fatness)
{
	int x = 0, y = 0;
	int height = model.size()/width;

	glBegin(GL_QUADS);
		for(int i=0; i<model.size(); ++i)
		{
			auto s = model[i];
			float fx = float(x)*cubeSize;
			float fy = float(y)*cubeSize;

			if ( s == '#')
			{
				/*
				 * If before '#' was '-' we need to draw left wall, also in case where nothing
				 * was before '#'
				 */
				if((x>0 && model[y*width + x-1]=='-') || x==0)
				{
					/*
					 * side left face
					 */
					glNormal3f(-1.0, 0.0, 0.0);
					glVertex3f(fx, -fy, -fatness);		//topleft
					glVertex3f(fx, -fy, 0.0);			//topright
					glVertex3f(fx, -fy-cubeSize, 0.0);	//bottomright
					glVertex3f(fx, -fy-cubeSize, -fatness);	//bottomleft
				}

				/*
				 * Same thing as above but case where '-' is after '#'
				 */
				if((x<(width-1) && model[y*width + x+1]=='-') || x==(width-1))
				{
					/*
					 * side right face
					 */
					glNormal3f(1.0, 0.0, 0.0);
					glVertex3f(fx+cubeSize, -fy, 0.0);
					glVertex3f(fx+cubeSize, -fy, -fatness);
					glVertex3f(fx+cubeSize, -fy-cubeSize, -fatness);
					glVertex3f(fx+cubeSize, -fy-cubeSize, 0.0);
				}

				/*
				 * If above '#' is '-' we need to draw wall
				 */
				if((y>0 && model[(y-1)*width + x]=='-') || y==0)
				{
					/*
					 * upper side face
					 */
					glNormal3f(0.0, 1.0, 0.0);
					glVertex3f(fx, -fy, 0.0);
					glVertex3f(fx, -fy, -fatness);
					glVertex3f(fx+cubeSize, -fy, -fatness);
					glVertex3f(fx+cubeSize, -fy, 0.0);
				}

				/*
				 * If under '#' is '-' we need to draw wall
				 */
				if((y<(height-1) && model[(y+1)*width + x]=='-') || y==(height-1))
				{
					/*
					 * bottom side face
					 */
					glNormal3f(0.0, -1.0, 0.0);
					glVertex3f(fx, -fy-cubeSize, -fatness);
					glVertex3f(fx, -fy-cubeSize, 0.0);
					glVertex3f(fx+cubeSize, -fy-cubeSize, 0.0);
					glVertex3f(fx+cubeSize, -fy-cubeSize, -fatness);
				}

				/*
				 * Top face
				 */
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f(fx, -fy, 0.0);		//topleft
				glVertex3f(fx+cubeSize, -fy, 0.0);	//topright
				glVertex3f(fx+cubeSize, -fy-cubeSize, 0.0);	//bottomright
				glVertex3f(fx, -fy-cubeSize, 0.0);	//bottomleft

				/*
				 * Bottom face
				 */
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(fx, -fy, -cubeSize);		//topleft
				glVertex3f(fx+cubeSize, -fy, -cubeSize);	//topright
				glVertex3f(fx+cubeSize, -fy-cubeSize, -cubeSize);	//bottomright
				glVertex3f(fx, -fy-cubeSize, -cubeSize);	//bottomleft
			}

			if((++x)%width==0 && x!=0)
			{
				++y;
				x = 0;
			}
		}
	glEnd();

}

void View::stringToModel(const std::string model, int width, float cubeSize)
{
	int x = 0, y = 0;
	int height = model.size()/width;

	glBegin(GL_QUADS);
		auto sIt = model.begin();
auto &s = *sIt;
for(; sIt != model.end(); ++sIt)
		{
			float fx = float(x)*cubeSize;
			float fy = float(y)*cubeSize;

			if ( s == '#')
			{
				/*
				 * If before '#' was '-' we need to draw left wall, also in case where nothing
				 * was before '#'
				 */
				if((model[y*width + x-1]=='-' && x>0) || x==0)
				{
					/*
					 * side left face
					 */
					glNormal3f(-1.0, 0.0, 0.0);
					glVertex3f(fx, -fy, -cubeSize);		//topleft
					glVertex3f(fx, -fy, 0.0);			//topright
					glVertex3f(fx, -fy-cubeSize, 0.0);	//bottomright
					glVertex3f(fx, -fy-cubeSize, -cubeSize);	//bottomleft
				}

				/*
				 * Same thing as above but case where '-' is after '#'
				 */
				if((model[y*width + x+1]=='-' && x<(width-1)) || x==(width-1))
				{
					/*
					 * side right face
					 */
					glNormal3f(1.0, 0.0, 0.0);
					glVertex3f(fx+cubeSize, -fy, 0.0);
					glVertex3f(fx+cubeSize, -fy, -cubeSize);
					glVertex3f(fx+cubeSize, -fy-cubeSize, -cubeSize);
					glVertex3f(fx+cubeSize, -fy-cubeSize, 0.0);
				}

				/*
				 * If above '#' is '-' we need to draw wall
				 */
				if((model[(y-1)*width + x]=='-' && y>0) || y==0)
				{
					/*
					 * upper side face
					 */
					glNormal3f(0.0, 1.0, 0.0);
					glVertex3f(fx, -fy, 0.0);
					glVertex3f(fx, -fy, -cubeSize);
					glVertex3f(fx+cubeSize, -fy, -cubeSize);
					glVertex3f(fx+cubeSize, -fy, 0.0);
				}

				/*
				 * If under '#' is '-' we need to draw wall
				 */
				if((model[(y+1)*width + x]=='-' && y<(height-1)) || y==(height-1))
				{
					/*
					 * bottom side face
					 */
					glNormal3f(0.0, -1.0, 0.0);
					glVertex3f(fx, -fy-cubeSize, -cubeSize);
					glVertex3f(fx, -fy-cubeSize, 0.0);
					glVertex3f(fx+cubeSize, -fy-cubeSize, 0.0);
					glVertex3f(fx+cubeSize, -fy-cubeSize, -cubeSize);
				}

				/*
				 * Top face
				 */
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f(fx, -fy, 0.0);		//topleft
				glVertex3f(fx+cubeSize, -fy, 0.0);	//topright
				glVertex3f(fx+cubeSize, -fy-cubeSize, 0.0);	//bottomright
				glVertex3f(fx, -fy-cubeSize, 0.0);	//bottomleft

				/*
				 * Bottom face
				 */
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(fx, -fy, -cubeSize);		//topleft
				glVertex3f(fx+cubeSize, -fy, -cubeSize);	//topright
				glVertex3f(fx+cubeSize, -fy-cubeSize, -cubeSize);	//bottomright
				glVertex3f(fx, -fy-cubeSize, -cubeSize);	//bottomleft
			}

			if((++x)%width==0 && x!=0)
			{
				++y;
				x = 0;
			}
		}
	glEnd();
}


