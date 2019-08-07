#include "pch.h"
#include "Bullet.h"

Sprite* Bullet::mSprite = NULL;

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
	return EBullet;
}

BulletType Bullet::GetBulletType()
{
	return BDefaultBullet;
}

void Bullet::OnSetPosition()
{
	if (Grid::instance != nullptr)
	{
		Grid::instance->Move(this);
	}
}

void Bullet::HitShield()
{
	mIsHitShield = true;
}

void Bullet::SetState(int state)
{
	mState = state;
}
