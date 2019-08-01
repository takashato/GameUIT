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

Sprite::~Sprite()
{
	delete mTexture;
}

void Sprite::Draw(D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 transform, int alpha, D3DXVECTOR3 flipExtra)
{
	mSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR2 inScale, inTransform;
	D3DXVECTOR2 inScalingCenter(position.x, position.y);

	if (scale == D3DXVECTOR2())
	{
		inScale = D3DXVECTOR2(1.0f, 1.0f);
	}
	else
	{
		inScale = scale;
	}

	if (transform != D3DXVECTOR2())
	{
		inTransform = transform;
	}

	// Transformation
	D3DXMatrixTransformation2D(&mMatrix, &inScalingCenter, .0F, &inScale, NULL, .0F, &inTransform);

	D3DXMATRIX oldMatrix;
	mSpriteHandler->GetTransform(&oldMatrix);
	mSpriteHandler->SetTransform(&mMatrix);

	D3DXVECTOR3 center(mWidth / 2.0f, mHeight / 2.0f, .0f);
	if (flipExtra.x != 0)
	{
		position.x += flipExtra.x;
	}

	mSpriteHandler->Draw(
		mTexture,
		&mRect,
		&center,
		&position,
		D3DCOLOR_ARGB(alpha, 255, 255, 255)
	);
	mSpriteHandler->SetTransform(&oldMatrix);

	mSpriteHandler->End();
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
