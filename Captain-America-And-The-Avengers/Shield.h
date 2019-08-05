#pragma once
#include "Weapon.h"
#include "AnimationScript.h"
#include "Enemy.h"
#include "Player.h"
#include "Capsule.h"
#include "SoundManager.h"

enum ShieldState {
	EShieldIdle,
	EShieldRun,
	EShieldHigh,
	EShieldSit
};

class GunStock;

class Shield : public Weapon
{
public:
	Shield(Player* player);
	~Shield();

	void LoadAnimations();

	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 transform);

	ShieldState GetState();
	void SetState(ShieldState state);

	void Throw();

	void ChangeAnimationByState(int state);

	void OnSetPosition();

	RECT GetBoundingBox();

	float CalYOfLinearEquation(float x1, float y1, float x2, float y2, float posX);

	float GetWidth();
	float GetHeight();

	D3DXVECTOR3 GetReturnPoint();
	ShieldState GetStateByPlayerState();
	bool IsThrown();

	void OnCollision(std::vector<CollisionEvent*>& cEvent);

private:
	Player* mPlayer = nullptr;

	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniIdle = NULL;
	Animation* mAniSitShield = NULL;
	Animation* mAniHighShield = NULL;
	Animation* mAniRunShield = NULL;
	ShieldState mState = EShieldIdle;

	/*Camera* mCamera;*/
	float mCounter = 0;
	D3DXVECTOR3 throwPos;
	bool isThrown = false;
	bool flyDirection = true;  // fly right
	EntityDirection throwingStateDirection;
	float maxLengthFly;
	float YChangeDirection;
};

