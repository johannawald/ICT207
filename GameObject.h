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

class GameObject 
{
	private:
		Vector3D mPosition;
		Vector3D mScale;
		Vector3D mMovement;
		int mModelIndex;
		int mTextureIndex;
		int mCollisionIndex;
	public:
		GameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pScale, int pModelIndex, int pTextureIndex, int pCollisionIndex);
		float GetXPosition();
		float GetYPosition();
		float GetZPosition();

		float GetXScale();
		float GetYScale();
		float GetZScale();

		int getModelIndex();
		int getTextureIndex();
};