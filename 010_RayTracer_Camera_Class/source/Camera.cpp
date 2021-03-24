#include "Camera.h"

#define _USE_MATH_DEFINES
#include <cmath>

Camera::Camera()
{
	m_projectionMatrix = Matrix4::IDENTITY;
	m_Transform = Matrix4::IDENTITY;
}

Camera::~Camera()
{
}

void Camera::SetPosition(Vector3 a_v3Pos)
{
	m_Transform.SetColumn(3, a_v3Pos);
}

Vector3 Camera::GetPosition() 
{ 
	Vector4 pos = m_Transform.GetColumn(3);
	return Vector3(pos.x, pos.y, pos.z);
}

void Camera::SetPerspective(float a_fieldOfView, float a_aspectRatio, float a_near, float a_far)
{
	m_aspectRatio = a_aspectRatio;
	m_fov = a_fieldOfView * MathLib::DEG2RAD;
	m_zNear = a_near;
	m_zFar = a_far;
	m_projectionMatrix.Perspective(m_fov, a_aspectRatio, a_near, a_far);
}

void Camera::SetOrthographic(float a_left, float a_right, float a_top, float a_bottom, float a_near, float a_far)
{
	m_aspectRatio = (a_right - a_left) / (a_bottom - a_top);
	m_zNear = a_near;
	m_zFar = a_far;
	m_projectionMatrix.Orthographic(a_left, a_right, a_top, a_bottom, a_near, a_far);
}
void Camera::LookAt(const Vector3& a_v3Target, const Vector3& a_v3Up)
{
	Matrix4 viewMatrix = Matrix4::LookAt(GetPosition(), a_v3Target, a_v3Up);
	m_Transform = viewMatrix.Inverse();
}

Ray Camera::CastRay(Vector2 a_screenspaceCoord)
{
	//Get Projection View Matrix
	Matrix4 projViewMatrix = m_projectionMatrix * m_Transform.Inverse();
	//Invert to transform screen coordinate into world space
	Matrix4 invPV = projViewMatrix.Inverse();
	//multiply screen coordinate by inverse projection matrix to get position on near plane
	Vector4 nearProjSpaceCoords = invPV * Vector4(a_screenspaceCoord.x, a_screenspaceCoord.y, -1.f, 1.f);
	//We need to handle the perspective divide to get the coordinate on the near place
	nearProjSpaceCoords = nearProjSpaceCoords * (1.f / nearProjSpaceCoords.w);
	Vector3 v3Near = Vector3(nearProjSpaceCoords.x, nearProjSpaceCoords.y, nearProjSpaceCoords.z);
	//subtract camera position from near plane location to get direction of ray.
	Vector3 v3Projected = v3Near - GetPosition();
	v3Projected.Normalize();
	//create ray starting from camera position with projection
	Ray cameraRay( GetPosition(), v3Projected);
	return cameraRay;
}