#pragma once
#include "Sprite.h"

class Animation
{
private:
	Sprite* mSprite; // Spritesheet
	int mWidth, mHeight;
	int mColNum, mRowNum;
	int mFrame; // Frame number, start from 0

	float mTimePerFrame; // Time interval
	float mTimer; // Time counter

	RECT mRect;

public:
	Animation(const wchar_t* filePath, int width, int height, int colNum, int rowNum = 1, float timePerFrame = 0.1F);
	void Draw(D3DXVECTOR3 position);
	virtual void Update(float deltaTime);
	void SetFrame(int frame);
	void IncFrame();
	void UpdateRect();
};