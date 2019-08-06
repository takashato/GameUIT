#pragma once
#include "Animation.h"
#include "Entity.h"
#include "AnimationScript.h"
#include "Camera.h"

#define DYNAMICGROUND_IDLE_STATE 0

class DynamicGround : public Entity
{
	static constexpr auto FLY_SPEED = 35.0f;

public:
	DynamicGround(D3DXVECTOR3 position = D3DXVECTOR3(344.0f, 416.0f, 0.f), int subTypeID = 1);
	~DynamicGround();

	void LoadAnimations();
	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 trans = D3DXVECTOR2(.0f, .0f));

	void OnSetPosition();

	RECT GetBoundingBox();
	CollidableObjectType GetCollidableObjectType();
	GroundType GetGroundType();
private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;
	Animation* mCurrentAni = NULL;

	Animation* mAniIdle = NULL;
	D3DXVECTOR3 center = D3DXVECTOR3(150.0f, 390.0f, 0.f);
	int mState;
	int mLastState;
	int mSubTypeID;
	float mCounter = 0;
};

