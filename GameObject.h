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
		Vector3D mMovement;

		eModels mModelIndex;
		eTextures mTextureIndex;
		int mCollisionIndex;

		//void (Class::*collisionMethod)(void);
	public:
		//void (GameController::*c
		GameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pScale, eModels pModelIndex, eTextures pTextureIndex, int pCollisionIndex);

		float GetXPosition();
		float GetYPosition();
		float GetZPosition();

		float GetXScale();
		float GetYScale();
		float GetZScale();

		void Transform(Vector3D pTransform);

		eModels getModelIndex();
		eTextures getTextureIndex();
};