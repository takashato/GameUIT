#include "pch.h"
#include "SceneManager.h"
#include "Barrel.h"

Sprite* Barrel::mSprite = NULL;
AnimationScript* Barrel::mAniScripts = NULL;
Animation* Barrel::mAniBarrel = NULL;


Barrel::Barrel(D3DXVECTOR3 position, int flyDirection, float playerX, int flyDirectionY)
{
	LoadAnimations();
	mPosition = position;
	mState = 0;
	SetVelocityX(flyDirection * BULLET_SPEED);
	SetVelocityY(flyDirectionY * BULLET_SPEED);
	if (flyDirection == -1)
		mA = mPosition.x - playerX;
	else mA = playerX - mPosition.x;
	mFlyDirection = flyDirection;
	mFlyDirectionY = flyDirectionY;



	if (GeoUtils::IsIntersect(GetBoundingBox(), SceneManager::GetInstance().GetScene()->GetCamera()->GetBound())) {
		SoundManager::GetInstance().CPlaySound(SoundType::BossShootBigBullets);
	}
}

Barrel::~Barrel()
{
}

void Barrel::LoadAnimations()
{
	if (mSprite == nullptr)
	{
		mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\BossRedAlert2.png");
		mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\RedAlertBullet.xml");

		mAniBarrel = new Animation(mSprite, mAniScripts->GetRectList("Barrel", "0"), 0.1F);
	}

	mCurrentAni = mAniBarrel;
}

void Barrel::Update(float deltaTime)
{
	if (mDirection == -1)
	{
		if (mPosition.x>mA)
		{
			AddPositionX(deltaTime * mVelocityX);
			AddPositionY(deltaTime * mVelocityY);
		}
		else
		{
			AddPositionX(-mVelocityX * deltaTime);
			AddPositionY(-mVelocityY * deltaTime);
		}
	}
	else if (mDirection == 1)
	{
		if (mPosition.x < mA)
		{
			AddPositionX(deltaTime * mVelocityX);
			AddPositionY(deltaTime * mVelocityY);
		}
		else
		{
			AddPositionX(-mVelocityX * deltaTime);
			AddPositionY(-mVelocityY * deltaTime);
		}
	}
	if(mPosition.y>200)
		mState = 1;
	auto camBound = SceneManager::GetInstance().GetScene()->GetCamera()->GetBound();
	if (mPosition.x <= camBound.left + DELTA_CAM_TO_DESTROY
		|| mPosition.x >= camBound.right - DELTA_CAM_TO_DESTROY
		|| mPosition.y <= camBound.top + DELTA_CAM_TO_DESTROY
		|| mPosition.y >= camBound.bottom - DELTA_CAM_TO_DESTROY) // Out of camera
	{
		mState = 1; // Pending destroy
	}
}

void Barrel::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentAni != nullptr && mState != -1)
	{
		mCurrentAni->SetFlippedHorizontally(mFlyDirection == 1);
		mCurrentAni->Draw(GetPosition(), transform);
		this->RenderBoundingBox(transform);
	}
	else
	{
		mCurrentAni->Draw(GetPosition());
		this->RenderBoundingBox(D3DXVECTOR2(0, 0));
	}
}

int Barrel::GetState()
{
	return mState;
}

void Barrel::OnSetPosition()
{
	Bullet::OnSetPosition();
}

BulletType Barrel::GetBulletType()
{
	return BulletType::BBarrel;
}

void Barrel::HitShield()
{
	mIsHitShield = true;
}
