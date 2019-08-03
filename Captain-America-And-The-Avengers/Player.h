#pragma once
#include "Animation.h"
#include "Entity.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "PlayerStanding.h"
#include "AnimationScript.h"
#include "Camera.h"

class Shield;

class Player : public Entity
{
public:
	Player();
	void LoadAnimations();

	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 trans = D3DXVECTOR2(.0f, .0f));
	void HandleKeyboard(Keyboard* keyboard);

	void OnKeyDown(BYTE code);
	void OnKeyUp(BYTE code);

	PlayerState* GetState();
	void SetState(EPlayerState state);
	EPlayerState GetLastState();

	Animation* StateToAnimation(EPlayerState state);
	void ChangeAnimationByState(EPlayerState state);
	Animation* GetCurrentAnimation();

	void OnSetPosition();
	void UpdateSize();

	RECT GetBoundingBox();
	CollidableObjectType GetCollidableObjectType();

	void OnCollision(std::vector<CollisionEvent*>& cEvent);

	Shield* GetShield();
	void SetShield(Shield* shield);


	Animation* mAniStanding = NULL;
	Animation* mAniPunching = NULL;
	Animation* mAniThrowingShield = NULL;
	Animation* mAniHighShielding = NULL;
	Animation* mAniRunning = NULL;
	Animation* mAniLowJumping = NULL;
	Animation* mAniHighJumping = NULL;
	Animation* mAniSitting = NULL;
	Animation* mAniLowPunching = NULL;
	Animation* mAniKicking = NULL;
	Animation* mAniTakeDamage = NULL;
	Animation* mAniTakeDown = NULL;
	Animation* mAniInvincibleStand = NULL;
	Animation* mAniSurfing = NULL;
	Animation* mAniSittingOnShield = NULL;
	Animation* mAniSwimming = NULL;
	Animation* mAniCling = NULL;

	bool shouldFall = false;
private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mCurrentAni = NULL;

	PlayerState* mState;
	friend class PlayerStanding;		PlayerStanding mStateStanding;

	EPlayerState mLastState;

	Shield* mShield = nullptr;

	float mCounter;

	bool ExitIsOke;//Chap nhan qua man khi an cuc exit
};