#include "pch.h"
#include "Game.h"
#include "IronBar.h"

IronBar::IronBar(D3DXVECTOR3 position, float w, float h)
{
	mWidth = w; 
	mHeight = h;
	SetPosition(position);
	SetVelocityX(0.f);
	SetVelocityY(0.f);
}


IronBar::~IronBar()
{
}

void IronBar::Draw(D3DXVECTOR2 transform)
{
	this->RenderBoundingBox(transform);
}

void IronBar::OnSetPosition()
{
}

RECT IronBar::GetBoundingBox()
{
	RECT rect;
	rect.left = (long)mPosition.x;
	rect.top = (long)mPosition.y;
	rect.right = (long)(mWidth + mPosition.x);
	rect.bottom = (long)(mHeight + mPosition.y);
	return rect;
}

CollidableObjectType IronBar::GetCollidableObjectType()
{
	return EIronBar;
}