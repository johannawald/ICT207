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

//not used anymore as level one -> level two??

#pragma once

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <math.h>
#include <time.h>

#include "texturedPolygons.h"
#include "IStateController.h"
#include "BasisController.h"
#include "MoveController.h"

class LevelOneController : public IStateController, BasisController
{
private:
	MoveController mCamera;
	bool loaded; 

	// ratio of screen
	float ratio;
	// screen width and height
	int width, height;

	// creates bounding boxes for collsion detection
	void DrawOuterWalls();
	void DrawArchitecture();
	void Draw3DModels();
	void DrawObjects();
	void DrawControlRoom();
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
};
