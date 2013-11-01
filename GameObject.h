/**
 * @GameObject
 *
 * @author Johanna Wald, GameObject, 12/10/2013
 * @version 1
 * @date 12/10/2013 Johanna Wald - Started
 * @date 20/10/2013 Johanna Wald - Added more member variables for the texture-coordinates

 */

#pragma once

#include <GL\freeglut.h>
#include "Vector3D.h"
#include "BoundingBox.h"
#include "ModelManager.h"
#include "DrawManager.h"
#include "GameController.h"

class GameObject 
{
	private:
		Vector3D mPositionOriginal;
		Vector3D mPosition;
		Vector3D mScale;
		Vector3D mSize;
		Vector3D mMovement;
		Vector3D mRotation;

		eModels mModelIndex;
		GLuint mTextureIndex;
		int mTexCoordX;
		int mTexCoordY;
		int mCollisionIndex;
		
		//void (GameController::*mCollisionMethod)(void) ; //*JW
	public:
		GameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pSize, Vector3D& pScale, Vector3D& pRotation, 
				   int pModelIndex, GLuint pTextureIndex, int pTexCoordX, int pTexCoordY, int pCollisionIndex);
				  // , void (GameController::*pCollisionMethod)(void) = nullptr);

		void Draw(ModelManager& pModelManager, DrawManager& pDrawManger, CollisionDetection& pCollision);
		void Transform(const Vector3D& pTransform);
		void Move(const Vector3D& pTransform);
};