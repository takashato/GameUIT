#include "pch.h"
#include "Game.h"
#include "NormalBullet.h"

NormalBullet::NormalBullet(D3DXVECTOR3 position) : Bullet()
{
	LoadAnimations();
	SetPosition(position);
	mState = NORMALBULLET_FLYING_STATE;
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\NormalBullet.xml");

	mAniFlying = new Animation(mSprite, mAniScripts->GetRectList("Flying", "0"), 0.1F);

	mCurrentAni = mAniFlying;
}

void NormalBullet::Update(float deltaTime, GunEnemy* gunEnemy)
{
	D3DXVECTOR3 gunEnemyPosition = gunEnemy->GetPosition();

	if (gunEnemy->GetState() == GUNENEMY_STANDING_STATE)
	{
		isDraw = true;
		if (gunEnemy->GetDirection() == Left)
		{
			if (GetVelocityX() > -100)
				AddVelocityX(-15);
			if (GetVelocityX() != 0.f)
				AddPositionX(GetVelocityX()*0.08);
		}
		else
		{
			if (GetVelocityX() < 100)
				AddVelocityX(15);
			if (GetVelocityX() != 0.f)
				AddPositionX(GetVelocityX()*0.08);
		}
	}
	else
	{
		gunEnemyPosition.y = gunEnemyPosition.y - 12;
		SetPosition(gunEnemyPosition);
		isDraw = false;
	}
}

void NormalBullet::Draw(D3DXVECTOR2 transform)
{
	if (isDraw)
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
}

int NormalBullet::GetState()
{
	return mState;
}

void NormalBullet::OnSetPosition()
{
}

BulletType NormalBullet::GetBulletType()
{
	return BulletType::BNormalBullet;
}
