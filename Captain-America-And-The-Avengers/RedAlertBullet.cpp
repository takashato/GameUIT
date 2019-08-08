#include "pch.h"
#include "SceneManager.h"
#include "RedAlertBullet.h"

Sprite* RedAlertBullet::mSprite = NULL;
AnimationScript* RedAlertBullet::mAniScripts = NULL;
Animation* RedAlertBullet::mAniFly = NULL;


RedAlertBullet::RedAlertBullet(D3DXVECTOR3 position, int flyDirection, int flyDirectionY)
{
	LoadAnimations();
	mPosition = position;
	mState = 0;
	SetVelocityX(flyDirection * BULLET_SPEED);
	SetVelocityY(flyDirectionY * BULLET_SPEED);

	mFlyDirection = flyDirection;
	mFlyDirectionY = flyDirectionY;

	if (flyDirectionY == 1)
	{
		//---------
	}
	else
	{
		mCurrentAni = mAniFly;
	}

	if (GeoUtils::IsIntersect(GetBoundingBox(), SceneManager::GetInstance().GetScene()->GetCamera()->GetBound())) {
		SoundManager::GetInstance().CPlaySound(SoundType::BossShootBigBullets);
	}
}

RedAlertBullet::~RedAlertBullet()
{
}

void RedAlertBullet::LoadAnimations()
{
	if (mSprite == nullptr)
	{
		mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\BossRedAlert2.png");
		mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\RedAlertBullet.xml");

		mAniFly = new Animation(mSprite, mAniScripts->GetRectList("Fly", "0"), 0.1F);
	}

	mCurrentAni = mAniFly;
}

void RedAlertBullet::Update(float deltaTime)
{
	if (!mIsHitShield)
	{
		AddPositionX(deltaTime * mVelocityX);
		AddPositionY(deltaTime * mVelocityY);
	}
	else
	{
		AddPositionX(-mVelocityX * deltaTime);
		if (mVelocityY == 0.0f)
			AddPositionY(BULLET_SPEED * deltaTime);
		else
			AddPositionY(-mVelocityY * deltaTime);
	}

	auto camBound = SceneManager::GetInstance().GetScene()->GetCamera()->GetBound();
	if (mPosition.x <= camBound.left + DELTA_CAM_TO_DESTROY
		|| mPosition.x >= camBound.right - DELTA_CAM_TO_DESTROY
		|| mPosition.y <= camBound.top + DELTA_CAM_TO_DESTROY
		|| mPosition.y >= camBound.bottom - DELTA_CAM_TO_DESTROY) // Out of camera
	{
		mState = 1; // Pending destroy
	}
}

void RedAlertBullet::Draw(D3DXVECTOR2 transform)
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

int RedAlertBullet::GetState()
{
	return mState;
}

void RedAlertBullet::OnSetPosition()
{
	Bullet::OnSetPosition();
}

BulletType RedAlertBullet::GetBulletType()
{
	return BulletType::BRedAlertBullet;
}

void RedAlertBullet::HitShield()
{
	mIsHitShield = true;
}
