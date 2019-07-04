#ifndef __ANIMATION__
#define __ANIMATION__

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprite.h"

using namespace std;

class Animation : public Sprite
{
public:
    //ham ho tro lay animation voi anh co duy nhat 1 hang
    Animation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

    Animation();

    virtual void Update(float dt);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void Draw(D3DXVECTOR2 translate);

    ~Animation();

protected:
    //su dung cho ke thua
    void InitWithAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

    int                         mRows, //so hang cua animation
                                mColumns, //so cot cua animation
                                mCurrentIndex, //gia tri frame hien tai - bat dau tu 0 -> tong so frame - 1
                                mCurrentRow, // hang hien tai
                                mCurrentColumn, // cot hien tai
                                mFrameWidth, // chieu rong cua 1 frame 
                                mFrameHeight, // chieu dai cua 1 frame
                                mTotalFrame;  //tong so frame


    float                       mTimePerFrame, //thoi gian luan chuyen 1 frame
                                mCurrentTotalTime; //tong thoi gian hien tai de thuc hien timeperframe

    RECT                        mRect;
};

#endif
