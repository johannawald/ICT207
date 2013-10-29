/**
 * @class GameController
 * @brief The GameController should manage the Game itself
 *
 * The GameController should later manage the game itself with it levels 
 * and settings and stuff like that
 *
 * @author Johanna Wald
 * @version 01
 * @date 15/09/2013
 */

#pragma once

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <math.h>
#include <time.h>

//#include "camera.h"
#include "texturedPolygons.h"
#include "IStateController.h"
#include "BasisGameController.h"
#include "CollisionDetection.h"
#include "GameObject.h"
#include "MoveController.h"

class GameController : public IStateController, public BasisGameController
{
private:
	bool mPush;
	bool mPull;
	
	int* mBoxesCollisionIndex;

	void PullBox(int pIndex);
	void PushBox(int pIndex);

	void DrawTexttest();
	void SetGameObject();

	void DrawOuterWalls();
	void DrawArchitecture();
	void Draw3DModels();
	
	virtual void DrawObjects();
	virtual void InitGameObjects();

	void DrawTimer();
	void RenderBitmapString(float x, float y, float z, void *font, char *string);
	void RenderStrokeFontString(float x, float y, float z, void *font, char *string);
	void SetOrthographicProjection();
	void RestorePerspectiveProjection();

public:
	/**
        * @brief constructor creates a new GameController object.
    */
	GameController(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture);
	void CollisionWithObject(GameObject* pGameObject);
	int CheckCollision();
	void BeforeCollision(int pIndex);
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
