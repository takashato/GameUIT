#pragma once
#include "Entity.h"

class Ground : public Entity
{
public:
	Ground(D3DXVECTOR3 position, GroundType groundType = EGroundNormal, int width = 16, int height = 16);
	~Ground();
	void LoadAnimations();

	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 transform);

	int GetState();
	void SetState(int state);

	void ChangeAnimationByState(int state);

	void OnSetPosition();

	GroundType GetGroundType();

	RECT GetBoundingBox();
	CollidableObjectType GetCollidableObjectType();
	bool isCollidedWithPlayer = false;
protected:
	int mState = -1;
	GroundType mGroundType;
};

