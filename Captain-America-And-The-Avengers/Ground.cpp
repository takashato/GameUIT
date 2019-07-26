#include "pch.h"
#include "Game.h"
#include "Ground.h"

Ground::Ground(D3DXVECTOR3 position) : Entity()
{
	mWidth = mHeight = 16;
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

RECT Ground::GetBoundingBox() 
{
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = mWidth;
	rect.bottom = mHeight;
	return rect;
}

CollidableType Ground::GetCollidableType()
{
	return EPlatform;
}
