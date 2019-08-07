#include "pch.h"
#include "Game.h"
#include "BreakGround.h"

BreakGround::BreakGround(D3DXVECTOR3 position) : Ground(position, EGroundBreak, 32, 16)
{
	mGroundType = GroundType::EGroundBreak;
	LoadAnimations();
	SetPosition(position);
	SetState(BREAKGROUND_IDLE_STATE);
}

BreakGround::~BreakGround()
{
}

void BreakGround::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\DynamicGround.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\BreakGround.xml");

	mAniIdle = new Animation(mSprite, mAniScripts->GetRectList("Idle", "0"), 0.05F);
	mAniBreak = new Animation(mSprite, mAniScripts->GetRectList("Breaking", "0"), 0.05F);

	mCurrentAni = mAniIdle;
}

void BreakGround::Update(float deltaTime)
{
	
	Entity::Update(deltaTime);
	if (isCollidedWithPlayer)
	{	
		SetState(BREAKGROUND_BREAKING_STATE);
		isCollidedWithPlayer = false;
	}
	else
	{
		mCounter += deltaTime;
		if (mCounter > 2.0f)
		{
			SetState(BREAKGROUND_IDLE_STATE);
			mCounter = 0;
		}
	}
	
}

void BreakGround::Draw(D3DXVECTOR2 trans)
{
	if (mCurrentAni != NULL) mCurrentAni->Draw(GetPosition(), trans);
	this->RenderBoundingBox(trans);
}

void BreakGround::OnSetPosition()
{

}

GroundType BreakGround::GetGroundType()
{
	return mGroundType;
}

int BreakGround::GetState()
{
	return mState;
}

void BreakGround::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void BreakGround::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case BREAKGROUND_IDLE_STATE:
		mCurrentAni = mAniIdle;
		break;
	case BREAKGROUND_BREAKING_STATE:
		mCurrentAni = mAniBreak;
		break;
	}
}

RECT BreakGround::GetBoundingBox()
{
	if (mCurrentAni == nullptr) {
		return RECT();
	}
	RECT bb;
	if (mCurrentAni == mAniIdle)
	{
		bb.left = mPosition.x;
		bb.top = mPosition.y;
		bb.right = mPosition.x + mCurrentAni->GetWidth();
		bb.bottom = mPosition.y + mCurrentAni->GetHeight();
	}
	else
	{
		bb.left = mPosition.x;
		bb.top = mPosition.y;
		bb.right = mPosition.x + 2;
		bb.bottom = mPosition.y + 2;
	}
	return bb;
}