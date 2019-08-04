#pragma once

namespace GeoUtils
{
	D3DXVECTOR3 GetRectCenter(RECT rect);
	bool IsIntersect(RECT obj, RECT other);
}