//1회 컴파일
#pragma once
//API
#include <Windows.h>
#include <time.h>//시스템 시간
#include <string>
#include <fstream>//파일 스트림

//Seequece 컨테이너
#include <vector>
#include <list>
//리소스 헤더
#include "resource.h"

//유저 임의 헤더
#include "UNIT.h"
//#include "Bullet.h"
//#include "Bomb.h"
#include "Object.h"
using namespace std;


//지형 코드 정의
#define ICE 0
#define ROAD 1
#define BLANK 3
#define SAND1 4
#define SAND2 5
#define SAND3 6
#define SAND4 7
#define SAND5 8
#define SAND6 9
#define SAND7 10
#define SAND8 11
#define SAND9 12
#define SAND10 13
#define SAND11 14

//게임창 크기
#define GAME_TOTW 64*40
#define GAME_W  1368
#define GAME_H  768
#define TANK_WIDE 64
#define TANK_HIGH 64
#define BULLET_WIDE 25
#define BULLET_HIGH 40



//게임타이머
#define GAME_ID 1
#define GAME_TIME 15
//키매핑
#define KEYDOWN(key) GetAsyncKeyState(key)&0x8000
#define KEYUP(key) !(GetAsyncKeyState(key)&0x8000)
//사운드 재생
#define PLAYA(MUSIC) PlaySound(MAKEINTRESOURCE(MUSIC),GetModuleHandle(NULL),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT)
#define PLAYB(MUSIC) PlaySound(MAKEINTRESOURCE(MUSIC),GetModuleHandle(NULL),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT|SND_NOSTOP)

//게임 state 정의
#define GAME 0
#define PAUSE 1
#define GAMEOVER 2
#define WIN 3
#define NEXTSTAGE 4
#define EDIT 5
#define GAMESTART 6
#define GAMESELECT 7
#define GAMEWIN 8
//적 유형
#define NORMAL_Enemy 0
#define SPEED_Enemy 1
#define POWER_Enemy 2
#define ARMOR_Enemy 3
//객체 유형
#define NONE 4
#define LIFE 0
#define POWER 1
#define SPEED 2
#define WEAPON 3

//레벨업시 추가 
#define ADD_SPEED 0
#define ADD_POWER 1
#define ADD_HP 2
#define ADD_MP 3
#define CUT_HP 4

//물체 폭발
#define PLAYER_BOMB 0
#define ENERMY_BOMB 1
#define OBJECT_BOMB 2

#define ARMOR1 10
#define ARMOR2 11
#define ARMOR3 12
#define ARMOR4 13
#define ARMOR5 14

//적 분류
#define Enemy  99
//프로시저함수
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//게임시작
void GameStart();
//게임 루프, 메인
void Game();
//키 입력
void Key();
//배경
void DrawBG();
//게임 랜더링(그림)
void DrawGame();
//윈도우창 출력
void PrintToScreen();
//맵 블록 그리기(
void DrawBlock();
void DrawPiton();
//플레이어 탄막 발사 처리 및 그림
void PlayerBullet();
//폭발 이펙트 랜더링
void DrawBomb();
//가시 범위에서 가장 먼 적을 공격하기 위한 미사일 발사
//void OpenMissile(HERO&);
//필살기
void DrawMissile();
//초기화
void DataInit();
//총알이 벽돌에 부딪힘
//bool BulletHitBlock(Bullet&);
//영웅 벽돌에 부딪힐 경우
//bool TankHitBlock(BaseTank&);
//총알에 영웅이 맞을 경우
//bool BulletHitTank(Bullet&, BaseTank&);
//탄막과 탱크 판정
//bool TankHitTank(BaseTank&, BaseTank&);
//탄막간에 충돌 판정
//bool BulletHitBullet(Bullet&, Bullet&);
//적 생성 및 처리
void Enemy_UNIT();
//적 탄만
void EnemyBullet();
//아이템 그리기 및 효과적용
void Item();
//맵 편집
void Edit();
//맵저장
void Save();
//맵 로딩
void Load();
//장애물 및 맵 로딩
void AssignBlockMap();
//이동 처리
bool Move(C_UNIT&, int);
//충돌판정
bool Collide(int, int, int, int, int, int, int, int);
//플레이어캐릭 그리기
void DrawPlayer();
//플레이어 상태 업데이트
void PlayerStep(C_UNIT&);//유니크 클래스 참조
//공격
void ATTACK(C_UNIT&);
//레이저 계열
void Laser_ATTACK(C_UNIT&);
//가시 범위 가장 먼 적에게 미사일 발사
void OpenMissile(C_UNIT&);
//탄막 움직임
void BulletMove();
//화면이동
void ScreenMove();
//폭발
void OpenExplode(int, int, int, int, int);
//탄막 그림
void DrawBullet();
//적군이 시야에 있는지 체크
void UnitBlockCheck();
//적 체크
void EnemyStep();
//적 그리기
void DrawEnemy();
//적 AI
void EnemyAI(C_UNIT&);
//플레이어 상태 표시
void DrawStateMap();


//핸들 
void HandleThing();
//화면 흔들림
void ShakeScreen();



void DrawLaser(int, int, int, int);

void DrawCharge();


void ATTACKCharge(C_UNIT&, double, double);


void ProtonCollide();

void DrawStart();

void DrawIntroduce();

void DrawSelect();

void DrawCredits();


void DrawLevelUp();

void DrawDeath();