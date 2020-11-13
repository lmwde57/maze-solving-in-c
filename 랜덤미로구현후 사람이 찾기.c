/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// 미로 크기 
#define MAX_X 21 //y(세로)축 최대 크기
#define MAX_Y 21 //x(가로)축 최대 크기
//일단은 크기 고정(헷갈리지 않게 작성.) 추후 유동적으로 변동 가능하게 할것.

int posX = 1, posY = 1; //position 이거는 y가 세로 x가 가로

int map[MAX_X][MAX_Y];

void initMap() { //미로 초기화
	int i, j;

	for (i = 0; i < MAX_Y; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			if (i == 0 || j == 0 || i == MAX_Y - 1 || j == MAX_X - 1) // 테두리 만들기
				map[i][j] = 1; // 1 = 벽
			else
				map[i][j] = 0; // 0 = 공백 공백이 곧 길이라는 느낌이긴 하다. 이것이 2가 될 경우 전체 공백
		}
	}
	map[1][1] = 0; // 2 = 길 시작점 설정 (0이어도 크게 문제 x)
}

void SetLoad() { //길 생성관련
	srand((unsigned)time(NULL));
	int i, Dir; // Direction

	for (i = 0; i < 10000; i++)
	{
		Dir = rand() % 4; // 0 = 위, 1 = 오른쪽, 2 = 아래, 3 = 왼쪽 

		switch (Dir)
		{
		case 0:
			if (posY == 1) continue; // 위쪽으로 갈 길이 없는 경우 

			if (map[posY - 2][posX] == 0) // 2칸 이동한 칸이 공백인 경우
			{
				posY--; map[posY][posX] = 2;
				posY--; map[posY][posX] = 2;
			}
			else if (map[posY - 2][posX] == 2) // 2칸 이동한 칸에 길이 있는 경우
				posY -= 2;
			break;
			//아래 비슷한 과정
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

void Draw_Maze() { //미로 그리기(출력)
	int i, j;
	for (i = 0; i < MAX_Y; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			if (map[i][j] == 0 || map[i][j] == 1) // 벽
				printf("□");
			else if (map[i][j] == 3) { // 시작점 지정
				printf("●");
			}
			else if (i == MAX_Y - 2 && j == MAX_X - 2) // 도착점 지정
				printf("▼");
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
	int ch_x = 1, ch_y = 1; // character의 위치 [x가 높이관련 y가 너비관련]
	int cmd = 0; // command 화살표 관련
	while (1) {
		system("cls"); // 이전 결과를 지우고 이후 결과 재출력 (깜빡임)
		printf("길찾기 성공 후 End를 누르십시오.\n");
		printf("(▼에 도착시 길찾기 성공입니다.)\n");
		character(ch_x, ch_y);
		Draw_Maze();
		//map_create();
		cmd = _getch();
		if (cmd == 77 && map[ch_x][ch_y + 1] == 2) {
			map[ch_x][ch_y] = 2;
			ch_y++; // →방향 77
		}
		else if (cmd == 72 && map[ch_x - 1][ch_y] == 2) {
			map[ch_x][ch_y] = 2;
			ch_x--; // ↑방향 72
		}
		else if (cmd == 75 && map[ch_x][ch_y - 1] == 2) {
			map[ch_x][ch_y] = 2;
			ch_y--; // ←방향 75
		}
		else if (cmd == 80 && map[ch_x + 1][ch_y] == 2) {
			map[ch_x][ch_y] = 2;
			ch_x++; // ↓방향 80
		}
		if (map[19][18] == 3 && cmd == 77 && map[ch_x][ch_y + 1] == 4) {
			map[ch_x][ch_y] = 0;
			ch_y++;
			map[19][19] = 0; // 내가 만들 모든 미로의 도착지점이 [최대크기-1][최대크기-1] 인 점을 감안. 위의 주석과 동일
		}
		if (map[19][19] == 3 && cmd == 79) {
			printf("길찾기 성공!! \n프로그램을 종료합니다...\n"); // End 버튼으로 종료 79
			return 0;
		}
	}
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// 미로 크기 
#define MAX_X 21 //y(세로)축 최대 크기
#define MAX_Y 21 //x(가로)축 최대 크기
//일단은 크기 고정(헷갈리지 않게 작성.) 추후 유동적으로 변동 가능하게 할것.

int posX = 1, posY = 1; //position 이거는 y가 세로 x가 가로

int map[MAX_X][MAX_Y];

void initMap() { //미로 초기화
	int i, j;

	for (i = 0; i < MAX_Y; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			if (i == 0 || j == 0 || i == MAX_Y - 1 || j == MAX_X - 1) // 테두리 만들기
				map[i][j] = -1; // 1 = 벽
			else
				map[i][j] = -2; // 0 = 공백 공백이 곧 길이라는 느낌이긴 하다. 이것이 2가 될 경우 전체 공백
		}
	}
	map[1][1] = 0; // 2 = 길 시작점 설정 (0이어도 크게 문제 x)
}

void SetLoad() { //길 생성관련
	srand((unsigned)time(NULL));
	int i, Dir; // Direction

	for (i = 0; i < 10000; i++)
	{
		Dir = rand() % 4; // 0 = 위, 1 = 오른쪽, 2 = 아래, 3 = 왼쪽 

		switch (Dir)
		{
		case 0:
			if (posY == 1) continue; // 위쪽으로 갈 길이 없는 경우 

			if (map[posY - 2][posX] == -2) // 2칸 이동한 칸이 공백인 경우
			{
				posY--; map[posY][posX] = 0;
				posY--; map[posY][posX] = 0;
			}
			else if (map[posY - 2][posX] == 0) // 2칸 이동한 칸에 길이 있는 경우
				posY -= 2;
			break;
			//아래 비슷한 과정
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

void Draw_Maze() { //미로 그리기(출력)
	int i, j;
	for (i = 0; i < MAX_Y; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			if (map[i][j] == -1 || map[i][j] == -2) // 벽
				printf("□");
			else if (map[i][j] == 3) { // 시작점 지정
				printf("●");
			}
			else if (i == MAX_Y - 2 && j == MAX_X - 2) // 도착점 지정
				printf("▼");
			else if (map[i][j] == 0)
				printf("  ");
		}
		printf("\n");
	}
}

void character(int x, int y) {
	map[x][y] = 3;
}

int main() {
	initMap();
	SetLoad();
	//Draw_Maze();
	int ch_x = 1, ch_y = 1; // character의 위치 [x가 높이관련 y가 너비관련]
	int cmd = 0; // command 화살표 관련
	while (1) {
		system("cls"); // 이전 결과를 지우고 이후 결과 재출력 (깜빡임)
		printf("길찾기 성공 후 End를 누르십시오.\n");
		printf("(▼에 도착시 길찾기 성공입니다.)\n");
		character(ch_x, ch_y);
		Draw_Maze();
		//map_create();
		cmd = _getch();
		if (cmd == 77 && map[ch_x][ch_y + 1] == 0) {
			map[ch_x][ch_y] = 0;
			ch_y++; // →방향 77
		}
		else if (cmd == 72 && map[ch_x - 1][ch_y] == 0) {
			map[ch_x][ch_y] = 0;
			ch_x--; // ↑방향 72
		}
		else if (cmd == 75 && map[ch_x][ch_y - 1] == 0) {
			map[ch_x][ch_y] = 0;
			ch_y--; // ←방향 75
		}
		else if (cmd == 80 && map[ch_x + 1][ch_y] == 0) {
			map[ch_x][ch_y] = 0;
			ch_x++; // ↓방향 80
		}
		if (map[19][18] == 3 && cmd == 77 && map[ch_x][ch_y + 1] == 4) {
			map[ch_x][ch_y] = 0;
			ch_y++;
			map[19][19] = 0; // 내가 만들 모든 미로의 도착지점이 [최대크기-1][최대크기-1] 인 점을 감안. 위의 주석과 동일
		}
		if (map[19][19] == 3 && cmd == 79) {
			printf("길찾기 성공!! \n프로그램을 종료합니다...\n"); // End 버튼으로 종료 79
			return 0;
		}
	}
}
