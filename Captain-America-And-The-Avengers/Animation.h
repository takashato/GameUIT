#pragma once
#include "Sprite.h"

class Animation
{
private:
	Sprite* mSprite; // Spritesheet

	std::vector<RECT> mFrames;
	int mFrame; // Frame number, start from 0

	float mTimePerFrame; // Time interval
	float mTimer; // Time counter
	float mBlinkTimer = .0f;

	RECT mRect;

	bool mHorizontallyFlip = false; // Flip horizontally

	int mWidth = -1, mHeight = -1;

	bool mCycle = false, mLoop;

	bool mBlink = false, mIsBlinking = false;

public:
	Animation(Sprite* sprite, std::vector<RECT> frames, float timePerFrame = 0.1F, bool loop = true);

	void Draw(D3DXVECTOR3 position, D3DXVECTOR2 translation = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	virtual void Update(float deltaTime);

	void SetFrame(int frame);
	void IncFrame();

	int GetFrameNumber();
	int GetCurrentFrame();

	RECT GetCurrentFrameRect();

	void SetTimePerFrame(float timePerFrame);
	float GetTimePerFrame();

	int GetWidth();
	int GetHeight();

	void SetBlink(bool val);
	bool GetBlink();

	bool IsFlippedHorizontally();
	void SetFlippedHorizontally(bool flag);

	void Reset();
	bool IsDoneCycle();
};