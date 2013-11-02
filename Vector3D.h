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
		* @brief constructor of the Vector3D
	*/
	Vector3D(void);
	/**
		* @brief alternative constructor of the Vector3D
		* @param float x
		* @param float y
		* @param float z
	*/
	Vector3D(float x, float y, float z);
	/**
		* @brief deconstructor of the Vector3D		
	*/
	~Vector3D(void);
	/**
		* @brief GetDistance
		* @params const Vector3D& pPoint
		* @return Vector3D&
	*/
	Vector3D& GetDistance(const Vector3D& pPoint) const;
	//float GetDistance(const Vector3D& pPoint) const;
	/**
		* @brief Set 
		* @params float r
		* @params float s
		* @params float t
		* @return Vector3D&
	*/
    Vector3D& Set(float r, float s, float t);
      /**
		* @brief Operator []
		* @params long k
		* @return float&
	  */
    float& operator [](long k);
      /**
		* @brief Operator []
		* @params long k
		* @return const float&
	  */
        const float& operator [](long k) const;

        /**
		* @brief Operator +=
		* @params const Vector3D& v
		* @return Vector3D&
	  */
        Vector3D& operator +=(const Vector3D& v);
 
        /**
		* @brief Operator -=
		* @params long k
		* @return Vector3D&
	  */
        Vector3D& operator -=(const Vector3D& v);
      
		/**
		* @brief Operator *=
		* @params float t
		* @return Vector3D&
	  */
        Vector3D& operator *=(float t);
	 /**
		* @brief Operator /=
		* @params float t
		* @return Vector3D&
	  */     
        Vector3D& operator /=(float t);
        
		/**
		* @brief Operator %=
		* @params const Vector3D& v
		* @return Vector3D&
	  */
        Vector3D& operator %=(const Vector3D& v);
        
		/**
		* @brief Operator &=
		* @params const Vector3D& v
		* @return Vector3D&
	  */
        Vector3D& operator &=(const Vector3D& v);

		/**
		* @brief Operator -
		* @params void
		* @return Vector3D
	  */
        Vector3D operator -(void) const;
        
/**
		* @brief Operator +
		* @params const Vector3D& v
		* @return Vector3D
	  */
        Vector3D operator +(const Vector3D& v) const;
        
        /**
		* @brief Operator -
		* @params const Vector3D& v
		* @return Vector3D
	  */
        Vector3D operator -(const Vector3D& v) const;
        
     /**
		* @brief Operator *
		* @params float t
		* @return Vector3D
	  */        
        Vector3D operator *(float t) const;
        
		/**
		* @brief Operator /
		* @params float t
		* @return Vector3D
	  */
        Vector3D operator /(float t) const;
        
		/**
		* @brief Operator *
		* @params const Vector3D& v
		* @return float
	  */
        float operator *(const Vector3D& v) const;
        
        /**
		* @brief Operator %
		* @params const Vector3D& v
		* @return Vector3D
	  */
        Vector3D operator %(const Vector3D& v);
        
		/**
		* @brief Operator &
		* @params const Vector3D& v
		* @return Vector3D
	  */
        Vector3D operator &(const Vector3D& v);
        
		/**
		* @brief Operator ==
		* @params const Vector3D& v
		* @return bool
	  */
		bool operator ==(const Vector3D& v) const;
        
		/**
		* @brief Operator !=
		* @params const Vector3D& v
		* @return bool
	  */
        bool operator !=(const Vector3D& v) const;

    /**
		* @brief Normalize 
		* @params void
		* @return Vector3D reference
	*/
        Vector3D& Normalize(void);
};

