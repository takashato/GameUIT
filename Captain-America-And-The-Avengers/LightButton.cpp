#include "pch.h"
#include "LightButton.h"

LightButton::LightButton(D3DXVECTOR3 position)
{
	mPosition = position;
	mWidth = 16;
	mHeight = 16;
}

LightButton::~LightButton()
{
}

void LightButton::Draw(D3DXVECTOR2 trans)
{
	this->RenderBoundingBox(trans);
}

RECT LightButton::GetBoundingBox()
{
	RECT rect;
	rect.left = mPosition.x;
	rect.top = mPosition.y;
	rect.right = rect.left + mWidth;
	rect.bottom = rect.top + mHeight;
	return rect;
}

CollidableObjectType LightButton::GetCollidableObjectType()
{
	return CollidableObjectType::EButton;
}
