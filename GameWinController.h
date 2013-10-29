/**
 * @class GameWinController
 * @brief Encapsulated class for the GameWin
 *
 *
 * @author Johanna Wald
 * @version 01
 * @date 26/10/2013 Johanna Wald - Version1
 */

#pragma once

#include <cstdlib>
#include <GL/glut.h>
#include <windows.h>

#include "IStateController.h"
#include "BasisController.h"

class GameWinController : public IStateController, BasisController {
private:
public:
	GameWinController(AudioManager* am, ModelManager* mm, TextureManager* tm);
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
