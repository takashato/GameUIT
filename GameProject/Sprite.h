#pragma once
class Sprite {
public:
	Sprite(const wchar_t* filePath, RECT sourceRect = RECT(), int width = NULL, int height = NULL, D3DCOLOR colorKey = NULL);
	void Draw(D3DXVECTOR3 postion);

	void SetRect(RECT rect);

	D3DXIMAGE_INFO GetImageInfo();

	static bool IsRect(RECT rect);

protected:
	int mWidth, mHeight;

	RECT mRect;
	D3DXVECTOR3 mPosition;
	D3DXVECTOR2 mScale;
	float mRotation;

	D3DXIMAGE_INFO mImageInfo;

	LPD3DXSPRITE mSpriteHandler;
	LPDIRECT3DTEXTURE9 mTexture;

};