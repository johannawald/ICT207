/**
 * @class GameController
 * @date 06/09/2013 Johanna Wald
 */

#include "IStateController.h"

#pragma once

class GameController : public IStateController	
{
private:
	public:
	GameController(void);

	void Init();
	void Draw();
	void Update();
	void SpecialKey(int key, int x, int y);
	void SpecialKeyUp(int key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void Keyboard(unsigned char key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void PassiveMotion(int x, int y);
	void Reshape(int w, int h);
};
