#include "pch.h"
#include "Game.h"
#include "GunStock.h"

GunStock::GunStock(D3DXVECTOR3 position)
{
	LoadAnimations();
	SetPosition(position);
	mState = GUNSTOCK_RIGHT_DIRECT;
}


GunStock::~GunStock()
{
}

void GunStock::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\GunStock.xml");

	mAniRight = new Animation(mSprite, mAniScripts->GetRectList("Right", "0"), 0.1F);
	mAniBottomRightt = new Animation(mSprite, mAniScripts->GetRectList("BottomRight", "0"), 0.1F);
	mAniTop = new Animation(mSprite, mAniScripts->GetRectList("Top", "0"), 0.1F);
	mAniRotating = new Animation(mSprite, mAniScripts->GetRectList("Rotating", "0"), 0.1F);
	mAniTopRight = new Animation(mSprite, mAniScripts->GetRectList("TopRight", "0"), 0.1F);

	mCurrentAni = mAniRight;
}

void GunStock::Update(float deltaTime, Player* player)
{
	Enemy::Update(deltaTime, player);

	if (mCurrentAni == mAniRotating)
	{
		mCounter += deltaTime;
		if (mCounter > 0.5f)
		{
			switch (lastState)
			{
			case GUNSTOCK_RIGHT_DIRECT:
				SetState(GUNSTOCK_BOTTOMRIGHT_DIRECT);
				break;
			case GUNSTOCK_BOTTOMRIGHT_DIRECT:
				SetState(GUNSTOCK_TOP_DIRECT);
				break;
			case GUNSTOCK_TOPRIGHT_DIRECT:
				SetState(GUNSTOCK_RIGHT_DIRECT);
				break;
			case GUNSTOCK_TOP_DIRECT:
				SetState(GUNSTOCK_TOPRIGHT_DIRECT);
				break;
			}
			mCounter = 0;
		}
	}
	if (mCurrentAni != nullptr) mCurrentAni->Update(deltaTime);
	if (mBullet != nullptr) mBullet->Update(deltaTime);
}

void GunStock::Draw(D3DXVECTOR2 transform)
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

int GunStock::GetState()
{
	return mState;
}

void GunStock::SetState(int state)
{
	lastState = mState;
	mState = state;
	ChangeAnimationByState(mState);
}

void GunStock::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case GUNSTOCK_RIGHT_DIRECT:
		mCurrentAni = mAniRight;
		break;
	case GUNSTOCK_BOTTOMRIGHT_DIRECT:
		mCurrentAni = mAniBottomRightt;
		break;
	case GUNSTOCK_ROTATING_STATE:
		mCurrentAni = mAniRotating;
		break;
	case GUNSTOCK_TOPRIGHT_DIRECT:
		mCurrentAni = mAniTopRight;
		break;
	case GUNSTOCK_TOP_DIRECT:
		mCurrentAni = mAniTop;
		break;
	}
}

void GunStock::OnSetPosition()
{
	Enemy::OnSetPosition();
}

EnemyType GunStock::GetEnemyType()
{
	return EnemyType::EGunStockEnemy;
}

Bullet* GunStock::GetBullet()
{
	return mBullet;
}

void GunStock::SetBullet(Bullet* bullet)
{
	mBullet = (NormalBullet*)bullet;
}


void GunStock::BeAttacked()
{
	SetState(GUNSTOCK_ROTATING_STATE);
}

//void GunStock::OnDie()
//{
//	ChangeAnimationByState(GUNENEMY_DYING_STATE);
//	mCurrentAni->Reset();
//}

//void GunStock::SetInvincible(bool val)
//{
//	Enemy::SetInvincible(val);
//	if (val)
//	{
//		mAniStanding->SetBlink(true);
//		mAniSitting->SetBlink(true);
//		mAniDying->SetBlink(true);
//		std::cout << "Blink on\n";
//	}
//	else
//	{
//		mAniStanding->SetBlink(false);
//		mAniSitting->SetBlink(false);
//		mAniDying->SetBlink(false);
//		std::cout << "Blink off\n";
//	}
//}
