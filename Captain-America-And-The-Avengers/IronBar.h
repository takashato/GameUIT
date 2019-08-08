#pragma once
#include "Entity.h"

class IronBar : public Entity
{
public:
	IronBar(D3DXVECTOR3 position, float w, float h);
	~IronBar();

	void Draw(D3DXVECTOR2 transform);
	void OnSetPosition();
	RECT GetBoundingBox();
	CollidableObjectType GetCollidableObjectType();
};

