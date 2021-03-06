#pragma once
#include <Windows.h>
#include "Main.h"
	class C_Bomb
	{
	public:

		C_Bomb
		(
			int _id = 4,
			int _x = 0,
			int _y = 0,
			int _owner = 0,
			int _size = 0,
			int _bombX = 0,
			int _step = 0,
			int _temp = 0,
			bool _end = false
		);
		~C_Bomb(void);

		int id;
		int x;
		int y;
		int owner;
		int size;
		int bombX;
		int step;
		int temp;
		bool end;
		void DrawBomb(HDC&, HDC&);
	};

