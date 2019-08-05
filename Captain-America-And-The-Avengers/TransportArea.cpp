#include "pch.h"
#include "TransportArea.h"

TransportArea::TransportArea(D3DXVECTOR3 position, int width, int height)
{
	mPosition = position;
	mWidth = width;
	mHeight = height;
}

RECT TransportArea::GetBoundingBox()
{
	RECT rect;
	rect.top = mPosition.y;
	rect.left = mPosition.x;
	rect.right = rect.left + mWidth;
	rect.bottom = rect.top + mHeight;
	return rect;
}

CollidableObjectType TransportArea::GetCollidableObjectType()
{
	return CollidableObjectType::ETransportArea;
}
