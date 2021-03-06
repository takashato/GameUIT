#pragma once
class Sprite {
public:
	Sprite(const wchar_t* filePath, RECT sourceRect = RECT(), int width = NULL, int height = NULL, D3DCOLOR colorKey = NULL);
	~Sprite();

	void Draw(D3DXVECTOR3 postion, D3DXVECTOR2 scale = D3DXVECTOR2(1.0f, 1.0f),
		D3DXVECTOR2 transform = D3DXVECTOR2(), int alpha = 255,
		D3DXVECTOR3 flipExtra = D3DXVECTOR3(.0f, .0f, .0f),
		D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255)
	);
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

	D3DXMATRIX mMatrix;

};