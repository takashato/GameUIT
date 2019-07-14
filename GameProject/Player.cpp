#include "pch.h"
#include "Player.h"

Player::Player() : Entity()
{
	mAniStanding = new Animation(L"Resources\\Sprites\\Players\\Cap\\stand.png", 25, 45, 1, 1, 0.1F);
	mAniRunning = new Animation(L"Resources\\Sprites\\Players\\Cap\\run_shield.png", 51, 43, 2, 1, 0.2F);
	mCurrentAni = mAniStanding;

	mState = new PlayerStandingState(this);
	SetPosition(D3DXVECTOR3(100.0f, 30.0f, 0.f));
}

void Player::Update(float deltaTime)
{
	mCurrentAni->SetFlippedHorizontally(mDirection == Left);

	if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
}

void Player::Draw()
{
	//auto nPosition = GetPosition() + D3DXVECTOR3(mCurrentAni->GetWidth() / 2, mCurrentAni->GetHeight() / 2, .0F);
	if (mCurrentAni != NULL) mCurrentAni->Draw(GetPosition());
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
	case EPlayerState::Running:
	default:
		mCurrentAni = mAniRunning;
		break;
	}
}

void Player::OnSetPosition()
{
}
