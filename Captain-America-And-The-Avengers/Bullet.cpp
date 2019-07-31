#include "pch.h"
#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

RECT Bullet::GetBoundingBox()
{
	if (mCurrentAni == nullptr) {
		return RECT();
	}

	RECT bb;
	bb.left = mPosition.x;
	bb.top = mPosition.y;
	bb.right = mPosition.x + mCurrentAni->GetWidth();
	bb.bottom = mPosition.y + mCurrentAni->GetHeight();
	return bb;
}

CollidableObjectType Bullet::GetCollidableObjectType()
{
	return EEnemy;
}

BulletType Bullet::GetBulletType()
{
	return BDefaultBullet;
}