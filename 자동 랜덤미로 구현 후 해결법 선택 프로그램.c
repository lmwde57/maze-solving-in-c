#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <WinCon.h> //windows.h ������Ͽ� ���������� ������ ���� �־��.

void setColor(unsigned short text) { // ����, ����, ������ ������ �����ϴ� �Լ�
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

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
	map[1][1] = 0; // 2 = �� ������ ���� (0�̾ ũ�� ���� x -- ������ 0�̸� ������ ������
}                                      // [1][1] ���� �������� ���� ����̴� ��ó�� ���ΰ�)

void SetLoad() { //�� ��������
	srand((unsigned)time(NULL));
	int i, Dir; // Direction

	for (i = 0; i < 10000; i++)
	{
		Dir = rand() % 4; // 0 = ��, 1 = ������, 2 = �Ʒ�, 3 = ���� 

		// �ش� �̷��� Ư¡
		// 1. ���� �� �����ۿ� ����.
		// 2. ���� ���� ������ �ʴ´�.
		// 3. ����� ��� �� �κп� ���ؼ� 2x2 �̻��� ������ ���°� ������ �ʴ´�. (������ �ʴ´�.)

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
			if (posX == MAX_X - 2) continue; // ���������� �� ���� ���� ���

			if (map[posY][posX + 2] == -2) // 2ĭ �̵��� ĭ�� ������ ���
			{
				posX++; map[posY][posX] = 0;
				posX++; map[posY][posX] = 0;
			}
			else if (map[posY][posX + 2] == 0) // 2ĭ �̵��� ĭ�� ���� �ִ� ���
				posX += 2;
			break;

		case 2:
			if (posY == MAX_Y - 2) continue; // �Ʒ������� �� ���� ���� ��� 

			if (map[posY + 2][posX] == -2) // 2ĭ �̵��� ĭ�� ������ ���
			{
				posY++; map[posY][posX] = 0;
				posY++; map[posY][posX] = 0;
			}
			else if (map[posY + 2][posX] == 0) // 2ĭ �̵��� ĭ�� ���� �ִ� ���
				posY += 2;
			break;

		case 3:
			if (posX == 1) continue; // �������� �� ���� ���� ��� 

			if (map[posY][posX - 2] == -2) // 2ĭ �̵��� ĭ�� ������ ���
			{
				posX--; map[posY][posX] = 0;
				posX--; map[posY][posX] = 0;
			}
			else if (map[posY][posX - 2] == 0) // 2ĭ �̵��� ĭ�� ���� �ִ� ���
				posX -= 2;
			break;
		}
	}
}

