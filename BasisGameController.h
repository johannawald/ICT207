/**
 * @class BasisGameController
 * @brief The BasisGAmeController provides all the basic functionality for a GameController
 *
 * @author Johanna Wald
 * @version 01
 * @date 25/10/2013 Johanna Wald - Basic Implementation
 * @date 25/10/2013 Johanna Wald - Added various methods and member variables (mCameraBB, mGameObjects...) for the game mechanics
 * @date 26/10/2013 Johanna Wald - Added doxygon comments
 
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
		/**
		* @brief MovementController handels the movement in the world / level
		*/
	MoveController mCamera;
		/**
		* @brief saves and checks the collision
		*/
	CollisionDetection mCollision;

	
	void addGameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pSize, Vector3D& pScale, Vector3D& pRotation, 
					   int pModelIndex, GLuint pTextureIndex, int pTexCoordX, int pTexCoordY, int pCollisionIndex, void (*pCollisionMethod)(void) = nullptr);

	void addCollisionGameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pSize, Vector3D& pScale, Vector3D& pRotation,
								int pModel, GLuint pTexture, int pTexCoordX, int pTexCoordY, int& pCollisionIndex, void (*pCollisionMethod)(void) = nullptr);
	

	void MoveGameObject(const int pIndex, const Vector3D& pTranslate);
	GameObject* GetGameObject(const int pIndex) const;
	void TranslateGameObjects(const Vector3D& pTranslation);
	

	virtual void Draw();

		/**
		* @brief Draw function for the gameobject-array. Runs through all gameobjects and calls it's draw()-function
		* @param none
		* @return void
		*/
	virtual void DrawGameObjects();
		/**
         * @brief Calls the MouseMotion() function of the camera / MovementController class
		 *
		 * @param int x - the x position of the mouse 
		 * @param int y - the y position of the mouse
         */
	virtual void MouseMotion(int x, int y);
		/**
         * @brief Calls the SpecialKey() function of the camera / MovementController class
		 *
		 * @param int key - the key pressed
		 * @param int x - the x position of the mouse
		 * @param int y - the y poition of the mouse
         */
	virtual void SpecialKey(int key, int x, int y);
		/**
         * @brief Calls the SpecialKeyUp() function of the camera / MovementController class
		 *
		 * @param int key - the key pressed
		 * @param int x - the x position of the mouse
		 * @param int y - the y poition of the mouse
         */
	virtual void SpecialKeyUp(int key, int x, int y); 
		/**
         * @brief Calls the Keyboard() function of the camaer / MovementController class
		 *
		 * @param int button - the mouse button pressed
		 * @param int state - the state of the mouse button pressed (eg. state == GLUT_DOWN)
		 * @param int x - the x position of the mouse
		 * @param int y - the y position of the mouse
         */
	virtual void Keyboard(unsigned char key, int x, int y);
		/**
         * @brief Calls the KeyboardUp() function of the camera / MovementController class
		 *
		 * @param int button - the mouse button pressed
		 * @param int state - the state of the mouse button pressed (eg. state == GLUT_DOWN)
		 * @param int x - the x position of the mouse
		 * @param int y - the y position of the mouse
         */
	virtual void KeyboardUp(unsigned char key, int x, int y);
		/**
         * @brief Calls the Mouse() function of the camera / MovementController class
		 *
		 * @param int button - the mouse button pressed
		 * @param int state - the state of the mouse button pressed (eg. state == GLUT_DOWN)
		 * @param int x - the x position of the mouse
		 * @param int y - the y position of the mouse
         */
	virtual void Mouse(int button, int state, int x, int y);
	
	virtual int CheckCollision();
	virtual void CollisionWithObject(GameObject* pGameObject) = 0;
	virtual void WallCollision(int pIndex, float pCollisionValue); 
	virtual void PhysicCollision(int pIndex, float pCollisionValue);
	virtual void BeforeCollision(int pIndex, float pCollisionValue);
public:	
	BasisGameController(AudioManager* pAudiomanager, ModelManager* pModelmanager, TextureManager* pTexturemanager);
};
