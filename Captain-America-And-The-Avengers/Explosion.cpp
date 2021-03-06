#include "pch.h"
#include "Explosion.h"

AnimationScript* Explosion::mAniScripts = nullptr;
Sprite* Explosion::mSprite = nullptr;
Animation* Explosion::mAniExplosing = nullptr;

Explosion::Explosion(Entity* source)
{
	LoadAnimations();
	mPosition = source->GetPosition();
	SoundManager::GetInstance().CPlaySound(SoundType::Explosive);
}

Explosion::~Explosion()
{
}

void Explosion::LoadAnimations()
{
	if (mSprite == nullptr)
	{
		mSprite = new Sprite(L"Resources\\Sprites\\Players\\Cap\\Captain America.png");
		mAniScripts = new AnimationScript("Resources\\Sprites\\Item\\Explosion.xml");

		mAniExplosing = new Animation(mSprite, mAniScripts->GetRectList("Explosive", "0"), 0.2F, false);
	}

	mCurrentAni = mAniExplosing;
	mCurrentAni->Reset();
}

void Explosion::Update(float deltaTime)
{
	if (mCurrentAni->IsDoneCycle())
	{
		mGridNode->Remove(this);
		delete this;
	}
	else
		mCurrentAni->Update(deltaTime);
}

void Explosion::Draw(D3DXVECTOR2 transform)
{
	mCurrentAni->Draw(mPosition, transform);
	this->RenderBoundingBox(transform);
	//SoundManager::GetInstance().CPlaySound(SoundType::Explosive);
}

RECT Explosion::GetBoundingBox()
{
	RECT rect;
	rect.top = mPosition.y;
	rect.left = mPosition.x;
	rect.right = rect.left + mWidth;
	rect.bottom = rect.top + mHeight;
	return rect;
}

CollidableObjectType Explosion::GetCollidableObjectType()
{
	return CollidableObjectType::EExplosion;
}