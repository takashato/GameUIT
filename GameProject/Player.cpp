#include "pch.h"
#include "Player.h"

Player::Player() : Entity()
{
	mAniNormal = new Animation(L"Resources\\Sprites\\Aladdin_normal.png", 20, 53, 1, 1, 0.1F);
	mAniRunning = new Animation(L"Resources\\Sprites\\Aladdin_run.png", 38, 55, 12, 1, 0.5F / 12);
	mCurrentAni = mAniNormal;

	mState = PLAYER_STATE_NORMAL;
}

void Player::Update(float deltaTime)
{
	if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
}

void Player::Draw()
{
	if (mCurrentAni != NULL) mCurrentAni->Draw(GetPosition());
}

PLAYER_STATE Player::GetState()
{
	return mState;
}

void Player::SetState(PLAYER_STATE state)
{
	mState = state;
	switch (mState)
	{
	case PLAYER_STATE_RUNNING:
		mCurrentAni = mAniRunning;
		break;
	case PLAYER_STATE_NORMAL:
	default:
		mCurrentAni = mAniNormal;
		break;

	}
}

void Player::OnSetPosition()
{
}
