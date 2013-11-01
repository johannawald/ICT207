/**
 * @class BoundingBox.h
 * @brief The BoundingBox is a class to represent a bounding box with a min and a max-vector3D
 *
 * @author Johanna Wald
 * @version 01
 * @date 20/10/2013 Johanna Wald - Basic Implementation
 * @date 25/10/2013 Johanna Wald - added consts and cleared code
 * @date 25/10/2013 Johanna Wald - changed all member variables to private
 */

#pragma once

#include "Vector3D.h"

class BoundingBox
{
private:
	Vector3D mMax;
    Vector3D mMin;
    Vector3D mOriginalMax;
    Vector3D mOriginalMin;	
public:
	/**
		* @brief constructor with parameters to initialize the bounding box
		* @param const Vector3D& pMin - sets the value of the member variables "mMin" and "mOriginalMin"
        * @param const Vector3D& pMax - sets the value of the member variables "mMax" and "mOriginalMax"
	*/
	BoundingBox(const Vector3D& pMin, const Vector3D& pMax);
	/**
		* @brief constructor with parameters to initialize the bounding box, it calculates min and max-border
		* @param const Vector3D& pPosition - position of the bounding box
        * @param const Vector3D& pMax - size of the bounding box
	*/
	BoundingBox(const Vector3D& pPosition, const float pSize);
	BoundingBox();
	/**
		* @brief returns the length of a bounding box
		* @param const float pValue1 - Length of the first side
        * @param const float pValue2 - Length of the second side (can be reverse)
		* @return const float the length
	*/
	const float GetLength(const float pValue1, const float pValue2) const;
	/**
		* @brief returns the min-vector for the bounding box
		* @param none
        * @return const Vector3D& const reference of the min vector
	*/
	const Vector3D& GetMin() const;
	/**
		* @brief returns the max-vector for the bounding box
		* @param none
        * @return const Vector3D& const reference of the max vector
	*/
	const Vector3D& GetMax() const;
	/**
		* @brief sets the bounding box with changing the min and max vectors
		* @param const Vector3D& pPosition position of the bounding box
		* @param const Vector3D& pSize size of the bounding box
        * @return void
	*/
	void SetBoundingBox(const Vector3D& pPosition, const Vector3D& pSize);
	/**
		* @brief returns the center of the bounding box as a vector
		* @param none
        * @return const Vector3D& center of the bounding boxd
	*/
	const Vector3D& GetCenter() const;
	/**
		* @brief returns the size of the bounding box as a vector
		* @param none
        * @return const Vector3D& size of the bounding boxd
	*/
	const Vector3D& GetSize() const;
	/**
		* @brief translates / updates the bounding box with help of the private member variables "mOriginalMin", "mOriginalMax"
		* @param const Vector3D& pTranslate translation-matrix
        * @return void
	*/
	void Translate(const Vector3D& pTranslate);
	/**
		* @brief translates the original bounding box and changes the position of it
		* @param const Vector3D& pTranslate translation-matrix
        * @return void
	*/
	void TranslatePosition(const Vector3D& pTranslate);
};
