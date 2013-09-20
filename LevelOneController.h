/**
 * @class BushCourtController
 * @brief Encapsulates Shay's World (Campus Tour)
 *
 * Encapsulates Shays World (Campus Tour) turning it into its
 * own class.
 *
 * @author Shay Leary - Original, March 2005
 * @author Raymond Forster - Encapsulation as Class, September 2013
 * @version 01
 * @date 01/03/2005 Shay Leary - Original
 * @date 06/09/2013 Raymond Forster - started
 */

#pragma once

#include <cstdlib>
#include <math.h>
#include <GL/glut.h>
#include <time.h>

#include <windows.h> // only used if mouse is required (not portable)
#include "camera.h"
#include "texturedPolygons.h"
#include "Transition.h"
#include "IStateController.h"
#include "BasisController.h";


class LevelOneController : public IStateController, BasisController
{
private:
	bool loaded; 
	Transition transition;

	GLdouble movementSpeed;
	GLdouble rotationSpeed;
	
	GLdouble stepIncrement;
	GLdouble angleIncrement;
	int frameCount;
	clock_t lastClock;

	unsigned char* LevelOneController::image;
	// ratio of screen
	float ratio;
	// screen width and height
	int width, height;
	// display campus map
	bool DisplayMap;
	// display welcome screen
	bool DisplayWelcome;
	// display exit screen
	bool DisplayExit;

	Camera cam;
	TexturedPolygons tp;

	void CheckNumberPad();
public:
	LevelOneController(void);
	virtual ~LevelOneController(void);

	void Init();
	void Draw();
	void Reshape();
	void Update();
	void Reshape(int w, int h);
	void SpecialKey(int key, int x, int y);
	void SpecialKeyUp(int key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void Keyboard(unsigned char key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void PassiveMotion(int x, int y);

	//Draw Functions
	void DrawOuterWalls();
	void DrawArchitecture();
	void Draw3DModels();
	void DrawObjects();

	void IncrementFrameCount();	
	// loads images and creates texture
	void CreateTextures();
	// creates bounding boxes for collsion detection
	void CreateBoundingBoxes();

	// deletes image and clears memory
	void DeleteImageFromMemory(unsigned char* tempImage);
};
