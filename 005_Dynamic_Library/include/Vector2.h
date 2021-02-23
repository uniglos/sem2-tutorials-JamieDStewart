#pragma once

#ifdef MATH_LIB_DLL
#define MATHAPI __declspec(dllexport)
#elif MATH_LIB_STATIC
#define MATHAPI 
#else
#define MATHAPI __declspec(dllimport)
#endif

//\=============================================================================
// Vector2 - 2 dimensional vector class
//\=============================================================================
class MATHAPI Vector2
{
public:
	//\=========================================================================
	//\Member variables
	//\=========================================================================
	float x; float y;
#pragma region Constructors/Destructors
	//\=========================================================================
	//\Constructors
	//\=========================================================================
	Vector2();
	Vector2(const float a_x, const float a_y);
	Vector2(const Vector2& a_v2);
	//\=========================================================================
	//\Destructor
	//\=========================================================================
	~Vector2();
#pragma endregion
#pragma region Opeartor Overloads
	//\=========================================================================
	//\ Equivalence Operators
	//\=========================================================================
	bool			operator ==			(const Vector2& a_v2) const;
	bool			operator !=			(const Vector2& a_v2) const;
	//\=========================================================================
	//\ Negate Operator
	//\=========================================================================
	const Vector2	operator - () const;
	//\=========================================================================
	//\ Addition Operators
	//\=========================================================================
	Vector2			operator +			(const Vector2& a_v2) const;
	//\=========================================================================
	//\ Dot Product Functionality
	//\=========================================================================
	float					Dot(const Vector2& a_v2) const;
	friend float			Dot(const Vector2& a_v2A, const Vector2& a_v2B);
	//\=========================================================================
#pragma endregion
};