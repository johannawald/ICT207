/**
 * @class BasisGameController
 * @brief The BasisGAmeController provides all the basic functionality for a GameController
 *
 * @author Johanna Wald
 * @version 01
 * @date 25/10/2013 Johanna Wald - Basic Implementation
 */

#pragma once

#include "BasisController.h"
#include "MoveController.h"
#include "CollisionDetection.h"
#include "ModelManager.h"
#include "TextureManager.h"

class BoundingBox;
class GameObject;
class AudioManager;
class ModelManager;
class TextureManager;
class BasisGameController : public BasisController {
private:
	BoundingBox* mCameraBB;
	std::vector<GameObject*> mGameObject;
protected:
	MoveController mCamera;
	CollisionDetection mCollision;
	virtual void Draw();
	void addCollisionGameObject(const Vector3D& pPosition, const Vector3D& pSize, 
								const eModels pModel, const eTextures pTexture, int&  pCollisionIndex);
	virtual void MouseMotion(int x, int y);
	virtual void SpecialKey(int key, int x, int y);
	virtual void SpecialKeyUp(int key, int x, int y); 
	virtual void Keyboard(unsigned char key, int x, int y);
	virtual void KeyboardUp(unsigned char key, int x, int y);
	virtual void Mouse(int button, int state, int x, int y);
	virtual void DrawGameObjects();
	virtual void CollisionWithObject(GameObject* pGameObject) = 0;
	virtual int CheckCollision();
	virtual void WallCollision(int pIndex); //*JW
	virtual void BeforeCollision(int pIndex);

	void translateGameObjects(float x, float y, float z);
	void addGameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pScale, eModels pModelIndex, eTextures pTextureIndex, int pCollisionIndex);
public:	
	BasisGameController(AudioManager* pAudiomanager, ModelManager* pModelmanager, TextureManager* pTexturemanager);
};
