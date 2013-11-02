/**
 * @class CollisionDetection
 * @brief The CollisionDetection handles Collision and stores the Bouncing Boxes
 *
 *
 * @author Johanna Wald
 * @version 01
 * @date 20/10/2013 Johanna Wald - Basic Implementation
 * @date 22/10/2013 Johanna Wald - a looot of bugfixing
 * @date 22/10/2013 Johanna Wald - added consts and changed variable names (naming convention)
 * @date 25/10/2013 Johanna Wald - added comments, more consts
 */

#pragma once

#include "BoundingBox.h"
#include <GL\freeglut.h>
#include <vector>
#include "Vector3D.h"

class DrawManager;
class CollisionDetection
{
private:
	std::vector<BoundingBox*> mBoundingBoxes;
	const bool PointCollision(const BoundingBox *pBoundingBox, const Vector3D& pPoint) const;
public:
		/**
		* @brief draws all the collision boxes
		* @param const DrawManager& pDrawManager to draw the rects
		* @return void 
		*/
	void Draw(const DrawManager& pDrawManager) const;
		/**
		* @brief adds a collision box to the private member variable list and returns the index of it
		* @param const Vector3D& pMin new min value for the collision box
		* @param const Vector3D& pMax new max value for the collision box
		* @return const int index of collision box
		*/
	const int AddCollisionBox(const Vector3D& pMin, const Vector3D& pMax);
		/**
		* @brief returns the collision box of the element on index pIndex
		* @param const int pIndex of the index of the element in the mBoundingBox-array
		* @return const BoundingBox& the bounding box itself
		*/
	const BoundingBox& GetCollisionBox(const int pIndex) const;
		/**
		* @brief translates the bounding box at index pIndex with the Matrix pTranslation, keeps the original coordinates
		* @param const int pIndex index of the element in the array
		* @param const Vector3D& pTranslation translation matrix for the translation
		* @return void
		*/
	void TranslateBoundingBox(const int pIndex, const Vector3D& pTranslation);
		/**
		* @brief translates all bounding boxes with the Matrix pTranslation, keeps the original coordinates
		* 
		* uses the function TranslateBoundingBox()
		*
		* @param const Vector3D& pTranslation translation matrix for the translation
		* @return void
		*/
	void TranslateBoundingBoxes(const Vector3D& pTranslation);
		/**
		* @brief moves the bounding boxes on index pIndex Matrix (in array) with matrix pTranslation
		* 
		* uses the function Move() of the bounding box
		*
		* @param const int pIndex index of bounding box in array
		* @param const Vector3D& pTranslation translation matrix for the translation
		* @return void
		*/
	void MoveBoundingBox(const int pIndex, const Vector3D& pTranslation);
		/**
		* @brief checks if there is a collision between pBoundingBox1 and pBoundingBox2
		* 
		*
		* @param const BoundingBox& pBoundingBox1 first bounding box that should be checked
		* @param const BoundingBox& pBoundingBox2 second bounding box that should be checked
		* @param const bool pCY flag, if the y-axis is included in the collisino detection (default = true)
		* @return float value how many pixel at the axis are colliding / how "bad" the collision is
		*/
	float Collision(const BoundingBox& pBoundingBox1, const BoundingBox& pBoundingBox2, const bool pCY = true);

	float Collisions(const int pBBIndex, int& pIndex, const bool pCY);
	float Collisions(const BoundingBox& pBoundingBox1, int& pIndex, const bool pCY = true, const int pSkip = -1);
};


