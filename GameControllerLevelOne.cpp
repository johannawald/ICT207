#include "GameControllerLevelOne.h"
#include "StateMachine.h"
#include "DrawManager.h"
#include <sstream>
#include <iostream>


GameControllerLevelOne::GameControllerLevelOne(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture): GameController(pAudio, pModel, pTexture)
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
	//addBomb();
	addCollisionGameObject(Vector3D(0, GetGroundLevel()+10, 750), Vector3D(), Vector3D(50, 50, 50), Vector3D(0.2f, 0.2f, 0.2f), Vector3D(), mBox, taBomb, 1, 1, mBombIndex);
	
	
	addCollisionGameObject(Vector3D(-115, GetGroundLevel()+10, 250), Vector3D(), Vector3D(90, 90, 90), Vector3D(0.2f, 0.2f, 0.2f), Vector3D(), mBox, taBox, 1, 1, mBoxesCollisionIndex[0]);
	addCollisionGameObject(Vector3D(0, GetGroundLevel()+10, 250), Vector3D(), Vector3D(90, 90, 90), Vector3D(0.2f, 0.2f, 0.2f), Vector3D(), mBox, taBox, 1, 1, mBoxesCollisionIndex[1]);
	addCollisionGameObject(Vector3D(115, GetGroundLevel()+10, 250), Vector3D(), Vector3D(90, 90, 90), Vector3D(0.2f, 0.2f, 0.2f), Vector3D(), mBox, taBox, 1, 1, mBoxesCollisionIndex[2]);	
	//floor
	//addCollisionGameObject(Vector3D(-200, GetGroundLevel(), -200), Vector3D(), Vector3D(400, 1200, 0), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 3, 1, mCollisionIndex);
	//roof
	//addCollisionGameObject(Vector3D(-200, 400+GetGroundLevel(), -200), Vector3D(), Vector3D(400, 120, 0), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 3, 1, mCollisionIndex);
	//walls
	//something's wrong here:
	//addCollisionGameObject(Vector3D(-100, GetGroundLevel(), -100), Vector3D(), Vector3D(100, 0, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, mCollisionIndex);
	//addCollisionGameObject(Vector3D(-100, mGround, 100), Vector3D(), Vector3D(200, 0, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, mCollisionIndex);
	addCollisionGameObject(Vector3D(-200, GetGroundLevel(), 100), Vector3D(), Vector3D(100, 0, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, mCollisionIndex);
	
	addCollisionGameObject(Vector3D(100, GetGroundLevel(), 100), Vector3D(), Vector3D(100, 0, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, mCollisionIndex);
	addCollisionGameObject(Vector3D(-200, GetGroundLevel(), 100), Vector3D(), Vector3D(0, 400, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, mCollisionIndex);
	addCollisionGameObject(Vector3D(200, GetGroundLevel(), 100), Vector3D(), Vector3D(0, 400, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, mCollisionIndex);
	addCollisionGameObject(Vector3D(-100, GetGroundLevel(), 700), Vector3D(), Vector3D(200, 0, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, mCollisionIndex);
	addCollisionGameObject(Vector3D(-100, GetGroundLevel(), 500), Vector3D(), Vector3D(0, 200, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, mCollisionIndex);
	addCollisionGameObject(Vector3D(100, GetGroundLevel(), 500), Vector3D(), Vector3D(0, 200, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, mCollisionIndex);
	addCollisionGameObject(Vector3D(-200, GetGroundLevel(), 500), Vector3D(), Vector3D(100, 0, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, mCollisionIndex);
	addCollisionGameObject(Vector3D(100, GetGroundLevel(), 500), Vector3D(), Vector3D(100, 0, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, mCollisionIndex);
}

