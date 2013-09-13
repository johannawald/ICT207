//  @ Unit : ICT207
//  @ File Name : IStateController.h
//  @ Author : Johanna Wald
//
//

// Interface for GameState.controller. You have to have the following functions:
//	•	void keydownevent(): handle key events (to change state)
//	•	void init(): to init the controller
//	•	void draw(): draw the state (normally view->draw())
//	•	void update() : update data in the model

#pragma once

class IStateController {
public:	
	virtual ~IStateController() {
		int a;
	};
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Update(int w, int h) = 0;
	virtual void SpecialKey(int key, int x, int y) = 0;
	virtual void SpecialKeyUp(int key, int x, int y) = 0;
	virtual void KeyboardUp(unsigned char key, int x, int y) = 0;
	virtual void Keyboard(unsigned char key, int x, int y) = 0;
	virtual void Mouse(int button, int state, int x, int y) = 0;
	virtual void PassiveMotion(int x, int y) = 0;
	virtual void Reshape(int w, int h) = 0;
};
