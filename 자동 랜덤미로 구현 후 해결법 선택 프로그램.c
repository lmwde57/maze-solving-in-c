#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <WinCon.h> //windows.h 헤더파일에 속해있으나 만약을 위해 넣어둠.

void setColor(unsigned short text) { // 숫자, 글자, 문자의 색상을 설정하는 함수
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

// 미로 크기 
#define MAX_X 21 //y(세로)축 최대 크기
#define MAX_Y 21 //x(가로)축 최대 크기
//혼동의 여지가 있으므로 MAX_X와 MAX_Y의 크기를 동일하게 해주는 것이 좋음.

int posX = 1, posY = 1; //position 이거는 y가 세로 x가 가로

int map[MAX_X][MAX_Y];

void initMap() { //미로 초기화
	int i, j;

	for (i = 0; i < MAX_Y; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			if (i == 0 || j == 0 || i == MAX_Y - 1 || j == MAX_X - 1) // 테두리 만들기
				map[i][j] = -1; // -1 = 벽
			else
				map[i][j] = -2; // -2 = 공백, 공백이 곧 길이라는 느낌이긴 하다. tmi 이것이 0이 될 경우 전체 공백 테두리만 생성
		}
	}
	map[1][1] = 0; // 2 = 길 시작점 설정 (0이어도 크게 문제 x -- 엄밀히 0이면 문제가 있으나
}                                      // [1][1] 지점 고정으로 인해 없어보이는 것처럼 보인것)

void SetLoad() { //길 생성관련
	srand((unsigned)time(NULL));
	int i, Dir; // Direction

	for (i = 0; i < 10000; i++)
	{
		Dir = rand() % 4; // 0 = 위, 1 = 오른쪽, 2 = 아래, 3 = 왼쪽 

		// 해당 미로의 특징
		// 1. 길이 한 가지밖에 없다.
		// 2. 길이 절대 막히지 않는다.
		// 3. 절대로 어떠한 길 부분에 대해서 2x2 이상의 정방형 형태가 나오지 않는다. (보이지 않는다.)
		// 단점 : 미로를 한 프로그램 내에서 재생성할 때 시작지점 주변 3x3 부근에서 길이 막히는 경우가 생기나 원인은 알 수 없다.
		// 아마 이전 미로의 것을 어느정도 받아오는 것 같다.

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
			if (posX == MAX_X - 2) continue; // 오른쪽으로 갈 길이 없는 경우

			if (map[posY][posX + 2] == -2) // 2칸 이동한 칸이 공백인 경우
			{
				posX++; map[posY][posX] = 0;
				posX++; map[posY][posX] = 0;
			}
			else if (map[posY][posX + 2] == 0) // 2칸 이동한 칸에 길이 있는 경우
				posX += 2;
			break;

		case 2:
			if (posY == MAX_Y - 2) continue; // 아래쪽으로 갈 길이 없는 경우 

			if (map[posY + 2][posX] == -2) // 2칸 이동한 칸이 공백인 경우
			{
				posY++; map[posY][posX] = 0;
				posY++; map[posY][posX] = 0;
			}
			else if (map[posY + 2][posX] == 0) // 2칸 이동한 칸에 길이 있는 경우
				posY += 2;
			break;

		case 3:
			if (posX == 1) continue; // 왼쪽으로 갈 길이 없는 경우 

			if (map[posY][posX - 2] == -2) // 2칸 이동한 칸이 공백인 경우
			{
				posX--; map[posY][posX] = 0;
				posX--; map[posY][posX] = 0;
			}
			else if (map[posY][posX - 2] == 0) // 2칸 이동한 칸에 길이 있는 경우
				posX -= 2;
			break;
		}
	}
}

