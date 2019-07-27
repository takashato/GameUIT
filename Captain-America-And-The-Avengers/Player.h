#pragma once
#include "Animation.h"
#include "Entity.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"

class Player : public Entity
{
public:
	Player();
	void LoadAnimations();

	void Update(float deltaTime);
	void Draw();
	void HandleKeyboard(Keyboard* keyboard);

	PlayerState* GetState();
	void SetState(PlayerState* state);

	void ChangeAnimationByState(EPlayerState state);

	void OnSetPosition();

	void SetCamera(Camera* camera);

	RECT GetBoundingBox();
	CollidableType GetCollidableType();

	void CheckCollision(std::list<Entity*> entities);

private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;
	
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

	Animation* mCurrentAni = NULL;

	PlayerState* mState;

	Camera* mCamera;

	float mCounter;

	bool ExitIsOke;//Chap nhan qua man khi an cuc exit
};