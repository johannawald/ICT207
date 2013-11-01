/**
 * @class GameController
 * @brief The GameController should manage the Game itself
 *
 * The GameController should later manage the game itself with it levels 
 * and settings and stuff like that
 *
 * @author Johanna Wald
 * @version 01
 * @date 15/09/2013 Johanna Wald - set up class
 * @date 01/10/2013 Johanna Wald - added all the gamecontroller basic functions
 * @date 10/10/2013 Johanna Wald - changed base class to BasisGameController

 */

#pragma once

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <math.h>
#include <time.h>

#include "texturedPolygons.h"
#include "IStateController.h"
#include "BasisGameController.h"
#include "CollisionDetection.h"
#include "GameObject.h"
#include "MoveController.h"
#include "Explosion.h"

class GameController : public IStateController, public BasisGameController
{
private:
	Explosion mExplosion;
	bool mPush;
	bool mPull;
	const bool mSoundOn;

	bool mLostAnimation;
	bool mBombSoundPlaying; 
	bool mLost;

	bool ObjectIsBox(const int pIndex) const;
	void PullBox(int pIndex);
	void PushBox(int pIndex);

	void DrawTexttest();
	void SetGameObject();

	void DrawOuterWalls();
	void DrawArchitecture();
	void Draw3DModels();
	
	virtual void DrawObjects();
	virtual void InitGameObjects();

	void RenderBitmapString(float x, float y, float z, void *font, char *string);
	void RenderStrokeFontString(float x, float y, float z, void *font, char *string);
	void SetOrthographicProjection();
	void RestorePerspectiveProjection();
protected:
	const int mGround;
	int mCollisionIndex; //placeholder
	int* mBoxesCollisionIndex;
	void DrawTimer();
	void SetNewExplosion(const float x, const float y, const float z);
	
public:
	void WinGame() const;
	/**
        * @brief constructor creates a new GameController object.
    */
	GameController(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture);

	void CollisionWithObject(GameObject* pGameObject);
	int CheckCollision();
	void BeforeCollision(int pIndex, float pCollisionValue);
	
	void Init();
	void Draw();
	void Update();
	void Reshape(int w, int h);
	void SpecialKey(int key, int x, int y);
	void SpecialKeyUp(int key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void Keyboard(unsigned char key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void PassiveMotion(int x, int y);
	void MouseMotion(int x, int y);
};
