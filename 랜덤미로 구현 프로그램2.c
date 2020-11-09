#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// �̷� ũ�� 
#define MAX_X 21 //y�� �ִ� ũ��
#define MAX_Y 21 //x�� �ִ� ũ��
//�ϴ��� ũ�� ����(�򰥸��� �ʰ� �ۼ�.) ���� ���������� ���� �����ϰ� �Ұ�.

int posX = 1, posY = 1; //position

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
	map[1][1] = 2; // 2 = �� ������ ���� (0�̾ ũ�� ���� x)
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
			else if (i == 1 && j == 1) // ������ ����
				printf("��");
			else if (i == MAX_Y - 2 && j == MAX_X - 2) // ������ ����
				printf("��");
			else if(map[i][j] == 2)
				printf("  ");
		}
		printf("\n");
	}
}

int main()
{
	//initMap();
	SetLoad();
	Draw_Maze();

	return 0;
}