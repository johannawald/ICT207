//  @ Unit : ICT207
//  @ File Name : IStateController.h
//  @ Author : Johanna Wald
//
//

// Interface (abstract class) for a gameState controller
// The programm is just dealing with this class
// Since the functions are abstract, you have to implement them in derived classes
// The StateMachine has a member Variable based on this class and call them 

#pragma once

/*#include "ModelManager.h"
#include "AudioManager.h"
#include "TextureManager.h"*/

class IStateController {
public:	
	virtual ~IStateController() {};
	//Initialization of your class
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void SpecialKey(int key, int x, int y) = 0;
	virtual void SpecialKeyUp(int key, int x, int y) = 0;
	virtual void KeyboardUp(unsigned char key, int x, int y) = 0;
	virtual void Keyboard(unsigned char key, int x, int y) = 0;
	virtual void Mouse(int button, int state, int x, int y) = 0;
	virtual void PassiveMotion(int x, int y) = 0;
	virtual void Reshape(int w, int h) = 0;
};
