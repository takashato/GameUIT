#pragma once
#include "Animation.h"
#include "Ground.h"
#include "AnimationScript.h"
#include "Camera.h"

#define BREAKGROUND_IDLE_STATE 0
#define BREAKGROUND_BREAKING_STATE 1

class BreakGround : public Ground
{
public:
	BreakGround(D3DXVECTOR3 position);
	~BreakGround();

	void LoadAnimations();
	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 trans = D3DXVECTOR2(.0f, .0f));

	void OnSetPosition();

	void ChangeAnimationByState(int state);
	GroundType GetGroundType();
	RECT GetBoundingBox();
	int GetState();
	void SetState(int state);
private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;
	Animation* mCurrentAni = NULL;

	Animation* mAniIdle = NULL;
	Animation* mAniBreak = NULL;
	float mCounter = 0;
};

