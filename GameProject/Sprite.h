#pragma once
class Sprite {
public:
	Sprite(const wchar_t* filePath, RECT sourceRect = RECT(), int width = NULL, int height = NULL, D3DCOLOR colorKey = NULL);
	void Draw(D3DXVECTOR3 postion);
protected:
	D3DXVECTOR2 mScale;
	D3DXVECTOR3 mPosition;
	float mRotation;

	D3DXIMAGE_INFO mImageInfo;

	LPD3DXSPRITE mSpriteHandler;
	LPDIRECT3DTEXTURE9 mTexture;

};