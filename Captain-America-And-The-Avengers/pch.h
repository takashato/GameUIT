#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include <tchar.h>
#include <vector>
#include <map>

#include "define.h"

#include "GameException.h"
#include "ISingleton.h"