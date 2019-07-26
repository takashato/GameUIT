#include "pch.h"
#include "Game.h"
#include "Ground.h"

Ground::Ground(D3DXVECTOR3 position) : Entity()
{
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
	rect.left = GetPosition().x;
	rect.top = GetPosition().y;
	rect.right = rect.left + mWidth;
	rect.bottom = rect.top + mHeight;
	return rect;
}