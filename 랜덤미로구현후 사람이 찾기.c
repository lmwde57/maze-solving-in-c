#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// �̷� ũ�� 
#define MAX_X 21 //y(����)�� �ִ� ũ��
#define MAX_Y 21 //x(����)�� �ִ� ũ��
//�ϴ��� ũ�� ����(�򰥸��� �ʰ� �ۼ�.) ���� ���������� ���� �����ϰ� �Ұ�.

int posX = 1, posY = 1; //position �̰Ŵ� y�� ���� x�� ����

int map[MAX_X][MAX_Y];

void initMap() { //�̷� �ʱ�ȭ
	int i, j;

	for (i = 0; i < MAX_Y; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			if (i == 0 || j == 0 || i == MAX_Y - 1 || j == MAX_X - 1) // �׵θ� �����
				map[i][j] = 1; // 1 = ��
			else
				map[i][j] = 0; // 0 = ���� ������ �� ���̶�� �����̱� �ϴ�. �̰��� 2�� �� ��� ��ü ����
		}
	}
	map[1][1] = 0; // 2 = �� ������ ���� (0�̾ ũ�� ���� x)
}

void SetLoad() { //�� ��������
	srand((unsigned)time(NULL));
	int i, Dir; // Direction

	for (i = 0; i < 10000; i++)
	{
		Dir = rand() % 4; // 0 = ��, 1 = ������, 2 = �Ʒ�, 3 = ���� 

		switch (Dir)
		{
		case 0:
			if (posY == 1) continue; // �������� �� ���� ���� ��� 

			if (map[posY - 2][posX] == 0) // 2ĭ �̵��� ĭ�� ������ ���
			{
				posY--; map[posY][posX] = 2;
				posY--; map[posY][posX] = 2;
			}
			else if (map[posY - 2][posX] == 2) // 2ĭ �̵��� ĭ�� ���� �ִ� ���
				posY -= 2;
			break;
			//�Ʒ� ����� ����
		case 1:
			if (posX == MAX_X - 2) continue;

			if (map[posY][posX + 2] == 0)
			{
				posX++; map[posY][posX] = 2;
				posX++; map[posY][posX] = 2;
			}
			else if (map[posY][posX + 2] == 2)
				posX += 2;
			break;

		case 2:
			if (posY == MAX_Y - 2) continue;

			if (map[posY + 2][posX] == 0)
			{
				posY++; map[posY][posX] = 2;
				posY++; map[posY][posX] = 2;
			}
			else if (map[posY + 2][posX] == 2)
				posY += 2;
			break;

		case 3:
			if (posX == 1) continue;

			if (map[posY][posX - 2] == 0)
			{
				posX--; map[posY][posX] = 2;
				posX--; map[posY][posX] = 2;
			}
			else if (map[posY][posX - 2] == 2)
				posX -= 2;
			break;
		}
	}
}

void Draw_Maze() { //�̷� �׸���(���)
	int i, j;
	for (i = 0; i < MAX_Y; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			if (map[i][j] == 0 || map[i][j] == 1) // ��
				printf("��");
			else if (map[i][j] == 3) { // ������ ����
				printf("��");
			}
			else if (i == MAX_Y - 2 && j == MAX_X - 2) // ������ ����
				printf("��");
			else if (map[i][j] == 2)
				printf("  ");
		}
		printf("\n");
	}
}

void character(int x, int y) {
	map[x][y] = 3;
}

int main() {
	//initMap();
	SetLoad();
	//Draw_Maze();
	int ch_x = 1, ch_y = 1; // character�� ��ġ [x�� ���̰��� y�� �ʺ����]
	int cmd = 0; // command ȭ��ǥ ����
	while (1) {
		system("cls"); // ���� ����� ����� ���� ��� ����� (������)
		printf("��ã�� ���� �� End�� �����ʽÿ�.\n");
		printf("(�忡 ������ ��ã�� �����Դϴ�.)\n");
		character(ch_x, ch_y);
		Draw_Maze();
		//map_create();
		cmd = _getch();
		if (cmd == 77 && map[ch_x][ch_y + 1] == 2) {
			map[ch_x][ch_y] = 2;
			ch_y++; // ����� 77
		}
		else if (cmd == 72 && map[ch_x - 1][ch_y] == 2) {
			map[ch_x][ch_y] = 2;
			ch_x--; // ����� 72
		}
		else if (cmd == 75 && map[ch_x][ch_y - 1] == 2) {
			map[ch_x][ch_y] = 2;
			ch_y--; // ����� 75
		}
		else if (cmd == 80 && map[ch_x + 1][ch_y] == 2) {
			map[ch_x][ch_y] = 2;
			ch_x++; // ����� 80
		}
		if (map[19][18] == 3 && cmd == 77 && map[ch_x][ch_y + 1] == 4) {
			map[ch_x][ch_y] = 0;
			ch_y++;
			map[19][19] = 0; // ���� ���� ��� �̷��� ���������� [�ִ�ũ��-1][�ִ�ũ��-1] �� ���� ����. ���� �ּ��� ����
		}
		if (map[19][19] == 3 && cmd == 79) {
			printf("��ã�� ����!! \n���α׷��� �����մϴ�...\n"); // End ��ư���� ���� 79
			return 0;
		}
	}
}