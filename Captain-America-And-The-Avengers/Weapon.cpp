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
	return RECT();
}

CollidableObjectType Weapon::GetCollidableObjectType()
{
	return EWeapon;
}
