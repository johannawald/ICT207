//  @ Project : QPT 1 - pacmet
//  @ File Name : StateMachine.h
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//
//

// Dieses Singelton verwaltet die State des Games. 
// Sie hält eine Liste von IStateControllern, die jeweils über die Statemachine aufgerufen werden. 
// Sie ist so ausgelegt, dass mehrer Controller gleichzeitig aktiv sein können (z. B. GameControllerManager und PauseController)
// Das wird über die states selbst gelöst, hier kann z. B. einfach die update()-Funktion deaktiviert werden
// In ihrer init()-, update()-, draw()- und keydown()-Funktion ruft sie die jeweiligen Funktionen der Liste auf, 
// falls da jeweilige Flag dazu im GameState aktiv sein

#pragma once

#include "GameState.h"
#include <vector>

class IStateController;
class StateMachine {
private:
	//GameState gamestate;
	static bool init;
    static StateMachine* statemachine;
	StateMachine(GameState* gamestate);
public:	
	static GameState* bushcourtcontroller;
	//static std::vector<GameState*> state;
	GameState* state;
	static StateMachine* getInstance();

	static void setController(GameState* gamestate);
	static void setController(IStateController* controller);

	~StateMachine();
	
	void Init();
	void Draw();
	void Update(int w, int h);
	void SpecialKey(int key, int x, int y);
	void SpecialKeyUp(int key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void Keyboard(unsigned char key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void PassiveMotion(int x, int y);
	void Reshape(int w, int h);
};
