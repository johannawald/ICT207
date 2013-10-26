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

class GameObject;
class AudioManager;
class ModelManager;
class TextureManager;
class BasisGameController : public BasisController {
private:	
	
protected:
	MoveController mCamera;
	CollisionDetection mCollision;
	virtual void Draw();

	virtual void MouseMotion(int x, int y);
	virtual void SpecialKey(int key, int x, int y);
	virtual void SpecialKeyUp(int key, int x, int y); 
	virtual void Keyboard(unsigned char key, int x, int y);
	virtual void KeyboardUp(unsigned char key, int x, int y);
	virtual void Mouse(int button, int state, int x, int y);

	virtual void CollisionWithObject(GameObject* pGameObject) = 0;
	virtual void CheckCollision();
public:	
	BasisGameController(AudioManager* pAudiomanager, ModelManager* pModelmanager, TextureManager* pTexturemanager);
};
