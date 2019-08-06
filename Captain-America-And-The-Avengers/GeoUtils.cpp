#include "pch.h"
#include "GeoUtils.h"

D3DXVECTOR3 GeoUtils::GetRectCenter(RECT rect)
{
	return D3DXVECTOR3((rect.left + rect.right) / 2.0f, (rect.top + rect.bottom) / 2.0f, .0f);
}

bool GeoUtils::IsIntersect(RECT obj, RECT other)
{
	return obj.left < other.right && obj.right > other.left
		&& obj.top < other.bottom && obj.bottom > other.top;
}
