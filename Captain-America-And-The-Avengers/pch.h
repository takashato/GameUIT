#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9shape.h>
#include <dsound.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <atlbase.h>
#include <atlconv.h>
#include <math.h>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include <tchar.h>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

#include "define.h"
#include "enums.h"

#include "GameException.h"
#include "ISingleton.h"