#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <dinput.h>
#include <windowsx.h>
#include "GameComponents\GameGlobal.h"
#include "GameComponents\GameTime.h"
#include "GameComponents\Game.h"
#include "GameControllers\SceneManager.h"

using namespace std;

#define WIN_NAME L"Game DirectX"
#define WIN_TITLE L"Game DirectX"
#define FPS 60
#define KEYBOARD_BUFFERD_SIZE 1024

/*

*/
int initWindow(int cmdShow);
int InitDevice();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

LPDIRECT3D9             mDirect3D9;
LPD3DXSPRITE            mSpriteHandler;
PDIRECT3D9              mD3d;
LPDIRECT3DDEVICE9       mDevice;
HINSTANCE               mHInstance;
int                     mCmdShow;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
    mHInstance = hInstance;
    initWindow(cmdShow);
    return 0;
}

int initWindow(int cmdShow)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = mHInstance;

    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = NULL;

    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WIN_NAME;
    wc.hIconSm = NULL;

    RegisterClassEx(&wc);

    //WS_OVERLAPPEDWINDOW <=> WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE
    HWND hWnd = CreateWindow(
        WIN_NAME,
        WIN_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        GameGlobal::GetWidth(),
        GameGlobal::GetHeight(),
        NULL,
        NULL,
        mHInstance,
        NULL);

    GameGlobal::SetCurrentHINSTACE(mHInstance);
    GameGlobal::SetCurrentHWND(hWnd);

    ShowWindow(hWnd, cmdShow);
    UpdateWindow(hWnd);

    if (InitDevice())
    {
        Game *game = new Game(FPS);
    }

    return 0;
}

int InitDevice()
{
    mD3d = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = GameGlobal::GetWidth();
    d3dpp.BackBufferHeight = GameGlobal::GetHeight();

    HRESULT dvresult = mD3d->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        GameGlobal::getCurrentHWND(),
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &mDevice);
    GameGlobal::SetCurrentDevice(mDevice);

    D3DXCreateSprite(GameGlobal::GetCurrentDevice(), &mSpriteHandler);
    GameGlobal::SetCurrentSpriteHandler(mSpriteHandler);

    return 1;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    /*
    su dung cac event cua window
    */
    switch (message)
    {
    case WM_DESTROY:
        GameGlobal::isGameRunning = false;
        PostQuitMessage(0);
        break;

    case WM_LBUTTONDOWN:
        SceneManager::GetInstance()->GetCurrentScene()->OnMouseDown((float)GET_X_LPARAM(lParam), 
                                                                    (float)GET_Y_LPARAM(lParam));
        break;

    case WM_KEYDOWN:
        SceneManager::GetInstance()->GetCurrentScene()->OnKeyDown(wParam);
        break;

    case WM_KEYUP:
        SceneManager::GetInstance()->GetCurrentScene()->OnKeyUp(wParam);
        break;
        

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}