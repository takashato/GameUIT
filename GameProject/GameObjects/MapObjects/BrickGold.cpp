#include "BrickGold.h"

BrickGold::BrickGold(D3DXVECTOR3 position)
{
    init(position);
}

BrickGold::~BrickGold()
{
}

const char * BrickGold::FileName()
{
    return "Resources/goldbrick.png";
}

int BrickGold::TotalFrame()
{
    return 4;
}

int BrickGold::Row()
{
    return 1;
}

int BrickGold::Column()
{
    return 4;
}

float BrickGold::SecondPerFrame()
{
    return 0.3f;
}
