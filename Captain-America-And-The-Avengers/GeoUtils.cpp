#include "pch.h"
#include "GeoUtils.h"

D3DXVECTOR3 GeoUtils::GetRectCenter(RECT rect)
{
	return D3DXVECTOR3((rect.left + rect.right) / 2.0f, (rect.top + rect.bottom) / 2.0f, .0f);
}
