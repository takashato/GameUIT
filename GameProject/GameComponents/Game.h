#ifndef __GAME__
#define __GAME__
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>
#include <dinput.h>

#include "GameTime.h"

#define KEYBOARD_BUFFERD_SIZE 1024

class Game
{
public:
    Game(int fps = 60);
    ~Game();

protected:

    PDIRECT3DSURFACE9       mBackground,
                            mBackBuffer;

    int                     mWidth,
                            mHeight;
    static int              mIsDone;
    float                   mFPS;

    //khoi tao vong lap cho game
    void InitLoop();

    //ham dung de ve sau khi update
    void Render();

    //ham update cua game
    void Update(float dt);
};

#endif