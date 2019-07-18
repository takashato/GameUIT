#include "pch.h"
#include "Game.h"
#include "Player.h"

Player::Player() : Entity()
{	
	LoadAnimations();
	mState = new PlayerStandingState(this);
	SetPosition(D3DXVECTOR3(100.0f, 30.0f, 0.f));
}

void Player::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Players\\Cap\\Captain America.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Players\\Cap\\Animation Captain America And Shield.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Standing", "0"), 0.1F);
	mAniPunching = new Animation(mSprite, mAniScripts->GetRectList("Punching", "0"), 0.15F);
	mAniHighShielding = new Animation(mSprite, mAniScripts->GetRectList("HighShielding", "0"), 0.1F);
	mAniSitting = new Animation(mSprite, mAniScripts->GetRectList("Sitting", "0"), 0.1F);
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.15F);
	mAniLowJumping = new Animation(mSprite, mAniScripts->GetRectList("LowJump", "0"), 0.15F);
	mAniHighJumping = new Animation(mSprite, mAniScripts->GetRectList("HighJump", "0"), 0.05F);

	mCurrentAni = mAniStanding;
}

void Player::Update(float deltaTime)
{
	if (mState != nullptr) mState->Update(deltaTime);

	mCurrentAni->SetFlippedHorizontally(mDirection == Right);

	mCounter += deltaTime;
	if (mCounter > MOVEMENT_UPDATE_TIME)
	{
		if (GetVelocityX() != .0f) {
			AddPositionX(GetVelocityX() * mCounter);
		}
		if (GetVelocityY() != .0f) {
			AddPositionY(GetVelocityY() * mCounter);
		}
		mCounter = 0;
	}


	if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
}

void Player::Draw()
{
	if (mCamera)
	{
		D3DXVECTOR2 trans = D3DXVECTOR2(Game::GetInstance().GetWidth() / 2 - mCamera->GetPosition().x,
			Game::GetInstance().GetHeight() / 2 - mCamera->GetPosition().y);
		if (mCurrentAni != NULL) mCurrentAni->Draw(GetPosition(), trans);
	}
	else
	{
		if (mCurrentAni != NULL) mCurrentAni->Draw(GetPosition());
	}
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

	delete mState;
	mState = state;
	ChangeAnimationByState(mState->GetState());
}

void Player::ChangeAnimationByState(EPlayerState state)
{
	switch (state)
	{
	case EPlayerState::Standing:
		mCurrentAni = mAniStanding;
		break;
	case EPlayerState::Jumping:
	case EPlayerState::Falling:
		mCurrentAni = mAniLowJumping;
		break;
	case EPlayerState::HighJumping:
		mCurrentAni = mAniHighJumping;
		break;
	case EPlayerState::Sitting:
		mCurrentAni = mAniSitting;
		break;
	case EPlayerState::HighShielding:
		mCurrentAni = mAniHighShielding;
		break;
	case EPlayerState::Punching:
		mCurrentAni = mAniPunching;
		break;
	case EPlayerState::Running:
	default:
		mCurrentAni = mAniRunning;
		break;
	}
}

void Player::OnSetPosition()
{
}

void Player::SetCamera(Camera* camera)
{
	mCamera = camera;
}
