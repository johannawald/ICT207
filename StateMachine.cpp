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

StateMachine* StateMachine::statemachine = nullptr;
std::vector<GameState*> StateMachine::state = std::vector<GameState*>();
bool StateMachine::init = false;

StateMachine::StateMachine(GameState* gamestate) {
	StateMachine::state.push_back(gamestate);
	//StateMachine::state[StateMachine::state.size()-1]->controller->Init();
}

StateMachine::~StateMachine() {				
	for (int i = 0; i < StateMachine::state.size(); i++) {
		delete StateMachine::state[i];			
	}
	StateMachine::state.clear();	
	statemachine = NULL;
}

StateMachine* StateMachine::getInstance()
{	
	if (StateMachine::statemachine==NULL) {
		statemachine = new StateMachine(new GameState(new BushCourtController));
        return statemachine;
    }
    else return statemachine;
}

void StateMachine::setController(GameState* gamestate) {	
	if (StateMachine::statemachine!=NULL) 
		delete statemachine;		
	
	statemachine = new StateMachine(gamestate); 			
}

void StateMachine::setController(IStateController* controller) {	
	setController(new GameState(controller));
}

/*void StateMachine::setPauseController() {
	if (!StateMachine::state.empty()) {
		StateMachine::state[0]->keydown=false;
		StateMachine::state[0]->update=false;
	}	
	//addController(new PauseMenueController);
}

void StateMachine::setContinueController() {	
	if (!StateMachine::state.empty()) {		
		if (StateMachine::state.size()>1) {
			int size = StateMachine::state.size();
			delete StateMachine::state.back();
			StateMachine::state.pop_back();	
		}
		StateMachine::state[0]->keydown=true;
		StateMachine::state[0]->update=true;
	}
}

void StateMachine::setMultiPlayerController() {
	//GameControllerClientManager* gm = new GameControllerClientManager;	
	//setController(gm);
	if (!StateMachine::state.empty()) {
		StateMachine::state[0]->keydown=false;
		StateMachine::state[0]->update=false;
	}	
	//addController(new MultiPlayerController(gm));
}

void StateMachine::addController(GameState* gamestate) {	
	StateMachine::state.push_back(gamestate);	
	StateMachine::state[StateMachine::state.size()-1]->controller->init();
	statemachine = getInstance();	
}

void StateMachine::addController(IStateController* controller) {
	addController(new GameState(controller));
}
*/
void StateMachine::Init() {
	for (int i = 0; i < StateMachine::state.size(); i++) 
		//if (StateMachine::state[i]->init) 
		StateMachine::state[i]->controller->Init();
}

void StateMachine::Draw() {
	for (int i = 0; i < StateMachine::state.size(); i++) 
		//if (StateMachine::state[i]->draw) {
			StateMachine::state[i]->controller->Draw();
		//}
}

void StateMachine::Update(int w, int h) {
	for (int i = 0; i < StateMachine::state.size(); i++) 
		//if (StateMachine::state[i]->update) 
			StateMachine::state[i]->controller->Update(w,h);
}

void StateMachine::SpecialKey(int key, int x, int y)
{
	for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state[i]->controller->SpecialKey(key,x,y);
}

void StateMachine::SpecialKeyUp(int key, int x, int y)
{
	for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state[i]->controller->SpecialKeyUp(key,x,y);
}

void StateMachine::KeyboardUp(unsigned char key, int x, int y)
{
	for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state[i]->controller->KeyboardUp(key,x,y);
}

void StateMachine::Keyboard(unsigned char key, int x, int y)
{
	for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state[i]->controller->Keyboard(key,x,y);
}

void StateMachine::Mouse(int button, int state, int x, int y)
{
	for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state[i]->controller->Mouse(button, state, x, y);
}

void StateMachine::PassiveMotion(int x, int y)
{
	for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state[i]->controller->PassiveMotion(x,y);
}

void StateMachine::Reshape(int w, int h)
{
	for (int i = 0; i < StateMachine::state.size(); i++) 
		StateMachine::state[i]->controller->Reshape(w,h);
}
