#include "stdafx.h"
#include "Bomb.h"

C_Bomb::C_Bomb
(int _id, int _x, int _y, int _owner, int _size, int _bombX, int _step, int _temp, bool _end) :
id(_id), x(_x), y(_y), owner(_owner), size(_size), bombX(_bombX), step(_step), temp(_temp), end(_end) {}




C_Bomb::~C_Bomb(void)
{
}

void C_Bomb::DrawBomb(HDC& hdc1, HDC& hdc2) 
{
	if (end == false)
	{

		size = temp;+16;
		int offset = size/2;
		TransparentBlt(hdc1, x - offset, y - offset, size, size, hdc2, bombX, 0, size, size, RGB(127, 127, 127));
		if ((++step) % 3 == 0)//3프레임 이후 다음 화면 전환(폭발 애니메이션)
		{
			temp += 16;
			bombX += temp;

		}

		if (step == id * 4)//디스플레이 총애니메이션 프레임 갯수(여기선 4 id * 총 프레임 갯수)
		{
			end = true;
			temp = 0;
			bombX = 0;
		}
	}
}



