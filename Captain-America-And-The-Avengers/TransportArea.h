#pragma once
#include "Enemy.h"

class TransportArea : public Entity
{
public:
	TransportArea(D3DXVECTOR3 position, int width, int height);
	~TransportArea() = default;

	void Draw(D3DXVECTOR2 trans);

	// Inherited via Entity
	virtual RECT GetBoundingBox() override;
	virtual CollidableObjectType GetCollidableObjectType() override;
};