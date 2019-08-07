#include "pch.h"
#include "Game.h"
#include "NormalBullet.h"

NormalBullet::NormalBullet(D3DXVECTOR3 position, int flyDirection)
{
	LoadAnimations();
	mPosition = position;
	position.y = position.y + 4;
	SetPosition(position);
	mState = NORMALBULLET_FLYING_STATE;
	SetVelocityX(flyDirection * BULLET_SPEED);

	if (GeoUtils::IsIntersect(GetBoundingBox(), SceneManager::GetInstance().GetScene()->GetCamera()->GetBound())) {
		SoundManager::GetInstance().CPlaySound(SoundType::BossShootSmallBullets);
	}
}

NormalBullet::~NormalBullet()
{
	delete mSprite;
	delete mAniScripts;
	delete mAniFlying;
}

void NormalBullet::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\NormalBullet.xml");

	mAniFlying = new Animation(mSprite, mAniScripts->GetRectList("Flying", "0"), 0.1F);

	mCurrentAni = mAniFlying;
}

void NormalBullet::Update(float deltaTime)
{
	if (!mIsHitShield)
	{
		AddPositionX(deltaTime * mVelocityX);
	}
	else
	{
		AddPositionY(-abs(mVelocityX) * deltaTime);
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

void NormalBullet::Draw(D3DXVECTOR2 transform)
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

int NormalBullet::GetState()
{
	return mState;
}

void NormalBullet::OnSetPosition()
{
	Bullet::OnSetPosition();
}

BulletType NormalBullet::GetBulletType()
{
	return BulletType::BNormalBullet;
}

void NormalBullet::HitShield()
{
	mIsHitShield = true;
}
