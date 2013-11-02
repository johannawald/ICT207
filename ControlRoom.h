/**
 * @class ControlRoom
 * @brief Encapsulated class containing all of the Control Room's objects.
 *
 * Contains draw and configuration methods for the initialization,
 * operation and drawing of the control room. Based upon the
 * encapsulated version of Shay's World.
 *
 * @author Daniel Manganaro
 * @version 03
 * @date 15/10/2013 Daniel Manganaro - Version1
 * @date 20/10/2013 Johanna Wald - added some basic functionallity
 * @date 25/10/2013 Johanna Wald - added gameobjects
 */

#pragma once

#include <cstdlib>
#include <GL/glut.h>
#include <windows.h>

#include "GameController.h"

class ControlRoom : public GameController {
private:
	int mIndexConsole;
	int mIndexLadder;
	bool mShowConsoleScreen;

	void InitWalls();
	void InitFloor();
	void DrawConsoleScreen(const GLdouble &xImgSize, const GLdouble &yImgSize, 
						   const GLdouble &xStart, const GLdouble &yStart, const GLdouble &zStart,
						   const GLdouble &xTimes, const GLdouble &yTimes, const bool &flip);

	virtual void InitGameObjects();
	virtual void DrawObjects();	
public:
	ControlRoom(AudioManager* am, ModelManager* mm, TextureManager* tm);

	virtual void Keyboard(unsigned char key, int x, int y);
};
