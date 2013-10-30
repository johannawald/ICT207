/**
 * @GameObject
 *
 * @author Johanna Wald, GameObject, 12/10/2013
 * @version 1
 * @date 12/10/2013 Johanna Wald - Started
 */

#pragma once

#include <GL\freeglut.h>
#include "Vector3D.h"
#include "BoundingBox.h"
#include "ModelManager.h"
#include "TextureManager.h"

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
		eTextures mTextureIndex;
		int mCollisionIndex;

		//void (Class::*collisionMethod)(void);
	public:
		//void (GameController::*c
		GameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pSize, Vector3D& pScale, Vector3D& pRotation, 
				   eModels pModelIndex, eTextures pTextureIndex, int pCollisionIndex);
		
		void Draw(ModelManager* pModelManager);

		float GetXPosition();
		float GetYPosition();
		float GetZPosition();

		/*float GetXScale();
		float GetYScale();
		float GetZScale();*/

		Vector3D& GetSize();

		void Transform(Vector3D pTransform);
		void Move(Vector3D pTransform); //call the transformoriginal in collisionbox also move

		eModels getModelIndex();
		eTextures getTextureIndex();
};