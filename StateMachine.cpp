//  @ Project : QPT 1 - pacmet
//  @ File Name : StateMachine.cpp
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//
//

#include "StateMachine.h"
#include "IStateController.h"
#include <vector>
#include "BushCourtController.h"
#include "GameController.h"

StateMachine* StateMachine::statemachine = nullptr;
GameState* StateMachine::bushcourtcontroller = nullptr;
//std::vector<GameState*> StateMachine::state = std::vector<GameState*>();
bool StateMachine::init = false;

StateMachine::StateMachine(GameState* gamestate) {
	//StateMachine::state.push_back(gamestate);
	state = gamestate;
	//StateMachine::state[StateMachine::state.size()-1]->controller->Init();
}

StateMachine::~StateMachine() {
	if (StateMachine::state!=bushcourtcontroller)
		delete StateMachine::state;		
	statemachine = NULL;
}

StateMachine* StateMachine::getInstance()
{	
	if (StateMachine::statemachine==NULL) {
		if (bushcourtcontroller==nullptr) {
			bushcourtcontroller = new GameState(new BushCourtController);
		}
		statemachine = new StateMachine(bushcourtcontroller); // BushCourtController));
        return statemachine;
    }
    else return statemachine;
}

void StateMachine::setController(GameState* gamestate) {	
	if (statemachine!=NULL)
		delete statemachine;	
	statemachine = new StateMachine(gamestate); 
}

void StateMachine::setController(IStateController* controller) {	
	setController(new GameState(controller));
}

void StateMachine::Init() {
	//for (int i = 0; i < StateMachine::state.size(); i++) 
		//if (StateMachine::state[i]->init) 
		StateMachine::state->controller->Init();
}

void StateMachine::Draw() {
	//for (int i = 0; i < StateMachine::state.size(); i++) 
		//if (StateMachine::state[i]->draw) {
			StateMachine::state->controller->Draw();
		//}
}

void StateMachine::Update(int w, int h) {
	StateMachine::state->controller->Update(w,h);
}

void StateMachine::SpecialKey(int key, int x, int y)
{
	//for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state->controller->SpecialKey(key,x,y);
}

void StateMachine::SpecialKeyUp(int key, int x, int y)
{
	//for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state->controller->SpecialKeyUp(key,x,y);
}

void StateMachine::KeyboardUp(unsigned char key, int x, int y)
{
	//for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state->controller->KeyboardUp(key,x,y);
}

void StateMachine::Keyboard(unsigned char key, int x, int y)
{
	//for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state->controller->Keyboard(key,x,y);
}

void StateMachine::Mouse(int button, int state, int x, int y)
{
	//for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state->controller->Mouse(button, state, x, y);
}

void StateMachine::PassiveMotion(int x, int y)
{
	//for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state->controller->PassiveMotion(x,y);
}

void StateMachine::Reshape(int w, int h)
{
	//for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state->controller->Reshape(w,h);
}