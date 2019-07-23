#include "pch.h"
#include "Game.h"
#include "GunEnemy.h"

GunEnemy::GunEnemy() : Entity()
{
	LoadAnimations();
	SetPosition(D3DXVECTOR3(100.0f, 30.0f, 0.f));
	mState = GUNENEMY_SITTING_STATE;
}


GunEnemy::~GunEnemy()
{
}

void GunEnemy::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\GunEnemy.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Standing", "0"), 0.1F);
	mAniSitting = new Animation(mSprite, mAniScripts->GetRectList("Sitting", "0"), 0.1F);
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.1F);

	mCurrentAni = mAniStanding;
}

void GunEnemy::Update(float deltaTime)
{

}

void GunEnemy::Draw()
{

}

int GunEnemy::GetState()
{
	return mState;
}

void GunEnemy::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void GunEnemy::ChangeAnimationByState(int state)
{

}

void GunEnemy::OnSetPosition()
{
}

void GunEnemy::SetCamera(Camera* camera)
{
	mCamera = camera;
}
