//1, 41, 45, 61, 73, 85, 97, 109

#include <iostream>
#include "Main.h"
using namespace std;

const int map_num = 3, block_width = 40, block_height = 9;
int terrain_input[map_num][block_width * block_height] = 
{
	48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 46, 48, 48, 50, 48, 48, 50, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 46, 48, 48, 53, 49, 49, 54, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 46, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 46, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 45, 45, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 45, 45, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 45, 45, 45, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 45, 45, 48, 48, 48, 48, 48, 48, 48, 48,
	48, 48, 48, 50, 48, 48, 48, 50, 48, 48, 48, 50, 48, 48, 55, 59, 59, 59, 56, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 46, 46, 46, 46, 46, 46, 48, 50, 48, 48, 48, 50, 48, 48, 55, 59, 59, 59, 59, 52, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 50, 48, 46, 48, 50, 48, 46, 46, 46, 46, 46, 46, 59, 59, 59, 59, 56, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 50, 48, 46, 48, 50, 48, 46, 48, 50, 48, 48, 55, 59, 59, 59, 59, 54, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 50, 48, 46, 48, 50, 48, 46, 48, 55, 58, 58, 59, 59, 59, 59, 56, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 50, 48, 46, 48, 50, 48, 46, 48, 55, 57, 57, 59, 59, 59, 59, 56, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 50, 48, 46, 48, 50, 48, 46, 48, 50, 48, 48, 55, 59, 59, 59, 56, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 50, 48, 46, 46, 46, 46, 46, 48, 50, 48, 48, 53, 59, 59, 59, 54, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 50, 48, 48, 48, 50, 48, 48, 48, 50, 48, 48, 48, 55, 59, 54, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
	48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 45, 45, 45, 45, 45, 45, 45, 45, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 45, 45, 45, 45, 45, 45, 45, 45, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 48, 48, 48, 48, 48, 48, 48
};
int terrain_output[map_num][block_width * block_height] = {};

