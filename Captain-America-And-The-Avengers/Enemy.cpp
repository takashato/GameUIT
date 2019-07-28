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
	return RECT();
}

CollidableObjectType Enemy::GetCollidableObjectType()
{
	return EEnemy;
}

EnemyType Enemy::GetEnemyType()
{
	return EDefaultEnemy;
}
