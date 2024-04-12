// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <d3d11.h>
#include <DirectXMath.h>

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

#include "Src/Frameworks/Utility/Singleton.h"

#include "Src/Frameworks/System/Device.h"

#include "Src/Managers/GameManager.h"

extern HWND hWnd;