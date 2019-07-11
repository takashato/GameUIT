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

	mRect = sourceRect;
	if (width) 
	{
		mWidth = width;
	}
	if (height) 
	{
		mHeight = height;
	}
	if (!IsRect(sourceRect)) 
	{
		mRect.left = 0;
		mRect.right = mWidth;
		mRect.top = 0;
		mRect.bottom = mHeight;
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

void Sprite::Draw(D3DXVECTOR3 position, D3DXVECTOR2 scale)
{
	D3DXVECTOR2 inScale;

	inScale = scale;

	// Transformation
	D3DXMatrixScaling(&mMatrix, 1.0f, 1.0f, .0F);

	D3DXMATRIX oldMatrix;
	mSpriteHandler->GetTransform(&oldMatrix);
	mSpriteHandler->SetTransform(&mMatrix);

	D3DXVECTOR3 center(mWidth / 2, mHeight / 2, .0f);

	mSpriteHandler->Draw(
		mTexture,
		&mRect,
		NULL,
		&position,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	mSpriteHandler->SetTransform(&oldMatrix);
}

void Sprite::SetRect(RECT rect)
{
	mRect = rect;
}

D3DXIMAGE_INFO Sprite::GetImageInfo()
{
	return mImageInfo;
}

bool Sprite::IsRect(RECT rect)
{
	if (rect.left == rect.right || rect.top == rect.bottom)
		return false;
	return true;
}
