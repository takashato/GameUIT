#include "pch.h"
#include "Game.h"
#include "BossRedAlert.h"
#include <cmath>

BossRedAlert::BossRedAlert(D3DXVECTOR3 position)
{
	mDirection = Left;
	LoadAnimations();
	SetPosition(position);
	mState = BOSSREDALERT_IDLE_STATE;
	SetVelocityX(0.f);
	SetVelocityY(0.f);
	mCenter = position;
	mCenter.y = mCenter.y + 15;
}


BossRedAlert::~BossRedAlert()
{
}

void BossRedAlert::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\BossRedAlert.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\BossRedAlert.xml");

	mAniIdle = new Animation(mSprite, mAniScripts->GetRectList("Idle", "0"), 0.1F);
	mAniTossTheBarrel = new Animation(mSprite, mAniScripts->GetRectList("TossTheBarrel", "0"), 1.F,false);

	mCurrentAni = mAniIdle;
}

void BossRedAlert::Update(float deltaTime, Player* player)
{


	Entity::Update(deltaTime);
	mCurrentAni->SetFlippedHorizontally(mDirection==Right);
	if (mState == BOSSREDALERT_IDLE_STATE)
	{
		CheckDirection(player);
		if (mCounter > 0.9f)
		{
			SetState(BOSSREDALERT_TOSS_THE_BARREL_STATE);
			mCounter = 0;
		}
	}
	if (mState == BOSSREDALERT_TOSS_THE_BARREL_STATE)
	{
		if (mCounter>3.f)//Neu thung thung no roi
		{
			mCurrentAni->Reset();
			SetState(BOSSREDALERT_IDLE_STATE);
			mCounter = 0;
		}
	}
	mCounter += deltaTime;
	
	mCurrentAni->Update(deltaTime);
}

void BossRedAlert::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentAni != nullptr && mState != -1)
	{
		mCurrentAni->Draw(GetPosition(), transform);
		this->RenderBoundingBox(transform);
	}
	else
	{
		mCurrentAni->Draw(GetPosition());
		this->RenderBoundingBox(D3DXVECTOR2(0, 0));
	}
}

int BossRedAlert::GetState()
{
	return mState;
}

void BossRedAlert::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void BossRedAlert::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case BOSSREDALERT_IDLE_STATE:
		mCurrentAni = mAniIdle;
		break;
	case BOSSREDALERT_TOSS_THE_BARREL_STATE:
		mCurrentAni = mAniTossTheBarrel;
	}
}

void BossRedAlert::OnSetPosition()
{
}

void BossRedAlert::CheckDirection(Player* player)
{
	if (player->GetPosition().x > mPosition.x + 20 && mDirection == Left)
	{
		mDirection = Right;
	}
	if (player->GetPosition().x < mPosition.x - 20 && mDirection == Right)
	{
		mDirection = Left;
	}

}
