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
 * @date 16/10/2013 Raymond Forster - Version2: Added 3rd Person Camera
 */

#pragma once

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <math.h>
#include <time.h>

//#include "camera.h"
#include "texturedPolygons.h"
#include "IStateController.h"
#include "BasisController.h"

class LevelOneController : public IStateController, BasisController
{
private:
	
	bool insertedLevel;
	bool loaded; 
	
	GLdouble movementSpeed; //ray, delete that after you inserted your camera movement
	GLdouble rotationSpeed; //ray, delete that after you inserted your camera movement
	
	GLdouble stepIncrement; //ray, delete that after you inserted your camera movement
	GLdouble angleIncrement; //ray, delete that after you inserted your camera movement
	int frameCount;
	clock_t lastClock; 
	// ratio of screen
	float ratio;
	// screen width and height
	int width, height;

	// camera data members
	float camSpeed;
	// angle of rotation values
	float camXpos; //= 0.0; 
	float camYpos; //= 0.0; 
	float camZpos; //= 0.0; 
	float camXrot; //= 0.0; 
	float camYrot; //= 0.0;
	
	// distance from character
	float camRadius; //= 2.5f;

	// max and min camera angle
	float camMaxAngle; //= 30.0;
	float camMinAngle; //= 0.0;
	float camLastx; // last mouse x position 
	float camLasty; // last mouse y position
	int camDiffy;
	int camDiffx;
	float camYrotrad;
	float camXrotrad;
	bool camMouseClicked;
	bool* camKeyStates; 
	bool* camSpecialKeyStates;

public:
	/**
            * @brief constructor creates a new LevelOneController object.
    */
	LevelOneController(AudioManager* am, ModelManager* mm, TextureManager* tm);
	/**
             * @brief Destructor destroys LevelOneController object when it goes out of scope.
             * @param none
	*/
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
	void MouseMotion(int x, int y);

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
	// creates bounding boxes for collsion detection

	// enables depth testing, lighting and shading
	void Enable(void);
	// control key presses
	void KeyOperations(void);
};
