#include "pch.h"
#include "Animation.h"

Animation::Animation(Sprite* sprite, std::vector<RECT> frames, float timePerFrame)
{
	mSprite = sprite;

	mTimePerFrame = timePerFrame;
	mTimer = 0.0F;

	mFrames = frames;

	SetFrame(0);
}

void Animation::Draw(D3DXVECTOR3 position, D3DXVECTOR2 translation)
{
	RECT rect = GetCurrentFrameRect();
	mSprite->SetRect(rect);
	if (mHorizontallyFlip)
	{
		position.x += (rect.right - rect.left);
	}
	mSprite->Draw(position, D3DXVECTOR2(mHorizontallyFlip ? -1.0f : 1.0f, 1.0f), translation);
}

void Animation::Update(float deltaTime)
{
	//std::cout << "mTimer: " << mTimer << ", delta: " << deltaTime << std::endl;
	if (GetFrameNumber() <= 1) return; // Not need update, static animation, lol

	mTimer += deltaTime;
	if (mTimer >= mTimePerFrame) 
	{
		mTimer = 0;
		//std::cout << "Hit!!! Remaining " << mTimer << std::endl;
		IncFrame();
	}
}

void Animation::SetFrame(int frame)
{
	int frameNum = GetFrameNumber();
	if (frame >= frameNum)
	{
		mFrame = 0;
	}
	else if (frame < 0)
	{
		mFrame = frameNum - 1;
	}
	else
	{
		mFrame = frame;
	}
}

void Animation::IncFrame()
{
	SetFrame(mFrame + 1);
}

int Animation::GetFrameNumber()
{
	return static_cast<int>(mFrames.size());
}

RECT Animation::GetCurrentFrameRect()
{
	return mFrames[mFrame];
}

void Animation::SetTimePerFrame(float timePerFrame)
{
	mTimePerFrame = timePerFrame;
}

float Animation::GetTimePerFrame()
{
	return mTimePerFrame;
}

int Animation::GetWidth()
{
	return 0;
}

int Animation::GetHeight()
{
	return 0;
}

bool Animation::IsFlippedHorizontally()
{
	return mHorizontallyFlip;
}

void Animation::SetFlippedHorizontally(bool flag)
{
	mHorizontallyFlip = flag;
}
