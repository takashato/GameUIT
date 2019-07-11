#include "pch.h"
#include "Player.h"

Player::Player() : Entity()
{
	mAniNormal = new Animation(L"Resources\\Sprites\\Aladdin_normal.png", 20, 53, 1, 1, 0.1F);
	mAniRunning = new Animation(L"Resources\\Sprites\\Aladdin_run.png", 38, 55, 12, 1, 0.5F / 12);
	mCurrentAni = mAniNormal;

	mState = Normal;
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

PlayerState Player::GetState()
{
	return mState;
}

void Player::SetState(PlayerState state)
{
	mState = state;
	switch (mState)
	{
	case Running:
		mCurrentAni = mAniRunning;
		break;
	case Normal:
	default:
		mCurrentAni = mAniNormal;
		break;
	}
}

void Player::OnSetPosition()
{
}
