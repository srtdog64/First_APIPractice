#pragma once
class C_Thing
{
public:
	C_Thing
	(
		int _id,
		int _x,
		int _y,
		int _time,
		int _last
	) :
		id(_id), x(_x), y(_y), time(_time), last(_last) {}

	~C_Thing(void) {}

	int id;
	int x;
	int y;
	int time;   //��� ������ ���ӽð�
	int last;  //������ ������ ȿ�� �ð�.
};

