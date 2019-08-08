#pragma once
#include "Entity.h"
#include "AnimationScript.h"
#include "Animation.h"

class BossRedAlert;

class Dynamite : public Entity
{
public:
	Dynamite(D3DXVECTOR3 position, int flyDirection = 1);
	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 trans);
	virtual RECT GetBoundingBox() override;
	virtual CollidableObjectType GetCollidableObjectType() override;
	void Throw();
	bool isThrown = false;
	bool pendingDelete = false;

	BossRedAlert* boss;
private:
	static Sprite* mSprite;
	static Animation* mAni;

	int flyDirection;

	D3DXVECTOR3 oldPos;

	static float DYNAMITE_VELO_X;
	static float DYNAMITE_VELO_Y;
	static float MAX_HEIGHT;
};