#pragma once
#include <libMath.h>

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(Vector3 a_v3Pos);
	Vector3 GetPosition();
	void SetPerspective(float a_fieldOfView, float a_aspectRatio, float a_near, float a_far);
	void SetOrthographic(float a_left, float a_right, float a_top, float a_bottom, float a_near, float a_far);
	void LookAt(const Vector3& a_v3Target, const Vector3& a_v3Up);

	Ray CastRay(Vector2 a_screenspaceCoord);
	Matrix4 GetTransform() { return m_Transform; }
	Matrix4 GetProjectionMatrix() { return m_projectionMatrix; }
private:
	Matrix4 m_projectionMatrix;
	Matrix4 m_Transform;
	float m_aspectRatio;
	float m_fov;
	float m_zNear;
	float m_zFar;
};