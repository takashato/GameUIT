#include "pch.h"
#include "Game.h"
#include "DynamicGround.h"

DynamicGround::DynamicGround(D3DXVECTOR3 position, int subTypeID) : Ground(position)
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
		else if (mCounter >= 0.2f && mCounter < 3.0f)
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
		mCounter += deltaTime;
		if (mCounter < 0.2f)
		{
			SetVelocityX(0.f);
			SetVelocityY(0.f);
		}
		else if (mCounter >= 0.2f && mCounter < 2.2f)
		{
			if (GetDirection() == Left)
			{
				SetVelocityX(GetDirection()*FLY_SPEED);
				AddPositionX(GetVelocityX() * deltaTime);
				SetVelocityY(GetDirection()*FLY_SPEED*(-1));
				AddPositionY(GetVelocityY() * deltaTime);
			}
			else
			{
				SetVelocityX(GetDirection()*FLY_SPEED);
				AddPositionX(GetVelocityX() * deltaTime);
				SetVelocityY(GetDirection()*FLY_SPEED*(-1));
				AddPositionY(GetVelocityY() * deltaTime);
			}
		}
		else
		{
			mCounter = 0;
			SetDirection(GetDirection() == Left ? Right : Left);
		}
	}
	else if (mSubTypeID == 2)
	{
		//if (GetDirection() == Left)
		//{
		//	/*SetVelocityX(GetDirection()*FLY_SPEED);
		//	AddPositionX(GetVelocityX() * deltaTime);*/
		//	AddPositionX(GetDirection()*0.5);
		//	D3DXVECTOR3 dynamicPosition = this->GetPosition();

		//	float y;
		//	y = sqrt(50 * 50 - (dynamicPosition.x - center.x)*(dynamicPosition.x - center.x)) + center.y;
		//	SetPositionY(y);
		//}
		//if (GetDirection() == Right)
		//{
		//	/*SetVelocityX(GetDirection()*FLY_SPEED);
		//	AddPositionX(GetVelocityX() * deltaTime);*/
		//	AddPositionX(GetDirection()*0.5);
		//	D3DXVECTOR3 dynamicPosition = this->GetPosition();

		//	float y;
		//	y = -sqrt(50 * 50 - (dynamicPosition.x - center.x)*(dynamicPosition.x - center.x)) + center.y;
		//	SetPositionY(y);
		//}

		//D3DXVECTOR3 dynamicGroundPosition = this->GetPosition();
		//if (dynamicGroundPosition.x == 100  || dynamicGroundPosition.x == 200)
		//	SetDirection(GetDirection() == Left ? Right : Left);

		mCounter += deltaTime;

		mPosition.x = 620.0 + 50.0f * cos(omega * mCounter);
		mPosition.y = 650.0 - 50.0f * omega * sin(omega * mCounter);
		mPosition.z = 0.f;
		SetPosition(mPosition);
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
	return EGroundDynamic;
}