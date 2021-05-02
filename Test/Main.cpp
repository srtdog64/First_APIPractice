// Test.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "stdafx.h"
#include  "Main.h"
#include "Bullet.h"
#include "Block.h"
#include "mciapi.h"
#include "Bomb.h"
#include "Thing.h"
#include <MMSystem.h>//사운드 삽입
#pragma  comment (lib,"winmm.lib")//사운드재생

#define MAX_LOADSTRING 100

// 호환가능 메모리장치
HDC bufferDC;
HDC bufferDC2;
HDC winDC;
HDC backgroundDC;
HDC Player_DC;
HDC Enemy_DC;
HDC bulletDC;
HDC BlockDC;
HDC bombDC;
HDC armorDC;
HDC attrDC;
HDC attringDC;
HDC adding_attrDC;
HDC level_upDC;
HDC missileDC;
HDC recoveryDC;
HDC GOALDC;
HDC bottomDC;
HDC topDC;
HDC skillDC;
HDC gamewinallDC;


//NEW 메모리
HDC player_state_mapDC;
HDC thingDC;
HDC startDC;
HDC selectDC;
HDC gamewinDC;
HDC gameoverDC;
HDC playerdeadDC;
HDC	introduceDC;
// HDC blankDC;
HDC sandDC;
HDC lvDC;
HBRUSH hBruRed;
HBRUSH hBruBlue;
HBRUSH hBruYellow;
HBRUSH hBruWhite;
HBRUSH hBru_Laser;
HPEN hPen_Border;
HPEN hPen_laser;
HPEN hPen_black;
HBRUSH  hBru_Black;
HBRUSH	hBru_hp;
HBRUSH  hBru_charge;

//호환 비트맵
HBITMAP bufferBMP;
HBITMAP bufferBMP2;
HBITMAP backgroundBMP;
HBITMAP PlayerBMP;
HBITMAP player_state_map;
HBITMAP bulletBMP;
HBITMAP BlockBMP;
HBITMAP bombBMP;
HBITMAP ITEMBMP;
HBITMAP TopBmp;
HBITMAP Enemy_UNITBMP;
HBITMAP blank;
HBITMAP sand;
HBITMAP armorBMP;
HBITMAP missileBMP;
HBITMAP recoveryBMP;
HBITMAP CreditBMP;
HBITMAP startBMP;
HBITMAP SelectBMP;
HBITMAP gameoverBMP;
HBITMAP gamewinBMP;
HBITMAP playerdeadBMP;
HBITMAP introduceBMP;
HBITMAP creditsBMP;
HBITMAP gamewinallBMP;
HBITMAP LVBMP;
HBITMAP GOALBMP;
HBITMAP level_upbmp;
HBITMAP BulletBMP;
HBITMAP STATUPBMP;
HBITMAP BottomBMP;


//new


//직사각형 블록 충돌 감지 감소
const int offset=5;
int game_no=0;
const int game_max=4;//게임 스테이지 최종

//물체가 아이템을 만드는지 체크
void JudgeThingE(C_UNIT*);//유닛의 아이템 드랍 체크
void JudgeThingB(C_Block*);//블록의 아이템 드랍 체크

//마우스 클릭시 나오는 현재 맵 블록 속성
int mouse_id = WALL;
int mouse_x;
int mouse_y;
//게임창 핸들
HWND hWnd;
//게임타이머
UINT game_timer; //UINT는 부호가 정해지지 않은 정수
//게임상태
int game_state;
//보스 모드
bool boss_mode = false;
//플레이어 유닛
C_UNIT* Player;
const int mp_decrease_cd = 150;
int mp_decrease_frame = 0;
//플레이어 총알
list<C_Bullet*>bullet;
//폭발 관련 
list<C_Bomb*> bomb;
//아이템 관련
list <C_Thing*>thing;
//적
list<C_UNIT*> enemy;
//block 개체 컨테이너 클래스
list<C_Block*>object;


//좌표 오프셋(화면 표시 좌표를 계산하는 데 사용됨)
double offset_x = 0;
const int offset_y = -96;

//지도 block의 너비 및 높이 갯수
const int block_wide = GAME_TOTW / 64;
const int block_high = (GAME_H + offset_y * 2) / 64;
const int rows = 9;
const int cols = 40;
//맵들
vector<int> block_map;
const int map_max = 1;
int map_bg[block_wide * block_high] = { 0 };
int block_layout[block_high * block_wide] = {};
//로드 이미지 함수
// LoadImage(로드할 모듈 핸들(독립형 리소스시 NULL),리소스 불러옴,이미지 유형 선택,이미지 폭과 높이,옵션 설정)





//모래,얼음,강 등등의지형지물, 게임의 레벨(스테이지)
int mapIndex[block_wide * block_high] = {};
int map_all[game_max][block_wide * block_high] = 
{
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 5, 3, 3, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 8, 4, 4, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,

    3, 3, 3, 5, 3, 3, 3, 5, 3, 3, 3, 5, 3, 3, 10, 14, 14, 14, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 5, 3, 3, 3, 5, 3, 3, 10, 14, 14, 14, 14, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 1, 3, 5, 3, 1, 1, 1, 1, 1, 1, 14, 14, 14, 14, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 1, 3, 5, 3, 1, 3, 5, 3, 3, 10, 14, 14, 14, 14, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 1, 3, 5, 3, 1, 3, 10, 13, 13, 14, 14, 14, 14, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 1, 3, 5, 3, 1, 3, 10, 12, 12, 14, 14, 14, 14, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 1, 3, 5, 3, 1, 3, 5, 3, 3, 10, 14, 14, 14, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 1, 1, 1, 1, 1, 3, 5, 3, 3, 8, 14, 14, 14, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 3, 3, 5, 3, 3, 3, 5, 3, 3, 3, 10, 14, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,

    3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 3, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 3, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3

};
//모래,얼음,강 등등의지형지물, 게임의 레벨(스테이지)

int block_all[game_max][block_high * block_wide] = 
{
	2, 0, 0, 0, 0, 0, 2, 0, 90, 2, 0, 0, 1, 1, 0, 0, 4, 8, 8, 0, 90, 4, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 5, 0, 92, 5, 0, 2, 2, 2, 0, 0, 0, 2, 1, 1, 0, 0, 0, 1, 0, 0, 2, 0, 1, 6, 4, 8, 8, 0, 0, 0, 4, 0, 0, 90, 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 91, 2, 9, 2, 1, 2, 0, 0, 1, 1, 0, 2, 1, 1, 0, 5, 0, 0, 4, 4, 4, 4, 4, 1, 2, 1, 0, 4, 1, 1, 0, 4, 0, 0, 0, 5, 5, 0, 5, 0, 7, 0, 0, 2, 0, 0, 2, 0, 2, 5, 0, 0, 0, 0, 2, 0, 0, 6, 4, 0, 90, 0, 4, 0, 0, 0, 0, 2, 0, 2, 4, 0, 90, 2, 0, 0, 90, 0, 5, 0, 0, 5, 2, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 2, 1, 6, 4, 0, 91, 0, 4, 0, 0, 2, 0, 33, 31, 34, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 2, 90, 0, 0, 1, 1, 4, 0, 90, 0, 4, 0, 0, 1, 0, 32, 2, 32, 0, 0, 0, 5, 0, 5, 0, 0, 0, 8, 8, 8, 8, 8, 5, 1, 0, 0, 1, 1, 2, 0, 0, 0, 0, 2, 0, 0, 4, 4, 4, 4, 4, 2, 2, 33, 31, 35, 6, 36, 31, 34, 0, 4, 0, 0, 0, 0, 1, 1, 0, 1, 0, 8, 2, 0, 0, 0, 1, 1, 0, 5, 0, 0, 1, 0, 0, 0, 0, 6, 4, 8, 8, 0, 0, 32, 2, 6, 4, 6, 2, 32, 0, 2, 0, 0, 0, 0, 0, 0, 91, 0, 1, 8, 0, 0, 0, 2, 0, 90, 0, 0, 0, 2, 1, 0, 0, 1, 1, 0, 4, 8, 8, 0, 1, 32, 6, 4, 92, 4, 6, 32, 5, 0, 0, 0, 0, 1, 90, 0, 1, 0, 92, 8,

	0, 4, 0, 0, 4, 0, 0, 0, 5, 8, 0, 0, 0, 0, 0, 0, 0, 6, 0, 7, 5, 0, 2, 4, 0, 2, 0, 91, 2, 0, 4, 0, 1, 0, 4, 0, 7, 7, 7, 7, 0, 0, 0, 90, 0, 0, 92, 0, 4, 0, 5, 0, 7, 6, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 1, 0, 4, 4, 0, 2, 4, 0, 2, 1, 1, 1, 0, 94, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 91, 0, 0, 0, 0, 0, 0, 5, 91, 0, 0, 0, 8, 5, 2, 4, 4, 91, 2, 0, 1, 0, 0, 1, 4, 0, 0, 32, 0, 0, 2, 2, 0, 0, 8, 0, 0, 0, 6, 0, 4, 0, 6, 0, 0, 5, 0, 0, 92, 0, 0, 0, 8, 8, 0, 2, 1, 1, 0, 4, 33, 31, 31, 1, 0, 92, 4, 32, 7, 93, 0, 0, 0, 0, 8, 0, 7, 0, 5, 0, 0, 0, 4, 0, 0, 0, 0, 0, 91, 0, 0, 7, 7, 2, 2, 0, 0, 2, 0, 1, 32, 0, 0, 0, 4, 0, 4, 32, 7, 0, 0, 9, 0, 0, 8, 0, 6, 0, 8, 0, 7, 0, 8, 0, 0, 0, 0, 0, 5, 5, 6, 5, 0, 0, 0, 4, 4, 4, 90, 1, 32, 91, 1, 2, 0, 92, 0, 36, 34, 93, 0, 0, 5, 0, 8, 0, 5, 0, 0, 0, 0, 0, 8, 91, 7, 0, 0, 0, 5, 5, 0, 5, 5, 2, 1, 1, 1, 31, 31, 31, 35, 2, 0, 0, 1, 0, 2, 0, 32, 0, 2, 2, 0, 4, 0, 0, 0, 0, 90, 0, 0, 0, 5, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 93, 2, 1, 4, 0, 2, 0, 4, 0, 4, 4, 0, 0, 2, 0, 1, 94, 0, 0, 4, 0, 5, 0, 0, 4, 4, 0, 4, 0, 6, 0, 0, 5, 0, 0, 90, 0, 5, 5, 7, 7, 0, 0, 4, 1, 0, 91, 0, 2, 0, 1, 1, 4, 4, 0, 7, 7, 7, 7,

	0, 0, 0, 7, 6, 0, 8, 0, 0, 0, 0, 7, 0, 92, 4, 0, 2, 92, 0, 0, 90, 0, 0, 6, 0, 0, 0, 0, 6, 0, 7, 1, 1, 90, 5, 0, 94, 5, 5, 0,
	0, 0, 0, 7, 0, 90, 0, 0, 0, 0, 6, 7, 92, 94, 5, 0, 5, 92, 4, 0, 90, 91, 0, 0, 5, 0, 6, 0, 0, 0, 4, 1, 1, 90, 5, 2, 0, 4, 5, 0,
	0, 0, 0, 0, 0, 90, 0, 7, 5, 5, 0, 5, 0, 0, 7, 8, 7, 0, 4, 0, 90, 91, 0, 6, 5, 0, 0, 0, 6, 0, 4, 1, 1, 91, 5, 93, 5, 0, 5, 0,
	0, 0, 0, 0, 0, 0, 0, 7, 5, 91, 0, 5, 2, 7, 7, 8, 7, 7, 4, 0, 0, 92, 0, 0, 5, 0, 6, 0, 0, 0, 4, 1, 1, 92, 5, 0, 5, 0, 5, 4,
	0, 0, 0, 7, 0, 0, 0, 8, 8, 4, 0, 2, 0, 8, 8, 8, 8, 8, 6, 5, 93, 0, 0, 6, 5, 0, 0, 0, 6, 0, 4, 1, 1, 93, 5, 6, 5, 0, 5, 9,
	0, 0, 0, 7, 0, 0, 0, 7, 5, 91, 0, 5, 2, 7, 7, 8, 7, 7, 4, 0, 0, 92, 0, 0, 5, 0, 6, 0, 0, 0, 4, 1, 1, 92, 5, 0, 5, 0, 5, 4,
	0, 0, 0, 7, 0, 90, 0, 7, 5, 5, 0, 5, 0, 0, 7, 8, 7, 0, 4, 0, 90, 91, 0, 6, 0, 0, 0, 0, 6, 0, 4, 1, 1, 91, 2, 0, 5, 0, 6, 0,
	0, 0, 0, 7, 0, 90, 0, 0, 0, 0, 6, 7, 92, 94, 5, 0, 5, 92, 4, 0, 90, 91, 0, 0, 2, 0, 6, 0, 0, 0, 4, 1, 1, 90, 2, 0, 5, 4, 6, 0,
	0, 0, 0, 7, 6, 0, 8, 0, 0, 0, 0, 7, 0, 92, 4, 0, 2, 92, 0, 0, 90, 0, 0, 6, 5, 0, 0, 0, 6, 0, 7, 1, 1, 90, 5, 5, 94, 94, 4, 0,

	0, 1, 0, 0, 1, 92, 92, 1, 1, 1, 1, 1, 1, 2, 1, 0, 7, 0, 4, 0, 90, 0, 0, 0, 4, 0, 0, 94, 4, 0, 4, 7, 2, 1, 94, 1, 94, 4, 4, 4, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 2, 0, 1, 7, 0, 0, 0, 4, 91, 0, 4, 7, 0, 4, 0, 0, 91, 0, 7, 5, 0, 1, 94, 1, 4, 9, 4, 0, 1, 1, 33, 31, 31, 34, 1, 1, 1, 1, 1, 1, 94, 2, 0, 7, 0, 91, 0, 92, 0, 0, 0, 7, 0, 94, 0, 4, 0, 0, 7, 4, 5, 2, 1, 94, 4, 4, 4, 0, 0, 1, 32, 94, 94, 32, 1, 1, 1, 1, 1, 1, 2, 0, 1, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 0, 7, 7, 6, 5, 4, 1, 1, 2, 94, 1, 0, 0, 1, 32, 94, 94, 32, 1, 1, 1, 1, 1, 1, 2, 0, 0, 8, 8, 8, 6, 6, 0, 0, 2, 7, 0, 0, 8, 0, 0, 0, 5, 4, 6, 5, 0, 2, 94, 1, 94, 1, 1, 0, 36, 31, 31, 35, 1, 1, 1, 1, 1, 1, 2, 1, 0, 7, 7, 7, 2, 2, 7, 7, 7, 7, 0, 92, 0, 0, 0, 4, 4, 8, 4, 6, 4, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 94, 2, 1, 7, 6, 2, 0, 0, 0, 7, 0, 0, 8, 0, 4, 5, 4, 5, 5, 4, 5, 4, 5, 2, 1, 2, 2, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 2, 0, 0, 7, 2, 92, 0, 90, 92, 7, 0, 93, 4, 5, 5, 0, 6, 4, 8, 0, 0, 1, 1, 0, 2, 6, 6, 0, 1, 0, 1, 1, 92, 92, 1, 1, 1, 1, 1, 1, 2, 0, 1, 7, 94, 0, 93, 93, 94, 7, 0, 0, 92, 0, 8, 0, 4, 0, 0, 0, 2, 93, 0, 94, 2, 6,
};



