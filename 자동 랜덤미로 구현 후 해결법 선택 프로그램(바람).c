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
//ȥ���� ������ �����Ƿ� MAX_X�� MAX_Y�� ũ�⸦ �����ϰ� ���ִ� ���� ����.

int posX = 1, posY = 1; //position �̰Ŵ� y�� ���� x�� ����

int map[MAX_X][MAX_Y];

void initMap() { //�̷� �ʱ�ȭ
	int i, j;

	for (i = 0; i < MAX_Y; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			if (i == 0 || j == 0 || i == MAX_Y - 1 || j == MAX_X - 1) // �׵θ� �����
				map[i][j] = -1; // -1 = ��
			else
				map[i][j] = -2; // -2 = ����, ������ �� ���̶�� �����̱� �ϴ�. tmi �̰��� 0�� �� ��� ��ü ���� �׵θ��� ����
		}
	}
	map[1][1] = 0; // 2 = �� ������ ���� (0�̾ ũ�� ���� x -- �ٽ� �����غ��� 0�̸� ������ ������
}                                      // [1][1] ���� �������� ���� ����̴� �� ó�� ���ΰ�)

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

			if (map[posY - 2][posX] == -2) // 2ĭ �̵��� ĭ�� ������ ���
			{
				posY--; map[posY][posX] = 0;
				posY--; map[posY][posX] = 0;
			}
			else if (map[posY - 2][posX] == 0) // 2ĭ �̵��� ĭ�� ���� �ִ� ���
				posY -= 2;
			break;
			//�Ʒ� ����� ����
		case 1:
			if (posX == MAX_X - 2) continue;

			if (map[posY][posX + 2] == -2)
			{
				posX++; map[posY][posX] = 0;
				posX++; map[posY][posX] = 0;
			}
			else if (map[posY][posX + 2] == 0)
				posX += 2;
			break;

		case 2:
			if (posY == MAX_Y - 2) continue;

			if (map[posY + 2][posX] == -2)
			{
				posY++; map[posY][posX] = 0;
				posY++; map[posY][posX] = 0;
			}
			else if (map[posY + 2][posX] == 0)
				posY += 2;
			break;

		case 3:
			if (posX == 1) continue;

			if (map[posY][posX - 2] == -2)
			{
				posX--; map[posY][posX] = 0;
				posX--; map[posY][posX] = 0;
			}
			else if (map[posY][posX - 2] == 0)
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
			if (map[i][j] == -1 || map[i][j] == -2) // �� ������ ������ ���� �������� ��޵� -1�� ���ü��� ���� ������ ���
				printf("��");
			else if (map[i][j] == 3) { // ������ ����
				printf("��");
			}
			else if (i == MAX_Y - 2 && j == MAX_X - 2) // ������ ����
				printf("��");
			else if (map[i][j] == 0)
				printf("  ");
		}
		printf("\n");
	}
}

void character(int x, int y) {
	map[x][y] = 3;
}

void squaredfs();

int f[MAX_X][MAX_Y];
int banbok = 0;
save[MAX_X][MAX_Y];
//int[i][j] ���� [i]�� �ش��ϴ� �κ��� ������ [j]�� �ش��ϴ� �κ��� ������
void DFS(int i, int j) {
	f[i][j] = -1;
	//printf("%d, %d %d\n", i, j, banbok);
	banbok = banbok + 1; //DFS�� ���� �� ��°�� ĭ�� �湮�ߴ��� ī��Ʈ
	save[i][j] = banbok; //ī��Ʈ ���� ���߿� ����ϱ� ���� �迭
	squaredfs();
	if (i - 1 > 0 && (map[i - 1][j] != -1 && map[i - 1][j] != -2) && f[i - 1][j] == 0) DFS(i - 1, j);     //��     ��
	if (j + 1 < MAX_Y && (map[i][j + 1] != -1 && map[i][j + 1] != -2) && f[i][j + 1] == 0) DFS(i, j + 1); //������ ��
	if (i + 1 < MAX_X && (map[i + 1][j] != -1 && map[i + 1][j] != -2) && f[i + 1][j] == 0) DFS(i + 1, j); //�Ʒ�   ��
	if (j - 1 > 0 && (map[i][j - 1] != -1 && map[i][j - 1] != -2) && f[i][j - 1] == 0) DFS(i, j - 1);     //����   ��
	//�ð�������� ���� �켱 Ž��
}

