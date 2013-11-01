#include "GameControllerLevelOne.h"
#include "StateMachine.h"
#include "DrawManager.h"
#include <sstream>
#include <iostream>


GameControllerLevelOne::GameControllerLevelOne(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture): GameController(pAudio, pModel, pTexture)
{
}


//--------------------------------------------------------------------------------------
//  Draw the Objects
//--------------------------------------------------------------------------------------
void GameControllerLevelOne::DrawObjects() 
{
	glPushMatrix();
		DrawTimer();
		//floor
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilefloor), 3, 1, -200, 0, -200, 400, 1200, 0);
		//roof
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilefloor), 3, 1, -200, 400, -200, 400, 120, 0);
		//walls
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -100, 0, -100, 200, 0, 400);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -100, 0, -100, 0, 200, 400);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, 100, 0, -100, 0, 200, 400);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -200, 0, 100, 100, 0, 400);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, 100, 0, 100, 100, 0, 400);

		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -200, 0, 100, 0, 400, 400);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, 200, 0, 100, 0, 400, 400);

		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -100, 0, 700, 200, 0, 400);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -100, 0, 500, 0, 200, 400);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, 100, 0, 500, 0, 200, 400);

		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -200, 0, 500, 100, 0, 400);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, 100, 0, 500, 100, 0, 400);

	glPopMatrix();
}

void GameControllerLevelOne::InitGameObjects()
{
	//3 boxes, along ~z=3000
	int a, b;
	addCollisionGameObject(Vector3D(-60,20,100), Vector3D(), Vector3D(100, 100, 100), Vector3D(0.2f, 0.2f, 0.2f), Vector3D(), mBox, taBox, a);
	addCollisionGameObject(Vector3D(-60,-20,300), Vector3D(), Vector3D(100, 100, 100), Vector3D(0.2f, 0.2f, 0.2f), Vector3D(), mBox, taBox, b);	

}
