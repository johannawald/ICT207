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



	void translateBoundingBoxOriginal(int i, const Vector3D& pTranslation);
	float CollisionX(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2);
	float CollisionY(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2);
	float CollisionZ(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2);
	float Collision2(const BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2, bool pCX = true, bool pCY = true, bool pCZ = true);
	float Collisions(const int pBBIndex, int& pIndex, const bool pCY);
	float Collisions(const BoundingBox* pBoundingBox1, int& pIndex, const bool pCY = true, const int pSkip = -1);
	float Collision(const Vector3D& pPoint, int &pIndex, const BoundingBox* bb, const bool pCY = true);
};


