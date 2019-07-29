#include "pch.h"
#include "Camera.h"

Camera::Camera(int width, int height)
{
	mWidth = width;
	mHeight = height;

	mPosition = D3DXVECTOR3(.0f, .0f, .0f);
}

void Camera::SetPosition(float x, float y)
{
	mPosition = D3DXVECTOR3(x, y, .0f);
}

void Camera::SetPosition(D3DXVECTOR3 position)
{
	mPosition = position;
}

void Camera::SetPositionX(float val)
{
	mPosition.x = val;
}

void Camera::SetPositionY(float val)
{
	mPosition.y = val;
}

void Camera::AddPositionX(float val)
{
	mPosition.x += val;
}

void Camera::AddPositionY(float val)
{
	mPosition.y += val;
}

int Camera::GetWidth()
{
	return mWidth;
}

int Camera::GetHeight()
{
	return mHeight;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return mPosition;
}

RECT Camera::GetBound()
{
	RECT bound;

	bound.left = (long)(mPosition.x - mWidth / 2);
	bound.right = (long)(bound.left + mWidth);
	bound.top = (long)(mPosition.y - mHeight / 2);
	bound.bottom = (long)(bound.top + mHeight);

	return bound;
}

D3DXVECTOR2 Camera::GetTransform()
{
	return D3DXVECTOR2((long)(mWidth / 2 - GetPosition().x), (long)(mHeight / 2 - GetPosition().y));
}

Camera::~Camera()
{
}
