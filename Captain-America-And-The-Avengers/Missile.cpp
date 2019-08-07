#include "pch.h"
#include "Missile.h"
#include "SceneManager.h"

Sprite* Missile::mSprite = NULL;
AnimationScript* Missile::mAniScripts = NULL;
Animation* Missile::mAniFlying = NULL;

Missile::Missile(D3DXVECTOR3 position, int flyDirection, int flyDirectionY)
{
	LoadAnimations();
	mPosition = position;
	orginalPos = position;
	mState = 0;
	SetVelocityX(flyDirection * BULLET_SPEED);
	SetVelocityY(flyDirectionY * BULLET_SPEED);

	if (GeoUtils::IsIntersect(GetBoundingBox(), SceneManager::GetInstance().GetScene()->GetCamera()->GetBound())) {
		SoundManager::GetInstance().CPlaySound(SoundType::BeAttack);
	}
}

Missile::~Missile()
{
}

void Missile::LoadAnimations()
{
	if (mSprite == nullptr)
	{
		mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
		mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\MissileOfMissileEnemy.xml");

		mAniFlying = new Animation(mSprite, mAniScripts->GetRectList("Left", "0"), 0.1F);
	}

	mCurrentAni = mAniFlying;
}

void Missile::Update(float deltaTime)
{
	if (!mIsHitShield)
	{
		AddPositionX(deltaTime * mVelocityX);
		AddPositionY(deltaTime * mVelocityY);
	}
	else
	{
		if (mVelocityY == 0.0f)
		{
			AddPositionY(-abs(mVelocityX) * deltaTime);
		}
		else
		{
			AddPositionX(-mVelocityX * deltaTime);
			AddPositionY(-mVelocityY * deltaTime);
		}
	}

	if (abs(orginalPos.x - mPosition.x) >= 200.0f) // Max length
	{
		mState = 1; // Pending destroy
		SceneManager::GetInstance().GetScene()->GetGrid()->Add(new Explosion(this));
	}
}

void Missile::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentAni != nullptr && mState != -1)
	{
		mCurrentAni->SetFlippedHorizontally(mVelocityX > 0.0f);
		mCurrentAni->Draw(GetPosition(), transform);
		this->RenderBoundingBox(transform);
	}
	else
	{
		mCurrentAni->Draw(GetPosition());
		this->RenderBoundingBox(D3DXVECTOR2(0, 0));
	}
}

int Missile::GetState()
{
	return mState;
}

void Missile::OnSetPosition()
{
	Bullet::OnSetPosition();
}

BulletType Missile::GetBulletType()
{
	return BulletType::BLittleMissile;
}

void Missile::HitShield()
{
	mIsHitShield = true;
}
