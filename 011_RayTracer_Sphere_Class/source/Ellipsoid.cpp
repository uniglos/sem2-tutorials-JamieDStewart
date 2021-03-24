#include "Ellipsoid.h"

Ellipsoid::Ellipsoid() : m_radius(1.f)
{
}

Ellipsoid::Ellipsoid(const Vector3& a_position, const float& a_radius) : m_radius(a_radius)
{
	SetPosition(a_position);
	SetScale(Vector3(m_radius, m_radius, m_radius));
	
	/*Matrix4 shearMatrix;
	shearMatrix.Shear(2.f, 3.f, 0.f, 2.f, 0.f, 1.3f);
	m_Transform = m_Transform * shearMatrix;;*/
}

Ellipsoid::~Ellipsoid()
{
}

//Function to calculate the point of intersection with an ellipsoid and a ray
//returns true if intersection occurs, tests for intersections in front of the ray (not behind)
bool Ellipsoid::IntersectTest(const Ray& a_ray, Vector3& a_hitPos, Vector3& a_surfNormal) const
{
	//The normal matrix is the inverse transpose of the transform
	Matrix4 normalMatrix = m_Transform.GetTranspose().Inverse();
	
	Matrix4 invTx = m_Transform.Inverse();								//Get the inverse of the transform matrix
	Vector4 rayOrigin = invTx * Vector4(a_ray.Origin(), 1.f);			//Multiply ray origin by inverse to get in local space
	Vector4 rayDir = Normalize(invTx * Vector4(a_ray.Direction()));		//Get ray direction in local space

	Vector3 OC = rayOrigin.xyz();			//Vector from Ray Origin to Center of sphere
	float b = Dot(OC, rayDir.xyz());		//dot product of direction with vector to center of sphere
	float c = Dot(OC, OC) - 1.f;			//Dot product of OC subtract radius squared (radius of 1 for unit sphere)
	float discriminant = b * b - c;			//Discriminant part under sqrt of quadratic (b- c)
	if (discriminant < 0.f)
	{
		return false;						//If less than 0 we have no intersections
	}
	else
	{
		//test for both intersection points  to see if intersection occurs behind ray origin
		//discard negative intersection distances as intersection is behind ray
		float dist = -1.f;						//Start with distance initialised as negative
		float i0 = -b - sqrt(discriminant);		//complete negative part of quadratic equation
		float i1 = -b + sqrt(discriminant);		//complete positive part of quadratic equation
		if (i0 > 0.f)							//is first intersection point in front of ray origin
		{	dist = i0;	}
		else if (i1 > 0.f)						//if first point not in front of origin is second intersection point 
		{	dist = i1;	}
		else
		{	return false;	}					//Both intersection points behind ray origin
		//Now that we have closest positive intersection point
		Vector4 hp = rayOrigin + rayDir * dist;	//calculate hit point in local space to ellipsoid
		a_surfNormal = Normalize(hp.xyz());		//normalise this point provides direction of surface normal
		hp = invTx * hp;						//Multiply point by inverse transform matrix to get in world space
		a_hitPos = Vector3(hp.x, hp.y, hp.z);	//Nearest hitpoint on surface of ellipsoid to ray
		a_surfNormal = normalMatrix * a_surfNormal;	//Convert Normal into world space normal by multipling with normal matrix
		
		return true;							//return true as ray intersected ellipsoid
	}
	return false;								//nope, no intersections here
}