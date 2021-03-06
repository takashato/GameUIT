#include "pch.h"
#include "Animation.h"

Animation::Animation(Sprite* sprite, std::vector<RECT> frames, float timePerFrame, bool loop)
{
	mSprite = sprite;

	mTimePerFrame = timePerFrame;
	mTimer = 0.0F;

	mFrames = frames;

	// Determine width / height
	for (size_t i = 0; i < frames.size(); ++i)
	{
		int width = frames[i].right - frames[i].left;
		int height = frames[i].bottom - frames[i].top;

		if (width > mWidth) mWidth = width;
		if (height > mHeight) mHeight = height;
	}

	SetFrame(0);
	mCycle = false;

	mLoop = loop;
}

void Animation::Draw(D3DXVECTOR3 position, D3DXVECTOR2 translation, D3DCOLOR color)
{
	RECT rect = GetCurrentFrameRect();
	mSprite->SetRect(rect);
	D3DXVECTOR3 flipExtra(.0f, .0f, .0f);
	if (mHorizontallyFlip)
	{
		position.x += (rect.right - rect.left);
	}
	else
	{
		flipExtra.x += GetWidth() - (rect.right - rect.left);
	}
	mSprite->Draw(position, D3DXVECTOR2(mHorizontallyFlip ? -1.0f : 1.0f, 1.0f), translation, mIsBlinking ? 150 : 255, flipExtra, color);
}

void Animation::Update(float deltaTime)
{
	if (mBlink)
	{
		mBlinkTimer += deltaTime;
		if (mBlinkTimer > 0.075f)
		{
			mBlinkTimer = .0f;
			mIsBlinking = !mIsBlinking;
		}
	}

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
		if (mLoop)
		{
			mFrame = 0;
		}
		else
		{
			mFrame = frameNum - 1;
		}
		mCycle = true;
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

int Animation::GetCurrentFrame()
{
	return mFrame;
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
	return mWidth;
}

int Animation::GetHeight()
{
	return mHeight;
}

void Animation::SetBlink(bool val)
{
	mBlink = val;
	if (!mBlink)
	{
		mIsBlinking = false;
		mBlinkTimer = .0f;
	}
}

bool Animation::GetBlink()
{
	return mBlink;
}

bool Animation::IsFlippedHorizontally()
{
	return mHorizontallyFlip;
}

void Animation::SetFlippedHorizontally(bool flag)
{
	mHorizontallyFlip = flag;
}

void Animation::Reset()
{
	mFrame = 0;
	mCycle = false;
}

bool Animation::IsDoneCycle()
{
	return mCycle;
}
