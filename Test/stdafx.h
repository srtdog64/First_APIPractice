#pragma once
#include "targetver.h"
#include <windows.h>
#include <WinUser.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#pragma comment(lib, "msimg32.lib")//TransparentBlt의 참조 에러 방지


//stdafx.h 미리 컴파일된 헤더를 쓰면 속도가 빠르다
#include "Object.h"