#include "Vector2.h"

//\=============================================================================
//\Default Constructor
//\=============================================================================
Vector2::Vector2()
{
	x = 0.f; y = 0.f;
}
//\=============================================================================
//\ Constructor with X, Y Values
//\=============================================================================
Vector2::Vector2(const float a_x, const float a_y)
{
	x = a_x;
	y = a_y;
}
//\=============================================================================
//\ Copy Constructor
//\=============================================================================
Vector2::Vector2(const Vector2& a_v2)
{
	x = a_v2.x;
	y = a_v2.y;
}
//\=============================================================================
//\ Destructor
//\=============================================================================
Vector2::~Vector2()
{
	//nothing newed nothing deleted!
}
//\=============================================================================
// Equivalence operators
//\=============================================================================
bool Vector2::operator ==(const Vector2& a_v2) const
{
	return (x == a_v2.x && y == a_v2.y);
}

bool Vector2::operator !=(const Vector2& a_v2) const
{
	return (x != a_v2.x || y != a_v2.y);
}
//\=============================================================================
//\ Neg operator
//\=============================================================================
const Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}
//\=============================================================================
//\ Overload Operators for Vector2 addition
//\=============================================================================
Vector2 Vector2::operator+(const Vector2& a_v2) const
{
	return Vector2(x + a_v2.x, y + a_v2.y);
}
//\=============================================================================
//\Dot Product - projection of one vector along another 
//\              or the cosine value of the angle between two vectors
//\=============================================================================
float Vector2::Dot(const Vector2& a_v2) const
{
	return (x * a_v2.x + y * a_v2.y);
}
//\=============================================================================
//\ Dot Product - Friend function allows use to do the following in code
//\               Vector2 result = Dot( vec2A, vec2B );
//\				  notice the lack of "Vector2::" prior to the function name
//\=============================================================================
float Dot(const Vector2& a_v2A, const Vector2& a_v2B)
{
	return a_v2A.Dot(a_v2B);
}