bool LevelUping = false;
int AddAttring;
int adding = 0;
int uping = 0;
int shaking = 0;
//레벨별 업그레이드 요구 경험치 설정
int lvexp[11] = { 0,800,1200,1600,2000,2500,3000,3500,4000,5000,1000000 };

//적 유닛 정보
//maxhp,speed,attack,attack_cd,armor,exp
//enemy_attribute(적 속성)
int enemy_attr[5][6] = 
{
    120,2,10,100,0,80,
    180,3,15,50,1,100,
    240,2,20,70,2,120,
    350,4,25,80,3,150,
    500,1,30,100,4,200,
};

//bullet 데미지 설정
int bullet_attr[11][7] = 
{
    8,10,12 + offset * 2,15 + offset * 2,20,20,8,
    10,15,12 + offset * 2,15 + offset * 2,30,20,8,
    8,20,12 + offset * 2,18 + offset * 2,40,20,8,
    12,25,14 + offset * 2,20 + offset * 2,50,20,8,
    5,45,14 + offset * 2,22 + offset * 2,100,20,8,

    8,10,12 + offset * 2,15 + offset * 2,20,20,8,
    10,15,12 + offset * 2,15 + offset * 2,30,20,8,
    8,20,12 + offset * 2,18 + offset * 2,40,20,8,
    12,25,14 + offset * 2,20 + offset * 2,50,20,8,
    5,45,14 + offset * 2,22 + offset * 2,100,20,8,
    6,30,16 + offset * 2,22 + offset * 2,80,20,8,
};
//블록 체력 설정
int Block_attr[37][2] = 
    { Block_NONE,10000,
    GRASS,1000,TREE,200,WATER,10000,
    WALL,350,STONE,600,BUCKET,40,IRON,10000,PITON,10000,GOAL,500 
};
//도움말 만들기
bool keydown_f1 = false;
bool keydown_f2 = false;
bool keydown_f3 = false;
bool keydown_f4 = false;
bool keydown_f5 = false;
int credits = 0;
bool introduce_ing = false;
bool credits_ing = false;
//유닛 속도 최저, 최고
int charge = -1;
int chargemax = 60;
//레이저 충돌 
int proton_collider = 0;
//fps, 표기
int time_now, time_pre, fps, frame;
//LEVEL (스테이지,구분)
int wintime;
const int wintimemax = 200;
int stage;
//베이스
int base_time;
const int base_timemax = 100;
//플레이어 죽음 체크
int player_death = 0;//0은 살아있고 1은 죽음
//플레이어 MAX 능력치 설정
const int max_life = 100;
const int max_speed = 12;
const int max_fire_speed = 12;
const int max_bullet_speed = 12;
//
int gameover_time = 0;
int gamewin_time = 0;
//한 화면 최대 적 숫자, 적의 수 적 번호
int all_id = 0;
int enemy_num;
int enemy_rest;
const int enemy_maxscreen = 4;
const int enemy_max = 100;
int enemy_time = 0;
const int enemy_timemax = 100;
//아이템, 맵에 아이템이 머물 수 있는 시간
int item;
int item_x;
int item_y;
int item_stay_time;
const int item_stay_timemax = 1000;

//화면 흔들림(이거는 git hub 재 참조)
double bgx, bgy;
//플레이어 상태 표시줄 좌표
double hpX1, hpY1, hpX2, hpY2, mpX1, mpY1, mpX2, mpY2, fullhpX, fullmpX;
double expX1, expY1, expX2, expY2, fullexpX;
//레이저류 무기를 위한 제어 변수
int laser_index = 0;
bool laser_open = true;
//레이저 무기를 직사각형 좌표, 시작과 끝
int laserxs = 0;
int laserys = 0;
int laserxe = 0;
int laserye = 0;
//레이저 발사 여부 체크
int k_down = false;
//유도탄 발사 여부 체크
int l_down = false;
//미사일 변수
int missile_index = 0;
//폭발 트리거 발동시 애니메이션 OpenExplode 함수 불러옴.
int onceExplode = 0;
C_UNIT* lock_enemy = NULL; //조준된 적.(유도탄)


//a미사일 포인터
//Missile* myMissile = NULL;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST));//IDC를 수정가능

	GameStart();

    //음악재생
    //https://ldh-room.tistory.com/entry/APISound-%EC%B6%94%EA%B0%80-MCI%ED%95%A8%EC%88%98
   // mciSendString(_T("Opening.wav Alias music"), NULL, 0, NULL);//https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/using-mci-for-mp3-playback-r2053/
    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEST);//윈도우 이름
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   //화면 너비와 높이
   int width, height;

   width = GetSystemMetrics(SM_CXSCREEN);
   height = GetSystemMetrics(SM_CYSCREEN);

   //너비 1368, 높이 868
   bool fullScreen = true;
   if (width != 1368 || height != 768)
	   fullScreen = false;
   else
	   fullScreen = true;


   //화면 중앙 창만들기
   hWnd = hWnd = CreateWindow(szWindowClass, L"JDW_HOMEWORK(정동우 과제)", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
	   (width - (GAME_W + 6)) / 2, (height - (GAME_H + 28)) / 2 - 10, GAME_W + 6, GAME_H + 28, NULL, NULL, hInstance, NULL);//화면 크기 조정 hinstance가 내 게임 파일들이 전부 들어있는 객체
   //문자열을 유니코드 문자열로 만들려면 문자열 앞에 L을 붙이면된다!

   if (!hWnd)
   {
      return FALSE;
   }
   ShowCursor(FALSE);//윈도우 화면 마우스 숨김
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //윈도우 메모리 생성
   winDC = GetDC(hWnd);
   //버퍼 메모리 생성
   bufferDC = CreateCompatibleDC(winDC);//여기에 이미지들 미리 저장
   //WINDC 시뮬레이션
   bufferDC2 = CreateCompatibleDC(winDC);
   //백그라운드 메모리 생성
   backgroundDC = CreateCompatibleDC(winDC);
   //플레이어 생성
   Player_DC = CreateCompatibleDC(winDC);
   //
   Enemy_DC = CreateCompatibleDC(winDC);
   //탄환 메모리 생성
   bulletDC = CreateCompatibleDC(winDC);
   armorDC = CreateCompatibleDC(winDC);
   //블록 메모리 생성
   BlockDC = CreateCompatibleDC(winDC);
   //폭발 메모리 생성
   bombDC = CreateCompatibleDC(winDC);
   //미사일 메모리 생성
   missileDC = CreateCompatibleDC(winDC);

   sandDC = CreateCompatibleDC(winDC);
//HOW TO PLAY 창
   introduceDC = CreateCompatibleDC(winDC);


   //플레이어 상태창 DC
   player_state_mapDC = CreateCompatibleDC(winDC);
   //GOAL 포인트 DC
   GOALDC = CreateCompatibleDC(winDC);
   //new
   thingDC = CreateCompatibleDC(winDC);

   topDC = CreateCompatibleDC(winDC);
   //bottomDC = CreateCompatibleDC(winDC);
   attrDC = CreateCompatibleDC(winDC);
   skillDC = CreateCompatibleDC(winDC);
   recoveryDC = CreateCompatibleDC(winDC);
   gamewinallDC = CreateCompatibleDC(winDC);
   gameoverDC = CreateCompatibleDC(winDC);


   //blankDC=CreateCompatibleDC(winDC);


   //배경 이미지 생성
   bufferBMP = CreateCompatibleBitmap(winDC, GAME_TOTW, GAME_H);//모든것의 근간 기본적으로 여기에 공백 공간 그려짐
   bufferBMP2 = CreateCompatibleBitmap(winDC, GAME_W, GAME_H);

   hBruRed = CreateSolidBrush(RGB(161, 23, 21));
   hBruBlue = CreateSolidBrush(RGB(0, 90, 171));
   hBruYellow = CreateSolidBrush(RGB(251, 178, 23));
   hBruWhite = CreateSolidBrush(RGB(255, 255, 255));
   hBru_Laser = CreateSolidBrush(RGB(255, 255, 255));
   hBru_Black = CreateSolidBrush(RGB(50, 50, 50));
   hPen_Border = CreatePen(0, 1, RGB(100, 100, 100));//선긁기
   hPen_laser = CreatePen(0, 1, RGB(255, 255, 255));//레이저 선긁기
   hPen_black = CreatePen(0, 1, RGB(0, 0, 0));
   hBru_hp = CreateSolidBrush(RGB(186, 40, 53));
   hBru_charge = CreateSolidBrush(RGB(255, 222, 0));
   attrDC = CreateCompatibleDC(winDC);
   adding_attrDC = CreateCompatibleDC(winDC);
   level_upDC = CreateCompatibleDC(winDC);
   lvDC = CreateCompatibleDC(winDC);
   level_upDC = CreateCompatibleDC(winDC);


   //배경 이미지 생성2
   //LoadImage함수 설명:https://m.blog.naver.com/PostView.nhn?blogId=power2845&logNo=50142512822&proxyReferer=https:%2F%2Fwww.google.com%2F
   blank = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_BackGround), IMAGE_BITMAP, GAME_W, 576, LR_DEFAULTCOLOR);
   TopBmp = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_TOP), IMAGE_BITMAP, 1715, 96, LR_DEFAULTCOLOR);
   sand = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_SAND), IMAGE_BITMAP, 256, 256, LR_DEFAULTCOLOR);
