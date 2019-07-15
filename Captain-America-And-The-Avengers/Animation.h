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

	RECT mRect;

	bool mHorizontallyFlip = false; // Flip horizontally

public:
	Animation(Sprite* sprite, std::vector<RECT> frames, float timePerFrame = 0.1F);

	void Draw(D3DXVECTOR3 position);
	virtual void Update(float deltaTime);

	void SetFrame(int frame);
	void IncFrame();

	int GetFrameNumber();

	RECT GetCurrentFrameRect();

	void SetTimePerFrame(float timePerFrame);
	float GetTimePerFrame();

	int GetWidth();
	int GetHeight();

	bool IsFlippedHorizontally();
	void SetFlippedHorizontally(bool flag);
};