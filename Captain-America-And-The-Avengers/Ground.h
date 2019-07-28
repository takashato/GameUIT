#pragma once
#include "Entity.h"

class Ground : public Entity
{
public:
	Ground(D3DXVECTOR3 position);
	~Ground();
	void LoadAnimations();

	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 transform);

	int GetState();
	void SetState(int state);

	void ChangeAnimationByState(int state);

	void OnSetPosition();

	RECT GetBoundingBox();
	CollidableObjectType GetCollidableObjectType() override;

private:
	int mState = -1;
};