//폭파 애니메이션
   bombBMP = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_bomb), IMAGE_BITMAP, 463, 80, LR_DEFAULTCOLOR);

   //플레이어랑 적 BMP는 랑그릿사 스프라이트
   startBMP = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_Title), IMAGE_BITMAP, 1368, 768, LR_DEFAULTCOLOR);
   player_state_map = (HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_PLAYER_STATE_MAP), IMAGE_BITMAP, 290, 96, LR_DEFAULTCOLOR);
   LVBMP = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_LV), IMAGE_BITMAP, 500, 26, LR_DEFAULTCOLOR);
   PlayerBMP = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_Hero), IMAGE_BITMAP, 256, 192, LR_DEFAULTCOLOR);
   Enemy_UNITBMP = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_enemy1), IMAGE_BITMAP, 256, 960, LR_DEFAULTCOLOR);
   //블록 이미지는 유니티 공짜 에셋에서 가져오기
   BlockBMP = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BLOCK), IMAGE_BITMAP, 256, 640, LR_DEFAULTCOLOR);
   ITEMBMP = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_ITEM), IMAGE_BITMAP, 320, 64, LR_DEFAULTCOLOR);//아이템
   GOALBMP= (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_GOAL), IMAGE_BITMAP, 256, 64, LR_DEFAULTCOLOR);
   level_upbmp = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_LV_UP), IMAGE_BITMAP, 567, 452, LR_DEFAULTCOLOR);
   gamewinBMP = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_Clear), IMAGE_BITMAP, 567, 425, LR_DEFAULTCOLOR);
   bulletBMP = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_Bullet), IMAGE_BITMAP, 256, 832, LR_DEFAULTCOLOR);
   STATUPBMP = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_STATUP), IMAGE_BITMAP, 329, 96, LR_DEFAULTCOLOR);
   //BottomBMP = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_Bottom), IMAGE_BITMAP, 1366, 96, LR_DEFAULTCOLOR);
   introduceBMP = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_HOWTO), IMAGE_BITMAP, 700, 500, LR_DEFAULTCOLOR);//개발자 소개
   SelectBMP = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_select), IMAGE_BITMAP, 1366, 768, LR_DEFAULTCOLOR);//왜 안되는가?
   CreditBMP = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_credit), IMAGE_BITMAP, 700, 500, LR_DEFAULTCOLOR);
   gameoverBMP = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_GAMEOVER), IMAGE_BITMAP, 583, 425, LR_DEFAULTCOLOR);




   startDC = CreateCompatibleDC(winDC);


   //메모리(DC) 선택
   //SelectObject는 DC에 저장된 GDI 오브젝트 핸들값 변경시 사용 여기에 사용해야 시스템에 그려짐
   SelectObject(bufferDC, bufferBMP);
   SelectObject(bufferDC2, bufferBMP2);
   SelectObject(startDC, startBMP);
   SelectObject(backgroundDC,blank);
   SelectObject(selectDC, SelectBMP);
   SelectObject(selectDC, CreditBMP);
   SelectObject(player_state_mapDC, player_state_map);//플레이어 능력치
   SelectObject(lvDC, LVBMP);//레벨
   SelectObject(Player_DC, PlayerBMP);//플레이어
   SelectObject(Enemy_DC, Enemy_UNITBMP);//적
   SelectObject(BlockDC, BlockBMP);//파괴가능 타일(소위 블록)
   SelectObject(thingDC, ITEMBMP);//아이템 
   SelectObject(topDC, TopBmp);//상단 배경
   SelectObject(bottomDC, BottomBMP);//하단배경
   SelectObject(bombDC, bombBMP);//폭파 애니메이션을 넣어줄꺼, 폭파 애니메이션 관련 함수는 Bomb.cpp에
   SelectObject(GOALDC, GOALBMP);//골포인트
   SelectObject(gamewinDC, gamewinBMP);//스테이지 클리어 메세지
   SelectObject(level_upDC, level_upbmp);//레벨업 메세지
   SelectObject(bulletDC, bulletBMP);//레벨업 메세지
   SelectObject(attrDC, STATUPBMP);//스탯 강화창
   SelectObject(gameoverDC, gameoverBMP);//게임오버