int Block_input[map_num][block_width * block_height] = 
{
	13, 0, 0, 0, 0, 0, 13, 0, 61, 13, 0, 0, 1, 1, 0, 0, 29, 39, 39, 0, 61, 29, 0, 0, 0, 0, 0, 1, 1, 0, 0, 13, 33, 0, 85, 33, 0, 13, 13, 13, 0, 0, 0, 13, 1, 1, 0, 0, 0, 1, 0, 0, 13, 0, 1, 37, 29, 39, 39, 0, 0, 0, 29, 0, 0, 61, 0, 0, 29, 0, 0, 29, 0, 0, 0, 0, 73, 13, 41, 13, 1, 13, 0, 0, 1, 1, 0, 13, 1, 1, 0, 33, 0, 0, 29, 29, 29, 29, 29, 1, 13, 1, 0, 29, 1, 1, 0, 29, 0, 0, 0, 33, 33, 0, 33, 0, 38, 0, 0, 13, 0, 0, 13, 0, 13, 33, 0, 0, 0, 0, 13, 0, 0, 37, 29, 0, 61, 0, 29, 0, 0, 0, 0, 13, 0, 13, 29, 0, 61, 13, 0, 0, 61, 0, 33, 0, 0, 33, 13, 13, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 13, 1, 37, 29, 0, 73, 0, 29, 0, 0, 13, 0, 25, 21, 26, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 1, 13, 61, 0, 0, 1, 1, 29, 0, 61, 0, 29, 0, 0, 1, 0, 22, 13, 22, 0, 0, 0, 33, 0, 33, 0, 0, 0, 39, 39, 39, 39, 39, 33, 1, 0, 0, 1, 1, 13, 0, 0, 0, 0, 13, 0, 0, 29, 29, 29, 29, 29, 13, 13, 25, 21, 27, 37, 28, 21, 26, 0, 29, 0, 0, 0, 0, 1, 1, 0, 1, 0, 39, 13, 0, 0, 0, 1, 1, 0, 33, 0, 0, 1, 0, 0, 0, 0, 37, 29, 39, 39, 0, 0, 22, 13, 37, 29, 37, 13, 22, 0, 13, 0, 0, 0, 0, 0, 0, 73, 0, 1, 39, 0, 0, 0, 13, 0, 61, 0, 0, 0, 13, 1, 0, 0, 1, 1, 0, 29, 39, 39, 0, 1, 22, 37, 29, 85, 29, 37, 22, 33, 0, 0, 0, 0, 1, 61, 0, 1, 0, 85, 39,
	0, 29, 0, 0, 29, 0, 0, 0, 33, 39, 0, 0, 0, 0, 0, 0, 0, 37, 0, 38, 33, 0, 13, 29, 0, 13, 0, 73, 13, 0, 29, 0, 1, 0, 29, 0, 38, 38, 38, 38, 0, 0, 0, 61, 0, 0, 85, 0, 29, 0, 33, 0, 38, 37, 0, 0, 0, 33, 0, 0, 33, 0, 0, 0, 1, 0, 29, 29, 0, 13, 29, 0, 13, 1, 1, 1, 0, 109, 0, 0, 0, 0, 0, 0, 0, 0, 29, 0, 73, 0, 0, 0, 0, 0, 0, 33, 73, 0, 0, 0, 39, 33, 13, 29, 29, 73, 13, 0, 1, 0, 0, 1, 29, 0, 0, 22, 0, 0, 13, 13, 0, 0, 39, 0, 0, 0, 37, 0, 29, 0, 37, 0, 0, 33, 0, 0, 85, 0, 0, 0, 39, 39, 0, 13, 1, 1, 0, 29, 25, 21, 21, 1, 0, 85, 29, 22, 38, 97, 0, 0, 0, 33, 39, 0, 38, 0, 33, 0, 0, 0, 29, 0, 0, 0, 0, 0, 73, 0, 0, 38, 38, 13, 13, 0, 0, 13, 0, 1, 22, 0, 0, 0, 29, 0, 29, 22, 38, 0, 0, 41, 0, 0, 39, 0, 37, 0, 39, 0, 38, 0, 39, 0, 0, 0, 0, 0, 33, 33, 37, 33, 0, 0, 0, 29, 29, 29, 61, 1, 22, 73, 1, 13, 0, 85, 0, 28, 26, 97, 0, 0, 33, 0, 39, 0, 33, 0, 0, 0, 0, 0, 39, 73, 38, 0, 0, 0, 33, 33, 0, 33, 33, 13, 1, 1, 1, 21, 21, 21, 27, 13, 0, 0, 1, 0, 13, 0, 22, 0, 13, 13, 0, 29, 0, 0, 0, 0, 61, 0, 0, 0, 33, 0, 0, 39, 0, 0, 0, 0, 0, 0, 0, 97, 13, 1, 29, 0, 13, 0, 29, 0, 29, 29, 0, 0, 13, 0, 1, 109, 0, 0, 29, 0, 33, 0, 0, 29, 29, 0, 29, 0, 37, 0, 0, 33, 0, 0, 61, 0, 33, 33, 38, 38, 0, 0, 29, 1, 0, 73, 0, 13, 0, 1, 1, 29, 29, 0, 38, 38, 38, 38,
	0, 1, 0, 0, 1, 85, 85, 1, 1, 1, 1, 1, 1, 13, 1, 0, 38, 0, 29, 0, 61, 0, 0, 0, 29, 0, 0, 109, 29, 0, 29, 38, 13, 1, 109, 1, 109, 29, 29, 29, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 13, 0, 1, 38, 0, 0, 0, 29, 73, 0, 29, 38, 0, 29, 0, 0, 73, 0, 38, 33, 0, 1, 109, 1, 29, 41, 29, 0, 1, 1, 25, 21, 21, 26, 1, 1, 1, 1, 1, 1, 109, 13, 0, 38, 0, 73, 0, 85, 0, 0, 0, 38, 0, 109, 0, 29, 0, 0, 38, 29, 33, 13, 1, 109, 29, 29, 29, 0, 0, 1, 22, 109, 109, 22, 1, 1, 1, 1, 1, 1, 13, 0, 1, 38, 38, 38, 38, 38, 38, 38, 0, 38, 38, 38, 38, 38, 0, 38, 38, 37, 33, 29, 1, 1, 13, 109, 1, 0, 0, 1, 22, 109, 109, 22, 1, 1, 1, 1, 1, 1, 13, 0, 0, 39, 39, 39, 37, 37, 0, 0, 13, 38, 0, 0, 39, 0, 0, 0, 33, 29, 37, 33, 0, 13, 109, 1, 109, 1, 1, 0, 28, 21, 21, 27, 1, 1, 1, 1, 1, 1, 13, 1, 0, 38, 38, 38, 13, 13, 38, 38, 38, 38, 0, 85, 0, 0, 0, 29, 29, 39, 29, 37, 29, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 109, 13, 1, 38, 37, 13, 0, 0, 0, 38, 0, 0, 39, 0, 29, 33, 29, 33, 33, 29, 33, 29, 33, 13, 1, 13, 13, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 13, 0, 0, 38, 13, 85, 0, 61, 85, 38, 0, 97, 29, 33, 33, 0, 37, 29, 39, 0, 0, 1, 1, 0, 13, 37, 37, 0, 1, 0, 1, 1, 85, 85, 1, 1, 1, 1, 1, 1, 13, 0, 1, 38, 109, 0, 97, 97, 109, 38, 0, 0, 85, 0, 39, 0, 29, 0, 0, 0, 13, 97, 0, 109, 13, 37, 37

};
int Block_output[map_num][block_width * block_height] = {};

