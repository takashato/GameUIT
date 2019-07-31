#pragma once
#include "Animation.h"
#include "Entity.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
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

	PlayerState* GetState();
	void SetState(PlayerState* state);
	EPlayerState GetLastState();

	Animation* StateToAnimation(EPlayerState state);
	void ChangeAnimationByState(EPlayerState state);
	Animation* GetCurrentAnimation();

	void OnSetPosition();
	void UpdateSize();

	void SetCamera(Camera* camera);

	RECT GetBoundingBox();
	CollidableObjectType GetCollidableObjectType();

	void OnCollision(CollisionEvent* ce);

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
	EPlayerState mLastState;

	Shield* mShield = nullptr;

	Camera* mCamera;

	float mCounter;

	bool ExitIsOke;//Chap nhan qua man khi an cuc exit
};