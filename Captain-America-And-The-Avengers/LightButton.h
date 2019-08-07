#pragma once
#include "Entity.h"

class LightButton : public Entity
{
public:
	LightButton(D3DXVECTOR3 position);
	~LightButton();

	void Draw(D3DXVECTOR2 trans);

	virtual RECT GetBoundingBox() override;
	virtual CollidableObjectType GetCollidableObjectType() override;
};