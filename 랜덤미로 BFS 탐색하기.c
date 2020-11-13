#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// 미로 크기 
#define MAX_X 21 //y축 최대 크기
#define MAX_Y 21 //x축 최대 크기
//일단은 크기 고정(헷갈리지 않게 작성.) 추후 유동적으로 변동 가능하게 할것.

int posX = 1, posY = 1; //position

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
	map[1][1] = 0; // 2 = 길 시작점 설정 (0이어도 크게 문제 x -- 다시 생각해보니 0이면 문제가 있으나
}                                      // [1][1] 지점 고정으로 인해 없어보이는 것 처럼 보인것)

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
			else if (i == 1 && j == 1) // 시작점 지정
				printf("●");
			else if (i == MAX_Y - 2 && j == MAX_X - 2) // 도착점 지정
				printf("▼");
			else if (map[i][j] == 0)
				printf("  ");
		}
		printf("\n");
	}
}

void squarebfs();

void display() //처음에 보일 -1과 0으로 이루어진 미로
{
	int x, y;
	for (x = 0; x < 21; x++) // x 너비
	{
		for (y = 0; y < 21; y++) // y 높이
			printf("%3d", map[x][y]); //깔끔하게 출력하기 위해 %3d
		printf("\n");
	}
}

void BFS(int x, int y, int k) //너비 우선으로 모든 길 동시 탐색
{
	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };
	int i;

	if (x < 0 || x >= 21 || y < 0 || y >= 21)
		return;

	if (map[x][y] != 0)
		return;
	map[x][y] = k;
	squarebfs(); //이걸 쓰지않을 경우 반응 없음.
	for (i = 0; i < 4; ++i)
		BFS(x + dx[i], y + dy[i], k + 1);
}

void squarebfs() { //사각형으로 미로+방법수 출력
	int a, b;
	system("cls"); //이걸 void bfs 안에 있는 square를 사용함으로써 애니메이션처럼 출력
	for (a = 0; a < 21; a++) // a 너비
	{
		for (b = 0; b < 21; b++) //b 높이
		{
			if (map[a][b] == -1 || map[a][b] == -2)
			{
				printf("□"); // -1을 벽으로
			}
			else if (map[a][b] == 0) printf("  ");
			else if (map[a][b] != -1 || map[a][b] != -2) // BFS를 통해 길이 숫자로 나오므로 -1을 제외한 (아래주석)
			{
				printf("%2d", map[a][b]); // □와 맞추기 위해 %2d,                   모든 숫자에 대해서 그대로 출력
			}
		}
		printf("\n");
	}
}



int main()
{
	initMap();
	SetLoad();
	Draw_Maze();
	BFS(1, 1, 1);
	squarebfs();

	return 0;
}