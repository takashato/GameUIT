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
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\GunStock.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\GunStock.xml");

	mAniRight = new Animation(mSprite, mAniScripts->GetRectList("Right", "0"), 0.1F);
	mAniBottomRightt = new Animation(mSprite, mAniScripts->GetRectList("BottomRight", "0"), 0.1F);
	mAniTop = new Animation(mSprite, mAniScripts->GetRectList("Top", "0"), 0.1F);
	mAniRotating = new Animation(mSprite, mAniScripts->GetRectList("Rotating", "0"), 0.01F);
	mAniTopRight = new Animation(mSprite, mAniScripts->GetRectList("TopRight", "0"), 0.1F);
	mAniBottom = new Animation(mSprite, mAniScripts->GetRectList("Bottom", "0"), 0.1F);
	mAniBottomLeft = new Animation(mSprite, mAniScripts->GetRectList("BottomLeft", "0"), 0.1F);
	mAniLeft = new Animation(mSprite, mAniScripts->GetRectList("Left", "0"), 0.1F);
	mAniTopLeft = new Animation(mSprite, mAniScripts->GetRectList("TopLeft", "0"), 0.1F);

	mCurrentAni = mAniRight;
}

void GunStock::Update(float deltaTime, Player* player)
{
	Enemy::Update(deltaTime, player);

	if (mCurrentAni == mAniRotating)
	{
		mIntervalCounter = .0f;
		mCounter += deltaTime;
		if (mCounter > 0.5f)
		{
			switch (lastState)
			{
			case GUNSTOCK_RIGHT_DIRECT:
				SetState(GUNSTOCK_BOTTOMRIGHT_DIRECT);
				break;
			case GUNSTOCK_BOTTOMRIGHT_DIRECT:
				SetState(GUNSTOCK_BOTTOM_DIRECT);
				break;
			case GUNSTOCK_BOTTOM_DIRECT:
				SetState(GUNSTOCK_BOTTOMLEFT_DIRECT);
				break;
			case GUNSTOCK_BOTTOMLEFT_DIRECT:
				SetState(GUNSTOCK_LEFT_DIRECT);
				break;
			case GUNSTOCK_LEFT_DIRECT:
				SetState(GUNSTOCK_TOPLEFT_DIRECT);
				break;
			case GUNSTOCK_TOPLEFT_DIRECT:
				SetState(GUNSTOCK_TOP_DIRECT);
				break;
			case GUNSTOCK_TOP_DIRECT:
				SetState(GUNSTOCK_TOPRIGHT_DIRECT);				
				break;
			case GUNSTOCK_TOPRIGHT_DIRECT:
				SetState(GUNSTOCK_RIGHT_DIRECT);
				break;
			}
			mCounter = 0;
		}
	}
	else // Not rotating
	{
		mIntervalCounter += deltaTime;
		if (mIntervalCounter >= BULLET_INTERVAL_TIME)
		{
			int flyDirectionX = 1;
			if (mState == GUNSTOCK_BOTTOMLEFT_DIRECT
				|| mState == GUNSTOCK_LEFT_DIRECT
				|| mState == GUNSTOCK_TOPLEFT_DIRECT) flyDirectionX = -1;
			else if (mState == GUNSTOCK_TOP_DIRECT
				|| mState == GUNSTOCK_BOTTOM_DIRECT) flyDirectionX = 0;

			int flyDirectionY = -1; 
			if (mState == GUNSTOCK_BOTTOMLEFT_DIRECT
				|| mState == GUNSTOCK_BOTTOMRIGHT_DIRECT
				|| mState == GUNSTOCK_BOTTOM_DIRECT) flyDirectionY = 1;
			else if (mState == GUNSTOCK_LEFT_DIRECT
				|| mState == GUNSTOCK_RIGHT_DIRECT) flyDirectionY = 0;

			auto position = GeoUtils::GetRectCenter(GetBoundingBox());

			SceneManager::GetInstance().GetScene()->GetGrid()->Add(
				new NormalBullet(position, flyDirectionX, flyDirectionY)
			);

			mIntervalCounter = .0f;
		}
	}
	if (mCurrentAni != nullptr) mCurrentAni->Update(deltaTime);
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
	case GUNSTOCK_BOTTOM_DIRECT:
		mCurrentAni = mAniBottom;
		break;
	case GUNSTOCK_BOTTOMLEFT_DIRECT:
		mCurrentAni = mAniBottomLeft;
		break;
	case GUNSTOCK_LEFT_DIRECT:
		mCurrentAni = mAniLeft;
		break;
	case GUNSTOCK_TOPLEFT_DIRECT:
		mCurrentAni = mAniTopLeft;
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
