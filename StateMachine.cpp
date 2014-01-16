/**
 * @StateMachine.cpp
 *
 * @author Johanna Wald, StateMachine, 16/09/2013
 * @version 01
 * @date 16/09/2013 Johanna Wald
 * @date 19/11/2013 Johanna Wald added next state function
 */

#include "StateMachine.h"
#include "IStateController.h"
#include <vector>
#include "BushCourtController.h"
#include "GameController.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "ControlRoom.h"
#include "GameOverController.h"
#include "BushCourtController.h"
#include "GameControllerLevelOne.h"
#include "GameControllerLevelXML.h"

bool StateMachine::mSetBushCourt = false;
StateMachine* StateMachine::mStateMachine = nullptr;
BushCourtController* StateMachine::mBushcourtController = nullptr;
bool StateMachine::mInit = false;
IStateController* StateMachine::mState = nullptr;

StateMachine::StateMachine(IStateController* pController) {
	if (mBushcourtController==nullptr) 
	{
		mModelmanager = new ModelManager();
		mTexturemanager = new TextureManager();
		mAudiomanager = new AudioManager();
		mBushcourtController = new BushCourtController(mAudiomanager, mModelmanager, mTexturemanager, 1024, 1024);
	}
	if (pController==NULL)
		mState = mBushcourtController; //new GameControllerLevelXML(mAudiomanager, mModelmanager, mTexturemanager, 1024, 1024); //mBushcourtController;
	else
		mState = pController;
}

StateMachine::~StateMachine() {
	delete mState;
	delete mModelmanager;
	delete mTexturemanager;
	delete mAudiomanager;
	delete mBushcourtController;
}

StateMachine* StateMachine::getInstance()
{	
	if (StateMachine::mStateMachine==NULL)
		mStateMachine = new StateMachine(mBushcourtController);
    return mStateMachine;
}

void StateMachine::setBushCourtController() {	
	setController(mBushcourtController);
	mBushcourtController->SetCamPosition(-27000, 10450, 41400, 180);
	mBushcourtController->Restart();
}

void StateMachine::setController(IStateController* pController) {	
	//if (mStateMachine!=NULL)
	//delete mStateMachine;
	std::cout << mState << std::endl;
	if (mState!=mBushcourtController)
		delete mState;
	std::cout << " delete after" << std::endl;
	mState = pController; 
	pController->Init();
	std::cout << " end setController" << std::endl;
}

void StateMachine::Init() {
	StateMachine::mState->Init();
}

void StateMachine::Draw() {
	StateMachine::mState->Draw();
}

void StateMachine::Update() {
	StateMachine::mState->Update();
	if (StateMachine::mState->mNextState!=nullptr)
	{
		setController(StateMachine::mState->mNextState);
		mBushcourtController->mNextState = nullptr;
		//StateMachine::mState->mNextState = nullptr;
	}
	else if (mSetBushCourt)
	{
		setBushCourtController();
		mSetBushCourt = false;
	}
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