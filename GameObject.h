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
		Vector3D mMovement;
		BoundingBox* mBoundingBox;
		int model;
		int CollisionIndex;
	public:

		GameObject();
};