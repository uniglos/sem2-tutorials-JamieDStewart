#include "Primitive.h"

Primitive::Primitive() : m_Transform(Matrix4::IDENTITY), m_Scale()
{
}

Primitive::~Primitive()
{
}

//Get and set primitive matrix
Matrix4 Primitive::GetTransform() const 
{ 
	return m_Transform; 
}

void Primitive::SetTransform(const Matrix4& a_m4) 
{ 
	m_Transform = a_m4;
}

//Get and Set the position of the primitive
Vector3 Primitive::GetPosition() const 
{
	return m_Transform.GetColumnV3(3);
}

void Primitive::SetPosition(const Vector3& a_v3) 
{ 
	m_Transform.SetColumn(3, a_v3); 
}

//Get and Set the position of the primitive
Vector3 Primitive::GetScale() const 
{ 
	return m_Scale; 
}

void Primitive::SetScale(const Vector3& a_v3) 
{ 
	m_Scale = a_v3;
	Matrix4 scale;
	scale.Scale(a_v3);
	m_Transform = m_Transform * scale;
}

void Primitive::SetShear(float xy, float xz, float yx, float yz, float zx, float zy)
{
	Matrix4 sM4;
	sM4.Shear(xy, xz, yx, yz, zx, zy);
	m_Transform = m_Transform * sM4;
}
