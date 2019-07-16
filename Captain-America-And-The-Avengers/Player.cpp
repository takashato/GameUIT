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
	mSprite = new Sprite(L"Resources\\Sprites\\Players\\Cap\\capnamerica.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Players\\Cap\\scripts.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Standing", "0"), 0.1F);
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.15F);
	mAniLowJumping = new Animation(mSprite, mAniScripts->GetRectList("LowJump", "0"), 0.15F);
	mCurrentAni = mAniStanding;
}

void Player::Update(float deltaTime)
{
	mCurrentAni->SetFlippedHorizontally(mDirection == Left);

	mCounter += deltaTime;
	if (mCounter > MOVEMENT_UPDATE_TIME)
	{
		if (GetVelocityX() != 0) {
			AddPositionX(GetVelocityX() * mCounter);
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

void Player::HandleKeyboard(Keyboard& keyboard)
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
		mCurrentAni = mAniLowJumping;
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
