#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
int map[20][20] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 },
	{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1 },
	{ 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1 },
	{ 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 4, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
}; //사람이 초기에 직접 넣은 미로 나중에 미로 랜덤제작으로 넣을 예정
//너비20 높이20
void map_create() { //미로 생성
	int a, b; //a가 너비, b가 높이 

	for (a = 0; a < 20; a++) //너비20
	{
		for (b = 0; b < 20; b++) //높이20
		{
			if (map[a][b] == 1) // 1 = 벽
			{
				printf("□");
			}
			else if (map[a][b] == 0) // 0 = 길
			{
				printf("  ");
			}
			else if (map[a][b] == 3) // 3 = 움직일 아이콘
				printf("●");
			else if (map[a][b] == 4) //4 = 도착점
				printf("▼");
		}
		printf("\n");
	}
}

void character(int x, int y) {
	map[x][y] = 3;
}
int main()
{
	int ch_x = 1, ch_y = 1; // character의 위치 [x가 높이관련 y가 너비관련]
	int cmd = 0; // command 화살표 관련
	while (1) {
		system("cls"); // 이전 결과를 지우고 이후 결과 재출력 (깜빡임)
		printf("길찾기 성공 후 End를 누르십시오.\n");
		printf("(▼에 도착시 길찾기 성공입니다.)\n");
		character(ch_x, ch_y);
		map_create();
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
		if (map[17][18] == 3 && cmd == 80 && map[ch_x + 1][ch_y] == 4) {
			map[ch_x][ch_y] = 0;
			ch_x++;
			map[18][18] = 0; // 도착점 위치를 알기에 도착점으로 이동할 경우 도착점을 이동 가능한 경로로 설정.
			//추가로 달자면 어느 방향 화살표든 ==4로 지정해줄 경우 이동이 가능하게 할 수 있다. 
			//현재 고정된 미로이므로 추후에 유동적으로 할 것.
		}
		if (map[18][17] == 3 && cmd == 77 && map[ch_x][ch_y + 1] == 4) {
			map[ch_x][ch_y] = 0;
			ch_y++;
			map[18][18] = 0; // 내가 만들 모든 미로의 도착지점이 [최대크기-1][최대크기-1] 인 점을 감안. 위의 주석과 동일
		}
		if (map[18][18] == 3 && cmd == 79) {
			printf("길찾기 성공!! \n프로그램을 종료합니다...\n"); // End 버튼으로 종료 79
			return 0;
		}
	}
}