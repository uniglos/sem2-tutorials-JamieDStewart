#include "DirectionalLight.h"
#include <cmath>

DirectionalLight::DirectionalLight()
{
	SetDirection(Vector3(0.f, 0.f, 0.f));
}

DirectionalLight::DirectionalLight(const Matrix4& a_transform, const Vector3& a_colour, const Vector3& a_facing)
	: Light(a_transform, a_colour)
{
	SetDirection(a_facing);
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::SetDirection(const Vector3& a_direction, const Vector3& a_up)
{
	m_Transform.SetColumn(2, a_direction);
	m_Transform.SetColumn(1, a_up);
	m_Transform.Orthonormalise();
}

Vector3 DirectionalLight::GetDirection() const
{
	return m_Transform.GetColumn(2).xyz();
}

ColourRGB DirectionalLight::CaclulateLighting(const Vector3& a_hitPoint, const Vector3& a_eyePos, const Vector3& a_normal) const
{
	//work out diffuse -- treat all surfaces as being the same under this light
	// Ambient = 0.2f;
	// Diffuse = 0.8f;
	// Specular = 0.8f;
	// SpecularFactor = 200.f;
	//We will look at materials next tutorial.
	ColourRGB ambient = m_colourRGB * 0.1f;									//Get ambient colour for surface
	//Light direction is forward axis of light matrix
	Vector3 lightDirection = -GetDirection();								//Get direction to light from surface
	float lightDiffuse = MathUtil::Max(0.f, Dot(lightDirection, a_normal));	//Positive values indicate vectors in same dir
	ColourRGB diffuse = m_colourRGB * 0.9f * lightDiffuse;					//Blend light diffuse with diffuse value and colour
	//Calculate light specular value
	Vector3 eyeDir = Normalize(a_eyePos - a_hitPoint);						//Get the dir from view to surface
	Vector3 reflectionVec = Reflect(eyeDir, a_normal);						//Get the reflection vector of the eye around normal
	float specularFactor = std::powf(MathUtil::Max(0.f, Dot(reflectionVec, lightDirection)), 64.f);//Get the specular value
	ColourRGB specular = m_colourRGB * 0.9f * specularFactor;

	return ambient + diffuse + specular;

}
