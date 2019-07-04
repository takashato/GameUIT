#pragma once

#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "GameObject.h"

//vien gach
class Brick : public Entity
{
public:
    ~Brick();

    void Update(float dt);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void Draw(D3DXVECTOR2 transform);

protected:
    Brick();

    bool init(D3DXVECTOR3 position);

    void OnSetPosition(D3DXVECTOR3 poks);

    virtual const char* FileName() = 0; // bat buoc phai override ham nay
    virtual int TotalFrame() = 0; //so frame cua animation
    virtual int Row() = 0; // so row cua resource hinh anh animation
    virtual int Column() = 0; // so cot cua resource hinh anh animation
    virtual float SecondPerFrame() = 0; //so giay de chuyen frame cua animation

    Animation *mAnimation;
};
