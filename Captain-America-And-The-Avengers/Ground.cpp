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
	/*mCurrentAni->Draw(GetPosition(), transform);*/
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

void Ground::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{
	left = GetPosition().x;
	top = GetPosition().y;
	right = left + mWidth;
	bottom = top + mHeight;

}