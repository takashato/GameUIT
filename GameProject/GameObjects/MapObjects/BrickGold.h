#pragma once
#include "Brick.h"

class BrickGold : public Brick
{
public:
    BrickGold(D3DXVECTOR3 position);
    ~BrickGold();

    virtual const char* FileName();
    virtual int TotalFrame();
    virtual int Row();
    virtual int Column();
    virtual float SecondPerFrame();
};