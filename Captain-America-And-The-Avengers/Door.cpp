#include "pch.h"
#include "Door.h"

Door::Door(D3DXVECTOR3 position, std::string name)
{
	mPosition = position;
	mWidth = 23;
	mHeight = 43;
	doorName = name;
}

Door::~Door()
{
}

void Door::Draw(D3DXVECTOR2 trans)
{
	this->RenderBoundingBox(trans);
}

RECT Door::GetBoundingBox()
{
	RECT rect;
	rect.left = mPosition.x;
	rect.top = mPosition.y;
	rect.right = rect.left + mWidth;
	rect.bottom = rect.top + mHeight;
	return rect;
}

CollidableObjectType Door::GetCollidableObjectType()
{
	return CollidableObjectType::EDoor;
}
