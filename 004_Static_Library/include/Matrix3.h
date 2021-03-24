#pragma once

#include "Vector3.h"

//\=============================================================================
//\ Matrix3 class
//\		Class that implements a 3 by 3 homogeneous matrix
//\		Column-major Order
//\=============================================================================
class Matrix3
{
	friend class Matrix4;
private:
	//\=========================================================================
	//\ Member variables held in unnamed union for accessibility
	//\		items in a union share the same memory 
	//\		E.G m[0][0] == m_11 == m_xAxis.x
	//\			m[2][2] == m_33 == m_zAxis.z
	//\=========================================================================
	union
	{
		float m[3][3];
		struct
		{
			float m_11, m_21, m_31;		//Column 1 -> x axis
			float m_12, m_22, m_32;		//Column 2 -> y axis
			float m_13, m_23, m_33;		//Column 3 -> z axis
		};
		struct
		{
			Vector3 m_xAxis;
			Vector3 m_yAxis;
			Vector3 m_zAxis;
		};
	};
public:
	//\=========================================================================
	//\ Constants
	//\=========================================================================
	static const Matrix3 IDENTITY;
	//\=========================================================================
	//\ Constructors
	//\=========================================================================
	Matrix3();
	Matrix3(const float* a_mat);
	Matrix3(float a_m11, float a_m21, float a_m31,
			float a_m12, float a_m22, float a_m32,
			float a_m13, float a_m23, float a_m33);
	Matrix3(const Vector3& a_xAxis, const Vector3& a_yAxis, const Vector3& a_zAxis);
	Matrix3(const Matrix3& a_m3);
	//\=========================================================================
	//\ Destructor
	//\=========================================================================
	~Matrix3();
	//\=========================================================================
	// Component Access Operators
	//\=========================================================================
	float&			operator()		(int a_iRow, int a_iCol);
	float			operator()		(int a_iRow, int a_iCol) const;
	//\=========================================================================
	//\ Column and Row Access
	//\=========================================================================
	void			SetColumn		(int a_iCol, const Vector3& a_vCol);
	Vector3			GetColumn		(int a_iCol) const;
	//\=========================================================================
	//\ Equivalence Operators
	//\=========================================================================
	bool			operator ==		(const Matrix3& a_m3) const;
	bool			operator !=		(const Matrix3& a_m3) const;
	//\=========================================================================
	//\ Overload operators for Addition
	//\=========================================================================
	Matrix3			operator +		(const Matrix3& a_m3) const;
	const Matrix3&	operator +=		(const Matrix3& a_m3);
	//\=========================================================================
	//\ Overload operators for Subtraction
	//\=========================================================================
	Matrix3			operator -		(const Matrix3& a_m3) const;
	const Matrix3&	operator -=		(const Matrix3& a_m3);
	//\=========================================================================
	//\ Overload operators for multiplication
	//\=========================================================================
	Matrix3			operator *		(const float a_scalar) const;
	const Matrix3&	operator *=		(const float a_scalar);

	Vector3			operator *		(const Vector3& a_v3) const;

	Matrix3			operator *		(const Matrix3& a_m3) const;
	const Matrix3&	operator *=		(const Matrix3& a_m3);
	//\=========================================================================
	//\ Transpose
	//\=========================================================================
	void			Transpose		();
	Matrix3			GetTranspose	() const;
	//\=========================================================================
	//\ Scale 
	//\=========================================================================
	void			Scale			(const float a_scalar);
	void			Scale			(const Vector3& a_v3);
	//\=========================================================================
	//\ Identity
	//\=========================================================================
	void			Identity		();
	//==========================================================================
	//\Determinant
	//==========================================================================
	float			Determinant		()const;
	//\=========================================================================
	//\Inverse
	//\=========================================================================
	bool			Inverse			();
	Matrix3			GetInverse		()const;
	//\=========================================================================
};