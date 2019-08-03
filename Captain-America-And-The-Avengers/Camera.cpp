#include "pch.h"
#include "Camera.h"

static constexpr auto LEFT_APPEND = 14.0f;
static constexpr auto TOP_APPEND = 55.0f;
static constexpr auto RIGHT_APPEND = 14.0f;
static constexpr auto BOTTOM_APPEND = 63.0f;

Camera::Camera(int width, int height)
{
	mWidth = width;
	mHeight = height;

	mPosition = D3DXVECTOR3(.0f, .0f, .0f);
}

void Camera::Update(D3DXVECTOR3 position)
{
	if (!mIsLocked)
	{
		D3DXVECTOR3 cc = GetPosition();
		if (position.x < cc.x - LEFT_APPEND)
		{
			SetPositionX((int)(LEFT_APPEND + position.x));
		}
		else if (position.x > cc.x + RIGHT_APPEND)
		{
			SetPositionX((int)(position.x - LEFT_APPEND));
		}

		if (position.y < cc.y - TOP_APPEND)
		{
			SetPositionY((int)(TOP_APPEND + position.y));
		}
		else if (position.y > cc.y + BOTTOM_APPEND)
		{
			SetPositionY((int)(position.y - BOTTOM_APPEND));
		}
		
		if (GetBound().left < 0)
		{
			SetPosition(GetWidth() / 2, (int)GetPosition().y);
		}

		if (GetBound().right > mWorldBoundary.right)
		{
			SetPosition(mWorldBoundary.right - GetWidth() / 2,
				(int)GetPosition().y);
		}

		if (GetBound().top < 0)
		{
			SetPosition((int)GetPosition().x, GetHeight() / 2);
		}

		if (GetBound().bottom > mWorldBoundary.bottom)
		{
			SetPosition((int)GetPosition().x,
				mWorldBoundary.bottom - GetHeight() / 2);
		}
	}
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

void Camera::SetLock(bool lock)
{
	mIsLocked = lock;
}

void Camera::SetWorldBoundary(RECT boundary)
{
	mWorldBoundary = boundary;
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

D3DXVECTOR3 Camera::GetCenter()
{
	return GeoUtils::GetRectCenter(GetBound());
}

D3DXVECTOR2 Camera::GetTransform()
{
	return D3DXVECTOR2((long)(mWidth / 2 - GetPosition().x), (long)(mHeight / 2 - GetPosition().y));
}

Camera::~Camera()
{
}
