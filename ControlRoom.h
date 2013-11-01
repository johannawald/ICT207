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

#include "IStateController.h"
#include "BasisGameController.h"

class ControlRoom : public IStateController, BasisGameController {
private:
	int mIndexLadder;
	bool mShowConsole;

	void DrawFloor();
	void DrawWalls();
	void DrawStairs();
	void DrawConsole();
	void DrawLadder();

	void DrawConsoleScreen(const GLdouble &xImgSize, const GLdouble &yImgSize, 
						   const GLdouble &xStart, const GLdouble &yStart, const GLdouble &zStart,
						   const GLdouble &xTimes, const GLdouble &yTimes, const bool &flip);

	bool IsAtComputerPosition();
	int CheckCollision();
	void CollisionWithObject(GameObject* pGameObject);
public:
	ControlRoom(AudioManager* am, ModelManager* mm, TextureManager* tm);

	void Init();
	void Draw();
	void DrawObjects();
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
