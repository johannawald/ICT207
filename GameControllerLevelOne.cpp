#include "GameControllerLevelOne.h"
#include "StateMachine.h"
#include "DrawManager.h"
#include <sstream>
#include <iostream>
#include "GameWinController.h"
#include "GameControllerLevelXML.h"


GameControllerLevelOne::GameControllerLevelOne(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture, float pHeight, float pWidth): 
	GameController(pAudio, pModel, pTexture, pHeight, pWidth)
{
	mLevelNr=0;
}

void GameControllerLevelOne::DrawObjects() 
{
	glPushMatrix();	
		DrawTimer();
	glPopMatrix();
}

void GameControllerLevelOne::OnBeforeWin()
{	
	mNextState = new GameControllerLevelXML(GetAudio(), GetModel(), GetTexture(), GetWindowHeight(), GetWindowWidth());
}

void GameControllerLevelOne::InitGameObjects()
{
	int test = 0;
	addCollisionGameObject(Vector3D(10, GetGroundLevel()+10, -650), Vector3D(), Vector3D(100, 100, 100), Vector3D(0.5f, 0.5f, 0.5f), Vector3D(0, 0, 0), mBomb, GetTexture()->getTextureID(taBomb), 1, 1, mBombIndex);
	
	addCollisionGameObject(Vector3D(-120, GetGroundLevel()+10, -250), Vector3D(), Vector3D(90, 90, 90), Vector3D(0.2f, 0.2f, 0.2f), Vector3D(), mBox, GetTexture()->getTextureID(taBox), 1, 1, mBoxesCollisionIndex1);
	addCollisionGameObject(Vector3D(0, GetGroundLevel()+10, -250), Vector3D(), Vector3D(90, 90, 90), Vector3D(0.2f, 0.2f, 0.2f), Vector3D(), mBox, GetTexture()->getTextureID(taBox), 1, 1, mBoxesCollisionIndex2);
	addCollisionGameObject(Vector3D(120, GetGroundLevel()+10, -250), Vector3D(), Vector3D(90, 90, 90), Vector3D(0.2f, 0.2f, 0.2f), Vector3D(), mBox, GetTexture()->getTextureID(taBox), 1, 1, mBoxesCollisionIndex3);
	
	//floor
	addCollisionGameObject(Vector3D(-150, GetGroundLevel(), -450), Vector3D(), Vector3D(400, 0, 700), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilefloor), 1, 1, test);
	addCollisionGameObject(Vector3D(-20, GetGroundLevel(), -800), Vector3D(), Vector3D(140, 0, 350), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilefloor), 1, 1, test);

	addCollisionGameObject(Vector3D(-20, GetGroundLevel(), -800), Vector3D(), Vector3D(150, 500, 0), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, test);
	addCollisionGameObject(Vector3D(250, GetGroundLevel(), 250), Vector3D(), Vector3D(-400, 500, 0), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, test);

	addCollisionGameObject(Vector3D(250, GetGroundLevel(), -450), Vector3D(), Vector3D(0, 500, 700), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 2, 1, test);
	addCollisionGameObject(Vector3D(-150, GetGroundLevel(), 250), Vector3D(), Vector3D(0, 500, -700), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 2, 1, test);

	addCollisionGameObject(Vector3D(-150, GetGroundLevel(), -450), Vector3D(), Vector3D(130, 500, 0), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, test);
	addCollisionGameObject(Vector3D(120, GetGroundLevel(), -450), Vector3D(), Vector3D(130, 500, 0), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, test);
	//passage
	addCollisionGameObject(Vector3D(120, GetGroundLevel(), -800), Vector3D(), Vector3D(0, 500, 350), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 2, 1, test);
	addCollisionGameObject(Vector3D(-20, GetGroundLevel(), -450), Vector3D(), Vector3D(0, 500, -350), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 2, 1, test);

}

