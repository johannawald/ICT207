/**
 * @class GameController
 * @brief The GameController should manage the Game itself
 *
 * The GameController should later manage the game itself with it levels 
 * and settings and stuff like that
 *
 * @author Johanna Wald
 * @version 01
 * @date 15/09/2013
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
#include "CollisionDetection.h"
#include "GameObject.h"

class GameController : public IStateController, BasisController
{
private:
	std::vector<GameObject*> mGameObject;
	CollisionDetection cd; //*JW

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

	//Camera cam; //ray, delete that after you inserted your camera movement
	//TexturedPolygons tp; //use the texturemanager! //ray, we don't need that if we implemented the texturemanager! 

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
	bool camMouseClicked; //= false;
	bool* camKeyStates; //= new bool[256]; // Create an array of boolean values of length 256 (0-255)
	void DrawTexttest();
	void SetGameObject(); //*JW
	void DrawGameObjects();
public:
			/**
             * @brief constructor creates a new LevelOneController object.
             */
	GameController(AudioManager* am, ModelManager* mm, TextureManager* tm);
			/**
             * @brief Destructor destroys LevelOneController object when it goes out of scope.
             * @param none
			*/
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
	void MouseMotion(int x, int y);
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
	// enables depth testing, lighting and shading
	void Enable(void);
	// control key presses
	void KeyOperations(void);
};
