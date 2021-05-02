#pragma once

//�������Լ�: ���������Լ�
class C_Bullet
{
public:
	C_Bullet
		(
		double _x = 0,
		double _y = 0,
		int _speed = 6,		//�Ѿ� �ӵ�
		int _attack = 30,		//�Ѿ� ������
		int _id = 0,
		int _wide = 10,		//�Ѿ� ũ�� X��
		int _high = 10,		//�Ѿ� ũ�� Y��
		int _owner = 0,
		int _face = 0,
		int _explode = 0,		//
		int _offset_w = 0,	//
		int _offset_h = 0,		//
		bool _dead = false,//�Ѿ��� �ִ��� ������
		int _hp = 30
	) :
		x(_x),
		y(_y),
		speed(_speed),
		attack(_attack),
		id(_id),
		wide(_wide),
		high(_high),
		owner(_owner),
		face(_face),
		explode(_explode),
		offset_w(_offset_w),
		offset_h(_offset_h),
		dead(_dead),
		hp(_hp)
	{
	}

	~C_Bullet(void) {}
	double x;
	double y;
	int speed;
	int attack;
	int id;
	int wide;
	int high;
	int owner;
	int face;
	int explode;
	int offset_w;
	int offset_h;
	int dead;
	int hp;
};

