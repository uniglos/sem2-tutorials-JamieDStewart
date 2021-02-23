#include "Vector3.h"
#include <math.h>
//\=============================================================================
//\Default Constructor
//\=============================================================================
Vector3::Vector3()
{
	x = 0.f; y = 0.f; z = 0.f;
}
//\=============================================================================
//\ Constructor with X, Y Values
//\=============================================================================
Vector3::Vector3(const float a_x, const float a_y, const float a_z)
{
	x = a_x;
	y = a_y;
	z = a_z;
}
//\=============================================================================
//\ Copy Constructor
//\=============================================================================
Vector3::Vector3(const Vector3& a_v3)
{
	x = a_v3.x;
	y = a_v3.y;
	z = a_v3.z;
}
//\=============================================================================
//\ Destructor
//\=============================================================================
Vector3::~Vector3()
{
	//nothing newed nothing deleted!
}
//\=============================================================================
// Equivalence operators
//\=============================================================================
bool Vector3::operator ==(const Vector3& a_v3) const
{
	return (x == a_v3.x && y == a_v3.y && z == a_v3.z);
}

bool Vector3::operator !=(const Vector3& a_v3) const
{
	return (x != a_v3.x || y != a_v3.y || z != a_v3.z);
}
//\=============================================================================
//\ Neg operator
//\=============================================================================
const Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}
//\=============================================================================
//\ Overload Operators for Vector2 addition
//\=============================================================================
Vector3 Vector3::operator+(const Vector3& a_v3) const
{
	return Vector3(x + a_v3.x, y + a_v3.y, z + a_v3.z);
}

Vector3 Vector3::operator+(const float a_scalar) const
{
	return Vector3(x + a_scalar, y + a_scalar, z + a_scalar);
}
//\=============================================================================
//\ Overload Operators for Vector2 subtraction
//\=============================================================================
Vector3 Vector3::operator-(const Vector3& a_v3) const
{
	return Vector3(x - a_v3.x, y - a_v3.y, z - a_v3.z);
}

Vector3 Vector3::operator-(const float a_scalar) const
{
	return Vector3(x - a_scalar, y - a_scalar, z - a_scalar);
}
//\=============================================================================
//\ Overload Operators for Vector2 multiplication
//\=============================================================================
Vector3 Vector3::operator*(const float& a_scalar) const
{
	return Vector3(x * a_scalar, y * a_scalar, z * a_scalar);
}
//\=============================================================================
//\Dot Product - projection of one vector along another 
//\              or the cosine value of the angle between two vectors
//\=============================================================================
float Vector3::Dot(const Vector3& a_v3) const
{
	return (x * a_v3.x + y * a_v3.y + z * a_v3.z);
}
//\=============================================================================
//\ Dot Product - Friend function allows use to do the following in code
//\               Vector2 result = Dot( vec2A, vec2B );
//\				  notice the lack of "Vector2::" prior to the function name
//\=============================================================================
float Dot(const Vector3& a_v3A, const Vector3& a_v3B)
{
	return a_v3A.Dot(a_v3B);
}
//\=========================================================================
//\ Cross Product
//\=========================================================================
Vector3 Vector3::Cross(const Vector3& a_v3) const
{
	return Vector3(y * a_v3.z - a_v3.y * z, z * a_v3.x - x * a_v3.z, x * a_v3.y - y * a_v3.x);
}

Vector3	Cross(const Vector3& a_v3a, const Vector3& a_v3b)
{
	return a_v3a.Cross(a_v3b);
}
//\=============================================================================
//\ Get the length (magnitude) of the vector
//\=============================================================================
float Vector3::Length() const
{
	return sqrtf(x * x + y * y + z * z);	//to access SQRTF #include <math.h>
}
//\============================================================================
//\ Normalise the Vector
//\============================================================================
void Vector3::Normalize()
{
	float length = Length();
	if (length > 0.f)			//if this is false vector has no length
	{
		float invLen = 1.f / length;
		x *= invLen;
		y *= invLen;
		z *= invLen;
	}
}
//\=========================================================================
//\ Linear Interpolate
//\=========================================================================
Vector3	Lerp(const Vector3& a_v3A, const Vector3& a_v3B, const float a_t)
{
	return  (a_v3B - a_v3A) * a_t + a_v3A;
}