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
	//GameController::DrawObjects();
	glPushMatrix();
		
		//floor
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilefloor), 3, 1, -2000, 0, -2000, 4000, 12000, 0);
		//roof
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilefloor), 3, 1, -2000, 4000, -2000, 4000, 12000, 0);

		//walls
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -1000, 0, -1000, 2000, 0, 4000);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -1000, 0, -1000, 0, 2000, 4000);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, 1000, 0, -1000, 0, 2000, 4000);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -2000, 0, 1000, 1000, 0, 4000);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, 1000, 0, 1000, 1000, 0, 4000);

		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -2000, 0, 1000, 0, 4000, 4000);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, 2000, 0, 1000, 0, 4000, 4000);

		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -1000, 0, 7000, 2000, 0, 4000);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -1000, 0, 5000, 0, 2000, 4000);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, 1000, 0, 5000, 0, 2000, 4000);

		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -2000, 0, 5000, 1000, 0, 4000);
		GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, 1000, 0, 5000, 1000, 0, 4000);

	glPopMatrix();
}

void GameControllerLevelOne::InitGameObjects()
{
	//3 boxes, along ~z=3000
}
