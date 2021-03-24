#pragma once
#include <libMath.h>

class Camera
{
public:
	//\===========================================================================================================
	//\ Constructor Destructor
	//\===========================================================================================================
	Camera();
	~Camera();
	//\===========================================================================================================
	//\ Set/Get the positon of the camera in the world
	//\===========================================================================================================
	void SetPosition(Vector3 a_v3Pos);
	Vector3 GetPosition();
	//\===========================================================================================================
	//\ Set up the projection matrix for the camera
	//\ Set Perspective projection -- object get smaller the further away they are
	//\===========================================================================================================
	void SetPerspective(float a_fieldOfView, float a_aspectRatio, float a_near, float a_far);
	//\===========================================================================================================
	//\ Orthographic projection - no size change as objects are futher away from view
	//\===========================================================================================================
	void SetOrthographic(float a_left, float a_right, float a_top, float a_bottom, float a_near, float a_far);
	//\===========================================================================================================
	//\ Look at a point in the world wit the camera's local up direction set to the second direction
	//\===========================================================================================================
	void LookAt(const Vector3& a_v3Target, const Vector3& a_v3Up);
	//\===========================================================================================================
	//\ Cast a ray from a screen position out into the world space of the camera
	//\===========================================================================================================
	Ray CastRay(Vector2 a_screenspaceCoord);
	//\===========================================================================================================
	//\ Get Camera pos/rot matrix
	//\===========================================================================================================
	Matrix4 GetTransform() { return m_Transform; }
	//\===========================================================================================================
	//\ Get projection matrix
	//\===========================================================================================================
	Matrix4 GetProjectionMatrix() { return m_projectionMatrix; }
private:
	Matrix4 m_projectionMatrix;
	Matrix4 m_Transform;
	float m_aspectRatio;
	float m_fov;
	float m_zNear;
	float m_zFar;
};