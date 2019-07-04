#ifndef __SPRITE__
#define __SPRITE__
#include <d3d9.h>
#include <d3dx9.h>

#include "GameGlobal.h"

class Sprite
{
public:
    Sprite(const char* filePath, RECT sourceRect = RECT(), int width = NULL, int height = NULL, D3DCOLOR colorKey = NULL);

    Sprite();

    ~Sprite();

    LPDIRECT3DTEXTURE9 GetTexture();

    //void Draw();
    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(),RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void SetWidth(int width);
    int GetWidth();

    void SetHeight(int height);
    int GetHeight();

    D3DXIMAGE_INFO GetImageInfo(); // lay thong tin thuc cua hinh anh duoc lay

    D3DXVECTOR3 GetPosition();
    void SetPosition(D3DXVECTOR3 pos);
    void SetPosition(float x, float y);
    void SetPosition(D3DXVECTOR2 pos);

    D3DXVECTOR2 GetScale();
    void SetScale(D3DXVECTOR2 scale);

    D3DXVECTOR2 GetTranslation(); // phep tinh tien tu world position -> view position
    void SetTranslation(D3DXVECTOR2 translation); // phep tinh tien: tu the world position -> view position

    D3DXVECTOR2 GetRotationCenter();
    void SetRotationCenter(D3DXVECTOR2 rotationCenter);

    float GetRotation();
    void SetRotation(float rotation); // by radian

    void SetSourceRect(RECT rect);

    void FlipHorizontal(bool flag); // true: lat hinh theo chieu doc, false: binh thuong
    bool IsFlipHorizontal();

    void FlipVertical(bool flag); // true: lat hinh theo chieu ngang, false: binh thuong
    bool IsFlipVertical();

protected:
    //su dung cho ke thua
    void InitWithSprite(const char* filePath, RECT sourceRect = RECT(), int width = NULL, int height = NULL, D3DCOLOR colorKey = NULL);

    bool isRect(RECT rect);

    D3DXVECTOR3             mPosition; // vi tri cua Sprite, co goc la chinh giua hinh anh Texture
    LPDIRECT3DTEXTURE9      mTexture; // load hinh anh vao day
    LPD3DXSPRITE            mSpriteHandler; //SpriteHandler ho tro ve hinh
    D3DXIMAGE_INFO          mImageInfo; // thong tin thuc cua hinh anh duoc lay
    RECT                    mSourceRect; // hinh chu nhat cat tu anh cua texture
    
    int                     mWidth, mHeight; // kich thuoc cua texture

    bool                    mIsFlipVertical, // lat theo chieu doc
                            mIsFlipHorizontal; // lat theo chieu ngang

    float                   mRotation; // goc quay cua Sprite tinh theo radian

    D3DXVECTOR2             mScale; // Vector tuy chinh do phong to / thu nho cua texture
    D3DXVECTOR2             mTranslation; //Doi hinh anh vi tri thuc cua Sprite + mTranslate
    D3DXMATRIX              mMatrix; // ma tran cua Spite ho tro trong cac phep hinh hoc
    D3DXVECTOR2             mRotationCenter; // diem trung tam trong phep xoay hinh (origin vector)
};
#endif