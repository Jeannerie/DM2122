#include "Camera2.h"
#include "Application.h"
#include "Mtx44.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera2::Camera2()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera2::~Camera2()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalized();
	this->up = right.Cross(view).Normalized();
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera2::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera2::Update(double dt)
{
	static const float CAMERA_SPEED = 20.f;
	Vector3 view = (target - position).Normalized();
	if (Application::IsKeyPressed('W'))
	{
		Mtx44 rotation;
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalized();
		rotation.SetToRotation(-CAMERA_SPEED * dt, right.x, right.y, right.z);
		//apply rotation matrix
		position = rotation * position;
		up = right.Cross(view).Normalized();
	}
	if (Application::IsKeyPressed('A'))
	{
		//Create rotation matrix
		Mtx44 rotation;
		rotation.SetToRotation(-CAMERA_SPEED * dt, 0, 1, 0);
		//apply rotation matrix
		position = rotation * position;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('S'))
	{
		Mtx44 rotation;
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalized();
		rotation.SetToRotation(CAMERA_SPEED * dt, right.x, right.y, right.z);
		//apply rotation matrix
		position = rotation * position;
		up = right.Cross(view).Normalized();
	}
	if (Application::IsKeyPressed('D'))
	{
		Mtx44 rotation;
		rotation.SetToRotation(CAMERA_SPEED * dt, 0, 1, 0);
		//apply rotation matrix
		position = rotation * position;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('N'))
	{
		position += view * CAMERA_SPEED * dt;
	}	
	if (Application::IsKeyPressed('M'))
	{
		position -= view * CAMERA_SPEED * dt;
	}

}