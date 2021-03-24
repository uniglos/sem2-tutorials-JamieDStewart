#include <math.h>
#include "Ray.h"
//\=============================================================================
//\Default Constructor - using initialiser list
//\=============================================================================
Ray::Ray(): m_v3Origin(0.f, 0.f, 0.f), 
			m_v3Direction(0.f, 0.f, 1.f), 
			m_MinLength(0.f),
			m_MaxLength(std::numeric_limits<float>::max())
{
}
//\=============================================================================
//\ Constructor with Origin and Direction Values
//\=============================================================================
Ray::Ray(const Vector3& a_v3Origin, const Vector3& a_v3Direction, float a_minLength, float a_maxLength) : 
	m_v3Origin(a_v3Origin), m_v3Direction(a_v3Direction), m_MinLength(a_minLength), m_MaxLength(a_maxLength)
{
	if (m_v3Direction.Length() > 1.f)		//If length greater than 1 vector is not normalised
	{
		m_v3Direction.Normalize();
	}
}
//\=============================================================================
//\ Copy Constructor
//\=============================================================================
Ray::Ray(const Ray& a_Ray):
	m_v3Origin(a_Ray.m_v3Origin), m_v3Direction(a_Ray.m_v3Direction), m_MinLength(a_Ray.m_MinLength), m_MaxLength(a_Ray.m_MaxLength)
{
}
//\=============================================================================
//\ Destructor
//\=============================================================================
Ray::~Ray()
{
	//nothing newed nothing deleted!
}
//\=============================================================================
//\
//\=============================================================================
Vector3 Ray::PointAt(float a_distance)
{
	//If the distance is greater than the maximum allowed length of the ray
	//set the distance to the maximum possible length
	if (a_distance < m_MinLength)
	{
		a_distance = m_MinLength;
	}
	if (a_distance > m_MaxLength) 
	{
		a_distance = m_MaxLength;
	}
	return m_v3Origin + (m_v3Direction * a_distance);
}
//\=============================================================================
//\ Function to test intersection of ray with sphere with origin at a_center
//\ and radius or a_radius. Uses sqrt part of quadratic formula to return if intersection 
//\ is true or false. Points of intersection are not recorded
//\=============================================================================
bool Ray::DoesIntersectSphere(const Vector3& a_center, const float a_radius)
{
	Vector3 OC = m_v3Origin - a_center;				//Vector from Ray Origin to Center of sphere
	float a = m_v3Direction.Dot(m_v3Direction);		//As the ray is normalised this could be skipped (1^2 = 1)
	float b = 2.f * Dot(OC, m_v3Direction);			//Twice dot product of direction with vector to center of sphere
	float c = Dot(OC, OC) - a_radius * a_radius;	//Dot product of OC subtract radius squared
	float discriminant = b * b - 4.f * a * c;		//Discriminant part under sqrt of quadratic (b^2- 4ac)
	return (discriminant > 0.f);					//If greater than 0 we have one or more intersections
}
//\=============================================================================
//\ Function to test intersection of ray with sphere with origin at a_center
//\ and radius or a_radius. Uses sqrt part of quadratic formula to return if intersection 
//\ occurs. Returns smallest intercept distance.
//\=============================================================================
float Ray::IntersectSphere(const Vector3& a_center, const float a_radius)
{
	Vector3 OC = m_v3Origin - a_center;				//Vector from Ray Origin to Center of sphere
	float b = Dot(OC, m_v3Direction);				//dot product of direction with vector to center of sphere
	float c = Dot(OC, OC) - a_radius * a_radius;	//Dot product of OC subtract radius squared
	float discriminant = b * b - c;					//Discriminant part under sqrt of quadratic (b- c)
	if (discriminant < 0.f)
	{
		return -1.f;								//If less than 0 we have no intersections
	}
	else
	{
		return (-b - sqrtf(discriminant)); //Complete the quadratic equation formula for smallest value
	}
}