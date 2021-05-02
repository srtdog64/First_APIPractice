#pragma once
#include <Windows.h>
#include "UNIT.h"

#define DOWN 0
#define LEFT 1
#define UP 2
#define RIGHT 3


C_UNIT::~C_UNIT(void)
{
}


void C_UNIT::Change(int _face)
{
	if (++move_step > 2) move_step = 0;
}

void C_UNIT::Fire()
{
}

void C_UNIT::Death()
{
}

void C_UNIT::Draw(HDC& DC1, HDC& DC2, bool fire)
{
	
}