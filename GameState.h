//  @ Project : QPT 1 - pacmet
//  @ File Name : GameState.h
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//
//

// Beschreibt einen Game-State der StateMachine 
// Membervariablen:
//	•	IStateController* controller: Der Controller selbst mit init(), update(), draw() und keydown()-Funktion
//	•	bool draw: Das Flag ob draw aufgerufen werden soll
//	•	bool update: Das Flag ob update aufgerufen werden soll
//	•	bool init: Das Flag ob init aufgerufen werden soll
//	•	bool keydown: Das Flag ob keydown aufgerufen werden soll

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
