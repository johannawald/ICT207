/**
 * @class LevelOneController
 * @brief Encapsulated class containing all of Level One's objects.
 *
 * Contains draw and configuration methods for the initialization,
 * operation and drawing of the first level. Based upon the
 * encapsulated version of Shay's World.
 *
 * @author Jon Mace
 * @version 01
 * @date 20/09/2013 Jon Mace - Version1
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
#include "BasisController.h"


class LevelOneController : public IStateController, BasisController
{
private:
	bool insertedLevel;
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
			/**
             * @brief Default constructor creates a new LevelOneController object.
             *
             * @param none
             */
	LevelOneController(AudioManager* am, ModelManager* mm, TextureManager* tm);
	/**
             * @brief Destructor destroys LevelOneController object when it goes out of scope.
             * @param none
    */
	virtual ~LevelOneController(void);

	//shays code lol
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

			/**
             * @brief Draws the containing walls of the level
             *
             * @param none
			 * @return void
             */
	void DrawOuterWalls();

			/**
             * @brief Draws the world geometry of the level
             *
             * @param none
			 * @return void
             */
	void DrawArchitecture();

			/**
             * @brief Initializes and draws the 3d models (.obj) in the level
             *
             * @param none
			 * @return void
             */
	void Draw3DModels();

			/**
             * @brief Draws the objects (things that can change) in the level
             *
             * @param none
			 * @return void
             */
	void DrawObjects();

			/**
             * @brief Geometry for the control room
             *
             * @param none
			 * @return void
             */
	void DrawControlRoom();

	void IncrementFrameCount();	
	// loads images and creates texture
	void CreateTextures();
	// creates bounding boxes for collsion detection
	void CreateBoundingBoxes();

	// deletes image and clears memory
	void DeleteImageFromMemory(unsigned char* tempImage);
};