void squaredfs() { //�簢������ �̷�+����� ���
	int a, b;
	system("cls"); //�̰� void DFS �ȿ� �ִ� squaredfs�� ��������ν� �ִϸ��̼�ó�� ���
	for (a = 0; a < MAX_Y; a++) // a �ʺ�
	{
		for (b = 0; b < MAX_X; b++) //b ����
		{
			if (map[a][b] == -1 || map[a][b] == -2)
			{
				printf(" ��"); // -1�� ������
			}
			else if (map[a][b] != -1 || map[a][b] != -2) // DFS�� ���� ���� ���ڷ� �����Ƿ� -1�� ������ (�Ʒ��ּ�)
			{
				printf("%3d", save[a][b]); // ��� ���ڰ����� ���߱� ���� %3d,                          ��� ���ڿ� ���ؼ� �״�� ���
			}
		}
		printf("\n");
	}
}

void squarebfs();

void display() //ó���� ���� -1�� 0���� �̷���� �̷�
{
	int x, y;
	for (x = 0; x < MAX_Y; x++) // x �ʺ�
	{
		for (y = 0; y < MAX_X; y++) // y ����
			printf("%3d", map[x][y]); //����ϰ� ����ϱ� ���� %3d
		printf("\n");
	}
}

void BFS(int x, int y, int k) //�ʺ� �켱���� ��� �� ���� Ž��
{
	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };
	int i;

	if (x < 0 || x >= MAX_Y || y < 0 || y >= MAX_X)
		return;

	if (map[x][y] != 0)
		return;
	map[x][y] = k;
	squarebfs(); //�̰� �������� ��� ���� ����.
	for (i = 0; i < 4; ++i)
		BFS(x + dx[i], y + dy[i], k + 1);
}

void squarebfs() { //�簢������ �̷�+����� ���
	int a, b;
	system("cls"); //�̰� void BFS �ȿ� �ִ� squarebfs�� ��������ν� �ִϸ��̼�ó�� ���
	for (a = 0; a < MAX_X; a++) // a �ʺ�
	{
		for (b = 0; b < MAX_Y; b++) //b ����
		{
			if (map[a][b] == -1 || map[a][b] == -2)
			{
				printf("��"); // -1�� ������
			}
			else if (map[a][b] == 0) printf("  ");
			else if (map[a][b] != -1 || map[a][b] != -2) // BFS�� ���� ���� ���ڷ� �����Ƿ� -1�� ������ (�Ʒ��ּ�)
			{
				printf("%2d", map[a][b]); // ��� ���ڰ����� ���߱� ���� %2d,                           ��� ���ڿ� ���ؼ� �״�� ���
			}
		}
		printf("\n");
	}
}

int main() {
	printf("������ �̷��Դϴ�.\n");
	printf("1�� ����ã��, 2�� DFS, 3�� BFS\n");
	initMap();
	SetLoad();
	Draw_Maze();
	int suntak;
	scanf_s("%d", &suntak);
	if (suntak == 1) {
		//Draw_Maze();
		int ch_x = 1, ch_y = 1; // character�� ��ġ [x�� ���̰��� y�� �ʺ����]
		int cmd = 0; // command ȭ��ǥ ����
		while (1) {
			system("cls"); // ���� ����� ����� ���� ��� ����� (������)
			printf("��ã�� ���� �� End�� �����ʽÿ�.\n");
			printf("(�忡 ������ ��ã�� �����Դϴ�.)\n");
			character(ch_x, ch_y);
			Draw_Maze();
			cmd = _getch();
			if (cmd == 77 && map[ch_x][ch_y + 1] == 0) {
				map[ch_x][ch_y] = 0;
				ch_y++; // ����� 77
			}
			else if (cmd == 72 && map[ch_x - 1][ch_y] == 0) {
				map[ch_x][ch_y] = 0;
				ch_x--; // ����� 72
			}
			else if (cmd == 75 && map[ch_x][ch_y - 1] == 0) {
				map[ch_x][ch_y] = 0;
				ch_y--; // ����� 75
			}
			else if (cmd == 80 && map[ch_x + 1][ch_y] == 0) {
				map[ch_x][ch_y] = 0;
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
	else if (suntak == 2) {
		printf("\n\n");
		DFS(1, 1);
		squaredfs();
	}
	else if (suntak == 3) {
		printf("\n\n");
		BFS(1, 1, 1);
		squarebfs();
		//printf("\n");
		//display(); //square�� ��ġ�� ���� �̷�+����� ���
	}
}