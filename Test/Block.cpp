#include "stdafx.h"
#include "Block.h"
#include "Main.h"
#include <WinUser.h>

C_Block::~C_Block(void)
{
}
//TransparentBlt(hdc1,x,y,64,64,hdc2,xs,ys,64,64,RGB(255,255,255));
//참조:https://m.blog.naver.com/PostView.nhn?blogId=power2845&logNo=50147965306&proxyReferer=https:%2F%2Fwww.google.com%2F
void C_Block::DrawBlock(HDC& hdc1, HDC& hdc2)
{
	switch (id)
	{
	case GRASS:
		if (state == SHAKE_STATE)
		{

			TransparentBlt(hdc1, x, y, 64, 64, hdc2, (shake_step / 10) % 3 * 64, 64, 64, 64, RGB(255, 255, 255));//10프레임마다 변경, 3개의 이미지가 변환
			if ((++shake_step) == 30)
			{

				shake_step = 0;
				state = NORMAL_STATE;
			}

		}
		else if (state == SHOOT_STATE)
		{

			TransparentBlt(hdc1, x, y, 64, 64, hdc2, (shoot_step / 10) % 3 * 64, 2 * 64, 64, 64, RGB(255, 255, 255));//10프레임 체크, 3개의 이미지가 변환
			if ((++shoot_step) == 30)
			{

				shoot_step = 0;
				state = NORMAL_STATE;
			}

		}
		else
		{
			if (life <= 0)
			{
				id = Block_NONE;
			}
			else if (life <= 400)
			{
				TransparentBlt(hdc1, x, y, 64, 64, hdc2, 64, 0, 64, 64, RGB(255, 255, 255));
				state = DAMAGE_STATE;
			}
			else if (life <= 1000)
			{
				TransparentBlt(hdc1, x, y, 64, 64, hdc2, 0, 0, 64, 64, RGB(255, 255, 255));
			}
		}
		break;
	case TREE:
		if (state == SHOOT_STATE)
		{

			TransparentBlt(hdc1, x, y, 64, 64, hdc2, (shoot_step / 10) % 3 * 64, 4 * 64, 64, 64, RGB(255, 255, 255));//10프레임마다 변경, 3개의 이미지가 변환
			if ((++shoot_step) == 30)
			{

				shoot_step = 0;
				state = NORMAL_STATE;
			}

		}
		else
		{
			if (life <= 0)
			{
				id = Block_NONE;
			}
			else if (life <= 100)
			{
				TransparentBlt(hdc1, x, y, 64, 64, hdc2, 64, 3 * 64, 64, 64, RGB(255, 255, 255));
				state = DAMAGE_STATE;
			}
			else if (life <= 200)
			{
				TransparentBlt(hdc1, x, y, 64, 64, hdc2, 0, 3 * 64, 64, 64, RGB(255, 255, 255));
			}
		}
		break;
	case WATER_ONE:
		TransparentBlt(hdc1, x, y, 64, 64, hdc2, 0, 5 * 64, 64, 64, RGB(255, 255, 255));
		break;
	case WATER_TWO:
		TransparentBlt(hdc1, x, y, 64, 64, hdc2, 64, 5 * 64, 64, 64, RGB(255, 255, 255));
		break;
	case WATER_THREE:
		TransparentBlt(hdc1, x, y, 64, 64, hdc2, 0, 6 * 64, 64, 64, RGB(255, 255, 255));
		break;
	case WATER_FOUR:
		TransparentBlt(hdc1, x, y, 64, 64, hdc2, 64, 6 * 64, 64, 64, RGB(255, 255, 255));
		break;
	case WATER_FIVE:
		TransparentBlt(hdc1, x, y, 64, 64, hdc2, 2 * 64, 6 * 64, 64, 64, RGB(255, 255, 255));
		break;
	case WATER_SIX:
		TransparentBlt(hdc1, x, y, 64, 64, hdc2, 3 * 64, 6 * 64, 64, 64, RGB(255, 255, 255));
		break;
	case WALL:
		if (life <= 0)
		{
			id = Block_NONE;
		}
		else if (life <= 75)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 3 * 64, 7 * 64, 64, 64, RGB(255, 255, 255));
		}
		else if (life <= 150)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 2 * 64, 7 * 64, 64, 64, RGB(255, 255, 255));
		}
		else if (life <= 250)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 64, 7 * 64, 64, 64, RGB(255, 255, 255));
		}
		else if (life <= 350)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 0, 7 * 64, 64, 64, RGB(255, 255, 255));
		}
		break;
	case STONE:
		if (life <= 0)
		{
			id = Block_NONE;
		}
		else if (life <= 150)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 3 * 64, 8 * 64, 64, 64, RGB(255, 255, 255));
		}
		else if (life <= 300)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 2 * 64, 8 * 64, 64, 64, RGB(255, 255, 255));
		}
		else if (life <= 450)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 64, 8 * 64, 64, 64, RGB(255, 255, 255));
		}
		else if (life <= 600)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 0, 8 * 64, 64, 64, RGB(255, 255, 255));
		}
		break;
	case BUCKET:
		if (life <= 0)
		{
			id = Block_NONE;
			//OpenExplode(12, x + 32, y + 32 - 96, OBJECT_BOMB, BUCKET);
		}
		else {
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 0, 9 * 64, 64, 64, RGB(255, 255, 255));
		}

		break;
	case IRON:
		if (life <= 0)
		{
			id = Block_NONE;
		}
		else {
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 64, 9 * 64, 64, 64, RGB(255, 255, 255));
		}

		break;
	case PITON:
		TransparentBlt(hdc1, x, y, 64, 64, hdc2, 2 * 64, 9 * 64, 64, 64, RGB(255, 255, 255));
		if (cd > 0)cd--;
		break;
	case GOAL:
		if (life <= 0)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 258, 0, 48, 64, RGB(255, 0, 255));

		}
		else if (life <= 125)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 205, 0, 48, 64, RGB(255, 0, 255));
		}
		else if (life <= 250)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 154, 0, 48, 64, RGB(255, 0, 255));
		}
		else if (life <= 375)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 64, 0, 48, 64, RGB(255, 0, 255));
		}
		else if (life <= 500)
		{
			TransparentBlt(hdc1, x, y, 64, 64, hdc2, 0, 0, 48, 64, RGB(255, 0, 255));
		}
		break;
	default:
		break;

	}
}