void Draw_Maze() { //�̷� �׸���(���)
	int i, j;
	unsigned short text2 = 0x0002; //���� �ʷϻ�
	unsigned short text3 = 0x0003; //���� �ϴû�
	unsigned short text4 = 0x0004; //���� ������
	for (i = 0; i < MAX_Y; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			if (map[i][j] == -1 || map[i][j] == -2) {// ��, ������ ������ ���� �������� ��޵� -1�� ���ü��� ���� ������ ���
				setColor(text2);
				printf("��");
			}
			else if (map[i][j] == 3) { // ������ ����
				setColor(text3);
				printf("��");
			}
			else if (i == MAX_Y - 2 && j == MAX_X - 2) { // ������ ���� -> ������ �ƴ�.
				setColor(text4);
				printf("��");
			}
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

void squaredfs() { //�簢������ �̷� ��� + DFS ����� ���
	int a, b;
	unsigned short text2 = 0x0002; //���� �ʷϻ�
	unsigned short text5 = 0x0005; //���� ���ֻ�
	system("cls"); //�̰� void DFS �ȿ� �ִ� squaredfs�� ��������ν� �ִϸ��̼�ó�� ���
	for (a = 0; a < MAX_Y; a++) // a �ʺ�
	{
		for (b = 0; b < MAX_X; b++) //b ����
		{
			if (map[a][b] == -1 || map[a][b] == -2) {
				setColor(text2);
				printf(" ��"); // -1�� ������
			}
			else if (save[a][b] == 0) printf("   ");
			else if (map[a][b] != -1 || map[a][b] != -2) {// DFS�� ���� ���� ���ڷ� �����Ƿ� -1�� ������ (�Ʒ��ּ�)
				setColor(text5);
				printf("%3d", save[a][b]); // ��� ���ڰ����� ���߱� ���� %3d,                          ��� ���ڿ� ���ؼ� �״�� ���
			} //sqaredfs�� squarebfs���� dfs�� ���� save�迭�� ������ ���� ��ġ�� �� ��°�� �������� ���� ǥ��
		}     //���� save�� 0�϶� �������� �Ͽ� ���� ����ϰ�, bfs�� ���� map �迭�� �״�� �ٲ㼭 ������ ���Ƿ� map[a][b] == 0 ���� ���
		printf("\n");
	}
}

void squarebfs();

void display() //ó���� ���� -1�� -2, 0���� �̷���� �̷�
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
	int dx[] = { 0, 1, 0, -1 }; //���� ����
	int dy[] = { 1, 0, -1, 0 }; //���� ����
	int i;

	if (x < 0 || x >= MAX_Y || y < 0 || y >= MAX_X)
		return; //�����ϴ� �Լ��� �ƴϹǷ� �����

	if (map[x][y] != 0)
		return; //�����ϴ� �Լ��� �ƴϹǷ� �����
	map[x][y] = k;
	squarebfs(); //�̰� �������� ��� ���� ����.
	for (i = 0; i < 4; ++i)
		BFS(x + dx[i], y + dy[i], k + 1);
}

void squarebfs() { //�簢������ �̷� ��� + BFS ����� ���
	int a, b;
	unsigned short text2 = 0x0002; //���� �ʷϻ�
	unsigned short text5 = 0x0005; //���� ���ֻ�
	system("cls"); //�̰� void BFS �ȿ� �ִ� squarebfs�� ��������ν� �ִϸ��̼�ó�� ���
	for (a = 0; a < MAX_X; a++) // a �ʺ�
	{
		for (b = 0; b < MAX_Y; b++) //b ����
		{
			if (map[a][b] == -1 || map[a][b] == -2) {
				setColor(text2);
				printf("��"); // -1�� ������
			}
			else if (map[a][b] == 0) printf("  ");
			else if (map[a][b] != -1 || map[a][b] != -2) { // BFS�� ���� ���� ���ڷ� �����Ƿ� -1�� ������ (�Ʒ��ּ�)
				setColor(text5);
				printf("%2d", map[a][b]); // ��� ���ڰ����� ���߱� ���� %2d,                             ��� ���ڿ� ���ؼ� �״�� ���
			}
		}
		printf("\n");
	}
}

int main() {
	unsigned short text3 = 0x0003; //���� �����
	unsigned short text7 = 0x0007; //���� �Ͼ��
	printf("������ �̷��Դϴ�.\n");
	printf("1�� ����ã��, 2�� DFS, 3�� BFS\n");
	initMap();
	SetLoad();
	Draw_Maze();
	int select;
	scanf_s("%d", &select);
	if (select == 1) {
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
			//if (map[19][18] == 3 && cmd == 77 && map[ch_x][ch_y + 1] == 4) {
				//map[ch_x][ch_y] = 0;
				//ch_y++;
				//map[19][19] = 0; // ���� ���� ��� �̷��� ���������� [�ִ�ũ��-1][�ִ�ũ��-1] �� ���� ����. ���� �ּ��� ����
			//}
			if (map[19][19] == 3 && cmd == 79) {
				printf("��ã�� ����!! \n���α׷��� �����մϴ�...\n"); // End ��ư���� ���� 79
				return 0;
			}
		}
	}
	else if (select == 2) {
		printf("\n\n");
		DFS(1, 1);
		squaredfs();
		setColor(text3);
		printf("     %d", save[19][19]); //squaredfs�� �ּ��� ����� ������� save[][]�� ��� DFS�� �� ��°�� ã�Ҵ��� ���
		setColor(text7);
		printf("��°���� ã�ҽ��ϴ�.");
	}
	else if (select == 3) {
		printf("\n\n");
		BFS(1, 1, 1);
		squarebfs();
		setColor(text3);
		printf("      %d", map[19][19]); //squarebfs�� �ּ��� ����� ������� map[][]�� ��� DFS�� �� ��°�� ã�Ҵ��� ���
		setColor(text7);
		printf("��°���� ã�ҽ��ϴ�.");
		//printf("\n");
		//display(); //square�� ��ġ�� ���� �̷�+����� ���
	}
}