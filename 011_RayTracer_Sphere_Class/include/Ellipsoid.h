#pragma once
#include "Primitive.h"

class Ellipsoid : public Primitive
{
public:
	Ellipsoid();
	Ellipsoid(const Vector3& a_pos, const float& a_radius);
	virtual ~Ellipsoid();

	bool IntersectTest(const Ray& a_ray, Vector3& a_hitPos, Vector3& a_surfNormal) const override;

private:
	float m_radius;
};