#include "BrickNormal.h"

BrickNormal::BrickNormal(D3DXVECTOR3 position)
{
    init(position);
}

BrickNormal::~BrickNormal()
{
}


const char * BrickNormal::FileName()
{
    return "Resources/normalbrick.png";
}

int BrickNormal::TotalFrame()
{
    return 1;
}

int BrickNormal::Row()
{
    return 1;
}

int BrickNormal::Column()
{
    return 1;
}

float BrickNormal::SecondPerFrame()
{
    return 1.0f;
}