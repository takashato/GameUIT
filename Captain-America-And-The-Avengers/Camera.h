#pragma once
#include "Game.h"

class Camera
{
public:
	Camera(int width, int height);

	void SetPosition(int x, int y);
	void SetPosition(D3DXVECTOR3 position);

	int GetWidth();
	int GetHeight();

	D3DXVECTOR3 GetPosition();
	RECT GetBound();

	D3DXVECTOR2 GetTransform();

	~Camera();

private:
	int mWidth, mHeight;
	D3DXVECTOR3 mPosition;
};