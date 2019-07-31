#pragma once
#include "Entity.h"
#include "Animation.h"

class Weapon : public Entity 
{
public:
	Weapon();
	~Weapon();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(D3DXVECTOR2 transform) = 0;
	virtual RECT GetBoundingBox();
	virtual CollidableObjectType GetCollidableObjectType() override;

	virtual float GetWidth();
	virtual float GetHeight();

protected:
	Animation* mCurrentAni = NULL;
};

