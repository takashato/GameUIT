#include "pch.h"
#include "Game.h"
#include "DynamicGround.h"

DynamicGround::DynamicGround(D3DXVECTOR3 position, int subTypeID)
{
	LoadAnimations();
	mSubTypeID = subTypeID;
	SetPosition(position);
	SetDirection(EntityDirection::Left);
}

DynamicGround::~DynamicGround()
{
}

void DynamicGround::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\DynamicGround.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\DynamicGround.xml");

	mAniIdle = new Animation(mSprite, mAniScripts->GetRectList("Idle", "0"), 0.05F);

	mCurrentAni = mAniIdle;
}

void DynamicGround::Update(float deltaTime)
{
	
	if (mSubTypeID == 0)
	{
		mCounter += deltaTime;
		if (mCounter < 0.2f)
		{
			SetVelocityX(0.f);
			SetVelocityY(0.f);
		}
		else if (mCounter >= 0.2f && mCounter < 1.5f)
		{
			if (GetDirection() == Left)
			{
				SetVelocityX(GetDirection()*FLY_SPEED);
				AddPositionX(GetVelocityX() * deltaTime);
			}
			else
			{
				SetVelocityX(GetDirection()*FLY_SPEED);
				AddPositionX(GetVelocityX() * deltaTime);
			}
		}
		else
		{
			mCounter = 0;
			SetDirection(GetDirection() == Left ? Right : Left);
		}
	}
	else if (mSubTypeID == 1)
	{

	}
	else if (mSubTypeID == 2)
	{

	}


	if (mCurrentAni != NULL)
	{
		mCurrentAni->Update(deltaTime);
	}
}

void DynamicGround::Draw(D3DXVECTOR2 trans)
{
	if (mCurrentAni != NULL) mCurrentAni->Draw(GetPosition(), trans);
	this->RenderBoundingBox(trans);
}

void DynamicGround::OnSetPosition()
{
}

RECT DynamicGround::GetBoundingBox()
{
	if (mCurrentAni == nullptr) return RECT();

	RECT rect;

	rect.left = (long)mPosition.x;
	rect.top = (long)mPosition.y;
	rect.right = (long)(rect.left + mCurrentAni->GetWidth());
	rect.bottom = (long)(rect.top + mCurrentAni->GetHeight());

	return rect;
}

CollidableObjectType DynamicGround::GetCollidableObjectType()
{
	return EPlatform;
}

GroundType DynamicGround::GetGroundType()
{
	return EGroundNormal;
}