void Draw_Maze() { //미로 그리기(출력)
	int i, j;
	unsigned short text2 = 0x0002; //색상 초록색
	unsigned short text3 = 0x0003; //색상 하늘색
	unsigned short text4 = 0x0004; //색상 붉은색
	for (i = 0; i < MAX_Y; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			if (map[i][j] == -1 || map[i][j] == -2) {// 벽, 어차피 못가는 길인 공백으로 취급된 -1도 가시성에 좋게 벽으로 출력
				setColor(text2);
				printf("□");
			}
			else if (map[i][j] == 3) { // 시작점 지정
				setColor(text3);
				printf("●");
			}
			else if (i == MAX_Y - 2 && j == MAX_X - 2) { // 도착점 지정 -> 고정이 아님.
				setColor(text4);
				printf("▼");
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
//int[i][j] 에서 [i]에 해당하는 부분은 세로줄 [j]에 해당하는 부분은 가로줄
void DFS(int i, int j) {
	f[i][j] = -1;
	//printf("%d, %d %d\n", i, j, banbok);
	banbok = banbok + 1; //DFS를 통해 몇 번째로 칸을 방문했는지 카운트
	save[i][j] = banbok; //카운트 값을 나중에 출력하기 위한 배열
	squaredfs();
	if (i - 1 > 0 && (map[i - 1][j] != -1 && map[i - 1][j] != -2) && f[i - 1][j] == 0) DFS(i - 1, j);     //위     ↑
	if (j + 1 < MAX_Y && (map[i][j + 1] != -1 && map[i][j + 1] != -2) && f[i][j + 1] == 0) DFS(i, j + 1); //오른쪽 →
	if (i + 1 < MAX_X && (map[i + 1][j] != -1 && map[i + 1][j] != -2) && f[i + 1][j] == 0) DFS(i + 1, j); //아래   ↓
	if (j - 1 > 0 && (map[i][j - 1] != -1 && map[i][j - 1] != -2) && f[i][j - 1] == 0) DFS(i, j - 1);     //왼쪽   ←
	//시계방향으로 깊이 우선 탐색
}

void squaredfs() { //사각형으로 미로 출력 + DFS 방법수 출력
	int a, b;
	unsigned short text2 = 0x0002; //색상 초록색
	//unsigned short text5 = 0x0005; //색상 자주색
	//unsigned short text3 = 0x0003; //색상 하늘색
	//unsigned short text6 = 0x0006; //색상 노란색
	unsigned short text7 = 0x0007; //색상 하얀색
	//clock_t start = clock(); //DFS로 찾는 미로 시간 시작
	system("cls"); //이걸 void DFS 안에 있는 squaredfs를 사용함으로써 애니메이션처럼 출력
	for (a = 0; a < MAX_Y; a++) // a 너비
	{
		for (b = 0; b < MAX_X; b++) //b 높이
		{
			if (map[a][b] == -1 || map[a][b] == -2) {
				setColor(text2);
				printf(" □"); // -1을 벽으로
			}
			else if (save[a][b] == 0) printf("   ");
			else if (map[a][b] != -1 || map[a][b] != -2) {// DFS를 통해 길이 숫자로 나오므로 -1을 제외한 (아래주석)
				setColor(text7);
				printf("%3d", save[a][b]); // □와 숫자간격을 맞추기 위해 %3d,                          모든 숫자에 대해서 그대로 출력
			} //sqaredfs와 squarebfs에서 dfs의 경우는 save배열을 지나간 길의 위치를 몇 번째로 지나갔는 지를 표시
		}     //따라서 save가 0일때 공백으로 하여 길을 출력하고, bfs의 경우는 map 배열을 그대로 바꿔서 가져다 쓰므로 map[a][b] == 0 으로 사용
		printf("\n");
	}
	//if (save[19][19] != 0) {
		//clock_t end = clock(); //DFS로 찾는 미로 시간 종료
		//setColor(text6);
		//printf("해결 시간: %lf초\n", (double)(end - start) / CLOCKS_PER_SEC); //시간 출력

		//setColor(text3);
		//printf("     %d", save[19][19]); //squaredfs의 주석과 비슷한 방식으로 save[][]로 출력 DFS로 몇 번째에 찾았는지 출력
		//setColor(text7);
		//printf("번째에서 찾았습니다.");
		//exit(0); //exit(0 or 1);함수로 squaredfs함수 즉시종료 0 = 정상종료, 1 = 비정상종료
		//save[19][19]가 도착지점이므로 해당 지점 도착시 즉시 종료가능. 재귀호출함수라 시간을 재려면 포인터로 clock_t start = clock();
	//} // 이 부분을 넘겨주어야 함. 이 부분 주석처리를 지우고 아래 main의 select 2번의 squaredfs아래 부분을 전부 주석처리할 시 즉시 종료 프로그램으로 변경.
}

void squarebfs();
void display() //처음에 보일 -1과 -2, 0으로 이루어진 미로
{
	int x, y;
	for (x = 0; x < MAX_Y; x++) // x 너비
	{
		for (y = 0; y < MAX_X; y++) // y 높이
			printf("%3d", map[x][y]); //깔끔하게 출력하기 위해 %3d
		printf("\n");
	}
}

void BFS(int x, int y, int k) //너비 우선으로 모든 길 동시 탐색
{
	int dx[] = { 0, 1, 0, -1 }; //방향 설정
	int dy[] = { 1, 0, -1, 0 }; //방향 설정
	int i;

	if (x < 0 || x >= MAX_Y || y < 0 || y >= MAX_X)
		return; //리턴하는 함수가 아니므로 재실행

	if (map[x][y] != 0)
		return; //리턴하는 함수가 아니므로 재실행
	map[x][y] = k;
	squarebfs(); //이걸 쓰지않을 경우 반응 없음.
	for (i = 0; i < 4; ++i)
		BFS(x + dx[i], y + dy[i], k + 1);
}

void squarebfs() { //사각형으로 미로 출력 + BFS 방법수 출력
	int a, b;
	unsigned short text2 = 0x0002; //색상 초록색
	//unsigned short text5 = 0x0005; //색상 자주색
	unsigned short text7 = 0x0007; //색상 하얀색
	system("cls"); //이걸 void BFS 안에 있는 squarebfs를 사용함으로써 애니메이션처럼 출력
	for (a = 0; a < MAX_X; a++) // a 너비
	{
		for (b = 0; b < MAX_Y; b++) //b 높이
		{
			if (map[a][b] == -1 || map[a][b] == -2) {
				setColor(text2);
				printf("□"); // -1을 벽으로
			}
			else if (map[a][b] == 0) printf("  ");
			else if (map[a][b] != -1 || map[a][b] != -2) { // BFS를 통해 길이 숫자로 나오므로 -1을 제외한 (아래주석)
				setColor(text7);
				printf("%2d", map[a][b]); // □와 숫자간격을 맞추기 위해 %2d,                             모든 숫자에 대해서 그대로 출력
			}
		}
		printf("\n");
	}
}

int main() {

	typedef struct _CONSOLE_CURSOR_INFO {
		DWORD  dwSize;
		BOOL   bVisible;
	} CONSOLE_CURSOR_INFO, * PCONSOLE_CURSOR_INFO;

	static HANDLE hOut;
	CONSOLE_CURSOR_INFO cInfo;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cInfo.dwSize = 10; //커서 크기 조정 관련 10~100 유효값
	cInfo.bVisible = FALSE; // TRUE 혹은 FALSE 로 커서의 유무 조절 가능
	SetConsoleCursorInfo(hOut, &cInfo);
	//커서를 FALSE로 껐으므로 깜빡임이 없으나 콘솔창을 확대하는 순간 커서가 생성됨. (시스템 자체이므로 절대적 수정불가)

	unsigned short text3 = 0x0003; //색상 하늘색
	unsigned short text6 = 0x0006; //색상 노란색
	unsigned short text7 = 0x0007; //색상 하얀색

	initMap();
	SetLoad();
	Draw_Maze();
	int select;
	int select2;

	while (1) {
		printf("1은 재생성(Beta), 2는 미로찾기 시작\n");
		scanf_s("%d", &select2);
		if (select2 == 1) {
			system("cls");
			initMap();
			SetLoad();
			Draw_Maze();
		}
		else if (select2 == 2) {
			printf("생성된 미로입니다.\n");
			printf("1은 직접찾기, 2는 DFS, 3은 BFS\n");
			scanf_s("%d", &select);
			if (select == 1) {
				clock_t start = clock(); //사람이 직접 찾는 미로 시간 시작
				//Draw_Maze();
				int ch_x = 1, ch_y = 1; // character의 위치 [x가 높이관련 y가 너비관련]
				int cmd = 0; // command 화살표 관련
				while (1) {
					system("cls"); // 이전 결과를 지우고 이후 결과 재출력 (깜빡임)
					setColor(text7);
					printf("길찾기 성공 후 End를 누르십시오.\n");
					printf("(▼에 도착시 길찾기 성공입니다.)\n");
					character(ch_x, ch_y);
					Draw_Maze();
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
					//if (map[19][18] == 3 && cmd == 77 && map[ch_x][ch_y + 1] == 4) {
						//map[ch_x][ch_y] = 0;
						//ch_y++;
						//map[19][19] = 0; // 내가 만들 모든 미로의 도착지점이 [최대크기-1][최대크기-1] 인 점을 감안. 위의 주석과 동일
					//}
					if (map[19][19] == 3 && cmd == 79) {
						clock_t end = clock(); //사람이 직접 찾는 미로 시간 종료
						setColor(text6);
						printf("해결 시간: %lf초\n", (double)(end - start) / CLOCKS_PER_SEC); //시간 출력

						setColor(text7);
						printf("길찾기 성공!! \n프로그램을 종료합니다...\n"); // End 버튼으로 종료 79

						return 0;
					}
				}
			}
			else if (select == 2) {
				clock_t start = clock(); //DFS로 찾는 미로 시간 시작
				printf("\n\n");
				DFS(1, 1);
				squaredfs();

				clock_t end = clock(); //DFS로 찾는 미로 시간 종료
				setColor(text6);
				printf("해결 시간: %lf초\n", (double)(end - start) / CLOCKS_PER_SEC); //시간 출력

				setColor(text3);
				printf("     %d", save[19][19]); //squaredfs의 주석과 비슷한 방식으로 save[][]로 출력 DFS로 몇 번째에 찾았는지 출력
				setColor(text7);
				printf("번째에서 찾았습니다.");
				exit(0);

				return 0;
			}
			else if (select == 3) {
				clock_t start = clock(); //BFS로 찾는 미로 시간 시작
				printf("\n\n");
				BFS(1, 1, 1);
				squarebfs();

				clock_t end = clock(); //BFS로 찾는 미로 시간 시작
				setColor(text6);
				printf("해결 시간: %lf초\n", (double)(end - start) / CLOCKS_PER_SEC); //시간 출력

				setColor(text3);
				printf("      %d", map[19][19]); //squarebfs의 주석과 비슷한 방식으로 map[][]로 출력 BFS로 몇 번째에 찾았는지 출력
				setColor(text7);
				printf("번째에서 찾았습니다.");
				//printf("\n");
				//display(); //square을 거치지 않은 미로+방법수 출력

				return 0;
			}
			else printf("잘못 입력하셨습니다.\n");
		}
		else printf("잘못 입력하셨습니다.\n");
	}
}