//시스템시간 난수
   srand((unsigned)time(NULL));

   //플레이어 초기화
   return TRUE;
}
bool return_up;
//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_TIMER:
		switch (game_state)
		{
		case GAME:
			Game();
			break;
		case GAMESTART:
			/*
			mciSendString(_T("open honglian.mp3 Alias music2"),NULL,0,NULL);
			mciSendString(_T("play music2 repeat"),NULL,0,NULL);*/
			/*	PLAYA(IDR_START);*/


			DrawStart();
			if (keydown_f1 == true) 
			{
				DrawIntroduce();
			}
			if (keydown_f2 == true) 
			{
				DrawCredits();
			}
			if (KEYDOWN(VK_RETURN)) 
			{
				game_state = GAMESELECT;
			}
			BitBlt(winDC, 0, 0, GAME_W, GAME_H, bufferDC, 0, 0, SRCCOPY);

			return_up = false;
			break;
		case GAMESELECT:
			/*mciSendString(_T("close music2"),NULL,0,NULL);*/
			DrawSelect();
			/*
			
			if (keydown_f1==true)
			{
				DrawIntroduce();
			}
			if (keydown_f2==true)
			{
				DrawCredits();
			}


			if (KEYDOWN('1'))
			{
				Player->attack+=20;
				game_state=GAME;
			}else if (KEYDOWN('2'))
			{
				Player->speed+=2;
				game_state=GAME;
			}else if (KEYDOWN('3'))
			{
				Player->attack_cd-=15;
				game_state=GAME;
			}else if (KEYDOWN('4'))
			{
				Player->maxhp+=150;
				Player->hp=Player->maxhp;
				game_state=GAME;
			}else if (KEYDOWN('5'))
			{
				Player->maxmp+=75;
				Player->mp=Player->maxmp;
				game_state=GAME;
			}
			
			*/
			if (KEYUP(VK_RETURN))
				return_up = true;

			if (return_up && KEYDOWN(VK_RETURN))
				game_state = GAME;
			break;
		case GAMEOVER:
			gameover_time--;
			TransparentBlt(winDC, 0, 0, 1366, 768, gameoverDC, 0, 0, 583, 425, RGB(255, 255, 255));
			if (gameover_time == 0) 
			{
				GameStart();
			}
			break;
		case GAMEWIN:
			gamewin_time--;
			if (game_no == game_max - 1) 
			{
				TransparentBlt(winDC, 350, 100, 567, 425, gamewinallDC, 0, 0, 567, 425, RGB(255, 255, 255));
			}
			else TransparentBlt(winDC, 0, 0, 1366, 768, gamewinDC, 0, 0, 567, 425, RGB(255, 255, 255));
			if (gamewin_time == 0) 
			{
				game_no++;
				if (game_no == game_max) 
				{
					game_state = GAMESTART;
					game_no = 0;
					GameStart();
				}
				else
				{
					game_state = GAME;
					DataInit();
				}
			}
			break;
		default:
			break;
		}
		break;
		break;
		//ESC키 누를시 종료 창 뜨게
	case WM_KEYDOWN:
		//mciSendString(_T("close movie"),NULL,0,NULL);

		switch (wParam)
		{
		case VK_ESCAPE:
			if (MessageBox(hWnd, _T("Are you sure you want to quit the game?"), _T("Keyboard"), MB_OKCANCEL) == IDOK)
			{
				PostMessage(hWnd, WM_CLOSE, 0, 0);
			}
			break;
		case WM_CLOSE: 
			DestroyWindow(hWnd);
			break;
		case VK_F1:
			keydown_f1 ^= 1;
			keydown_f2 = false;
			break;
		case VK_F2:
			keydown_f2 ^= 1;
			keydown_f1 = false;
			break;
		case VK_F3:
			keydown_f3 ^= 1;
			if (keydown_f3) 
			{
				mciSendString(_T("close music"), NULL, 0, NULL);
			}
			else {
				mciSendString(_T("open honglian.mp3 Alias music"), NULL, 0, NULL);
				mciSendString(_T("play music repeat"), NULL, 0, NULL);
			}
			break;
		case VK_F4:
			keydown_f4 = !keydown_f4;
			break;
		case VK_F5:
			keydown_f5 ^= 1;
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//게임에 필요한 요소 시작점
//게임 시작
void GameStart() 
{
    game_state = GAMESTART;

    all_id = 0;
    //여기에 플레이어를 생성, 유닛 능력치 설정
    Player = new C_UNIT();
    Player->maxhp = 300;//기본 체력
    Player->maxmp = 100;//기본 마력
    Player->id = all_id++;
    Player->owner = 0;
    Player->armor = 0;//방어력
    Player->life = 1;//목숨 갯수, 
    Player->attack = 50;//기본 공격 데미지

    stage = 0;
    //game_state=GAME;
    DataInit();
}

//게임 메인
void Game()
{
    //화면이동
    ScreenMove();
    //적이 시야안에 있는지 체크
    UnitBlockCheck();

    //키 클릭 반응
    if ((uping == 0) && (!keydown_f5))
    {
        if (player_death == 0)
        {
            Key();
        }
        //업데이트
        BulletMove();
        PlayerStep(*Player);//유저 단계 체크
        EnemyStep();//적 반응
        if (proton_collider > 0) ProtonCollide();//레이저 반응

        frame++;
        time_now = GetTickCount64();//FPS 체크
        if (time_now - time_pre >= 1000)
        {
            fps = frame;
            frame = 0;
            time_pre = time_now;
        }
    }
    if (adding > 0)
    {
        adding--;
        if (adding < 0)
            adding = 0;
    }
    if (uping > 0)
    {
        uping--;
    }
    if (keydown_f3)
    {
        mciSendString(_T("close music"), NULL, 0, NULL);
    }

    //게임 인터페이스 그림
    DrawGame();
}

//키버튼 처리
void Key() 
{
	//유닛 움직임.
	if (KEYDOWN('S')) 
	{
		Player->face = DOWN;
		Player->stop = false;
		if (!keydown_f4)
		{
		//	PLAYB(MOVE_SOUND);//움직임 사운드,발소리
		}

		Move(*Player, DOWN);
	}
	else if (KEYDOWN('A')) 
	{
		Player->face = LEFT;
		Player->stop = false;
		if (!keydown_f4)
		//	PLAYB(MOVE_SOUND);
		Move(*Player, LEFT);
	}
	else if (KEYDOWN('W')) 
	{
		Player->face = UP;
		Player->stop = false;
		if (!keydown_f4)
		//	PLAYB(MOVE_SOUND);
		Move(*Player, UP);
	}
	else if (KEYDOWN('D')) 
	{
		Player->face = RIGHT;
		Player->stop = false;
		if (!keydown_f4)
		//	PLAYB(MOVE_SOUND);
		Move(*Player, RIGHT);
	}
	else if (KEYUP('S')) 
	{
		//Player->face=DOWN;
		Player->stop = true;
	}
	else if (KEYUP('A')) 
	{
		//Player->face=LEFT;
		Player->stop = true;
	}
	else if (KEYUP('W')) 
	{
		//Player->face=UP;
		Player->stop = true;
	}
	else if (KEYUP('D')) 
	{
		//Player->face=RIGHT;
		Player->stop = true;
	};
	if (KEYDOWN('J')) 
	{
		ATTACK(*Player);
	}
	if (KEYDOWN('K'))
	{
		if (Player->mp >= 20)
		{
			k_down = true;
			if ((++laser_index) > 1)//버튼 계속 누를 경우
			{
				laser_open = false;
				if (laser_index % 20 == 0)
				{
					Player->mp -= 10;
					Laser_ATTACK(*Player);

				}
			}
			if (laser_open)//버튼 누를 경우(짧게)
			{
				Player->mp -= 10;
				Laser_ATTACK(*Player);
			}
		}

	}
	else if (KEYUP('K'))
	{
		k_down = false;
		laser_index = 0;
		laser_open = true;
	}


	if ((KEYDOWN(VK_SPACE)) && (charge == -1) && (Player->mp >= 10)) 
	{
		if (Player->attack_frame == 0) 
		{
			charge = 0;
			Player->attack_frame = Player->attack_cd;
			Player->mp -= 10;
		}
	}
	if ((KEYUP(VK_SPACE)) && (charge != -1)) 
	{
		ATTACKCharge(*Player, charge, chargemax);
		charge = -1;
	}
	if (KEYDOWN(VK_OEM_1)) 
	{
		if ((proton_collider == 0) && (Player->mp >= 80)) 
		{
			proton_collider = 300;
			Player->mp -= 80;
		}
	}

	//업그레이드 및 공격력 증가 
	if (LevelUping == true && KEYDOWN('U'))
	{
		Player->attack += 12;
		LevelUping = false;
		AddAttring = 1;
		adding = 150;
	}
	if (LevelUping == true && KEYUP('U'))
	{
		//if(adding==0)
			//AddAttring=0;
	}
	//속도 업
	if (LevelUping == true && KEYDOWN('I'))
	{
		AddAttring = 2;
		Player->speed += 1;
		LevelUping = false;
		adding = 150;

	}
	if (LevelUping == true && KEYUP('I'))
	{


	}
	//HP 총량 업글
	if (LevelUping == true && KEYDOWN('O'))
	{
		AddAttring = 3;
		Player->maxhp += 100;
		Player->hp = Player->maxhp;
		LevelUping = false;
		adding = 150;

	}
	if (LevelUping == true && KEYUP('O'))
	{

	}
	//MP 총량 업글
	if (LevelUping == true && KEYDOWN('P'))
	{
		AddAttring = 4;
		Player->maxmp += 50;
		Player->mp = Player->maxmp;
		LevelUping = false;
		adding = 150;

	}
	if (LevelUping == true && KEYUP('P'))
	{

	}
}
//미사일 나중에 구현
//게임드로잉
void DrawGame() 
{
	//BitBlt(bufferDC,0,0,GAME_TOTW,GAME_H,PlayerDC,0,0,WHITENESS);

	//배경 그림
	DrawBG();
	//균열 그림(파괴시 나오는 그림)
	DrawPiton();
	//플레이어 그림(죽지 않았을경우)
	if (player_death == 0) {
		DrawPlayer();
		DrawLaser(laserxs, laserys, laserxe, laserye);
	}
	//적 그리기
	DrawEnemy();
	//블록 그리기
	DrawBlock();
	//아이템 그림 및 인 게임내 드랍
	Item();
	//총알 그리기
	DrawBullet();
	//폭발 그림
	if (!keydown_f5) 
	{
		DrawBomb();
	}
	//파워바 그리기
	if (player_death == 0 && charge >= 0) DrawCharge();
	//미사일 그리기
	//DrawMissile();
	//화면에 출력
	HandleThing();
	//DrawLaser(500,500,800,800);
	if (shaking > 0)//흔들림
	{
		ShakeScreen();
		shaking--;
	}
	if (keydown_f1 == true) 
	{
		DrawIntroduce();
	}
	if (keydown_f2 == true) 
	{
		DrawCredits();
	}
	PrintToScreen();
}
//데이터 초기화
void DataInit() 
{
	SetTimer(hWnd, GAME_ID, GAME_TIME, NULL);
	Player->face = RIGHT;
	Player->hp = Player->maxhp;
	Player->mp = Player->maxmp;
	Player->x = 30;
	Player->y = 250;
	offset_x = 0;

	time_now = 0;
	time_pre = GetTickCount64();
	fps = 0;
	frame = 0;

	for (int i = 0; i < block_wide; i++)
		for (int j = 0; j < block_high; j++) 
		{
			block_layout[j * block_wide + i] = block_all[game_no][j * block_wide + i];
		}
	for (int i = 0; i < block_wide; i++)
		for (int j = 0; j < block_high; j++) 
		{
			mapIndex[j * block_wide + i] = map_all[game_no][j * block_wide + i];
		}

	//BOSS모드
	boss_mode = false;
	//동적 리소스 할당
	//불렛 클리어
	for (list<C_Bullet*>::iterator i = bullet.begin(); i != bullet.end(); ++i)
		delete* i;
	bullet.clear();
	//폭발 클래스 비움 
	for (list<C_Bomb*>::iterator i = bomb.begin(); i != bomb.end(); ++i)
		delete* i;
	bomb.clear();
	//적 클래스 클리어
	for (list<C_UNIT*>::iterator i = enemy.begin(); i != enemy.end(); ++i)
		delete* i;
	enemy.clear();

	for (list<C_Thing*>::iterator i = thing.begin(); i != thing.end(); ++i)
		delete* i;
	thing.clear();
	Player->attack_temp = 0;
	Player->speed_temp = 0;

	for (list<C_Block*>::iterator i = object.begin(); i != object.end(); ++i)
		delete* i;
	object.clear();
	//수평
	wintime = 0;
	//베이스
	base_time = 0;
	//플레이어 부활
	player_death = false;
	//적 숫자
	//enemy_num=0;
	//enemy_rest=enemy_max;
	//enemy_time=1;
	//소품이 삭제되는 경우
	item = NONE;
	item_stay_time = 0;
	//오브젝트 컨테이너 초기화 함수
	AssignBlockMap();

	int blockX;
	int blockY;
	int mapX;
	int mapY;
	int blood;
	int i;//장애물 계산
	C_Block* block;
	object.clear();
	for (vector<int>::iterator iter = block_map.begin(); iter != block_map.end(); ++iter) 
	{
		int& id = *iter;
		i = iter - block_map.begin();
		blockX = i % block_wide;
		blockY = i / block_wide;

		if ((id > 0) && (id < 40)) 
		{
			mapX = blockX * 64;
			mapY = blockY * 64 - offset_y;
			blood = Block_attr[id][1];
			block = new C_Block(id, mapX, mapY, blood);
			object.push_back(block);
		}

		if (id >= 90) {
			int enemy_no = id % 10;//카테고리 판단, 90대 부터 시작, 90 카테고리 9의 0번 , 91 카테고리 9의 1번
			C_UNIT* et = new C_UNIT();
			//maxhp,speed,attack,attack_cd,armor
			et->maxhp = enemy_attr[enemy_no][0];
			et->hp = et->maxhp;
			et->speed = enemy_attr[enemy_no][1];
			et->attack = enemy_attr[enemy_no][2];
			et->attack_cd = enemy_attr[enemy_no][3];
			et->armor = enemy_attr[enemy_no][4];
			et->exp = enemy_attr[enemy_no][5];
			et->face = LEFT;
			//et->face = LEFT;
			et->activate = false;
			et->x = blockX * 64;
			et->y = blockY * 64;
			et->id = all_id++;	//고유 식별 아이디 
			et->owner = 1;		//1은 적을 의미
			et->no = enemy_no;		//인덱스를 통해 적을 관리한다.
			enemy.push_back(et);
		}

	}
}


void DrawStart() 
{
	BitBlt(bufferDC, 0, 0, GAME_W, GAME_H, startDC, 0, 0, SRCCOPY);
}

void DrawIntroduce() 
{
	SelectObject(introduceDC, introduceBMP);
	TransparentBlt(bufferDC, 333, 134, 700, 500, introduceDC, 0, 0, 700, 500, RGB(255, 0, 255));
}
void DrawCredits() 
{
	SelectObject(introduceDC, CreditBMP);
	TransparentBlt(bufferDC, 333, 134, 700, 500, introduceDC, 0, 0, 700, 500, RGB(255, 0, 255));
}
void DrawDeath() 
{
	TransparentBlt(bufferDC2, 350, 100, 567, 425, recoveryDC, 0, 0, 567, 425, RGB(255, 255, 255));
}



void DrawSelect() 
{
	BitBlt(bufferDC, 0, 0, GAME_W, GAME_H, bufferDC, 0, 0, WHITENESS);
	BitBlt(bufferDC, 0, 0, GAME_W, GAME_H, selectDC, 0, 0, SRCCOPY);
	TransparentBlt(bufferDC, Player->x, Player->y - offset_y, 64, 64, Player_DC, 64 * 3, 0, 64, 64, RGB(255, 255, 255));//플레이어 이동
	BitBlt(winDC, 0, 0, GAME_W, GAME_H, bufferDC, 0, 0, SRCCOPY);
}

void DrawBlock() //골포함 블록 애니메이션은 전부 다 block cpp에 있음
{
	for (list<C_Block*>::iterator iter = object.begin(); iter != object.end();)
	{
		bool erase = false;
		if (((*iter)->activate) && ((*iter)->id != PITON))
		{
			if ((*iter)->id == GOAL)
			{
				//승리
				if ((*iter)->life <= 0)
				{
					game_state = GAMEWIN;
					if (game_no == game_max - 1) 
					{
						gamewin_time = 400;
					}
					else gamewin_time = 250;
				}
				(*iter)->DrawBlock(bufferDC, GOALDC);

			}
			else
			{
				(*iter)->DrawBlock(bufferDC, BlockDC);
			}
		}
		if ((*iter)->id == Block_NONE)
		{
			JudgeThingB(*iter);
			iter = object.erase(iter);
			erase = true;
		}
		if (!erase)
		{
			iter++;
		}
	}
}

void DrawPiton() //균열 그림, 오브젝트의 체력 데미지 정도에 따라서 
{
	for (list<C_Block*>::iterator iter = object.begin(); iter != object.end(); iter++)
	{
		if ((*iter)->id == PITON)
		{
			(*iter)->DrawBlock(bufferDC, BlockDC);
		}
	}
}

//BitBlt(이미지 출력할 위치 핸들,이미지 출력할 위치 x좌표1,이미지 출력한 위치 y좌표2,원본이미지 너비3,원본이미지 높이4,이미지 핸들5,가져올 이미지 시작지점 x좌표,가져올 이미지 시작지점 y좌표,이미지 출력방법)
//주의사항 가져올 이미지의 시작지점은 x,y좌표 이 위치부터 원본이미지 너비,높이만큼 잘라 가져옴)
//백그라운드 그림(배경 그림)
void DrawBG() 
{
	double X;
	X = (((offset_x) / double(GAME_W)) - (int)(offset_x / GAME_W)) * GAME_W;
	//배경 그리기
	BitBlt(bufferDC, offset_x + (double)(GAME_W - X) - 1, 0 + 96, X, 576, backgroundDC, 0, 0, SRCCOPY);//SRCCOPY는 원본이미지 고대로 가져옴
	BitBlt(bufferDC, offset_x, 0 + 96, GAME_W - X, 576, backgroundDC, X, 0, SRCCOPY);
	//TOP 상단 
	BitBlt(bufferDC, offset_x + (double)(GAME_W - X) - 1, 0, X, 96, topDC, 0, 0, SRCCOPY);
	BitBlt(bufferDC, offset_x, 0, GAME_W - X, GAME_H, topDC, X, 0, SRCCOPY);
	//BUTTOM 하단
	//TransparentBlt(bufferDC, offset_x + (double)(GAME_W - X) - 1, GAME_H - 96, 1366, 96, bottomDC, 0, 0, 1366, 96, RGB(255, 255, 255));
//	BitBlt(bufferDC, offset_x + (double)(GAME_W - X) - 1, GAME_H - 96, X, 96, bottomDC, 0, 0, SRCCOPY);
	//BitBlt(bufferDC, offset_x, GAME_H - 96, GAME_W - X, GAME_H - 96, bottomDC, X, 0, SRCCOPY);
	for (int i = 0; i < rows * cols; i++)
	{

		int rowNum = i / cols;
		int colNum = i % cols;
		int x = colNum * 64;
		int y = rowNum * 64;
		if (mapIndex[i] != BLANK)
			TransparentBlt(bufferDC, x, y + 96, 64, 64, sandDC, (mapIndex[i] % 4) * 64, (mapIndex[i] / 4) * 64, 64, 64, RGB(255, 255, 255));
	}
}

//미사일 그림,일단 나중에 씀, 오류 해결 안됨 유투브 다시 참조해볼것
/*
void DrawMissile() 
{

	if (myMissile == NULL) return;

	if (lock_enemy != NULL) {
		myMissile->target_x = lock_enemy->x;
		myMissile->target_y = lock_enemy->y;
	}

	if (missile_index < 24)//미사일 상승 애니메이션
	{
		int pic_index = missile_index / 4;
		myMissile->y -= 3;
		TransparentBlt(bufferDC, myMissile->x, myMissile->y + 64, 64, 64, missileDC, pic_index * 64, 0, 64, 64, RGB(255, 255, 255));
	}
	if (missile_index == 16) {
		double degree_d = atan2(myMissile->target_y - myMissile->y, myMissile->target_x - myMissile->x);
		int degree = (int)(degree_d * 180 / PI);
		int area = -1;
		if (degree <= -157.5 || degree >= 157.5) area = 3; //left
		else if (degree >= -157.5 && degree <= -112.5) area = 4; //left-up
		else if (degree >= -112.5 && degree <= -67.5) area = 0;//up
		else if (degree >= -67.5 && degree <= -22.5) area = 5;//right-up
		else if (degree >= -22.5 && degree <= 22.5) area = 1;//right
		else if (degree >= 22.5 && degree <= 67.5) area = 6; //right-down
		else if (degree >= 67.5 && degree <= 112.5) area = 2;//down
		else if (degree >= 112.5 && degree <= 157.5) area = 7;//left-down

		printf("degree is:%d #area is:%d \n", degree, area);

		if (area == -1) area = 1;
		myMissile->direction = area;

		TransparentBlt(bufferDC, myMissile->x, myMissile->y + 64, 64, 64, missileDC, myMissile->direction % 4 * 64, (myMissile->direction / 4 + 1) * 64, 64, 64, RGB(255, 255, 255));
	}
	if (missile_index > 16)
	{
		int move_dist = 50;
		double real_dist = sqrt(pow(myMissile->target_x - myMissile->x, 2) + pow(myMissile->target_y - myMissile->y, 2));
		if (real_dist < move_dist)
		{
			myMissile->x = myMissile->target_x;
			myMissile->y = myMissile->target_y;

			if (lock_enemy != NULL)
				lock_enemy->hp -= 300;//높은 데미지
			OpenExplode(12, myMissile->x + 32, myMissile->y + 32, PLAYER_BOMB, BUCKET);
			TransparentBlt(bufferDC, myMissile->x, myMissile->y + 64, 64, 64, missileDC, myMissile->direction % 4 * 64, (myMissile->direction / 4 + 1) * 64, 64, 64, RGB(255, 255, 255));
			lock_enemy = NULL;
			myMissile = NULL;
		}
		else {
			double degree_d = atan2(myMissile->target_y - myMissile->y, myMissile->target_x - myMissile->x);
			myMissile->x += move_dist * cos(degree_d);
			myMissile->y += move_dist * sin(degree_d);
			TransparentBlt(bufferDC, myMissile->x, myMissile->y + 64, 64, 64, missileDC, myMissile->direction % 4 * 64, (myMissile->direction / 4 + 1) * 64, 64, 64, RGB(255, 255, 255));
		}

	}

	missile_index++;
}
*/

//화면에 출력
//화면에 버퍼 출력
void PrintToScreen()
{
	BitBlt(bufferDC2, 0 + bgx, 0 + bgy, GAME_W, GAME_H, bufferDC, 0 + offset_x, 0, SRCCOPY);
	char str[10] = "";
	sprintf_s(str, "%d", fps);
	//TextOutA(bufferDC2,1350,0,str,strlen(str)); // fps 표기
	DrawStateMap();
	DrawLevelUp();
	TransparentBlt(bufferDC2, 995, 677, 375, 96, skillDC, 0, 0, 375, 96, RGB(255, 255, 255));
	if (player_death > 0) DrawDeath();
	BitBlt(winDC, 0, 0, GAME_W, GAME_H, bufferDC2, 0, 0, SRCCOPY);
}

void DrawBomb() 
{
	for (list<C_Bomb*>::iterator iter = bomb.begin(); iter != bomb.end();)
	{
		//폭발 범위 및 좌표
		int x;
		int y;
		int size;
		C_Bomb* b = *iter;
		int damage = b->id / 5 + 1;
		if (b->id == 12) damage *= 2;
		b->DrawBomb(bufferDC, bombDC);
		//폭발 발생시 근처 적에게 데미지 줌
		size = b->size;
		x = b->x;//폭발의 중심좌표
		y = b->y + offset_y;

		for (list<C_Block*>::iterator iter = object.begin(); iter != object.end(); iter++)
		{
			C_Block& b = **iter;//참조
			//if (b.id!=BUCKET)
			{
				if (Collide(b.x, b.y, 64, 64, x - size / 2, y - size / 2 - offset_y, size, size))
				{
					b.life -= damage;
				}
			}

		}

		switch (b->owner)
		{
		case PLAYER_BOMB:
			//나의 폭발 공격, 적유닛감지, 폭발 범위안에 적 유닛가 있을시 데미지 
			for (list<C_UNIT*>::iterator enermy_iter = enemy.begin(); enermy_iter != enemy.end(); enermy_iter++)
			{
				C_UNIT& enermy = **enermy_iter;
				if (Collide(enermy.x, enermy.y, 64, 64, x - size / 2, y - size / 2, size, size))
				{
					enermy.hp -= damage;
				}

			}
			break;
		case ENERMY_BOMB:
			//내가 폭발 근처 있을시 
			if (Collide(Player->x, Player->y, 64, 64, x - size / 2, y - size / 2, size, size))
			{
				Player->hp -= damage;
			}
			break;
		case OBJECT_BOMB:
			//오브젝트의 체력 판정실시, 오브젝트 폭발시 근처에 나와 적에 대해서 체력판정실시
			for (list<C_UNIT*>::iterator enermy_iter = enemy.begin(); enermy_iter != enemy.end(); enermy_iter++)
			{
				C_UNIT& enemy = **enermy_iter;
				if (Collide(enemy.x, enemy.y, 64, 64, x - size / 2, y - size / 2, size, size))
				{
					enemy.hp -= damage;//적 체력 감소
				}

			}
			if (Collide(Player->x, Player->y, 64, 64, x - size / 2, y - size / 2, size, size))
			{
				Player->hp -= damage;//내 에너지 감소
			}
			break;

		default:
			break;
		}



		bool erase = false;
		if ((*iter)->end == true)
		{
			//delete (*iter);
			iter = bomb.erase(iter);
			erase = true;
		}
		if (erase == false)
		{
			iter++;
		}
	}
}

// 플레이어 탄환과 공격감지
void PlayerBullet() 
{
}
// 적 유닛 처리 및 그리기
void Enemy_UNIT() 
{
}
void EnemyBullet() 
{
}
// 소품 처리 및 그리기
void Item() 
{
}
// 모든지도 로딩
void AssignBlockMap() 
{
		block_map.assign(block_layout, block_layout + block_wide * block_high * map_max);
}
// 두 직사각형의 왼쪽 상단 지점의 좌표와 길이 및 너비 인 충돌 감지(즉 각 개체마다 사각 개체 부여 및 충돌 감지
bool Collide(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh) 
{

	ax += offset;
	ay += offset;
	aw -= offset * 2;
	ah -= offset * 2;
	bx += offset;
	by += offset;
	bw -= offset * 2;
	bh -= offset * 2;
	if ((ax >= bx) && (ax <= bx + bw) && (ay >= by) && (ay <= by + bh))return true;
	if ((ax + aw >= bx) && (ax + aw <= bx + bw) && (ay >= by) && (ay <= by + bh))return true;
	if ((ax >= bx) && (ax <= bx + bw) && (ay + ah >= by) && (ay + ah <= by + bh))return true;
	if ((ax + aw >= bx) && (ax + aw <= bx + bw) && (ay + ah >= by) && (ay + ah <= by + bh))return true;

	if ((bx >= ax) && (bx <= ax + aw) && (by >= ay) && (by <= ay + ah))return true;
	if ((bx + bw >= ax) && (bx + bw <= ax + aw) && (by >= ay) && (by <= ay + ah))return true;
	if ((bx >= ax) && (bx <= ax + aw) && (by + bh >= ay) && (by + bh <= ay + ah))return true;
	if ((bx + bw >= ax) && (bx + bw <= ax + aw) && (by + bh >= ay) && (by + bh <= ay + ah))return true;
	return false;
}

void BulletEnd(C_Bullet* b, int _x, int _y, int id) //총알 끝에서 폭발일어남
{
	int power = b->attack / 12;
	if (power <= 0)power = 1;
	if (power >= 11)power = 11;
	if (id == BUCKET) id = STONE;
	switch (b->face) 
	{
	case DOWN:
		OpenExplode(power, _x + b->wide / 2, _y + b->high / 2, b->owner, id);
		break;
	case LEFT:
		OpenExplode(power, _x + b->wide / 2, _y + b->high / 2, b->owner, id);
		break;
	case UP:
		OpenExplode(power, _x + b->wide / 2, _y + b->high / 2, b->owner, id);
		break;
	case RIGHT:
		OpenExplode(power, _x + b->wide / 2, _y + b->high / 2, b->owner, id);
		break;
	}

}

//erase함수는 지우기 함수다. 벡터를 지운다
void BulletMove()
{
	for (list<C_Bullet*>::iterator iter_bullet = bullet.begin(); iter_bullet != bullet.end();) 
	{
		C_Bullet* b = *iter_bullet;
		if (b->dead) { iter_bullet++; continue; }
		bool erase = false;
		int _x = b->x;
		int _y = b->y;
		switch (b->face) 
		{
		case DOWN:
			_y = _y + b->speed;
			if (_y > GAME_H - offset_y + 100) 
			{
				iter_bullet = bullet.erase(iter_bullet);
				erase = true;
				continue;
			}
			break;
		case LEFT:
			_x = _x - b->speed;
			if (_x < offset_x - 400) 
			{
				iter_bullet = bullet.erase(iter_bullet);
				erase = true;
				continue;
			}
			break;
		case UP:
			_y = _y - b->speed;
			if (_y < 0 + offset_y - 100) 
			{
				iter_bullet = bullet.erase(iter_bullet);
				erase = true;
				continue;
			}

			break;
		case RIGHT:
			_x = _x + b->speed;
			if (_x > offset_x + GAME_W + 400) 
			{
				iter_bullet = bullet.erase(iter_bullet);
				erase = true;
				continue;
			}
			break;
		}//switch end



		for (list<C_Block*>::iterator iter_object = object.begin(); iter_object != object.end(); iter_object++) 
		{
			C_Block* o = *iter_object;
			if ((Collide(_x, _y, b->wide, b->high, o->x, o->y + offset_y, 64, 64))) 
			{
				if ((o->id == TREE) || (o->id == WALL) || (o->id == STONE) || (o->id == BUCKET) || (o->id == IRON) || (o->id == GOAL)) 
				{
					o->life -= b->attack;
					if ((o->id == TREE) && (o->state == NORMAL_STATE)) 
					{
						o->state = SHOOT_STATE;//사격상태, O->life는 감소, 즉 오브젝트 라이프 감소 (b{Bullect 클래스의 공격력만큼)
					}/*
					if ((o->id==BUCKET)&&(o->life<=0)){
						OpenExplode(12,o->x+32,o->y+offset_y+32,OBJECT_BOMB,BUCKET);
					}*/
					BulletEnd(b, _x, _y, o->id);
					iter_bullet = bullet.erase(iter_bullet);
					erase = true;

					break;
				}
				if ((o->id == GRASS) && (o->state == NORMAL_STATE)) 
				{
					o->life -= b->attack;
					o->state = SHOOT_STATE; //잔디 오브젝트 라이프 감소 b 즉 공격력 만큼 감소
				}
			}
		}//object for end
		if (erase)continue;

		for (list<C_UNIT*>::iterator iter_unit = enemy.begin(); iter_unit != enemy.end(); iter_unit++) 
		{
			C_UNIT* t = *iter_unit;
			if ((b->owner != t->owner) && (t->activate) && (Collide((int)b->x, (int)b->y, b->wide, b->high, t->x, t->y, 64, 64))) 
			{
				t->hp -= b->attack;
				BulletEnd(b, _x, _y, Enemy);
				iter_bullet = bullet.erase(iter_bullet);
				erase = true;
				break;
			}

		}//enemy for end
		if ((b->owner == 1) && (Collide(Player->x, Player->y, 64, 64, b->x, b->y, b->wide, b->high))) 
		{
			Player->hp -= b->attack;
			BulletEnd(b, _x, _y, Enemy);
			iter_bullet = bullet.erase(iter_bullet);
			erase = true;
			break;
		}
		if (erase)continue;

		for (list<C_Bullet*>::iterator iter_bullet2 = bullet.begin(); iter_bullet2 != bullet.end(); iter_bullet2++) 
		{
			C_Bullet* b2 = *iter_bullet2;

			if ((b->owner != b2->owner) && (Collide(b->x, b->y, b->wide, b->high, b2->x, b2->y, b2->wide, b2->high))) 
			{
				b->hp -= b2->attack;
				b2->hp -= b->attack;
				if (b2->hp <= 0)b2->dead = true;
				if (b->hp <= 0) {
					b->dead = true;
					BulletEnd(b, _x, _y, Enemy);
					iter_bullet = bullet.erase(iter_bullet);
					erase = true;
					break;
				}
			}

		}//bullet2 for end
		if (erase)continue;

		b->x = _x;
		b->y = _y;
		if (!erase)iter_bullet++;
	}//bullet1 for end

	for (list<C_Bullet*>::iterator iter_bullet = bullet.begin(); iter_bullet != bullet.end();) 
	{
		C_Bullet* b = *iter_bullet;
		if (b->dead) {
			iter_bullet = bullet.erase(iter_bullet);
			BulletEnd(b, b->x, b->y, Enemy);
			continue;
		}
		iter_bullet++;
	}
}
//플레이어 상태 업데이트
void PlayerStep(C_UNIT& t)
{
	if (player_death > 0) 
	{
		player_death--;
		if (player_death == 0) 
		{
			t.hp = t.maxhp;
		}
	}
	else {
		if (!t.stop) 
		{
			t.frame++;
			t.step = (t.frame / t.frameper);
			if (t.step == t.stepmax) 
			{
				t.step = 0;
				t.frame = 0;
			}
		}
		if (t.hp <= 0) 
		{
			t.life--;
			OpenExplode(6, t.x + 32, t.y + 32, PLAYER_BOMB, Enemy);
			if (t.life == 0) 
			{
				game_state = GAMEOVER;
				gameover_time = 150;
			}
			else {
				player_death = 200;
			}
		}
		if (t.exp >= lvexp[t.lv]) 
		{
			uping = 100;
			t.exp -= lvexp[t.lv];
			t.lv++;
			LevelUping = true;
		}
		if (mp_decrease_frame > 0)mp_decrease_frame--;
		if (mp_decrease_frame == 0) {
			mp_decrease_frame = mp_decrease_cd;
			t.mp--;
		}
		if (t.attack_frame > 0)t.attack_frame--;
	}
}
//적 상태 업데이트
void EnemyStep() 
{
	for (list<C_UNIT*>::iterator iter_unit = enemy.begin(); iter_unit != enemy.end();) 
	{
		C_UNIT* et = *iter_unit;
		bool erase = false;
		if (et->hp <= 0) 
		{
			JudgeThingE(et);
			iter_unit = enemy.erase(iter_unit);
			OpenExplode(6, et->x + 32, et->y + 32, ENERMY_BOMB, Enemy);
			Player->exp += et->exp;
			Player->mp += et->exp / 30 + 4;
			if (et == lock_enemy)lock_enemy = NULL;//미사일에 조준된 적이 죽으면 미사일을 다시 쓸 수 있다.
			if (Player->mp > Player->maxmp) 
			{
				Player->mp = Player->maxmp;
			}
			erase = true;
		}
		if (!et->stop) 
		{
			et->frame++;
			et->step = (et->frame / et->frameper);
			if (et->step == et->stepmax) 
			{
				et->step = 0;
				et->frame = 0;
			}
			if ((!Move(*et, et->face)) && (et->face_frame == 0)) 
			{
				et->face = (et->face + rand() % 3 + 1) % 4;
				et->face_frame = et->face_cd;
			}
		}
		if (et->attack_frame > 0)et->attack_frame--;
		if (et->face_frame > 0)et->face_frame--;
		if (!erase)iter_unit++;
		if (et->activate)EnemyAI(*et);
	}
}

//로그라이크 듀토리얼 유튭 참조
int AIsearch(C_UNIT& t, int ex, int ey) 
{
	int ox = offset_x / 64;
	const int m = GAME_W / 64 + 4;
	const int n = block_high;
	int a[m][n];
	bool b[m][n];

	struct point 
	{
		int x; int y; int dist; int dire;
	}p;
	point dl[n * m];
	const int d[4][2] = { 0,1,-1,0,0,-1,1,0 };
	for (int i = 0; i < m; i++) 
	{
		for (int j = 0; j < n; j++) 
		{
			a[i][j] = 0;
			b[i][j] = false;
		}
	}
	for (list<C_Block*>::iterator iter_object = object.begin(); iter_object != object.end(); iter_object++) 
	{
		C_Block* ob = *iter_object; //블록 클래스의 오브젝트 포인터 반복자 오브젝트 iter_Object
		int x = ((double)ob->x - offset_x) / 64;
		int y = (int)(((double)ob->y + offset_y) / 64);
		if ((ob->activate) && (x >= 0) && (x < m)) 
		{
			a[x][y] = ob->id;
		}
	}

	int sx = ((t.x + 32) / 64) - ox;
	int sy = ((t.y + 32) / 64);
	int xx, yy;
	int find = -1;
	if (sx >= m) return find;
	b[sx][sy] = true;
	int head = 0;
	int tail = 1;
	p.x = sx;
	p.y = sy;
	p.dist = 0;
	p.dire = -1;
	dl[head] = p;
	while (head != tail)
	{
		for (int i = 0; i < 4; i++) 
		{
			xx = dl[head].x + d[i][0];
			yy = dl[head].y + d[i][1];
			if ((xx < 0) || (xx >= m) || (yy < 0) || (yy >= n))continue;
			if ((!b[xx][yy]) && ((a[xx][yy] == Block_NONE) || (a[xx][yy] == PITON) || (a[xx][yy] == GRASS) || (a[xx][yy] >= 90))) 
			{
				point newp;
				newp.x = xx;
				newp.y = yy;
				newp.dist = dl[head].dist + 1;
				if (dl[head].dire == -1)newp.dire = i;
				else newp.dire = dl[head].dire;
				dl[tail] = newp;
				tail++;
				b[xx][yy] = true;
				if ((xx == ex) && (yy == ey)) 
				{
					find = newp.dire;
					break;
				}
			}
		}
		head++;
		if (find > -1) break;
	}
	return find;
}

void AImove_close(C_UNIT& t) //플레이어가 근처에 있을때 적 움직임
{
	int ox = offset_x / 64;
	int ex = ((Player->x + 32) / 64) - ox;
	int ey = ((Player->y + 32) / 64);
	int find = AIsearch(t, ex, ey);
	if (find == -1) 
	{
		t.stop = true;
		int f = rand() % 10;
		if (f < 4) 
		{
			t.face = f;
			t.stop = false;
		}

	}
	else 
	{
		t.face = find;
		t.stop = false;
	}
};
void AIstop(C_UNIT& t) 
{
	t.stop = true;
};

void AImove_away(C_UNIT& t) //멀어질때
{
	int ox = offset_x / 64;
	int ex = ox + GAME_W / 64 + 2;
	int ey = rand() % block_high;
	int find = AIsearch(t, ex, ey);
	if (find == -1) 
	{
		t.stop = true;
		int f = rand() % 10;
		if (f < 4) 
		{
			t.face = f;
			t.stop = false;
		}
	}
	else 
	{
		t.face = find;
		t.stop = false;
	}
};
void EnemyAI(C_UNIT& t) 
{
	if (t.ai_frame > 0)t.ai_frame--;
	if (t.attack_frame == 0) 
	{
		int ran = rand() % 1500;
		int px = Player->x;
		int py = Player->y;
		switch (t.face) 
		{
		case DOWN:
			if (t.y < py) 
			{
				if (abs(t.x - px) <= 3) 
				{
					if (ran < 60) ATTACK(t);
				}
				else if (ran < 40) ATTACK(t);
			}
			else if (ran < 20) ATTACK(t);
			break;
		case LEFT:
			if (t.x > px) {
				if (abs(t.y - py) <= 2) 
				{
					if (ran < 60) ATTACK(t);
				}
				else if (ran < 40) ATTACK(t);
			}
			else if (ran < 20) ATTACK(t);
			break;
		case UP:
			if (t.y > py) {
				if (abs(t.x - px) <= 3) 
				{
					if (ran < 60) ATTACK(t);
				}
				else if (ran < 40) ATTACK(t);
			}
			else if (ran < 20) ATTACK(t);
			break;
		case RIGHT:
			if (t.x < px) {
				if (abs(t.x - px) <= 2) {
					if (ran < 60) ATTACK(t);
				}
				else if (ran < 40) ATTACK(t);
			}
			else if (ran < 20) ATTACK(t);
			break;
		}
	}

	if ((t.ai_frame == 0) || ((t.ai_frame == t.ai_judgecd * 4 / 5) && (t.ai_step == 0))) {
		t.ai_frame = t.ai_judgecd;
		t.ai_step = -1;

		const C_UNIT& p = *Player;
		double dist = abs(p.x - t.x) + abs(p.y - t.y);
		double hpercent = t.hp / t.maxhp;
		int ran = rand() % 100;

		if (dist <= 64 * 5) 
		{
			if (hpercent < 0.25) 
			{
				if (ran < 5) 
				{
					AImove_away(t);
					t.ai_step = 1;
				}
				else if (ran < 90) 
				{
					AImove_close(t);
					t.ai_step = 2;
				}
				else {
					AIstop(t);
					t.ai_step = 0;
				}
			}
			else {
				if (ran < 5) 
				{
					AImove_away(t);
					t.ai_step = 1;
				}
				else if (ran < 90) 
				{
					AImove_close(t);
					t.ai_step = 2;
				}
				else {
					AIstop(t);
					t.ai_step = 0;
				}
			}
		}
		else if (dist <= 64 * 12) 
		{
			if (hpercent < 0.25) 
			{
				if (ran < 5) 
				{
					AImove_away(t);
					t.ai_step = 1;
				}
				else if (ran < 80) 
				{
					AImove_close(t);
					t.ai_step = 2;
				}
				else {
					AIstop(t);
					t.ai_step = 0;
				}
			}
			else {
				if (ran < 5) 
				{
					AImove_away(t);
					t.ai_step = 1;
				}
				else if (ran < 80) 
				{
					AImove_close(t);
					t.ai_step = 2;
				}
				else {
					AIstop(t);
					t.ai_step = 0;
				}
			}
		}
		else if (dist <= 64 * 24) 
		{
			if (hpercent < 0.25) 
			{
				if (ran < 5) 
				{
					AImove_away(t);
					t.ai_step = 1;
				}
				else if (ran < 50) 
				{
					AImove_close(t);
					t.ai_step = 2;
				}
				else 
				{
					AIstop(t);
					t.ai_step = 0;
				}
			}
			else {
				if (ran < 5) 
				{
					AImove_away(t);
					t.ai_step = 1;
				}
				else if (ran < 70) 
				{
					AImove_close(t);
					t.ai_step = 2;
				}
				else 
				{
					AIstop(t);
					t.ai_step = 0;
				}
			}
		}
	}
	else if (t.ai_frame % t.ai_searchcd == 0) 
{
		switch (t.ai_step) 
		{
		case 0:
			AIstop(t);
			break;
		case 1:
			AImove_away(t);
			break;
		case 2:
			AImove_close(t);
			break;
		}
	}

}
//유닛 이동
bool Move(C_UNIT& t, int dire)
{
	if ((t.owner == 0) && (charge >= 0))return false;
	double _x, _y;
	switch (dire)
	{
	case LEFT:
		_x = t.x - (t.speed + t.speed_temp) * t.speedbate;
		_y = t.y;
		if (_x < 0) _x = 0;
		break;
	case UP:
		_x = t.x;
		_y = t.y - (t.speed + t.speed_temp) * t.speedbate;
		if (_y < 0) _y = 0;
		break;
	case DOWN:
		_x = t.x;
		_y = t.y + (t.speed + t.speed_temp) * t.speedbate;
		if (_y + 64 >= block_high * 64)_y = block_high * 64 - 64;
		break;
	case RIGHT:
		_x = t.x + (t.speed + t.speed_temp) * t.speedbate;
		_y = t.y;
		if (_x + 64 >= block_wide * 64)_x = block_wide * 64 - 64;
		break;
	}
	int block_x = (int)(_x + 32) / 64;
	int block_y = (int)(_y + 32) / 64;
	int temp = mapIndex[block_y * block_wide + block_x];
	if (temp == BLANK) 
	{
		t.speedbate = 1;
	}
	else if (temp == ROAD) 
	{
		t.speedbate = 1.33;
	}
	else if (temp == ICE) 
	{
		t.speedbate = 2;
	}
	else if (temp >= SAND1) 
	{
		t.speedbate = 0.5;
	}
	for (list<C_Block*>::iterator iter_object = object.begin(); iter_object != object.end(); iter_object++) 
	{
		C_Block* ob = *iter_object;
		if (ob->id != Block_NONE) 
		{
			//if(ob->activate){
			if (Collide((int)_x, (int)_y, 64, 64, ob->x, ob->y + offset_y, 64, 64)) 
			{
				if (ob->id == GRASS) 
				{
					if (ob->state == NORMAL_STATE) 
					{
						ob->state = SHAKE_STATE;
					}
				}
				else if (ob->id == PITON) 
				{
					if (ob->cd == 0) 
					{
						if (t.owner == 0)t.hp -= 5;
						else t.hp -= 3;
						ob->cd = 50;
						if (!keydown_f4 && t.id == Player->id)
						{
							//PLAYA(PITON_SOUND);
						}

					}
				}
				else return false;
			}
		}
	}//Block for end
	if (t.owner == 0)
	{
		for (list<C_UNIT*>::iterator iter_unit = enemy.begin(); iter_unit != enemy.end(); iter_unit++)
		{
			C_UNIT* bt = *iter_unit;
			if (bt->activate) 
			{
				if (Collide((int)_x, (int)_y, 64, 64, bt->x, bt->y, 64, 64)) 
				{
					return false;
				}
			}
		}
	}
	else if (t.owner == 1) 
	{
		if (Collide(Player->x, Player->y, 64, 64, _x, _y, 64, 64))return false;
		for (list<C_UNIT*>::iterator iter_unit = enemy.begin(); iter_unit != enemy.end(); iter_unit++)
		{
			C_UNIT* bt = *iter_unit;
			if ((bt->id != t.id) && (bt->activate) && (Collide(bt->x, bt->y, 64, 64, _x, _y, 64, 64)))
				return false;
		}
	}
	t.x = _x;
	t.y = _y;
	return true;
}

void DrawPlayer() 
{
	TransparentBlt(bufferDC, Player->x, Player->y - offset_y, 64, 64, Player_DC, Player->face * 64, Player->step * 64, 64, 64, RGB(32, 114, 157));//플레이어 그리기. RGB값은 무시하는 색깔

}
//컴퓨터 과학에서 배열이나 자료 구조 오브젝트 내의 오프셋(offset)은 일반적으로 동일 오브젝트 안에서 오브젝트 처음부터 주어진 요소나 지점까지의 변위차를 나타내는 정수형이다.
//여기서 오프셋을 사용하는 이유는 그림 판넬을 찍힌 좌표는 일정하게 찍게 만들었기때문에 일정 좌표만 이동하면 바로바로 그려지게 한것


void DrawEnemy() 
{
	tagPOINT poly[5];
	for (list<C_UNIT*>::iterator iter_tank = enemy.begin(); iter_tank != enemy.end(); iter_tank++) {
		C_UNIT* t = *iter_tank;
		if (t->activate) 
		{
			TransparentBlt(bufferDC, t->x, t->y - offset_y, 64, 64, Enemy_DC, t->face * 64, (t->no * 3 + t->step) * 64, 64, 64, RGB(32, 114, 157));

			int len = ((double)t->hp / (double)t->maxhp) * (64 - 10 * 2);
			poly[0].x = t->x + 10;
			poly[0].y = t->y - offset_y - 8;
			poly[1].x = t->x + 10 + (64 - 10 * 2);
			poly[1].y = t->y - offset_y - 8;
			poly[2].x = t->x + 10 + (64 - 10 * 2);
			poly[2].y = t->y - offset_y - 8 + 5;
			poly[3].x = t->x + 10;
			poly[3].y = t->y - offset_y - 8 + 5;
			poly[4].x = t->x + 10;
			poly[4].y = t->y - offset_y - 8;
			//HP 그림
			SelectObject(bufferDC, hPen_Border); //테두리 삭제
			SelectObject(bufferDC, hBru_hp);  //회색 채움
			Rectangle(bufferDC, t->x + 10, t->y - offset_y - 8, t->x + 10 + len, t->y - offset_y - 8 + 5);

			SelectObject(bufferDC, hPen_black);
			Polyline(bufferDC, poly, 5);
		}
	}
}



void ATTACKCharge(C_UNIT& t, double charge, double chargemax) 
{
	C_Bullet* b = new C_Bullet();
	b->owner = t.owner;
	if (b->owner == 0)
		if (!keydown_f4)
		{
			//PLAYA(OPEN_FIRE);
		}
	b->id = 10;
	b->speed = bullet_attr[b->id][0] * (1 + charge / chargemax * 2);
	b->attack = (bullet_attr[b->id][1] + t.attack + t.attack_temp) * (1 + charge / chargemax * 4);
	b->hp = bullet_attr[b->id][4] * (1 + charge / chargemax * 10);
	b->offset_w = bullet_attr[b->id][5];
	b->offset_h = bullet_attr[b->id][6];

	switch (t.face)
	{
	case DOWN:
		b->wide = bullet_attr[b->id][2];
		b->high = bullet_attr[b->id][3];
		b->x = t.x + 32 - b->high / 2;
		b->y = t.y + 64 - b->offset_w;
		break;
	case LEFT:
		b->wide = bullet_attr[b->id][3];
		b->high = bullet_attr[b->id][2];
		b->x = t.x - b->wide + b->offset_w;
		b->y = t.y + 32 - b->high / 2 - b->offset_h;
		break;
	case UP:
		b->wide = bullet_attr[b->id][2];
		b->high = bullet_attr[b->id][3];
		b->x = t.x + 32 - b->high / 2;
		b->y = t.y - b->wide + b->offset_w;;
		break;
	case RIGHT:
		b->wide = bullet_attr[b->id][3];
		b->high = bullet_attr[b->id][2];
		b->x = t.x + 64 - b->offset_w;
		b->y = t.y + 32 - b->high / 2 - b->offset_h;
		break;
	}
	if (charge > chargemax * 2 / 3) b->id = 10;
	else if (charge > chargemax * 1 / 3) b->id = 11;
	else b->id = 12;
	bullet.push_back(b);
}
void DrawCharge() 
{
	C_UNIT* t = Player;

	if (++charge >= chargemax) 
	{
		charge = chargemax;
	}


	int len = ((double)charge / (double)chargemax) * (64 - 10 * 2);
	tagPOINT poly[5];

	poly[0].x = t->x + 10;
	poly[0].y = t->y - offset_y + 64;
	poly[1].x = t->x + 10 + (64 - 10 * 2);
	poly[1].y = t->y - offset_y + 64;
	poly[2].x = t->x + 10 + (64 - 10 * 2);
	poly[2].y = t->y - offset_y + 64 + 5;
	poly[3].x = t->x + 10;
	poly[3].y = t->y - offset_y + 64 + 5;
	poly[4].x = t->x + 10;
	poly[4].y = t->y - offset_y + 64;
	SelectObject(bufferDC, hPen_Border); //x테두리 삭제,체력
	SelectObject(bufferDC, hBru_charge);  //회색 채우기
	Rectangle(bufferDC, t->x + 10, t->y - offset_y + 64, t->x + 10 + len, t->y - offset_y + 64 + 5);

	SelectObject(bufferDC, hPen_black);
	Polyline(bufferDC, poly, 5);
}
void DrawBullet() 
{
	for (list<C_Bullet*>::iterator iter_bullet = bullet.begin(); iter_bullet != bullet.end(); iter_bullet++) 
	{
		C_Bullet* b = *iter_bullet;
		TransparentBlt(bufferDC, b->x, b->y - offset_y, 64, 64, bulletDC, b->face * 64, b->id * 64, 64, 64, RGB(255, 255, 255));//공격 데미지 별로 총알 변화
	}
}

void ATTACK(C_UNIT& t) //J 누르면 나가는 기본 공격(근접공격으로 나중에 수정하기)
{
	if (t.attack_frame > 0)return;
	else {
		t.attack_frame = t.attack_cd;
		C_Bullet* b = new C_Bullet();
		b->owner = t.owner;
		if (b->owner == 0) 
		{
			if (!keydown_f4)
			{
				//PLAYA(OPEN_FIRE);
			}
		}

		b->id = t.armor;

		b->face = t.face;
		b->speed = bullet_attr[b->id][0];
		b->attack = bullet_attr[b->id][1] + t.attack + t.attack_temp;
		b->hp = bullet_attr[b->id][4];
		b->offset_w = bullet_attr[b->id][5];
		b->offset_h = bullet_attr[b->id][6];


		switch (t.face)
		{
		case DOWN:
			b->wide = bullet_attr[b->id][2];
			b->high = bullet_attr[b->id][3];
			b->x = t.x + 32 - b->high / 2;
			b->y = t.y + 64 - b->offset_w;
			break;
		case LEFT:
			b->wide = bullet_attr[b->id][3];
			b->high = bullet_attr[b->id][2];
			b->x = t.x - b->wide + b->offset_w;
			b->y = t.y + 32 - b->high / 2 - b->offset_h;
			break;
		case UP:
			b->wide = bullet_attr[b->id][2];
			b->high = bullet_attr[b->id][3];
			b->x = t.x + 32 - b->high / 2;
			b->y = t.y - b->wide + b->offset_w;;
			break;
		case RIGHT:
			b->wide = bullet_attr[b->id][3];
			b->high = bullet_attr[b->id][2];
			b->x = t.x + 64 - b->offset_w;
			b->y = t.y + 32 - b->high / 2 - b->offset_h;
			break;
		}
		bullet.push_back(b);
	}
}

void Laser_ATTACK(C_UNIT& Play) //k를 눌러 레이저 방출
{
	//레이저 방출시 데미지 설정 20초 mp 소모도 20

		//좌표
	int x = Player->x;
	int y = Player->y;

	bool isHit = false;

	switch (Play.face)
	{
	case DOWN:
		laserxs = x + 32;
		laserxe = x + 32;
		laserys = y + 64 - offset_y;

		for (list<C_Block*>::iterator iter = object.begin(); iter != object.end(); iter++)//장애물 시계방향이동
		{
			C_Block& b = **iter;

			if (b.id > 0 && b.id < 10)
			{
				//블록 손상
				if (b.x <= laserxs && b.x + 64 >= laserxs)//
				{
					if (b.y + 10 >= laserys)//블록이 적 아래
					{
						//풀
						if (b.id == GRASS && b.state == NORMAL_STATE)
						{
							b.state = SHOOT_STATE;
							b.life -= 150;
						}
						//
						if (b.id == TREE || b.id == WALL || b.id == STONE || b.id == IRON || b.id == BUCKET || b.id == GOAL)//
						{
							laserye = b.y;
							b.life -= 100;
							if (b.life >= 100 && b.id == TREE && b.state == NORMAL_STATE)
							{
								b.state = SHOOT_STATE;
							}
							/*
							if (b.id==BUCKET)
							{
								OpenExplode(6,laserxe,laserye+offset_y,PLAYER_BOMB,Block_NONE);
							}else
							{*/
							OpenExplode(6, laserxe, laserye + offset_y, PLAYER_BOMB, b.id);
							/*}

							if (b.id==BUCKET)
							{
								if (b.life<=0)
								{
									OpenExplode(12,b.x+32,b.y+32+offset_y,OBJECT_BOMB,BUCKET);
								}
							}*/
							isHit = true;
							break;
						}
					}


				}
			}
		}

		if (!isHit)//cpzm
		{
			laserye = GAME_H + offset_y;
		}

		break;

	case UP:
		laserxs = Play.x + 32;
		laserxe = Play.x + 32;
		laserys = Play.y - offset_y;
		for (list<C_Block*>::iterator iter = --object.end(); iter != object.begin(); iter--)//반시계방향
		{
			C_Block& b = **iter;

			if (b.id > 0 && b.id < 10)
			{

				if (b.x <= laserxs && b.x + 64 >= laserxs)//y범위
				{
					if (b.y - 10 <= laserys)//장애물 위
					{
						//w잔디
						if (b.id == GRASS && b.state == NORMAL_STATE)
						{
							b.state = SHOOT_STATE;
							b.life -= 150;
						}
						//
						if (b.id == TREE || b.id == WALL || b.id == STONE || b.id == IRON || b.id == BUCKET || b.id == GOAL)//
						{
							laserye = b.y + 64;
							b.life -= 100;
							if (b.life >= 100 && b.id == TREE && b.state == NORMAL_STATE)
							{
								b.state = SHOOT_STATE;
							}/*
							if (b.id==BUCKET)
							{
								OpenExplode(6,laserxe,laserye+offset_y,PLAYER_BOMB,Block_NONE);
							}else
							{*/
							OpenExplode(6, laserxe, laserye + offset_y, PLAYER_BOMB, b.id);
							/*}
							if (b.id==BUCKET)
							{
								if (b.life<=0)
								{
									OpenExplode(12,b.x+32,b.y+32+offset_y,OBJECT_BOMB,BUCKET);
								}
							}*/
							isHit = true;
							break;
						}
					}


				}
			}
		}
		if (!isHit)//지도밖으로 날아갈 시
		{
			laserye = -offset_y;
		}

		break;
	case LEFT:
		laserxs = Play.x;
		laserys = Play.y + 32 - 8 - offset_y;
		laserye = Play.y + 32 - 8 - offset_y;
		for (list<C_Block*>::iterator iter = --object.end(); iter != object.begin(); iter--)
		{
			C_Block& b = **iter;

			if (b.id > 0 && b.id < 10)
			{

				if (b.y <= laserys && b.y + 64 >= laserys)
				{
					if (b.x - 10 <= laserxs)
					{
						
						if (b.id == GRASS && b.state == NORMAL_STATE)
						{
							b.state = SHOOT_STATE;
							b.life -= 100;
						}
						//
						if (b.id == TREE || b.id == WALL || b.id == STONE || b.id == IRON || b.id == BUCKET || b.id == GOAL)
						{
							laserxe = b.x + 64;
							b.life -= 150;
							if (b.life >= 100 && b.id == TREE && b.state == NORMAL_STATE)
							{
								b.state = SHOOT_STATE;
							}/*
							if (b.id==BUCKET)
							{
								OpenExplode(6,laserxe,laserye+offset_y,PLAYER_BOMB,Block_NONE);
							}else
							{*/
							OpenExplode(6, laserxe, laserye + offset_y, PLAYER_BOMB, b.id);
							/*}
							if (b.id==BUCKET)
							{
								if (b.life<=0)
								{
									OpenExplode(12,b.x+32,b.y+32+offset_y,OBJECT_BOMB,BUCKET);
								}
							}*/
							isHit = true;
							break;
						}
					}


				}
			}
		}
		if (!isHit)
		{
			laserxe = offset_x;
		}

		break;
	case RIGHT:
		laserxs = Play.x + 64;
		laserys = Play.y + 32 - 8 - offset_y;
		laserye = Play.y + 32 - 8 - offset_y;
		for (list<C_Block*>::iterator iter = object.begin(); iter != object.end(); iter++)
		{
			C_Block& b = **iter;

			if (b.id > 0 && b.id < 10)
			{

				if (b.y <= laserys && b.y + 64 >= laserys)
				{
					if (b.x + 10 >= laserxs)
					{
						//
						if (b.id == GRASS && b.state == NORMAL_STATE)
						{
							b.state = SHOOT_STATE;
							b.life -= 100;
						}
						//
						if (b.id == TREE || b.id == WALL || b.id == STONE || b.id == IRON || b.id == BUCKET || b.id == GOAL)
						{
							laserxe = b.x;
							b.life -= 150;
							if (b.life >= 100 && b.id == TREE && b.state == NORMAL_STATE)
							{
								b.state = SHOOT_STATE;
							}/*
							if (b.id==BUCKET)
							{
								OpenExplode(6,laserxe,laserye+offset_y,PLAYER_BOMB,Block_NONE);
							}else
							{*/
							OpenExplode(6, laserxe, laserye + offset_y, PLAYER_BOMB, b.id);
							/*}
							if (b.id==BUCKET)
							{
								if (b.life<=0)
								{
									OpenExplode(12,b.x+32,b.y+32+offset_y,OBJECT_BOMB,BUCKET);
								}
							}*/
							isHit = true;
							break;
						}
					}


				}
			}
		}
		if (!isHit)
		{
			laserxe = GAME_W + offset_x;
		}

		break;


	default:
		break;
	}
	
	int temp = 0;
	if (laserxe < laserxs)
	{
		temp = laserxe;
		laserxe = laserxs;
		laserxs = temp;
	}
	else if (laserye < laserys)
	{
		temp = laserye;
		laserye = laserys;
		laserys = temp;
	}
	laserys += offset_y;
	laserye += offset_y;
	
	for (list<C_UNIT*>::iterator iter = enemy.begin(); iter != enemy.end(); iter++)
	{
		C_UNIT& b = **iter;
		if (((b.x + 32) >= laserxs && (b.x + 32) <= laserxe && b.y <= laserys && (b.y + 64) >= laserye) || (b.x <= laserxs && (b.x + 64) >= laserxe && (b.y + 32) >= laserys && (b.y + 32) <= laserye))
		{
			b.hp -= 100;
		}
	}

}


void ScreenMove() 
{
	if (Player->x - offset_x > 500 && Player->face == RIGHT)
	{
		offset_x += (((Player->x - offset_x - 500)) / 150) * (Player->speed + Player->speed_temp);
		if (offset_x > GAME_TOTW - GAME_W)
			offset_x = GAME_TOTW - GAME_W;
	}

	if ((GAME_W - (Player->x - offset_x)) > 866 && Player->face == LEFT)
	{
		offset_x -= ((GAME_W - (Player->x - offset_x)) - 866) / 150 * (Player->speed + Player->speed_temp);
		if (offset_x < 0)
			offset_x = 0;
	}
}

void UnitBlockCheck() 
{
	for (list<C_UNIT*>::iterator iter_unit = enemy.begin(); iter_unit != enemy.end(); iter_unit++) 
	{
		C_UNIT* et = *iter_unit;
		if ((et->x >= offset_x - 100) && (et->x <= offset_x + GAME_W + 400)) 
		{
			et->activate = true;
		}
		else et->activate = false;
	}
	for (list<C_Block*>::iterator iter_Block = object.begin(); iter_Block != object.end(); iter_Block++) 
	{
		C_Block* b = *iter_Block;
		if ((b->x >= offset_x - 100) && (b->x <= offset_x + GAME_W + 400)) 
		{
			b->activate = true;
		}
		else b->activate = false;
	}
}
//폭발생성
void OpenExplode(int power, int  x, int y, int owner, int id) 
{
	if (owner != ENERMY_BOMB)
	{
		if (id == BUCKET)
		{
			shaking = 50;
			if (!keydown_f4) 
			{
				;//PLAYA(OIL_EXPLODE);
			}
		}
		else
			if (id == WALL) 
			{
				if (!keydown_f4)
					;//PLAYA(WALL_DESTROY);
			}
			else
				if (id == IRON) 
				{
					if (!keydown_f4)
						;//PLAYA(IRON_SOUND);
				}
				else
					if (id == STONE) 
					{
						if (!keydown_f4)
							;//PLAYA(HIT_STONE);
					}
					else

						if (id == TREE) 
						{
							if (!keydown_f4)
								;//PLAYA(HIT_STONE);
						}
						else
							if (!keydown_f4) 
							{
								;//PLAYA(BULLET_EXPLODE);
							}

	}

	bomb.push_back(new C_Bomb(power, x, y - offset_y, owner));
}


void DrawStateMap()
{
	//플레이어 HP 그림
	hpX1 = 93.0;
	hpY1 = 25.0;
	hpY2 = 45.0;
	fullhpX = 141;

	//hpX2=111.0+50.6;
	SelectObject(bufferDC2, hBruWhite);
	Rectangle(bufferDC2, hpX1, hpY1, hpX1 + fullhpX, hpY2);
	hpX2 = hpX1 + (((double)(Player->hp) / (double)(Player->maxhp)) * fullhpX);
	SelectObject(bufferDC2, hBruRed);
	Rectangle(bufferDC2, hpX1, hpY1, hpX2, hpY2);

	//플레이어 MP 그림
	mpX1 = 93.0;
	mpY1 = 45.5;
	mpY2 = 67.0;
	fullmpX = 139.0;

	//mpX2=111.0+90.5;

	SelectObject(bufferDC2, hBruWhite);
	Rectangle(bufferDC2, mpX1, mpY1, mpX1 + fullmpX, mpY2);
	mpX2 = mpX1 + (((double)(Player->mp) / (double)(Player->maxmp)) * fullmpX);
	SelectObject(bufferDC2, hBruBlue);
	Rectangle(bufferDC2, mpX1, mpY1, mpX2, mpY2);
	//TransparentBlt(bufferDC2,0,1,332,110,player_state_mapDC,0,0,332,110,RGB(255,255,255));

	//플레이어 경험치 그림
	expX1 = 76.0;
	expY1 = 67.0;
	expY2 = 87.0;
	fullexpX = 158.0;

	SelectObject(bufferDC2, hBruWhite);
	Rectangle(bufferDC2, expX1, expY1, expX1 + fullexpX, expY2);
	expX2 = expX1 + (((double)(Player->exp) / (double)(lvexp[Player->lv])) * fullexpX);
	SelectObject(bufferDC2, hBruYellow);
	Rectangle(bufferDC2, expX1, expY1, expX2, expY2);
	TransparentBlt(bufferDC2, 0, 1, 286, 96, player_state_mapDC, 0, 0, 286, 96, RGB(255, 255, 255));
	TransparentBlt(bufferDC2, 240, 30, 32, 16, lvDC, (Player->lv - 1) * 37, 0, 37, 26, RGB(255, 255, 255));//240,30 위치에 32,16 LV DC를 그려라
}
//블록 파괴시 떨어지는 아이템
void JudgeThingB(C_Block* b)
{
	if (((b)->old_id == TREE || (b)->old_id == WALL || (b)->old_id == STONE))
	{
		//ITEM 드랍율
		int n;

		//생성된 아이템 유형
		int k = rand() % 5;
		if ((b)->old_id == WALL)
			n = rand() % 8;
		else if ((b)->old_id == TREE)
			n = rand() % 5;
		else
			n = rand() % 3;
		if (n == 0)
			thing.push_back(new C_Thing(k, (b)->x, (b)->y + offset_y, 2000, 3000));

	}
}


//적을 쓰러뜨렸을 시 떨어지는 아이템
void JudgeThingE(C_UNIT* b) 
{
	//아이템 드랍율
	int n = rand() % (10 - ((b)->no));
	//생성된 아이템 유형
	int k = rand() % 5;
	int j = rand() % (10 - (b->no));
	if (n == 0)
		thing.push_back(new C_Thing(k, (b)->x, (b)->y, 2000, 2000));
	if (n != 0 && j == 0)
		thing.push_back(new C_Thing((b->no) + 10, (b)->x, (b)->y, 2000, 2000));

}
void HandleThing()
{
	for (list<C_Thing*>::iterator b = thing.begin(); b != thing.end();)
	{

		bool erase = false;   //아이템 삭제 여부

		if ((*b)->time > 0)
		{
			if ((*b)->id >= 10 && (*b)->id <= 14)
				;//TransparentBlt(bufferDC, (*b)->x, (*b)->y - offset_y + 10, 64, 64, armorDC, 64, ((*b)->id - 10 + 5) * 64, 64, 64, RGB(255, 255, 255));
			else
			{
				TransparentBlt(bufferDC, (*b)->x, (*b)->y - offset_y, 64, 64, thingDC, (*b)->id * 64, 0, 64, 64, RGB(38, 94, 34));
			}

			--((*b)->time);
		}
		if (Player->face == RIGHT && abs(((Player->x) - ((*b)->x))) < 43 && abs(((Player->y) - ((*b)->y))) < 58 && (*b)->time > 0)
		{
			if (!keydown_f4)
				//PLAYA(GET_THING);
			switch ((*b)->id)
			{
			case ADD_SPEED://헤이스트
				Player->speed_temp += 1.5;
				break;
			case ADD_POWER://파워물약
				Player->attack_temp += 40;
				break;
			case ADD_HP://HP물약
			{
				Player->hp += (int)(0.3 * Player->maxhp);
				if (Player->hp > Player->maxhp)
					Player->hp = Player->maxhp;
			}
			break;
			case ADD_MP://MP물약
			{
				Player->mp += (int)(0.3 * Player->maxmp);
				if (Player->mp > Player->maxmp)
					Player->mp = Player->maxmp;
			}
			break;
			case CUT_HP://독약
				Player->hp -= (int)(0.15 * Player->maxhp);
				break;

			}
			(*b)->time = -10;    //아이템 사라지는 시간 체크, 플레이어 아이템 획득 체크
		}
		else
			if (Player->face == LEFT && abs(((Player->x) - ((*b)->x))) < 39 && abs(((Player->y) - ((*b)->y))) < 58 && (*b)->time > 0)
			{
				if (!keydown_f4)
					//PLAYA(GET_THING);
				switch ((*b)->id)
				{
				case ADD_SPEED:
					Player->speed_temp += 1.5;
					break;
				case ADD_POWER:
					Player->attack_temp += 40;
					break;
				case ADD_HP:
				{
					Player->hp += (int)(0.3 * Player->maxhp);
					if (Player->hp > Player->maxhp)
						Player->hp = Player->maxhp;
				}
				break;
				case ADD_MP:
				{
					Player->mp += (int)(0.3 * Player->maxmp);
					if (Player->mp > Player->maxmp)
						Player->mp = Player->maxmp;
				}
				break;
				case CUT_HP:
					Player->hp -= (int)(0.15 * Player->maxhp);
					break;


				}
				(*b)->time = -10;    
			}
			else
				if (Player->face == UP && abs(((Player->y) - ((*b)->y))) < 49 && abs(((Player->x) - ((*b)->x))) < 58 && (*b)->time > 0)
				{
					if (!keydown_f4)
						//PLAYA(GET_THING);
					switch ((*b)->id)
					{
					case ADD_SPEED:
						Player->speed_temp += 1.5;
						break;
					case ADD_POWER:
						Player->attack_temp += 40;
						break;
					case ADD_HP:
					{
						Player->hp += (int)(0.3 * Player->maxhp);
						if (Player->hp > Player->maxhp)
							Player->hp = Player->maxhp;
					}
					break;
					case ADD_MP:
					{
						Player->mp += (int)(0.3 * Player->maxmp);
						if (Player->mp > Player->maxmp)
							Player->mp = Player->maxmp;
					}
					break;
					break;
					case CUT_HP:
						Player->hp -= (int)(0.15 * Player->maxhp);
						break;
	
					}
					(*b)->time = -10;  
				}
				else
					if (Player->face == DOWN && abs(((Player->y) - ((*b)->y))) < 59 && abs(((Player->x) - ((*b)->x))) < 58 && (*b)->time > 0)
					{
						if (!keydown_f4)
						//	PLAYA(GET_THING);
						switch ((*b)->id)
						{
						case ADD_SPEED:
							Player->speed_temp += 1.5;
							break;
						case ADD_POWER:
							Player->attack_temp += 40;
							break;
						case ADD_HP:
						{
							Player->hp += (int)(0.3 * Player->maxhp);
							if (Player->hp > Player->maxhp)
								Player->hp = Player->maxhp;
						}
						break;
						case ADD_MP:
						{
							Player->mp += (int)(0.3 * Player->maxmp);
							if (Player->mp > Player->maxmp)
								Player->mp = Player->maxmp;
						}
						break;
						break;
						case CUT_HP:
							Player->hp -= (int)(0.15 * Player->maxhp);
							break;
						
						}
						(*b)->time = -10;   
					}


		if ((*b)->time == -10)                //아이템 지속시간
		{
			(*b)->last -= 1;
			if ((*b)->last < 0)
				(*b)->last = 0;
		}


		if ((*b)->time == -10 && (*b)->last == 0)            //아이템 삭제
		{
			switch ((*b)->id)
			{
			case ADD_SPEED:
				Player->speed_temp -= 1.5;
				break;
			case ADD_POWER:
				Player->attack_temp -= 40;
				break;
			case ADD_HP:
				break;
			case ADD_MP:
				break;
			case CUT_HP:
				break;
			}
			erase = true;
		}

		if (erase == true)					//아이템 맵 클리어 여부
		{
			b = thing.erase(b);
		}
		else if (erase == false)
		{
			b++;
		}
	}
}


//화면 흔들림
void ShakeScreen()
{
	int n = rand() % 8;
	switch (n)
	{
	case 0:
		bgx = 3.0;
		break;
	case 1:
		bgx = -3.0;
		break;
	case 2:
		bgy = 3.0;
		break;
	case 3:
		bgy = -3.0;
		break;
	case 4:
	{
		bgx = 1.2;
		bgy = 1.2;
	}
	break;
	case 5:
	{
		bgx = 1.2;
		bgy = 1.2;
	}
	break;
	case 6:
	{
		bgx = -1.2;
		bgy = -1.2;
	}
	break;
	case 7:
	{
		bgx = -1.2;
		bgy = 1.2;
	}
	break;

	default:
		break;
	}
}


void DrawLaser(int x1, int y1, int x2, int y2)
{
	if (k_down)
	{
		if (Player->mp >= 20)
		{
			if (!keydown_f4)
		///		PLAYA(LASER_SOUND);
			y1 -= offset_y + 3;
			y2 -= offset_y + 3;
			SelectObject(bufferDC, hBru_Laser);
			SelectObject(bufferDC, hPen_laser);
			if ((x2 - x1) > (y2 - y1))
			{
				y1 -= 2;
				y2 += 2;
			}
			else
			{
				x1 -= 2;
				x2 += 2;
			}
			Rectangle(bufferDC, x1, y1, x2, y2);
		}
	}
	else
	{
		return;
	}

}
//레이저 충돌 판정
void ProtonCollide() 
{
	if (proton_collider-- % 5 == 0) 
	{
		int x = rand() % GAME_W + offset_x;
		int y = rand() % (GAME_H - 192);
		OpenExplode(12, x, y, PLAYER_BOMB, BUCKET);
		shaking = 50;
	}
}
//레벨업 그림
void DrawLevelUp()
{
	if (LevelUping == true)
	{
		if (!keydown_f4)
			//PLAYB(LEVEL_UP_SOUND);
		TransparentBlt(bufferDC2, 5, 576 +60 + 10, 329, 96, attrDC, 0, 0, 329, 96, RGB(255, 0, 255));
		if (uping > 0)//레벨업 축하메세지
			//TransparentBlt(hdc1,x,y,64,64,hdc2,xs,ys,64,64,RGB(255,255,255));
			TransparentBlt(bufferDC2, 0, 0, 1366, 768, level_upDC, 0, 0, 567, 452, RGB(255, 255, 255));
	}
	if (LevelUping == false)//스탯포인트 위치 왼쪽.
	{
		if (AddAttring == 1 && adding > 0)
			TransparentBlt(bufferDC2, Player->x - 25 - offset_x, Player->y + 15, 83, 96, adding_attrDC, 0, 0, 83, 96, RGB(255, 0, 255));
		if (AddAttring == 2 && adding > 0)
			TransparentBlt(bufferDC2, Player->x - 18 - offset_x, Player->y + 15, 83, 96, adding_attrDC, 83, 0, 83, 96, RGB(255, 0, 255));
		if (AddAttring == 3 && adding > 0)
			TransparentBlt(bufferDC2, Player->x - 22 - offset_x, Player->y + 15, 83, 96, adding_attrDC, 166, 0, 83, 96, RGB(255, 0, 255));
		if (AddAttring == 4 && adding > 0)
			TransparentBlt(bufferDC2, Player->x - offset_x, Player->y + 15, 83, 96, adding_attrDC, 249, 0, 83, 96, RGB(255, 0, 255));
	}
}