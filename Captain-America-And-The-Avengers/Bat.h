#pragma once
#include "Animation.h"
#include "Enemy.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"

#define BAT_SWING_STATE 0
#define BAT_FLY_STATE 1
#define BAT_COCOON_SATTE 2
#define BAT_FLYWITHSHOCK_STATE 3




class Bat : public Enemy
{
public:
	Bat(D3DXVECTOR3 position);
	~Bat();
	void LoadAnimations();

	void Update(float deltaTime, Player* player);
	void Draw(D3DXVECTOR2 transform);

	int GetState();
	void SetState(int state);

	void ChangeAnimationByState(int state);

	void OnSetPosition();

	EnemyType GetEnemyType();
	void CheckDirection(Player* player);



private:
	D3DXVECTOR3 mCenter;
	bool isDown = true;
	int amplitudeA = 63, amplitudeB = 23;
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniSwing = NULL;
	Animation* mAniFlying = NULL;
	Animation* mAniCocoon = NULL;
	Animation* mAniFlyWithShock = NULL;
	int mState = -1;

	float mCounter = 0;
};

