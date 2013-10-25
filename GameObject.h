/**
 * @GameObject
 *
 * @author Johanna Wald, GameObject, 12/10/2013
 * @version 1
 * @date 12/10/2013 Johanna Wald - Started
 */

#pragma once

//#include "ModelManager.h"

struct Position {
	double x;
	double y;
	double z;
};

class GameObject 
{
	private:
		Position position;
		int model;
		int CollisionIndex;
	public:
		GameObject();
};