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

CollidableType Enemy::GetCollidableType()
{
	return EEnemy;
}

EnemyType Enemy::GetEnemyType()
{
	return EDefaultEnemy;
}
