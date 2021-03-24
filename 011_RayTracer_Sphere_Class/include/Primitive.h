#pragma once
#include <LibMath.h>

class Primitive
{
public:
	Primitive();
	virtual ~Primitive();
	//function to test for intersection with primitive and ray - pure virtual only implemented in derived classes
	virtual bool IntersectTest(const Ray& a_ray, Vector3& a_hitPos, Vector3& a_surfNormal) const = 0;
	//Get and set primitive matrix
	Matrix4 GetTransform() const;
	void SetTransform(const Matrix4& a_m4);
	//Get and Set the position of the primitive
	Vector3 GetPosition() const;
	void SetPosition(const Vector3& a_v3);
	//Get and Set the position of the primitive
	Vector3 GetScale() const;
	void SetScale(const Vector3& a_v3);
	
	void SetShear(float xy, float xz, float yx, float yz, float zx, float zy);

protected:
	Matrix4 m_Transform;		//Position Scale and Rotation
	Vector3 m_Scale;			//Scale Vector

};
