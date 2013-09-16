//  @ Unit : ICT207
//  @ File Name : GameState.h
//  @ Author : Johanna Wald
//
//

// A game state of the state machine 
// members:
//	•	IStateController* controller: The controller itself with init(), update(), draw() und keydown()-functions
//	•	bool draw: The Flag saying if draw should be called
//	•	bool update:The Flag saying if update should be called
//	•	bool init: The Flag saying if init should be called
//	•	bool keydown: The Flag saying if keydown should be called

#pragma once

#include "IStateController.h"

class GameState {
public:
	GameState(IStateController* c, bool d = true, bool u = true, bool i = true, bool k = true): controller(c), draw(d), update(u), init(i), keydown(k) {};
	GameState(): controller(nullptr), draw(false), update(false), init(false), keydown(false) {};
	~GameState() {
		delete controller;
		//std::cout << "~GameState" << std::endl;
	};
	IStateController* controller;
	bool draw;
	bool update;
	bool init;
	bool keydown;
};
