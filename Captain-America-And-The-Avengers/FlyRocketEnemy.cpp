#include "pch.h"
#include "Game.h"
#include "FlyRocketEnemy.h"
#include <cmath>

FlyRocketEnemy::FlyRocketEnemy(D3DXVECTOR3 position, int subTypeID) 
{
	mSubTypeID = subTypeID;
	mDirection = Right;
	LoadAnimations();
	SetPosition(position);
	mState = FLYROCKETENEMY_FLY_STATE;
	SetVelocityX(0.f);
	SetVelocityY(0.f);
	//calculate ellipse //Mac dinh truc lon = 180 truc be = 52
	mCenterEllipse = D3DXVECTOR2(mPosition.x + 90, mPosition.y);
	mTransformEllipse = mCenterEllipse;
}


FlyRocketEnemy::~FlyRocketEnemy()
{
}

void FlyRocketEnemy::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\FlyRocketEnemy.xml");

	mAniFlying = new Animation(mSprite, mAniScripts->GetRectList("Flying", "0"), 0.1F);
	mAniGunning = new Animation(mSprite, mAniScripts->GetRectList("Flying", "0"), 0.11F);
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.1F);

	mCurrentAni = mAniFlying;
}

void FlyRocketEnemy::Update(float deltaTime, Player* player)
{


	Entity::Update(deltaTime);
	mCurrentAni->SetFlippedHorizontally(mDirection == Right);

	mCounter += deltaTime;
	CheckDirection(player);
	if (mPosition.x > (mCenterEllipse.x) + 85 && isShootOke == true &&mFlagMove==1) {
		isShootOke = false;
		
	}
	if (mState == FLYROCKETENEMY_GUN_STATE)
	{
		CheckDirection(player);
		if (mCounter > 0.9f)
		{
			SetState(FLYROCKETENEMY_FLY_STATE);
			mCounter = 0;
		}
	}
	if (mState == FLYROCKETENEMY_FLY_STATE)
	{
		//Mac dinh truc lon = 180 truc be = 52 
		//Ta se co elip (x-trans.x)^2/(180/2)^2+ (y-trans.y)^2/(52/2)^2
		//Khai trien y theo x tao dc phuong trinh y = sqrt(26*26*(1-(((x-trans.x)*(x-trans.x))/(90*90)))) + tran.y
		if (mFlagMove == -1)
		{
			if ((mPosition.x + (-50 * deltaTime)) < mCenterEllipse.x - 90)
			{
				isShootOke = true;
				SetVelocityX((-(mCenterEllipse.x - 90)+mPosition.x)/deltaTime);
				mFlagMove = -mFlagMove;

			}
			else if(mPosition.x< mCenterEllipse.x - 85)
				SetVelocityX(-25);
			else
				SetVelocityX(-50);
			mPosition.y = (sqrt(26 * 26 * (1 - (((mPosition.x - mTransformEllipse.x)*(mPosition.x - mTransformEllipse.x)) / (90 * 90)))) + mTransformEllipse.y);
		}
		else
		{
			if ((mPosition.x + (50 * deltaTime)) > mCenterEllipse.x + 90)
			{
				isShootOke = true;
				SetVelocityX(((mCenterEllipse.x + 90) - mPosition.x) / deltaTime);
				mFlagMove = -mFlagMove;
			}
			else if (mPosition.x > mCenterEllipse.x + 85)
				SetVelocityX(25);
			else SetVelocityX(50);
			mPosition.y = (-1 * sqrt(26 * 26 * (1 - (((mPosition.x - mTransformEllipse.x)*(mPosition.x - mTransformEllipse.x)) / (90 * 90)))) + mTransformEllipse.y);
		}
	}

	mCurrentAni->Update(deltaTime);
}

void FlyRocketEnemy::Draw(D3DXVECTOR2 transform)
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

int FlyRocketEnemy::GetState()
{
	return mState;
}

void FlyRocketEnemy::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void FlyRocketEnemy::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case FLYROCKETENEMY_FLY_STATE:
		mCurrentAni = mAniFlying;
		break;
	case FLYROCKETENEMY_GUN_STATE:
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		mCurrentAni = mAniGunning;
		break;
	case BOSS_CHARLESTON_DYING_STATE:
		mCurrentAni = mAniDying;
		break;
	}
}

void FlyRocketEnemy::OnSetPosition()
{
}


void FlyRocketEnemy::CheckDirection(Player* player)
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
EnemyType FlyRocketEnemy::GetEnemyType()
{
	return EnemyType::EFlyEnemy;
}
