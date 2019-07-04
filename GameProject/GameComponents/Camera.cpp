#include "Camera.h"


Camera::Camera(int width, int height)
{
    mWidth = width ;
    mHeight = height ;

    mPosition = D3DXVECTOR3(0, 0, 0);
}


Camera::~Camera()
{

}

void Camera::SetPosition(float x, float y)
{
    SetPosition(D3DXVECTOR3(x, y, 0));
}

void Camera::SetPosition(D3DXVECTOR3 pos)
{
    mPosition = pos;
}

D3DXVECTOR3 Camera::GetPosition()
{
    return mPosition;
}

RECT Camera::GetBound()
{
    RECT bound; 

    bound.left = mPosition.x - mWidth / 2;
    bound.right = bound.left + mWidth;;
    bound.top = mPosition.y - mHeight / 2;
    bound.bottom = bound.top + mHeight;

    return bound;
}

int Camera::GetWidth()
{
    return mWidth;
}

int Camera::GetHeight()
{
    return mHeight;
}