#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera3::Camera3()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera3::~Camera3()
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
void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
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
void Camera3::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera3::Update(double dt)
{
    static const float CAMERA_SPEED = 30.f;
    Vector3 view = (target - position).Normalized();

    if (Application::IsKeyPressed('A'))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        position -= right * dt * 140;
        target -= right * dt * 140;
    }
    if (Application::IsKeyPressed('D'))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        position += right * dt * 140;
        target += right * dt * 140;
    }
    if (Application::IsKeyPressed('W'))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        position += view * dt * 140;
        target += view * dt * 140;
    }
    if (Application::IsKeyPressed('S'))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        position -= view * dt * 140;
        target -= view * dt * 140;
    }

    if (Application::IsKeyPressed(VK_UP))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        target += up * dt * 5;
    }
    if (Application::IsKeyPressed(VK_DOWN))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        target -= up * dt * 5;
    }
    if (Application::IsKeyPressed(VK_LEFT))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        target -= right * dt * 5;
    }
    if (Application::IsKeyPressed(VK_RIGHT))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        target += right * dt * 5;
    }
}