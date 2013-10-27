#include "Vector3D.h"
#include <math.h>

//https://www.terathon.com/code/vector3d.html

Vector3D::Vector3D(float x, float y, float z): x(x), y(y), z(z)
{
}

Vector3D::Vector3D(void)
{
}

Vector3D::~Vector3D(void)
{
}

   
        
        Vector3D& Vector3D::Set(float r, float s, float t)
        {
            x = r;
            y = s;
            z = t;
            return (*this);
        }


        float& Vector3D::operator [](long k)
        {
            return ((&x)[k]);
        }
        
        const float& Vector3D::operator [](long k) const
        {
            return ((&x)[k]);
        }
        
        
        Vector3D& Vector3D::operator +=(const Vector3D& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return (*this);
        }
        
        
        Vector3D& Vector3D::operator -=(const Vector3D& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return (*this);
        }
        
        
        Vector3D& Vector3D::operator *=(float t)
        {
            x *= t;
            y *= t;
            z *= t;
            return (*this);
        }
        
        Vector3D& Vector3D::operator /=(float t)
        {
            float f = 1.0F / t;
            x *= f;
            y *= f;
            z *= f;
            return (*this);
        }
        
        Vector3D& Vector3D::operator %=(const Vector3D& v)
        {
            float       r, s;
            
            r = y * v.z - z * v.y;
            s = z * v.x - x * v.z;
            z = x * v.y - y * v.x;
            x = r;
            y = s;
            
            return (*this);
        }
        
        Vector3D& Vector3D::operator &=(const Vector3D& v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return (*this);
        }
        
        Vector3D Vector3D::operator -(void) const
        {
            return (Vector3D(-x, -y, -z));
        }
        
        Vector3D Vector3D::operator +(const Vector3D& v) const
        {
            return (Vector3D(x + v.x, y + v.y, z + v.z));
        }
        

        Vector3D Vector3D::operator -(const Vector3D& v) const
        {
            return (Vector3D(x - v.x, y - v.y, z - v.z));
        }
        
        
        Vector3D Vector3D::operator *(float t) const
        {
            return (Vector3D(x * t, y * t, z * t));
        }
        
        Vector3D Vector3D::operator /(float t) const
        {
            float f = 1.0F / t;
            return (Vector3D(x * f, y * f, z * f));
        }
        
        float Vector3D::operator *(const Vector3D& v) const
        {
            return (x * v.x + y * v.y + z * v.z);
        }
 
        
        bool Vector3D::operator ==(const Vector3D& v) const
        {
            return ((x == v.x) && (y == v.y) && (z == v.z));
        }
        
        bool Vector3D::operator !=(const Vector3D& v) const
        {
            return ((x != v.x) || (y != v.y) || (z != v.z));
        }
        
        Vector3D& Vector3D::Normalize(void)
        {
            return (*this /= sqrtf(x * x + y * y + z * z));
        }