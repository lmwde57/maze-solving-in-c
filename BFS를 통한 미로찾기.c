#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>


int map[20][20] = {
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ -1, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, -1, 0, -1, 0, -1, 0, 0, -1 },
	{ -1, 0, -1, 0, -1, 0, -1, -1, -1, -1, 0, -1, 0, 0, 0, 0, 0, -1, 0, -1 },
	{ -1, -1, -1, 0, 0, 0, -1, 0, 0, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0, -1 },
	{ -1, 0, 0, 0, -1, 0, -1, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1 },
	{ -1, 0, -1, -1, -1, 0, 0, 0, 0, -1, -1, -1, -1, 0, -1, -1, -1, -1, 0, -1 },
	{ -1, 0, -1, 0, -1, 0, -1, -1, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, -1 },
	{ -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, -1, -1, 0, -1, -1, -1, -1 },
	{ -1, -1, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1 },
	{ -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, -1, 0, 0, -1, -1 },
	{ -1, 0, -1, -1, -1, -1, -1, 0, -1, -1, -1, 0, 0, -1, -1, -1, -1, 0, 0, -1 },
	{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, -1 },
	{ -1, -1, -1, -1, 0, -1, -1, -1, 0, -1, -1, 0, -1, -1, 0, -1, -1, -1, 0, -1 },
	{ -1, 0, 0, 0, 0, -1, 0, 0, -1, 0, -1, 0, 0, -1, 0, -1, 0, 0, 0, -1 },
	{ -1, 0, -1, -1, -1, -1, -1, 0, -1, 0, 0, 0, -1, -1, -1, -1, 0, -1, 0, -1 },
	{ -1, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, -1, -1, -1, 0, -1 },
	{ -1, -1, -1, 0, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1 },
	{ -1, 0, -1, -1, -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, -1, -1, -1, -1, 0, -1 },
	{ -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1 },
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
};
 // 1로 할 경우 오류가 발생. 전체를 하나로 합칠 때에 수정 예정. (-1의 경우 프로그래밍시 가시성은 별로이나 전체 프로그램을 묶을 시 편안.)
void square();

void display() //처음에 보일 -1과 0으로 이루어진 미로
{
	int x, y;
	for (x = 0; x < 20; x++) // x 너비
	{
		for (y = 0; y < 20; y++) // y 높이
			printf("%3d", map[x][y]); //깔끔하게 출력하기 위해 %3d
		printf("\n");
	}
}
void BFS(int x, int y, int k) //너비 우선으로 모든 길 동시 탐색
{
	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };
	int i;

	if (x < 0 || x >= 20 || y < 0 || y >= 20)
		return;

	if (map[x][y] != 0)
		return;
	map[x][y] = k;
	square(); //이걸 쓰지않을 경우 반응 없음.
	for (i = 0; i < 4; ++i)
		BFS(x + dx[i], y + dy[i], k + 1);
}

void square() { //사각형으로 미로+방법수 출력
	int a, b;
	system("cls"); //이걸 void bfs 안에 있는 square를 사용함으로써 애니메이션처럼 출력
	for (a = 0; a < 20; a++) // a 너비
	{
		for (b = 0; b < 20; b++) //b 높이
		{
			if (map[a][b] == -1)
			{
				printf("□"); // -1을 벽으로
			}
			else if (map[a][b] != -1) // BFS를 통해 길이 숫자로 나오므로 -1을 제외한 (아래주석)
			{
				printf("%2d", map[a][b]); // □와 맞추기 위해 %2d,                   모든 숫자에 대해서 그대로 출력
			}
		}
		printf("\n");
	}
}

int main()
{
	BFS(1, 1, 1);
	square();
	//printf("\n");
	//display(); //square을 거치지 않은 미로+방법수 출력
	return 0;
}
