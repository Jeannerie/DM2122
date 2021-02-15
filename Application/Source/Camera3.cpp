#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include "Assignment02.h"

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
    static const float CAMERA_SPEED = 10.f;
    Vector3 view = (target - position).Normalized();

    if (position.x >= 1000)
        position.x = 1000;

    if (position.x <= -1000)
        position.x = -1000;

    if (position.y >= 0)
        position.y = 0;
    if (position.y <= 0)
        position.y = 0;

    if (position.z >= 1000)
        position.z = 1000;
    if (position.z <= -1000)
        position.z = -1000;

    if (((position.x <= -185) && (position.x >= -188)) && ((position.z <= 29) && (position.z >= 10)))
    {
        Vector3 view = (target - position).Normalized();
        position.x = -185;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= -191) && (position.x >= -208)) && ((position.z <= 8) && (position.z >= 6 )))
    {
        Vector3 view = (target - position).Normalized();
        position.z = 7;
        position.y = 0;
        target = view + position; 
    }

    if (((position.x <= -211) && (position.x >= -213)) && ((position.z <= 29) && (position.z >= 7)))
    {
        Vector3 view = (target - position).Normalized();
        position.x = -214;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= -190) && (position.x >= -209)) && ((position.z <= 33) && (position.z >= 31)))
    {
        Vector3 view = (target - position).Normalized();
        position.z = 32;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= -187.5) && (position.x >= -191)) && ((position.z <= -111) && (position.z >= -131)))
    {
        Vector3 view = (target - position).Normalized();
        position.x = -188;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= -189.5) && (position.x >= -208.5)) && ((position.z <= -103) && (position.z >= -108)))
    {
        Vector3 view = (target - position).Normalized();
        position.z = -104;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= -213) && (position.x >= -215)) && ((position.z <= -111) && (position.z >= -129)))
    {
        Vector3 view = (target - position).Normalized();
        position.x = -214;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= -193) && (position.x >= -207)) && ((position.z <= -133) && (position.z >= -135)))
    {
        Vector3 view = (target - position).Normalized();
        position.z = -134;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= 85) && (position.x >= 60)) && ((position.z <= 32) && (position.z >= 10)))
    {
        Vector3 view = (target - position).Normalized();
        position.x = 56;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= 49) && (position.x >= 17)) && ((position.z <= 35) && (position.z >= 9)))
    {
        Vector3 view = (target - position).Normalized();
        position.x = 17;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= 271) && (position.x >= 23)) && ((position.z <= 7) && (position.z >= 4)))
    {
        Vector3 view = (target - position).Normalized();
        position.z = 5;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= 275) && (position.x >= 273)) && ((position.z <= 31) && (position.z >= 11)))
    {
        Vector3 view = (target - position).Normalized();
        position.x = 274;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= 269) && (position.x >= 20)) && ((position.z <= 35) && (position.z >= 31)))
    {
        Vector3 view = (target - position).Normalized();
        position.z = 36;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= 276) && (position.x >= 274)) && ((position.z <= -216) && (position.z >= -232)))
    {
        Vector3 view = (target - position).Normalized();
        position.x = 274;
        position.y = 0;
        target = view + position;
    }
   
    if (((position.x <= 279) && (position.x >= 193)) && ((position.z <= -166) && (position.z >= -215)))
    {
        Vector3 view = (target - position).Normalized();
        position.x = 240;
        position.y = 0;
        target = view + position;
    }

    if (((position.x <= 187) && (position.x >= 184)) && ((position.z <= -168) && (position.z >= -185)))
    {
        Vector3 view = (target - position).Normalized();
        position.x = 186;
        position.y = 0;
        target = view + position;
    }

    if (Application::IsKeyPressed('A'))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        position -= right * dt * 25;
        target -= right * dt * 25;
    }
    if (Application::IsKeyPressed('D'))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        position += right * dt * 25;
        target += right * dt * 25;
    }
    if (Application::IsKeyPressed('W'))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        position += view * dt * 30;
        target += view * dt * 30;
    }
    if (Application::IsKeyPressed('S'))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        position -= view * dt * 60;
        target -= view * dt * 60;
    }

    if (Application::IsKeyPressed(VK_UP))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        target += up * dt * 60;
    }
    if (Application::IsKeyPressed(VK_DOWN))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        target -= up * dt * 60;
    }
    if (Application::IsKeyPressed(VK_LEFT))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        target -= right * dt * 60;
    }
    if (Application::IsKeyPressed(VK_RIGHT))
    {
        Vector3 right = view.Cross(up).Normalized();
        right.y = 0;

        up = right.Cross(view).Normalized();

        target += right * dt * 60;
    }
}