#pragma once
#include "Vector3.h"
//\=============================================================================
// Vector4 - 4 dimensional vector class
//\=============================================================================
class Vector4
{
public:
	//\=========================================================================
	//\Member variables
	//\=========================================================================
	float x; float y; float z; float w;
#pragma region Constructors/Destructors
	//\=========================================================================
	//\Constructors
	//\=========================================================================
	Vector4();
	Vector4(const float a_x, const float a_y, const float a_z, const float a_w);
	Vector4(const Vector3& a_v4, float a_w = 0.f );
	Vector4(const Vector4& a_v4);
	//\=========================================================================
	//\Destructor
	//\=========================================================================
	~Vector4();
#pragma endregion
	Vector3			xyz() { return Vector3(x, y, z); }
#pragma region Opeartor Overloads
	//\=========================================================================
	//\ Equivalence Operators
	//\=========================================================================
	bool			operator ==			(const Vector4& a_v4) const;
	bool			operator !=			(const Vector4& a_v4) const;
	//\=========================================================================
	//\ Negate Operator
	//\=========================================================================
	const Vector4	operator - () const;
	//\=========================================================================
	//\ Addition Operators
	//\=========================================================================
	Vector4			operator +			(const Vector4& a_v4) const;
	Vector4			operator +			(const float a_scalar) const;
	//\=========================================================================
	//\ subtraction Operators
	//\=========================================================================
	Vector4			operator -			(const Vector4& a_v4) const;
	Vector4			operator -			(const float a_scalar) const;
	//\=========================================================================
	//\ Multiplication Operators
	//\=========================================================================
	Vector4			operator *			(const float& a_scalar) const;
	//\=========================================================================
	//\ Dot Product Functionality
	//\=========================================================================
	float					Dot(const Vector4& a_v4) const;
	friend float			Dot(const Vector4& a_v4A, const Vector4& a_v4B);
	//\=========================================================================
	//\ Get Length of Vector
	//\=========================================================================
	float					Length() const;
	//\=========================================================================
	//\ Normalise the Vector - modifies member variables (non const function)
	//\=========================================================================
	void					Normalize();
	friend	Vector4			Normalize(const Vector4& a_vec);
	//\=========================================================================
	//\ Linear Interpolate
	//\=========================================================================
	friend Vector4			Lerp(const Vector4& a_v4A, const Vector4& a_v4B, const float a_t);
#pragma endregion
};
