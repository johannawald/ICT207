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
#include "LevelOneController.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "ControlRoom.h"
#include "GameOverController.h"
#include "BushCourtController.h"

StateMachine* StateMachine::mStateMachine = nullptr;
IStateController* StateMachine::mBushcourtController = nullptr;
bool StateMachine::mInit = false;

StateMachine::StateMachine(IStateController* pController) {
	if (mBushcourtController==nullptr) 
	{
		mModelmanager = new ModelManager();
		mTexturemanager = new TextureManager();
		mAudiomanager = new AudioManager();
		mBushcourtController = new BushCourtController(mAudiomanager, mModelmanager, mTexturemanager);
	}
	if (pController==NULL)
		//state = mBushcourtController;
		//state = new ControlRoom(audiomanager, modelmanager, texturemanager);
		mState = new ControlRoom(mAudiomanager, mModelmanager, mTexturemanager);
		//state = new GameOverController(audiomanager, modelmanager, texturemanager);
	else
		mState = pController;
}

StateMachine::~StateMachine() {

}

StateMachine* StateMachine::getInstance()
{	
	if (StateMachine::mStateMachine==NULL)
		mStateMachine = new StateMachine(mBushcourtController);
    return mStateMachine;
}

void StateMachine::setBushCourtController() {	
	setController(mBushcourtController);
	mBushcourtController->Init();
	//sorry for that:
	dynamic_cast<BushCourtController*>(mBushcourtController)->SetCamPosition(-27000, 10450, 41400, 180);
}

void StateMachine::setController(IStateController* pController) {	
	if (mStateMachine!=NULL)
		delete mStateMachine;
	mStateMachine = new StateMachine(pController); 
}

void StateMachine::Init() {
	StateMachine::mState->Init();
}

void StateMachine::Draw() {
	StateMachine::mState->Draw();
}

void StateMachine::Update() {
	StateMachine::mState->Update();
}

void StateMachine::SpecialKey(int key, int x, int y)
{
	StateMachine::mState->SpecialKey(key,x,y);
}

void StateMachine::SpecialKeyUp(int key, int x, int y)
{
	StateMachine::mState->SpecialKeyUp(key,x,y);
}

void StateMachine::KeyboardUp(unsigned char key, int x, int y)
{
	StateMachine::mState->KeyboardUp(key,x,y);
}

void StateMachine::Keyboard(unsigned char key, int x, int y)
{
	StateMachine::mState->Keyboard(key,x,y);
}

void StateMachine::Mouse(int button, int state, int x, int y)
{
	StateMachine::mState->Mouse(button, state, x, y);
}

void StateMachine::PassiveMotion(int x, int y)
{
	StateMachine::mState->PassiveMotion(x,y);
}

void StateMachine::MouseMotion(int x, int y)
{
	StateMachine::mState->MouseMotion(x,y);
}

void StateMachine::Reshape(int w, int h)
{	
	StateMachine::mState->Reshape(w,h);
}