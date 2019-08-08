#include "pch.h"
#include "SceneManager.h"
#include "Dynamite.h"

Sprite* Dynamite::mSprite = nullptr;
Animation* Dynamite::mAni = nullptr;

float Dynamite::DYNAMITE_VELO_X = 40.0f;
float Dynamite::DYNAMITE_VELO_Y = 100.0f;
float Dynamite::MAX_HEIGHT = 50.0f;

Dynamite::Dynamite(D3DXVECTOR3 position, int flyDirection)
{
	if (mSprite == nullptr)
	{
		mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\BossRedAlert.png");
		std::vector<RECT> rectList;
		RECT rect;
		rect.left = 403;
		rect.top = 42;
		rect.right = rect.left + 20;
		rect.bottom = rect.top + 12;
		rectList.push_back(rect);
		mAni = new Animation(mSprite, rectList, 0.2F, false);
	}

	this->flyDirection = flyDirection;
	mPosition = position;
	oldPos = position;
	mWidth = 20;
	mHeight = 12;

	SetVelocityX(.0f);
	SetVelocityY(.0f);
}

void Dynamite::Update(float deltaTime)
{
	if (oldPos.y - mPosition.y >= MAX_HEIGHT)
	{
		SetVelocityY(DYNAMITE_VELO_Y);
	}
	else if (mPosition.y > 192)
	{
		pendingDelete = true;
		SceneManager::GetInstance().GetScene()->GetGrid()->Add(
			new Explosion(this)
		);
	}
	Entity::Update(deltaTime);
}

void Dynamite::Draw(D3DXVECTOR2 trans)
{
	mAni->Draw(mPosition, trans);
	this->RenderBoundingBox(trans);
}

RECT Dynamite::GetBoundingBox()
{
	RECT rect;
	rect.left = mPosition.x;
	rect.top = mPosition.y;
	rect.right = rect.left + mWidth;
	rect.bottom = rect.top + mHeight;
	return rect;
}

CollidableObjectType Dynamite::GetCollidableObjectType()
{
	return CollidableObjectType::EDynamite;
}

void Dynamite::Throw()
{
	isThrown = true;

	SetVelocityX(flyDirection * DYNAMITE_VELO_X);
	SetVelocityY(-DYNAMITE_VELO_Y);
}
