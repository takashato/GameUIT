#pragma once
// Debug
#define DEBUG
#define SHOW_CONSOLE
#define SET_TITLE_AS_FPS

// Windows
#define WIN_CLASS_NAME L"CapAAndTheAvengers"
#define WIN_TITLE L"Captain America and The Avengers"
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 525
#define BUFFER_WIDTH 256
#define BUFFER_HEIGHT 224
/*#define BUFFER_WIDTH 600
#define BUFFER_HEIGHT 525*/

// KEY
#define GAME_KEY_LEFT DIK_LEFT
#define GAME_KEY_RIGHT DIK_RIGHT
#define GAME_KEY_UP DIK_UP
#define GAME_KEY_DOWN DIK_DOWN
#define GAME_KEY_JUMP DIK_X
#define GAME_KEY_ATTACK DIK_Z
#define GAME_KEY_SURF DIK_C // test key

// VELOCITY
#define MOVEMENT_UPDATE_TIME 0.01666666666f
#define PLAYER_VELOCITY_X_MAX 100
#define PLAYER_ACC_X 200
#define PLAYER_VELOCITY_Y_MAX 400
#define PLAYER_GRAVITY 500

//Spawpoint
#define SPAWPOINT_CHARLESTON D3DXVECTOR3(22.5f, 402.0f, 0.0f)
#define SPAWPOINT_MiniMap D3DXVECTOR3(59.0f, 171.0f, 0.0f)
#define SPAWPOINT_PITTSBURGH D3DXVECTOR3(20.5f, 147.f, 0.f)
//ID Map
#define ID_MAP_CHARLESTON 0
#define ID_MAP_CHARLESTON_BOSS_LIGHT 1
#define ID_MAP_CHARLESTON_BOSS_DARK -1
#define ID_MAP_PITTSBURGH_DARK 2
#define ID_MAP_PITTSBURGH_LIGHT -2
#define ID_MAP_PITTSBURGH_DARK_EXTRA_1 3 
#define ID_MAP_PITTSBURGH_LIGHT_EXTRA_1 -3 
#define ID_MAP_PITTSBURGH_DARK_EXTRA_2 4
#define ID_MAP_PITTSBURGH_LIGHT_EXTRA_2 -4
#define ID_MAP_RED_ALERT 5
//Exit point
#define EXIT_CHARLESTON 1979
#define DEMO_EXIT_MINIMAP 220
#define EXIT_PITTSBURGH 981
