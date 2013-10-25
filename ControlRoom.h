/**
 * @class ControlRoom
 * @brief Encapsulated class containing all of the Control Room's objects.
 *
 * Contains draw and configuration methods for the initialization,
 * operation and drawing of the control room. Based upon the
 * encapsulated version of Shay's World.
 *
 * @author Daniel Manganaro
 * @version 01
 * @date 15/10/2013 Daniel Manganaro - Version1
 * @date 25/10/2013 Johanna Wald - Version2
 */

#pragma once

#include <cstdlib>
#include <GL/glut.h>
#include <windows.h>

#include "IStateController.h"
#include "BasisController.h"
#include "MoveController.h"

class ControlRoom : public IStateController, BasisController {
private:
	MoveController mCamera;

	bool loaded;
	// ratio of screen
	float ratio;
	// screen width and height
	int width, height;
	void DrawFloor();
	void DrawWalls();
	void DrawStairs();
	void DrawConsole();
	void DrawLadder();
public:
	ControlRoom(AudioManager* am, ModelManager* mm, TextureManager* tm);
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
