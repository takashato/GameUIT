#pragma once
#include "Weapon.h"
#include "AnimationScript.h"
#include "Player.h"
#include "Camera.h"

#define SHIELD_IDLE_STATE 0
#define SHIELD_RUNSHIELD_STATE 1
#define SHIELD_HIGHSHIELD_STATE 2
#define SHIELD_SITSHIELD_STATE 3

class Shield : public Weapon
{
public:
	Shield();
	~Shield();

	void LoadAnimations();

	void Update(float deltaTime, Player* player);
	void Draw(D3DXVECTOR2 transform);

	int GetState();
	void SetState(int state);

	void ChangeAnimationByState(int state);

	void OnSetPosition();

	RECT GetBoundingBox();

	float CalYOfLinearEquation(float x1, float y1, float x2, float y2, float posX);

private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniIdle = NULL;
	Animation* mAniSitShield = NULL;
	Animation* mAniHighShield = NULL;
	Animation* mAniRunShield = NULL;
	int mState = -1;

	/*Camera* mCamera;*/
	float mCounter = 0;
	D3DXVECTOR3 throwPos;
	bool isThrown = false;
	bool flyDirection = 1;
	EntityDirection throwingStateDirection;
	float maxLengthFly;
	float YChangeDirection;
};

