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

class BoundingBox;
class GameObject;
class AudioManager;
class ModelManager;
class TextureManager;
class BasisGameController : public BasisController {
private:
	const int mGroundLevel;
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
		/**
		* @brief adds a new game object to the list "mGameObjects"
		* @param Vector3D& pPosition - position of the game object
		* @param Vector3D& pMovement - movement of the game object
		* @param Vector3D& pSize - size of the game object (collision box)
		* @param Vector3D& pScale - scale of the game object (will be used for scaling the model)
		* @param Vector3D& pRotation - rotation of the game object (will be used for rotating the model)
		* @param int pModelIndex - model-index of the game object, should be set to -1 if it is no model
		* @param GLuint pTextureIndex - texture code that should be used to draw the game object
		* @param float pTexCoordX - texture x-coordinate for drawing the texture of the game object
		* @param float pTexCoordY - texture y-coordinate for drawing the texture of the game object
		* @param int pCollisionIndex - index of the collision box of game object in the array the collision detection clas
		* @param void (*pCollisionMethod)(void) - collision function that should be called if this game object collides with the camera
		* @return void
		*/	
	void addGameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pSize, Vector3D& pScale, Vector3D& pRotation, 
					   int pModelIndex, GLuint pTextureIndex, float pTexCoordX, float pTexCoordY, int pCollisionIndex, void (*pCollisionMethod)(void) = nullptr);

		/**
		* @brief adds a new game object to the list "mGameObjects" with calling addGameObject and creates a collision box for it
		* @param Vector3D& pPosition - position of the game object
		* @param Vector3D& pMovement - movement of the game object
		* @param Vector3D& pSize - size of the game object (collision box)
		* @param Vector3D& pScale - scale of the game object (will be used for scaling the model)
		* @param Vector3D& pRotation - rotation of the game object (will be used for rotating the model)
		* @param int pModelIndex - model-index of the game object, should be set to -1 if it is no model
		* @param GLuint pTextureIndex - texture code that should be used to draw the game object
		* @param float pTexCoordX - texture x-coordinate for drawing the texture of the game object
		* @param float pTexCoordY - texture y-coordinate for drawing the texture of the game object
		* @param int pCollisionIndex - index of the collision box of game object in the array the collision detection clas
		* @param void (*pCollisionMethod)(void) - collision function that should be called if this game object collides with the camera
		* @return void
		*/	
	void addCollisionGameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pSize, Vector3D& pScale, Vector3D& pRotation,
								int pModel, GLuint pTexture, float pTexCoordX, float pTexCoordY, int& pCollisionIndex, void (*pCollisionMethod)(void) = nullptr);
		/**
		* @brief moves all the game object with index pIndex using the vector "pTranslation"
		* @param const Vector3D& pTranslation - the vector that is used to translate all the game objects
		* @param const int pIndex - the index of the game object in the array
		* @return void
		*/
	void MoveGameObject(const int pIndex, const Vector3D& pTranslate);
	GameObject* GetGameObject(const int pIndex) const;
		/**
		* @brief translates all the game objects with the vector "pTranslation"
		* @param const Vector3D& pTranslation - the vector that is used to translate all the game objects
		* @return void
		*/
	void TranslateGameObjects(const Vector3D& pTranslation);
		/**
		* @brief get function for the ground value variable
		* @param none
		* @return const int ground level (member variable)
		*/
	const int GetGroundLevel() const;
		/**
		* @brief Draw function that overrides the one in the base class
		* does all the stuff that is necessary to provide a "clean" draw-state (pushMatrix(), popMatrix())
		* calls functions such as DrawGameObjects(), CheckCollision() and DrawObjects.
		*/
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
		/**
		* @brief Checks if there is a collision / collision handeling in general
		* @param none
		* @return int index of the last object that collides
		*/
	virtual int CheckCollision();
		/**
		* @brief collision handeling for wall avoidance
		* @param const int pIndex wall avoidance for the bounding box at index pIndex of the array in "mCollision"
		* @param const float pCollisionValue level of collision as a float
		* @return void
		*/
	virtual void WallCollision(int pIndex, float pCollisionValue);
		/**
		* @brief virtual fucntion to handle collisions in derived classes
		* (this function is called if a collision is detected)
		* @param const int pIndex of the object of the array in "mCollision" that collided and caused that function-call
		* @param const float pCollisionValue level of collision as a float
		* @return void
		*/
	virtual void BeforeCollision(int pIndex, float pCollisionValue);
public:	
	float COLLISIONVALUE; //*JW just for debug reasons
	float NEW_COLLISIONVALUE; //*JW just for debug reasons
	/**
        * @brief constructor creates a new BasisGameController object and sets the manager-variables
		* @param AudioManager* pAudiomanager - the audio manager of the state machine
		* @param ModelManager* pModelmanager - the model manager of the state machine
		* @param TextureManager* pTextureManager - the texture manager of the state machine
    */
	BasisGameController(AudioManager* pAudiomanager, ModelManager* pModelmanager, TextureManager* pTexturemanager);
};
