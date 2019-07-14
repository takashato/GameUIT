#include "pch.h"
#include "Animation.h"

Animation::Animation(const wchar_t* filePath, int width, int height, int colNum, int rowNum, float timePerFrame)
{
	mSprite = new Sprite(filePath, RECT(), width, height);

	if (width < 1 || height < 1 || colNum < 1 || rowNum < 1)
	{
		ThrowGameException("Invalid Anmation passed argument(s).");
	}

	mColNum = colNum;
	mRowNum = rowNum;

	int imgWidth = mSprite->GetImageInfo().Width;
	int imgHeight = mSprite->GetImageInfo().Height;

	if (width > imgWidth / colNum)
		mWidth = imgWidth / colNum;
	else
		mWidth = width;

	if (height > imgHeight / colNum)
		mHeight = imgHeight / rowNum;
	else
		mHeight = height;

	mTimePerFrame = timePerFrame;
	mTimer = 0.0F;

	SetFrame(0);
}

void Animation::Draw(D3DXVECTOR3 position)
{
	mSprite->SetRect(mRect);
	mSprite->Draw(position, D3DXVECTOR2(mHorizontallyFlip ? -1.0f : 1.0f, 1.0f));
}

void Animation::Update(float deltaTime)
{
	//std::cout << "mTimer: " << mTimer << ", delta: " << deltaTime << std::endl;
	if (mRowNum * mColNum <= 1) return; // Not need update, static animation, lol

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
	if (frame >= mColNum * mRowNum)
		mFrame = 0;
	else
		mFrame = frame;
	UpdateRect(); // Update after set frame
}

void Animation::IncFrame()
{
	SetFrame(mFrame + 1);
}

void Animation::UpdateRect()
{
	// Row, Col start from 0
	int currentCol = mFrame % mColNum;
	int currentRow = mFrame / mColNum;

	mRect.left = currentCol * mWidth;
	mRect.top = currentRow * mHeight;
	mRect.right = mRect.left + mWidth;
	mRect.bottom = mRect.top + mHeight;
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

bool Animation::IsFlippedHorizontally()
{
	return mHorizontallyFlip;
}

void Animation::SetFlippedHorizontally(bool flag)
{
	mHorizontallyFlip = flag;
}
