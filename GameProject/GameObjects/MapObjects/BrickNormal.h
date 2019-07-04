#pragma once
#include "Brick.h"
class BrickNormal : public Brick
{
public:
    ~BrickNormal();

    BrickNormal(D3DXVECTOR3 position);

    virtual const char* FileName();
    virtual int TotalFrame();
    virtual int Row();
    virtual int Column();
    virtual float SecondPerFrame();
};

