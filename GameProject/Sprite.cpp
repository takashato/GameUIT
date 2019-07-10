#include "pch.h"
#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(const wchar_t* filePath, RECT sourceRect, int width, int height, D3DCOLOR colorKey)
{
	HRESULT result;

	mScale.x = mScale.y = 1;
	mPosition = D3DXVECTOR3(.0F, .0F, .0F);
	mRotation = .0F;

	result = D3DXGetImageInfoFromFileW(filePath, &mImageInfo);
	if (result != D3D_OK)
	{
		std::stringstream ss;
		ss << "Failed to load sprite file " << filePath;
		ThrowGameException(ss.str());
	}

	mSpriteHandler = Game::GetInstance().GetSpriteHandler();
	LPDIRECT3DDEVICE9 device;
	mSpriteHandler->GetDevice(&device);

	result = D3DXCreateTextureFromFileExW(
		device,
		filePath,
		mImageInfo.Width,
		mImageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&mImageInfo,
		NULL,
		&mTexture
	);
	if (result != D3D_OK)
	{
		std::stringstream ss;
		ss << "Failed to create texture from file " << filePath;
		ThrowGameException(ss.str());
	} 
}

void Sprite::Draw(D3DXVECTOR3 position)
{
	mSpriteHandler->Draw(
		mTexture,
		NULL,
		NULL,
		&position,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}
