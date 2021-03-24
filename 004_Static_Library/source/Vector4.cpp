#include "Vector4.h"
#include <math.h>
//\=============================================================================
//\Default Constructor
//\=============================================================================
Vector4::Vector4()
{
	x = 0.f; y = 0.f; z = 0.f; w = 0.f;
}
//\=============================================================================
//\ Constructor with X, Y Values
//\=============================================================================
Vector4::Vector4(const float a_x, const float a_y, const float a_z, const float a_w):
	x(a_x), y(a_y), z(a_z), w(a_w)
{}
//\=============================================================================
//\ Construct from Vector3
//\=============================================================================
Vector4::Vector4(const Vector3& a_v3, float a_w):
	x(a_v3.x), y(a_v3.y), z(a_v3.z), w(a_w)
{
}
//\=============================================================================
//\ Copy Constructor
//\=============================================================================
Vector4::Vector4(const Vector4& a_v4):
	x(a_v4.x), y(a_v4.y), z(a_v4.z), w(a_v4.w)
{}
//\=============================================================================
//\ Destructor
//\=============================================================================
Vector4::~Vector4()
{
	//nothing newed nothing deleted!
}
//\=============================================================================
// Equivalence operators
//\=============================================================================
bool Vector4::operator ==(const Vector4& a_v4) const
{
	return (x == a_v4.x && y == a_v4.y && z == a_v4.z && w == a_v4.z);
}

bool Vector4::operator !=(const Vector4& a_v4) const
{
	return (x != a_v4.x || y != a_v4.y || z != a_v4.z || w != a_v4.w);
}
//\=============================================================================
//\ Neg operator
//\=============================================================================
const Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}
//\=============================================================================
//\ Overload Operators for Vector4 addition
//\=============================================================================
Vector4 Vector4::operator+(const Vector4& a_v4) const
{
	return Vector4(x + a_v4.x, y + a_v4.y, z + a_v4.z, w + a_v4.w);
}

Vector4 Vector4::operator+(const float a_scalar) const
{
	return Vector4(x + a_scalar, y + a_scalar, z + a_scalar, w + a_scalar);
}
//\=============================================================================
//\ Overload Operators for Vector2 subtraction
//\=============================================================================
Vector4 Vector4::operator-(const Vector4& a_v4) const
{
	return Vector4(x - a_v4.x, y - a_v4.y, z - a_v4.z, w - a_v4.w);
}

Vector4 Vector4::operator-(const float a_scalar) const
{
	return Vector4(x - a_scalar, y - a_scalar, z - a_scalar, w - a_scalar);
}
//\=============================================================================
//\ Overload Operators for Vector2 multiplication
//\=============================================================================
Vector4 Vector4::operator*(const float& a_scalar) const
{
	return Vector4(x * a_scalar, y * a_scalar, z * a_scalar, w * a_scalar);
}
//\=============================================================================
//\Dot Product - projection of one vector along another 
//\              or the cosine value of the angle between two vectors
//\=============================================================================
float Vector4::Dot(const Vector4& a_v4) const
{
	return (x * a_v4.x + y * a_v4.y + z * a_v4.z + w * a_v4.w);
}
//\=============================================================================
//\ Dot Product - Friend function allows use to do the following in code
//\               Vector2 result = Dot( vec2A, vec2B );
//\				  notice the lack of "Vector2::" prior to the function name
//\=============================================================================
float Dot(const Vector4& a_v4A, const Vector4& a_v4B)
{
	return a_v4A.Dot(a_v4B);
}
//\=============================================================================
//\ Get the length (magnitude) of the vector
//\=============================================================================
float Vector4::Length() const
{
	return sqrtf(x * x + y * y + z * z + w * w);	//to access SQRTF #include <math.h>
}
//\============================================================================
//\ Normalise the Vector
//\============================================================================
void Vector4::Normalize()
{
	float length = Length();
	if (length > 0.f)			//if this is false vector has no length
	{
		float invLen = 1.f / length;
		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;
	}
}
Vector4 Normalize(const Vector4& a_vec4)
{
	float mag = a_vec4.Length();
	if (mag > 0.f) {
		return Vector4(a_vec4.x / mag, a_vec4.y / mag, a_vec4.z / mag, a_vec4.w / mag);
	}
	return Vector4(0.f, 0.f, 0.f, 0.f);
}
//\=========================================================================
//\ Linear Interpolate
//\=========================================================================
Vector4	Lerp(const Vector4& a_v4A, const Vector4& a_v4B, const float a_t)
{
	return  (a_v4B - a_v4A) * a_t + a_v4A;
}