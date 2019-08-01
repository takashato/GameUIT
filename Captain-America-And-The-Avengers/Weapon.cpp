#include "pch.h"
#include "Weapon.h"

Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

RECT Weapon::GetBoundingBox()
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

CollidableObjectType Weapon::GetCollidableObjectType()
{
	return EWeapon;
}

float Weapon::GetWidth()
{
	return 0.0f;
}

float Weapon::GetHeight()
{
	return 0.0f;
}

void Weapon::OnCollision(CollisionEvent* ce)
{
}