#define Block_NONE 0
#define GRASS 1
#define TREE 2
#define WATER 3
#define WATER_ONE 31
#define WATER_TWO 32
#define WATER_THREE 33
#define WATER_FOUR 34
#define WATER_FIVE 35
#define WATER_SIX 36
#define WALL 4
#define STONE 5
#define BUCKET 6
#define IRON  7
#define PITON 8
#define BASTION 9


int main()
{
	for (int i = 0; i < map_num; i++)
		for (int j = 0; j < block_width * block_height; j++)
			terrain_output[i][j] = terrain_input[i][j] - 45;

	const int offset = 0;
	for (int i = 0; i < map_num; i++)
		for (int j = 0; j < block_width * block_height; j++)
			if (Block_input[i][j] == 1 + offset)
				Block_output[i][j] = GRASS;
			else if (Block_input[i][j] == 13 + offset)
				Block_output[i][j] = TREE;
			else if (Block_input[i][j] == 21 + offset || Block_input[i][j] == 22 + offset)
				Block_output[i][j] = WATER_ONE + Block_input[i][j] - (21 + offset);
			else if (Block_input[i][j] >= 25 + offset && Block_input[i][j] <= 28 + offset)
				Block_output[i][j] = WATER_THREE + Block_input[i][j] - (25 + offset);
			else if (Block_input[i][j] == 29 + offset)
				Block_output[i][j] = WALL;
			else if (Block_input[i][j] == 33 + offset)
				Block_output[i][j] = STONE;
			else if (Block_input[i][j] == 37 + offset)
				Block_output[i][j] = BUCKET;
			else if (Block_input[i][j] == 38 + offset)
				Block_output[i][j] = IRON;
			else if (Block_input[i][j] == 39 + offset)
				Block_output[i][j] = PITON;
			else if (Block_input[i][j] == 41 + offset)
				Block_output[i][j] = BASTION;
			else if (Block_input[i][j] == 61 + offset)
				Block_output[i][j] = 90;
			else if (Block_input[i][j] == 73 + offset)
				Block_output[i][j] = 91;
			else if (Block_input[i][j] == 85 + offset)
				Block_output[i][j] = 92;
			else if (Block_input[i][j] == 97 + offset)
				Block_output[i][j] = 93;
			else if (Block_input[i][j] == 109 + offset)
				Block_output[i][j] = 94;


	for (int i = 0; i < map_num; i++)
	{
		for (int j = 0; j < block_width * block_height; j++)
			cout << terrain_output[i][j] << ",";
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < map_num; i++)
	{
		for (int j = 0; j < block_width * block_height; j++)
			cout << Block_output[i][j] << ",";
		cout << endl;
	}

	system("pause");
	return 0;
}