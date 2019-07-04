#ifndef __SCENE__
#define __SCENE__
#include <d3dx9.h>
#include <d3d9.h>

#include "GameGlobal.h"

class Scene
{
public:
    virtual void Update(float dt);
    virtual void LoadContent();
    virtual void Draw();

    virtual void OnKeyDown(int keyCode);
    virtual void OnKeyUp(int keyCode);
    virtual void OnMouseDown(float x, float y);

    D3DCOLOR GetBackcolor();

    ~Scene();

protected:
    Scene();

    D3DCOLOR                mBackColor;

private :
};

#endif

