#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime, Player* player)
{
	if (mIsInvincible)
	{
		mInvincibleCounter += deltaTime;
		if (mInvincibleCounter >= 0.5f)
		{
			mInvincibleCounter = .0f;
			SetInvincible(false);
		}
	}
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

void Enemy::TakeDamage(Entity* source, int hp)
{
	if (!mIsInvincible) // Can take damage!
	{
		if (source->GetCollidableObjectType() == EWeapon) // Damage done by weapon!
		{
			//mHP -= hp;
			if (mHP <= 0)
			{
				OnDie();
			}
			else
			{
				OnAttacked();
			}
		}
	}
}

void Enemy::SetInvincible(bool val)
{
	mIsInvincible = val;
}

void Enemy::OnAttacked()
{
}

void Enemy::OnDie()
{
}

void Enemy::OnSetPosition()
{
	if (Grid::instance != nullptr)
	{
		Grid::instance->Move(this);
	}
}
