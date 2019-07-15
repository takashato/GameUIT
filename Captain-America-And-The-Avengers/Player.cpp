#include "pch.h"
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
	mCurrentAni = mAniStanding;
}

void Player::Update(float deltaTime)
{
	mCurrentAni->SetFlippedHorizontally(mDirection == Left);

	if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
}

void Player::Draw()
{
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
