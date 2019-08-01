#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

RECT Enemy::GetBoundingBox()
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

CollidableObjectType Enemy::GetCollidableObjectType()
{
	return EEnemy;
}

EnemyType Enemy::GetEnemyType()
{
	return EDefaultEnemy;
}

Bullet* Enemy::GetBullet()
{
	return mBullet;
}
