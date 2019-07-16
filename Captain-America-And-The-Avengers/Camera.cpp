#include "pch.h"
#include "Camera.h"

Camera::Camera(int width, int height)
{
	mWidth = width;
	mHeight = height;

	mPosition = D3DXVECTOR3(.0f, .0f, .0f);
}

void Camera::SetPosition(int x, int y)
{
	mPosition = D3DXVECTOR3(1.0f * x, 1.0f * y, .0f);
}

void Camera::SetPosition(D3DXVECTOR3 position)
{
	mPosition = position;
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

	bound.left = mPosition.x - mWidth / 2.0f;
	bound.right = 1.0f * bound.left + mWidth;
	bound.top = mPosition.y - mHeight / 2.0f;
	bound.bottom = 1.0f * bound.top + mHeight;

	return bound;
}

Camera::~Camera()
{
}
