#include "GameControllerLevelOne.h"
#include "StateMachine.h"
#include "DrawManager.h"
#include <sstream>
#include <iostream>


GameControllerLevelOne::GameControllerLevelOne(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture, float pHeight, float pWidth): 
	GameController(pAudio, pModel, pTexture, pHeight, pWidth)
{
	
}

void GameControllerLevelOne::DrawObjects() 
{
	glPushMatrix();
		DrawTimer();
	glPopMatrix();

}

void WinGame()
{
}

void GameControllerLevelOne::InitGameObjects()
{
	int test = 0;
	addCollisionGameObject(Vector3D(100, GetGroundLevel()+10, -650), Vector3D(), Vector3D(50, 50, 50), Vector3D(0.8f, 0.8f, 0.8f), Vector3D(0, 90, 0), mBomb, GetTexture()->getTextureID(taBomb), 1, 1, mBombIndex);
	
	addCollisionGameObject(Vector3D(-120, GetGroundLevel()+10, -250), Vector3D(), Vector3D(90, 90, 90), Vector3D(0.2f, 0.2f, 0.2f), Vector3D(), mBox, GetTexture()->getTextureID(taBox), 1, 1, mBoxesCollisionIndex[0]);
	addCollisionGameObject(Vector3D(0, GetGroundLevel()+10, -250), Vector3D(), Vector3D(90, 90, 90), Vector3D(0.2f, 0.2f, 0.2f), Vector3D(), mBox, GetTexture()->getTextureID(taBox), 1, 1, mBoxesCollisionIndex[1]);
	addCollisionGameObject(Vector3D(120, GetGroundLevel()+10, -250), Vector3D(), Vector3D(90, 90, 90), Vector3D(0.2f, 0.2f, 0.2f), Vector3D(), mBox, GetTexture()->getTextureID(taBox), 1, 1, mBoxesCollisionIndex[2]);
	
	
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

