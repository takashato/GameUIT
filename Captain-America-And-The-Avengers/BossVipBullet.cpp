#include "pch.h"
#include "SceneManager.h"
#include "BossVipBullet.h"

Sprite* BossVipBullet::mSprite = NULL;
AnimationScript* BossVipBullet::mAniScripts = NULL;
Animation* BossVipBullet::mAniFly = NULL;
Animation* BossVipBullet::mAniFlyDown = NULL;
Animation* BossVipBullet::mAniFlyLeftDown = NULL;

BossVipBullet::BossVipBullet(D3DXVECTOR3 position, int flyDirection, int flyDirectionY)
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
		mCurrentAni = mAniFlyDown;
	}
	else
	{
		mCurrentAni = mAniFly;
	}

	if (GeoUtils::IsIntersect(GetBoundingBox(), SceneManager::GetInstance().GetScene()->GetCamera()->GetBound())) {
		SoundManager::GetInstance().CPlaySound(SoundType::BossShootBigBullets);
	}
}

BossVipBullet::~BossVipBullet()
{
}

void BossVipBullet::LoadAnimations()
{
	if (mSprite == nullptr)
	{
		mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Boss_Wizard.png");
		mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\BossVipBullet.xml");

		mAniFly = new Animation(mSprite, mAniScripts->GetRectList("Fly", "0"), 0.1F);
		mAniFlyDown = new Animation(mSprite, mAniScripts->GetRectList("FlyDown", "0"), 0.1F);
		mAniFlyLeftDown = new Animation(mSprite, mAniScripts->GetRectList("FlyLeftDown", "0"), 0.1F);
	}

	mCurrentAni = mAniFly;
}

void BossVipBullet::Update(float deltaTime)
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

void BossVipBullet::Draw(D3DXVECTOR2 transform)
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

int BossVipBullet::GetState()
{
	return mState;
}

void BossVipBullet::OnSetPosition()
{
	Bullet::OnSetPosition();
}

BulletType BossVipBullet::GetBulletType()
{
	return BulletType::BBossVipBullet;
}

void BossVipBullet::HitShield()
{
	mIsHitShield = true;
}
