/**
 * @StateMachine.cpp
 *
 * @author Johanna Wald, StateMachine, 16/09/2013
 * @version 01
 * @date 16/09/2013 Johanna Wald
 */

#include "StateMachine.h"
#include "IStateController.h"
#include <vector>
#include "BushCourtController.h"
#include "GameController.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "AudioManager.h"

StateMachine* StateMachine::statemachine = nullptr;
IStateController* StateMachine::bushcourtcontroller = nullptr;
bool StateMachine::init = false;

StateMachine::StateMachine(IStateController* controller) {
	if (bushcourtcontroller==nullptr) {
		modelmanager = new ModelManager();
		texturemanager = new TextureManager();
		audiomanager = new AudioManager();
		//bushcourtcontroller = new BushCourtController(audiomanager, modelmanager, texturemanager);
	}
	if (controller==NULL)
		state = new GameController(audiomanager, modelmanager, texturemanager);
	else
		state = controller;
}

StateMachine::~StateMachine() {

}

StateMachine* StateMachine::getInstance()
{	
	if (StateMachine::statemachine==NULL)
		statemachine = new StateMachine(bushcourtcontroller);
    return statemachine;
}

void StateMachine::setBushCourtController() {	
	setController(bushcourtcontroller);
	bushcourtcontroller->Init();
	//sorry for that:
	dynamic_cast<BushCourtController*>(bushcourtcontroller)->SetCamPosition(-27000, 10450, 41400, 180);
}

void StateMachine::setController(IStateController* controller) {	
	if (statemachine!=NULL)
		delete statemachine;
	statemachine = new StateMachine(controller); 
}

void StateMachine::Init() {
	StateMachine::state->Init();
}

void StateMachine::Draw() {
	StateMachine::state->Draw();
}

void StateMachine::Update() {
	StateMachine::state->Update();
}

void StateMachine::SpecialKey(int key, int x, int y)
{
	StateMachine::state->SpecialKey(key,x,y);
}

void StateMachine::SpecialKeyUp(int key, int x, int y)
{
	StateMachine::state->SpecialKeyUp(key,x,y);
}

void StateMachine::KeyboardUp(unsigned char key, int x, int y)
{
	StateMachine::state->KeyboardUp(key,x,y);
}

void StateMachine::Keyboard(unsigned char key, int x, int y)
{
	StateMachine::state->Keyboard(key,x,y);
}

void StateMachine::Mouse(int button, int state, int x, int y)
{
	StateMachine::state->Mouse(button, state, x, y);
}

void StateMachine::PassiveMotion(int x, int y)
{
	StateMachine::state->PassiveMotion(x,y);
}

void StateMachine::MouseMotion(int x, int y)
{
	StateMachine::state->MouseMotion(x,y);
}

void StateMachine::Reshape(int w, int h)
{	
	StateMachine::state->Reshape(w,h);
}