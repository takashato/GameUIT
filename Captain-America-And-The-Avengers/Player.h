#pragma once
#include "Animation.h"
#include "Entity.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "PlayerStanding.h"
#include "PlayerRunning.h"
#include "PlayerJumping.h"
#include "PlayerFalling.h"
#include "PlayerSitting.h"
#include "PlayerHighJumping.h"
#include "PlayerThrowing.h"
#include "PlayerHighShielding.h"
#include "PlayerLowPunching.h"
#include "PlayerPunching.h"
#include "PlayerSitOnShield.h"
#include "PlayerSwimming.h"
#include "PlayerKicking.h"
#include "PlayerTakeDamage.h"
#include "PlayerTakeDown.h"
#include "PlayerCling.h"
#include "PlayerHealth.h"
#include "ExitSignal.h"
#include "PlayerSurfing.h"
#include "AnimationScript.h"
#include "Camera.h"

class Shield;

class Player : public Entity
{
	friend class PlayerHealth;
	friend class ExitSignal;
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

	bool OnCollision(std::vector<CollisionEvent*>& cEvent);
	bool CheckAABB(std::set<Entity*> &entities);

	Shield* GetShield();
	void SetShield(Shield* shield);

	void TakeDamage(int modifier = 1);
	PlayerHealth& GetHealth() { return mHealth; }
	
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
	Animation* mAniDiving = NULL;
	Animation* mAniHealth = NULL;
	Animation* mAniExitSignal = NULL;
	Animation* mAniElectricShock = NULL;

	bool shouldFall = false;

	bool canTransport = false;
private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mCurrentAni = NULL;

	PlayerState* mState;
	friend class PlayerStanding;		PlayerStanding mStateStanding;
	friend class PlayerRunning;			PlayerRunning mStateRunning;
	friend class PlayerJumping;			PlayerJumping mStateJumping;
	friend class PlayerHighJumping;		PlayerHighJumping mStateHighJumping;
	friend class PlayerFalling;			PlayerFalling mStateFalling;
	friend class PlayerSitting;			PlayerSitting mStateSitting;
	friend class PlayerThrowing;		PlayerThrowing mStateThrowing;
	friend class PlayerHighShielding;	PlayerHighShielding mStateHighShielding;
	friend class PlayerLowPunching;		PlayerLowPunching mStateLowPunching;
	friend class PlayerPunching;		PlayerPunching mStatePunching;
	friend class PlayerSitOnShield;		PlayerSitOnShield mStateSitOnShield;
	friend class PlayerSwimming;		PlayerSwimming mStateSwimming;
	friend class PlayerKicking;			PlayerKicking mStateKicking;
	friend class PlayerTakeDamage;		PlayerTakeDamage mStateTakeDamage;
	friend class PlayerTakeDown;		PlayerTakeDown mStateTakeDown;
	friend class PlayerSurfing;			PlayerSurfing mStateSurfing;
	friend class PlayerCling;			PlayerCling mStateCling;

	EPlayerState mLastState;

	Shield* mShield = nullptr;

	float mCounter;

	bool jumpThrough = false;
	Entity* skipGround = nullptr;

	EntityDirection mDirectionUnblock;

	bool mIsCollisionLeftRightSide;
	bool mIsCollectKeyCrystal;//Chap nhan qua man khi an cuc exit

	PlayerHealth mHealth;
	ExitSignal mExitSignal;
	bool mIsInvincible = false;
	float mInvincibleCounter = .0f;

	bool collideWithMovingGround = false;

	BYTE lastKeyUp, lastKeyDown;
	std::chrono::time_point<std::chrono::steady_clock> lastKeyUpTimePoint, lastKeyDownTimePoint;

	static constexpr auto PLAYER_HITBOX_HALF = 5;
	static constexpr auto INVINCIBLE_DURATION = 2;
};