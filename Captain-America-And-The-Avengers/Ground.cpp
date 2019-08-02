#include "pch.h"
#include "Game.h"
#include "Ground.h"

Ground::Ground(D3DXVECTOR3 position, GroundType groundType, int width, int height) : Entity()
{
	mGroundType = groundType;
	mWidth = width; mHeight = height;
	LoadAnimations();
	SetPosition(position);
	SetVelocityX(0.f);
	SetVelocityY(0.f);
}


Ground::~Ground()
{

}

void Ground::LoadAnimations()
{
	
	
}

void Ground::Update(float deltaTime)
{
	Entity::Update(deltaTime);
}

void Ground::Draw(D3DXVECTOR2 transform)
{
	this->RenderBoundingBox(transform);
}

int Ground::GetState()
{
	return mState;
}

void Ground::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void Ground::ChangeAnimationByState(int state)
{

}

void Ground::OnSetPosition()
{
}

GroundType Ground::GetGroundType()
{
	return mGroundType;
}

RECT Ground::GetBoundingBox() 
{
	RECT rect;
	rect.left = (long)mPosition.x;
	rect.top = (long)mPosition.y;
	rect.right = (long)(mWidth + mPosition.x);
	rect.bottom = (long)(mHeight + mPosition.y);
	return rect;
}

CollidableObjectType Ground::GetCollidableObjectType()
{
	return EPlatform;
}
