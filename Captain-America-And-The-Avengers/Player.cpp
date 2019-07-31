#include "pch.h"
#include "Game.h"
#include "Player.h"

Player::Player() : Entity()
{	
	ExitIsOke = true; //Chua xu lí an cuc exit
	LoadAnimations();
	mState = new PlayerStandingState(this);
}

void Player::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Players\\Cap\\Captain America.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Players\\Cap\\Animation Captain America And Shield.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Standing", "0"), 0.1F);
	mAniPunching = new Animation(mSprite, mAniScripts->GetRectList("Punching", "0"), 0.15F);
	mAniThrowingShield = new Animation(mSprite, mAniScripts->GetRectList("ThrowingShield", "0"), 0.15F, false);
	mAniHighShielding = new Animation(mSprite, mAniScripts->GetRectList("HighShielding", "0"), 0.1F);
	mAniSitting = new Animation(mSprite, mAniScripts->GetRectList("Sitting", "0"), 0.1F);
	mAniLowPunching = new Animation(mSprite, mAniScripts->GetRectList("LowPunching", "0"), 0.15F);
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.15F);
	mAniLowJumping = new Animation(mSprite, mAniScripts->GetRectList("LowJump", "0"), 0.15F);
	mAniHighJumping = new Animation(mSprite, mAniScripts->GetRectList("HighJump", "0"), 0.05F);
	mAniKicking = new Animation(mSprite, mAniScripts->GetRectList("Kicking", "0"), 0.1F);
	mAniTakeDamage = new Animation(mSprite, mAniScripts->GetRectList("TakeDamage", "0"), 0.1F);
	mAniTakeDown = new Animation(mSprite, mAniScripts->GetRectList("TakeDown", "0"), 0.2F);
	mAniInvincibleStand = new Animation(mSprite, mAniScripts->GetRectList("InvincibleStand", "0"), 0.05F);
	mAniSurfing = new Animation(mSprite, mAniScripts->GetRectList("Surfing", "0"), 0.2F);
	mAniSittingOnShield = new Animation(mSprite, mAniScripts->GetRectList("SittingOnShield", "0"), 0.1F);
	mAniSwimming = new Animation(mSprite, mAniScripts->GetRectList("Swimming", "0"), 0.1F);
	mAniCling = new Animation(mSprite, mAniScripts->GetRectList("Cling", "0"), 0.2F);


	mCurrentAni = mAniStanding;
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime); // Update position

	if (mCurrentAni != NULL)
	{
		mCurrentAni->SetFlippedHorizontally(mDirection == Right);

		if (mCurrentAni == mAniSurfing)
		{
			if (mCurrentAni->GetCurrentFrame() != 1)
				mCurrentAni->Update(deltaTime);
		}
		else
			mCurrentAni->Update(deltaTime);

		UpdateSize();
	}

	if (mState != nullptr) mState->Update(deltaTime);
}

void Player::Draw(D3DXVECTOR2 trans)
{
	if (mCurrentAni != NULL) mCurrentAni->Draw(GetPosition(), trans);
	this->RenderBoundingBox(trans);
}

void Player::HandleKeyboard(Keyboard* keyboard)
{
	if (mState != nullptr)
	{
		mState->HandleKeyboard(keyboard);
	}
}

PlayerState* Player::GetState()
{
	return mState;
}

void Player::SetState(PlayerState *state)
{
	if (state == nullptr || this == (void*)0xDDDDDDDD) return;
	mLastState = mState->GetState();
	delete mState;
	mState = state;
	ChangeAnimationByState(mState->GetState());
}

EPlayerState Player::GetLastState()
{
	return mLastState;
}

Animation* Player::StateToAnimation(EPlayerState state)
{
	switch (state)
	{
	case EPlayerState::Standing:
		return mAniStanding;
	case EPlayerState::Jumping:
	case EPlayerState::Falling:
		return mAniLowJumping;
	case EPlayerState::HighJumping:
		return mAniHighJumping;
	case EPlayerState::Sitting:
		return mAniSitting;
	case EPlayerState::HighShielding:
		return mAniHighShielding;
	case EPlayerState::Punching:
		return mAniPunching;
	case EPlayerState::LowPunching:
		return mAniLowPunching;
	case EPlayerState::ThrowingShield:
		return mAniThrowingShield;
	case EPlayerState::Kicking:
		return mAniKicking;
	case EPlayerState::TakeDamage:
		return mAniTakeDamage;
	case EPlayerState::TakeDown:
		return mAniTakeDown;
	case EPlayerState::InvincibleStand:
		return mAniInvincibleStand;
	case EPlayerState::Surfing:
		return mAniSurfing;
	case EPlayerState::SittingOnShield:
		return mAniSittingOnShield;
	case EPlayerState::Swimming:
		return mAniSwimming;
	case EPlayerState::Cling:
		return mAniCling;
	case EPlayerState::Running:
	default:
		return mAniRunning;
	}
}

void Player::ChangeAnimationByState(EPlayerState state)
{
	mCurrentAni = StateToAnimation(state);
	mCurrentAni->Reset();
	UpdateSize();
}

Animation* Player::GetCurrentAnimation()
{
	return mCurrentAni;
}

void Player::OnSetPosition()
{
}

void Player::UpdateSize()
{
	// Dynamically set width, height
	SetWidth((float)mCurrentAni->GetWidth());
	SetHeight((float)mCurrentAni->GetHeight());
}

void Player::SetCamera(Camera* camera)
{
	mCamera = camera;
}

RECT Player::GetBoundingBox()
{
	if (mCurrentAni == nullptr) return RECT();

	RECT rect;
	rect.left = (long)mPosition.x;
	rect.top = (long)mPosition.y;
	rect.right = (long)(rect.left + GetWidth());
	rect.bottom = (long)(rect.top + GetHeight());

	return rect;
}

CollidableObjectType Player::GetCollidableObjectType()
{
	return EPlayer;
}

void Player::OnCollision(CollisionEvent* ce)
{
	mState->OnCollision(ce);
}
