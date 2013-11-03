/**
 * @GameObject
 *
 * @author Johanna Wald, GameObject, 12/10/2013
 * @version 1
 * @date 12/10/2013 Johanna Wald - Started
 * @date 20/10/2013 Johanna Wald - Added more member variables for the texture-coordinates
 * @date 03/11/2013 Johanna Wald - Added doygen comments
 */

#pragma once

#include <GL\freeglut.h>
#include "Vector3D.h"
#include "ModelManager.h"
#include "DrawManager.h"

class GameObject 
{
private:
	Vector3D mPositionOriginal; /**< original position of the game object*/
	Vector3D mPosition;  /**< position of the game object*/
	Vector3D mScale; /**< scale of the model of the game object*/
	Vector3D mSize;  /**< size of the collision box of the game object*/
	Vector3D mMovement;  /**< movement of the game object*/
	Vector3D mRotation;  /**< roation of the model of the game object*/
	eModels mModelIndex;  /**< index of the model of the game object, -1 if it doesn't have a model */
	GLuint mTextureIndex;  /**< textureid of the game object*/
	int mTexCoordX;  /**< texture x-coordinate of the texture of the game object*/
	int mTexCoordY; /**< texture y-coordinate of the texture of the game object*/
	int mCollisionIndex; /**< collision index of the game object in the collision array*/
public:
		/**
		* @brief constructor of the gameobject to set the membervariables
		* @param Vector3D& pPosition - position of the game object
		* @param Vector3D& pMovement - movement of the game object
		* @param Vector3D& pSize - size of the game object (collision box)
		* @param Vector3D& pScale - scale of the game object (will be used for scaling the model)
		* @param Vector3D& pRotation - rotation of the game object (will be used for rotating the model)
		* @param int pModelIndex - model-index of the game object, should be set to -1 if it is no model
		* @param GLuint pTextureIndex - texture code that should be used to draw the game object
		* @param int pTexCoordX - texture x-coordinate for drawing the texture of the game object
		* @param int pTexCoordY - texture y-coordinate for drawing the texture of the game object
		* @param int pCollisionIndex - index of the collision box of game object in the array the collision detection clas
		*/
	GameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pSize, Vector3D& pScale, Vector3D& pRotation, 
				   int pModelIndex, GLuint pTextureIndex, int pTexCoordX, int pTexCoordY, int pCollisionIndex);
		/**
		* @brief draws the game object with it's set parameters
		* @param ModelManager& pModelManager - a reference of the model manager as a help variable to draw the gameobject if it's a model
		* @param ModelManager& pModelManager - a reference of the draw manager as a help variable to draw rects (if the game object is not a model)
		* @return void
		*/
	void Draw(ModelManager& pModelManager, DrawManager& pDrawManger);
		/**
		* @brief translates the game object with the vector pTranslate 
		* @param const Vector3D& pTranslate - the vector the gameobject has to be translated with
		* @return void
		*/
	void Translate(const Vector3D& pTranslate);
		/**
		* @brief moves the game object with the vector pTranslate 
		* @param const Vector3D& pTranslate - the vector the gameobject has to be moved with
		* @return void
		*/
	void Move(const Vector3D& pTransform);
};