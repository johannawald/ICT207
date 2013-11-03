/**
 *
 * @class Vector3d
 * @brief Class for creating a vector
 *
 * Implements all vector operations 
 * @author from https://www.terathon.com/code/vector3d.html Johanna Wald
 * 
 */


#pragma once

class Vector3D {
private:
	//static Vector3D s_vZero;
public:
	float x;
	float y;
	float z;
	
	/**
		* @brief create a new Vector3D object
	*/
	Vector3D(void);
	/**
		* @brief create a new Vector3D object and set the values of x, y and z
		* @param float x
		* @param float y
		* @param float z
	*/
	Vector3D(float x, float y, float z);
	/**
		* @brief destroy Vector3D object
	*/
	~Vector3D(void);
	/**
		* @brief calulates the distance between this vector and a point and returns the vector between them
		* @params const Vector3D& pPoint the point which a vector points to
		* @return Vector3D& the distance between this vector and a point
	*/
	Vector3D& GetDistance(const Vector3D& pPoint) const;
	//float GetDistance(const Vector3D& pPoint) const;
	/**
		* @brief Set the values of x, y and z of a vector object and return modified vector
		* @params float r saves the value of x
		* @params float s saves the value of y
		* @params float t saves the value of z
		* @return Vector3D& modified vector
	*/
    Vector3D& Set(float r, float s, float t);
      /**

        /**
		* @brief overload Operator += adds this vector and another vector together
		* @params const Vector3D& v vector for addition
		* @return Vector3D& new vector after addition 
	  */
        Vector3D& operator +=(const Vector3D& v);
 
        /**
		* @brief overload Operator -= subtracts another vector from this vector and return results
		* @params const Vector3D& v vector used for subtraction
		* @return Vector3D& new vector after subtraction
	  */
        Vector3D& operator -=(const Vector3D& v);
      
		/**
		* @brief overload Operator *= multiply this vector by a value and return results
		* @params float t value which vector is multiplied by 
		* @return Vector3D& new vector after multiplication 
	  */
        Vector3D& operator *=(float t);
	 /**
		* @brief overload Operator /= divide this vector by a value and return results
		* @params float t value which vector is divided by
		* @return Vector3D& new vector after division
	  */     
        Vector3D& operator /=(float t);
        
		/**
		* @brief overload Operator %= compute the remainder after division of this vector divided by another 
		* @params const Vector3D& v vector to divide by
		* @return Vector3D& remainder of the division
	  */
        Vector3D& operator %=(const Vector3D& v);
        
		/**
		* @brief overload Operator &= multiplies this vector with another vector
		* @params const Vector3D& v vector to multiply by
		* @return Vector3D& modified vector after multiplication
	  */
        Vector3D& operator &=(const Vector3D& v);

		/**
		* @brief overload Operator - performs inverse operation on this vector's components and return results
		* @params void
		* @return Vector3D modifed vector after inverse
	  */
        Vector3D operator -(void) const;
        
	   /**
		* @brief overload Operator + performs an addition with this vector's components and another vector's components and returns results
		* @params const Vector3D& v vector for addition
		* @return Vector3D modified vector after addition
	  */
        Vector3D operator +(const Vector3D& v) const;
        
        /**
		* @brief overload Operator - performs a subtraction with this vector's components and another vector's components and returns results
		* @params const Vector3D& v vector for subtraction 
		* @return Vector3D modifed vector after subtraction
	  */
        Vector3D operator -(const Vector3D& v) const;
        
     /**
		* @brief overload Operator * perform a multiplication on this vector's components with a value and return the results
		* @params float t value for multiplication
		* @return Vector3D modified vector after multiplication
	  */        
        Vector3D operator *(float t) const;
        
		/**
		* @brief overload Operator / perform a division on this vector's components with a value and return the results
		* @params float t value for divison
		* @return Vector3D modified vector after division 
	  */
        Vector3D operator /(float t) const;
        
		/**
		* @brief overload Operator * perform a multication on this vector's components with another vector's components and return the addition of the components results
		* @params const Vector3D& v vector for multiplication
		* @return float the value of the addition of each multiplication
	  */
        float operator *(const Vector3D& v) const;
        
        /**
		* @brief overload Operator % performs a division of this vector by another vector and returns the remainder
		* @params const Vector3D& v vector for division
		* @return Vector3D modified vector after division and remainder is calculated
	  */
        Vector3D operator %(const Vector3D& v);
        
		/**
		* @brief overload Operator &
		* @params const Vector3D& v
		* @return Vector3D
	  */
        Vector3D operator &(const Vector3D& v);
        
		/**
		* @brief overload Operator == checks if this vector's components are equal to another vector's components and returns true or false
		* @params const Vector3D& v vector to check against
		* @return bool true if values are equal, false if they are not equal
	  */
		bool operator ==(const Vector3D& v) const;
        
		/**
		* @brief overload Operator != checks if this vector's components are not equal to another vector's components and returns true of false
		* @params const Vector3D& v vector to check againt
		* @return bool true if values are not equal, false if they are equal
	  */
        bool operator !=(const Vector3D& v) const;

    /**
		* @brief normalizes this vector  
		* @params void
		* @return new normalized vector
	*/
        Vector3D& Normalize(void);
};

