#pragma once
//from https://www.terathon.com/code/vector3d.html johannawald
//format + comments missing

class Vector3D
{
public:
	float x;
	float y;
	float z;
	
	Vector3D(float x, float y, float z);
	Vector3D(void);
	~Vector3D(void);

    Vector3D& Set(float r, float s, float t);
      
        float& operator [](long k);
    
        const float& operator [](long k) const;

        
        Vector3D& operator +=(const Vector3D& v);
 
        
        Vector3D& operator -=(const Vector3D& v);
      
        Vector3D& operator *=(float t);
   
        
        Vector3D& operator /=(float t);
        
        Vector3D& operator %=(const Vector3D& v);
        
        Vector3D& operator &=(const Vector3D& v);
        Vector3D operator -(void) const;
        
        Vector3D operator +(const Vector3D& v) const;
        
        
        Vector3D operator -(const Vector3D& v) const;
        
     
        
        Vector3D operator *(float t) const;
        
        Vector3D operator /(float t) const;
        
        float operator *(const Vector3D& v) const;
        
        
        Vector3D operator %(const Vector3D& v);
        
        Vector3D operator &(const Vector3D& v);
        
        bool operator ==(const Vector3D& v) const;
        
        bool operator !=(const Vector3D& v) const;
        
        Vector3D& Normalize(void);
};

