#include "pch.h"
#include "Bullet.h"
#include "SceneManager.h"

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
	auto grid = SceneManager::GetInstance().GetScene()->GetGrid();
	if (grid != nullptr)
	{
		grid->Move(this);
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
