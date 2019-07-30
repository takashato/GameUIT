#pragma once
#include "Entity.h"
#include "Player.h"

class Weapon : public Entity 
{
public:
	Weapon();
	~Weapon();

	virtual void Update(float deltaTime, Player* player) = 0;
	virtual void Draw(D3DXVECTOR2 transform) = 0;
	virtual RECT GetBoundingBox();
	virtual CollidableObjectType GetCollidableObjectType() override;
protected:
	Animation* mCurrentAni = NULL;
};

