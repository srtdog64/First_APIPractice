//1ȸ ������
#pragma once
//API
#include <Windows.h>
#include <time.h>//�ý��� �ð�
#include <string>
#include <fstream>//���� ��Ʈ��

//Seequece �����̳�
#include <vector>
#include <list>
//���ҽ� ���
#include "resource.h"

//���� ���� ���
#include "UNIT.h"
//#include "Bullet.h"
//#include "Bomb.h"
#include "Object.h"
using namespace std;


//���� �ڵ� ����
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

//����â ũ��
#define GAME_TOTW 64*40
#define GAME_W  1368
#define GAME_H  768
#define TANK_WIDE 64
#define TANK_HIGH 64
#define BULLET_WIDE 25
#define BULLET_HIGH 40



//����Ÿ�̸�
#define GAME_ID 1
#define GAME_TIME 15
//Ű����
#define KEYDOWN(key) GetAsyncKeyState(key)&0x8000
#define KEYUP(key) !(GetAsyncKeyState(key)&0x8000)
//���� ���
#define PLAYA(MUSIC) PlaySound(MAKEINTRESOURCE(MUSIC),GetModuleHandle(NULL),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT)
#define PLAYB(MUSIC) PlaySound(MAKEINTRESOURCE(MUSIC),GetModuleHandle(NULL),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT|SND_NOSTOP)

//���� state ����
#define GAME 0
#define PAUSE 1
#define GAMEOVER 2
#define WIN 3
#define NEXTSTAGE 4
#define EDIT 5
#define GAMESTART 6
#define GAMESELECT 7
#define GAMEWIN 8
//�� ����
#define NORMAL_Enemy 0
#define SPEED_Enemy 1
#define POWER_Enemy 2
#define ARMOR_Enemy 3
//��ü ����
#define NONE 4
#define LIFE 0
#define POWER 1
#define SPEED 2
#define WEAPON 3

//�������� �߰� 
#define ADD_SPEED 0
#define ADD_POWER 1
#define ADD_HP 2
#define ADD_MP 3
#define CUT_HP 4

//��ü ����
#define PLAYER_BOMB 0
#define ENERMY_BOMB 1
#define OBJECT_BOMB 2

#define ARMOR1 10
#define ARMOR2 11
#define ARMOR3 12
#define ARMOR4 13
#define ARMOR5 14

//�� �з�
#define Enemy  99
//���ν����Լ�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//���ӽ���
void GameStart();
//���� ����, ����
void Game();
//Ű �Է�
void Key();
//���
void DrawBG();
//���� ������(�׸�)
void DrawGame();
//������â ���
void PrintToScreen();
//�� ��� �׸���(
void DrawBlock();
void DrawPiton();
//�÷��̾� ź�� �߻� ó�� �� �׸�
void PlayerBullet();
//���� ����Ʈ ������
void DrawBomb();
//���� �������� ���� �� ���� �����ϱ� ���� �̻��� �߻�
//void OpenMissile(HERO&);
//�ʻ��
void DrawMissile();
//�ʱ�ȭ
void DataInit();
//�Ѿ��� ������ �ε���
//bool BulletHitBlock(Bullet&);
//���� ������ �ε��� ���
//bool TankHitBlock(BaseTank&);
//�Ѿ˿� ������ ���� ���
//bool BulletHitTank(Bullet&, BaseTank&);
//ź���� ��ũ ����
//bool TankHitTank(BaseTank&, BaseTank&);
//ź������ �浹 ����
//bool BulletHitBullet(Bullet&, Bullet&);
//�� ���� �� ó��
void Enemy_UNIT();
//�� ź��
void EnemyBullet();
//������ �׸��� �� ȿ������
void Item();
//�� ����
void Edit();
//������
void Save();
//�� �ε�
void Load();
//��ֹ� �� �� �ε�
void AssignBlockMap();
//�̵� ó��
bool Move(C_UNIT&, int);
//�浹����
bool Collide(int, int, int, int, int, int, int, int);
//�÷��̾�ĳ�� �׸���
void DrawPlayer();
//�÷��̾� ���� ������Ʈ
void PlayerStep(C_UNIT&);//����ũ Ŭ���� ����
//����
void ATTACK(C_UNIT&);
//������ �迭
void Laser_ATTACK(C_UNIT&);
//���� ���� ���� �� ������ �̻��� �߻�
void OpenMissile(C_UNIT&);
//ź�� ������
void BulletMove();
//ȭ���̵�
void ScreenMove();
//����
void OpenExplode(int, int, int, int, int);
//ź�� �׸�
void DrawBullet();
//������ �þ߿� �ִ��� üũ
void UnitBlockCheck();
//�� üũ
void EnemyStep();
//�� �׸���
void DrawEnemy();
//�� AI
void EnemyAI(C_UNIT&);
//�÷��̾� ���� ǥ��
void DrawStateMap();


//�ڵ� 
void HandleThing();
//ȭ�� ��鸲
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