// omok.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

//키보드 매크로
#define UP 72		//방향키 위
#define DOWN 80		//방향키 아래
#define LEFT 75		//방향키 왼쪽
#define RIGHT 77	//방향키 오른쪽
#define ENTER 13	//엔터키
#define ESC 27		//ESC키

//흑백 매크로
#define BLACK 1
#define WHITE 2
#define EMPTY 0
#define DRAW_BLACK printf("○")
#define DRAW_WHITE printf("●")

//바둑판 크기 관련 매크로
#define StartpointX 20
#define StartpointY 10
#define MAX_X 15
#define MAX_Y 15
#define EndpointX (StartpointX + (MAX_X - 1) * 2)
#define EndpointY (StartpointY + (MAX_Y - 1))

int aix, aiy; //ai 변수

typedef struct _omokboard {
	int board[MAX_Y][MAX_X];
} Omokboard;

void gotoxy(int x, int y)	//gotoxy
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(int color_number)	//글자 색
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void incursor(int n)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = n;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void printOmokboard(int x, int y);


void mainUI(void);	//Main UI
void playUI(int select);	//게임화면
void RankUI(void);	//랭킹창 UI
void RankEasyHardUI(void);	//랭킹 난이도 선택
void selectAIuser(void); //AI대전 user대전 선택

int checkGameStatus(int board[MAX_Y][MAX_X]);	//winlose

void mainscreen(void);
void RankEasyHardprintscreen(void); 
void Rankprintscreen(void);				
void selectAIuserscreen(void);
void selectAIuserscreen(void);
void putstone(Omokboard *play, int x, int y, int player);	//엔터를 눌렀을 때 돌의 위치 기록
int checkcanstone(Omokboard* board, int x, int y, int direction);	//지정한 방향에서 놓을 수 있는 최초의 위치까지의 거리 반환
void checkstartstone(Omokboard* play, int* x, int* y); // 돌을 놓은 후 다음 상황에서 시작지점에 돌을 놓을 수 있는지, 못 놓는다면 대체로 놓을 곳 선정
void printboardrecord(Omokboard* record);

int turn(int board[MAX_Y][MAX_X], int depth, int* a, int* b, int evex, int evey); //AI 메인
int getWeight(int board[MAX_Y][MAX_X], int x, int y); //가중치 계산

int main() {
	//RankEasyHardUI();
	//printOmokboard();
	//playUI();
	selectAIuser();
	return 0;
}
void mainscreen(void) {
	system("mode con cols=92 lines=40");
	system("cls");
	system("mode con cols=92 lines=40");
	system("cls");
	gotoxy(20, 10);
	printf("랭킹 1등 ");
	gotoxy(20, 15);
	printf("랭킹 2등 ");
	gotoxy(20, 20);
	printf("랭킹 3등 ");
	gotoxy(20, 25);
	printf("뒤로가기 ");
}

void mainUI(void) {
	int X = 0, Y = 0;
	
}

int checkGameStatus(int board[MAX_Y][MAX_X]) {
	// 가로 방향 체크
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X - 4; j++) {
			if (board[i][j] != EMPTY &&
				board[i][j] == board[i][j + 1] &&
				board[i][j] == board[i][j + 2] &&
				board[i][j] == board[i][j + 3] &&
				board[i][j] == board[i][j + 4]) {
				return board[i][j]; // 승리한 플레이어 반환
			}
		}
	}

	// 세로 방향 체크
	for (int i = 0; i < MAX_X - 4; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			if (board[i][j] != EMPTY &&
				board[i][j] == board[i + 1][j] &&
				board[i][j] == board[i + 2][j] &&
				board[i][j] == board[i + 3][j] &&
				board[i][j] == board[i + 4][j]) {
				return board[i][j]; // 승리한 플레이어 반환
			}
		}
	}

	// 대각선 방향 체크 (왼쪽 위에서 오른쪽 아래로)
	for (int i = 0; i < MAX_Y - 4; i++) {
		for (int j = 0; j < MAX_X - 4; j++) {
			if (board[i][j] != EMPTY &&
				board[i][j] == board[i + 1][j + 1] &&
				board[i][j] == board[i + 2][j + 2] &&
				board[i][j] == board[i + 3][j + 3] &&
				board[i][j] == board[i + 4][j + 4]) {
				return board[i][j]; // 승리한 플레이어 반환
			}
		}
	}

	// 대각선 방향 체크 (오른쪽 위에서 왼쪽 아래로)
	for (int i = 0; i <  MAX_X - 4; i++) {
		for (int j = 4; j < MAX_Y; j++) {
			if (board[i][j] != EMPTY &&
				board[i][j] == board[i + 1][j - 1] &&
				board[i][j] == board[i + 2][j - 2] &&
				board[i][j] == board[i + 3][j - 3] &&
				board[i][j] == board[i + 4][j - 4]) {
				return board[i][j]; // 승리한 플레이어 반환
			}
		}
	}
	return 0;
}

void printboardrecord(Omokboard* record) {
	int x = StartpointX;
	int y = StartpointY;
	int rx = 0, ry = 0;
	printOmokboard(x, y);
	while (ry < MAX_Y) {
		while (record->board[ry][rx] == 0 && rx < MAX_X) {
			rx += 1;
		}
		if (rx >= MAX_X) {
			rx = 0;
			ry += 1;
			continue;
		}
		gotoxy(x + (rx * 2), y + ry);
		if (record->board[ry][rx] == BLACK)
			DRAW_BLACK;
		else if (record->board[ry][rx] == WHITE)
			DRAW_WHITE;
	}
}

void playUI(int select) {

	Omokboard* play;
	int X, Y, cursor, check, finish; //gotoxy와 관련된 변수
	int player = WHITE; //현재 돌을 놓는 플레이어 기록 변수

	play = (Omokboard*)malloc(sizeof(Omokboard));	//오목판 기록 메모리 할당
	for (int i = 0; i < MAX_Y; i++)			//오목판 기록 초기화
	{
		for (int j = 0; j < MAX_X; j++)
			play->board[i][j] = 0;
	}

	printOmokboard(StartpointX, StartpointY);			//오목판 UI불러오기
	incursor(0);
	X = StartpointX;
	Y = StartpointY;
	gotoxy(X, Y);
	if (player == BLACK)
		DRAW_BLACK;
	else if (player == WHITE)
		DRAW_WHITE;

	while (1) {
		gotoxy(0, 0);
		/*for (int i = 0; i < MAX_Y; i++)
		{
			for (int j = 0; j < MAX_X; j++)
				printf("%d ", play->board[i][j]);
			printf("\n");
		}  */
		cursor = _getch();

		switch (cursor) {
		case RIGHT:
			check = checkcanstone(play, X, Y, RIGHT);
			if (check == -1)
				break;
			gotoxy(X, Y);
			printf("  ");
			gotoxy(X, Y);
			if (Y == StartpointY) {
				if (X == StartpointX) {
					printf("┌");
				}
				else
					printf("┬");
			}
			else if (Y == EndpointY) {
				if (X == StartpointX) {
					printf("└");
				}
				else
					printf("┴");
			}
			else {
				if (X == StartpointX)
					printf("├");
				else
					printf("┼");
			}
			X = check;
			gotoxy(X, Y);
			if (player == BLACK)
				DRAW_BLACK;
			else if (player == WHITE)
				DRAW_WHITE;
			break;

		case LEFT: 
			check = checkcanstone(play, X, Y, LEFT);
			if (check == -1)
				break;
			gotoxy(X, Y);
			printf("  ");
			gotoxy(X, Y);
			if (Y == StartpointY) {
				if (X == EndpointX) {
					printf("┐");
				}
				else
					printf("┬");
			}
			else if (Y == EndpointY) {
				if (X == EndpointX) {
					printf("┘");
				}
				else
					printf("┴");
			}
			else {
				if (X == EndpointX)
					printf("┤");
				else
					printf("┼");
			}
			X = check;
			gotoxy(X, Y);
			if (player == BLACK)
				DRAW_BLACK;
			else if (player == WHITE)
				DRAW_WHITE;
			break;

		case DOWN: 
			check = checkcanstone(play, X, Y, DOWN);
			if (check == -1)
				break;
			gotoxy(X, Y);
			printf("  ");
			gotoxy(X, Y);
			if (X == StartpointX) {
				if (Y == StartpointY) {
					printf("┌");
				}
				else
					printf("├");
			}
			else if (X == EndpointX) {
				if (Y == StartpointY) {
					printf("┐");
				}
				else
					printf("┤");
			}
			else {
				if (Y == StartpointY)
					printf("┬");
				else
					printf("┼");
			}
			Y = check;
			gotoxy(X, Y);
			if (player == BLACK)
				DRAW_BLACK;
			else if (player == WHITE)
				DRAW_WHITE;
			break;

		case UP: 
			check = checkcanstone(play, X, Y, UP);
			if (check == -1)
				break;
			gotoxy(X, Y);
			printf("  ");
			gotoxy(X, Y);
			if (X == StartpointX) {
				if (Y == EndpointY)	//왼쪽 아래 모서리
					printf("└");
				else
					printf("├");	//왼쪽 끝
			}
			else if (X == EndpointX) {
				if (Y == EndpointY)	//오른쪽 아래 모서리
					printf("┘");
				else
					printf("┤");	//오른쪽 끝
			}
			else {
				if (Y == EndpointY)
					printf("┴");
				else
					printf("┼");
			}
			Y = check;
			gotoxy(X, Y);
			if (player == BLACK)
				DRAW_BLACK;
			else if (player == WHITE)
				DRAW_WHITE;
			break;

		case ENTER:
			putstone(play, X, Y, player);
			if (player == WHITE)
				player = BLACK;
			else if (player == BLACK)
				player = WHITE;
			finish = checkGameStatus(play -> board);
			if (finish == BLACK)
			{
				gotoxy(0, 0);
				printf("BLACK");
				return;
			}
			else if (finish == WHITE)
			{
				gotoxy(0, 0);
				printf("WHITE");
				return;
			}
			//AI모드 추가
			if (select == 1)
			{
				turn(play -> board, 4, 0, 0, X, Y);
				gotoxy((aix * 2) + StartpointX, aiy + StartpointY);
				DRAW_BLACK;
				putstone(play, aix, aiy, BLACK);
				finish = checkGameStatus(play->board);
				if (finish == BLACK)
				{
					gotoxy(0, 0);
					printf("BLACK");
					return;
				}
				else if (finish == WHITE)
				{
					gotoxy(0, 0);
					printf("WHITE");
					return;
				}
				if (player == WHITE)
					player = BLACK;
				else if (player == BLACK)
					player = WHITE;
			}
			X = StartpointX;
			Y = StartpointY;
			checkstartstone(play, &X, &Y);
			gotoxy(X, Y);
			if (player == BLACK)
				DRAW_BLACK;
			else if (player == WHITE)
				DRAW_WHITE;
			break;
		}
		gotoxy(80, 38);
		printf("%2d %2d", X, Y); 
		continue;
	}
}

void checkstartstone(Omokboard* play, int* x, int* y) {
	while (1) {
		gotoxy(0, 20);
		if (play->board[*y - StartpointY][(*x - StartpointX) / 2] != 0) {
			if (*x < EndpointX)
				*x += 2;
			else if (*y < EndpointY) {
				*y += 1;
				*x = StartpointX;
			}
		}
		else
			break;
	}
}

int checkcanstone(Omokboard* play, int x, int y, int direction)	//지정한 방향에서 놓을 수 있는 최초의 위치까지의 거리 반환 (-1반환시 제자리 정지)
{
	int res = 0, tmp, rx, ry, i = -99;
	/*if ((direction == RIGHT && x >= EndpointX) || (direction == LEFT && x <= StartpointX) || (direction == DOWN && y >= EndpointY) || (direction == UP && y <= StartpointY)) {
		return -1;
	} */

	rx = (x - StartpointX) / 2;
	ry = y - StartpointY;

	if (direction == LEFT || direction == UP)
		tmp = -1;
	else
		tmp = 1;

	if (direction == LEFT || direction == RIGHT) {
		for (i = rx + tmp; i >= 0 && i < MAX_X; i += tmp)
		{
			if (play->board[ry][i] == 0) {
				break;
			}
		}
		res = i;
		if (res == MAX_X || res == -1)
			return -1;
		else
			return (res * 2) + StartpointX;
	}

	else {
		for (i = ry + tmp; i >= 0 && i < MAX_Y; i += tmp) {
			if (play->board[i][rx] == 0) {
				break;
			}
		}
		res = i;
		if (res == MAX_Y || res == -1)
			return -1;
		else
			return res + StartpointY;
	}
}

void putstone(Omokboard *play, int x, int y, int player) {			//돌 놓은 위치 기록
	play->board[y - StartpointY][(x - StartpointX) / 2] = player;
}

//┌│┐─└ ┘┬ ┴ ┼├ ┤
void printOmokboard(int x, int y) {
	int X = x;
	int Y = y;
	system("mode con cols=92 lines=40");
	system("cls");
	gotoxy(X, Y);
	printf("┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐");	//15x15 변경시 수정
	for (int i = 0; i < MAX_Y-2; i++) {
		Y += 1;
		gotoxy(X, Y);
		printf("├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤");
	}
	Y += 1;
	gotoxy(X, Y);
	printf("└─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘");	//15x15 변경시 수정
}

void RankEasyHardprintscreen() {
	system("mode con cols=92 lines=40");
	system("cls");
	gotoxy(20, 15);
	printf("EASY");
	gotoxy(72, 15);
	printf("HARD");
	gotoxy(46, 25);
	printf("뒤로가기");
}

void selectAIuserscreen(void) {
	system("mode con cols=92 lines=40");
	system("cls");
	gotoxy(20, 15);
	printf("User");
	gotoxy(72, 15);
	printf("AI");
	gotoxy(46, 25);
	printf("뒤로가기");
}

void selectAIuser(void) {
	system("cls");
	int X = 18, Y = 15;
	int test, select;
	selectAIuserscreen();
	gotoxy(X, Y);
	printf(">");
	while (1) {
		test = _getch();
		switch (test) {
		case LEFT: gotoxy(X, Y);
			printf(" ");
			X = 18;
			Y = 15;
			gotoxy(X, Y);
			printf(">");
			break;
		case RIGHT: gotoxy(X, Y);
			printf(" ");
			X = 70;
			Y = 15;
			gotoxy(X, Y);
			printf(">");
			break;
		case DOWN: gotoxy(X, Y);
			printf(" ");
			X = 44;
			Y = 25;
			gotoxy(X, Y);
			printf(">");
			break;
		case ENTER: gotoxy(X, Y);
			if (X == 18) {
				select = 0;	//유저대전 선택
				playUI(select);
				return;
			}
			else if (X == 70) {
				select = 1;	//AI대전 선택
				playUI(select);
				return;
			}
			else if (X == 44) {
				return;
			}
		case ESC:
			return;
		}
		gotoxy(80, 38);
		printf("%2d %2d", X, Y); continue;
	}
	system("pause>nul");
	fflush(stdin);
}

void RankEasyHardUI(void)
{
	system("cls");
	int X = 18, Y = 15;
	int test, select;
	RankEasyHardprintscreen();
	gotoxy(X, Y);
	printf(">");
	while (1) {
		test = _getch();
		switch (test) {
		case LEFT: gotoxy(X, Y);
			printf(" ");
			X = 18;
			Y = 15;
			gotoxy(X, Y);
			printf(">");
			break;
		case RIGHT: gotoxy(X, Y);
			printf(" ");
			X = 70;
			Y = 15;
			gotoxy(X, Y);
			printf(">");
			break;
		case DOWN: gotoxy(X, Y);
			printf(" ");
			X = 44;
			Y = 25;
			gotoxy(X, Y);
			printf(">");
			break;
		case ENTER: gotoxy(X, Y);
			if (X == 18) {
				select = 0;
				RankUI();
				RankEasyHardprintscreen();
				gotoxy(X, Y);
				printf(">");
				break;
			}
			else if (X == 70) {
				select = 1;
				RankUI();
				system("cls");
				RankEasyHardprintscreen();
				gotoxy(X, Y);
				printf(">");
				break;
			}
			else if (X == 44) {
				return;
			}
		case ESC:
			return;
		}
		gotoxy(80, 38);
		printf("%2d %2d", X, Y); continue;
	}
	system("pause>nul");
	fflush(stdin);
}

void Rankprintscreen(void) {
	system("mode con cols=92 lines=40");
	system("cls");
	gotoxy(20, 10);
	printf("랭킹 1등 ");
	gotoxy(20, 15);
	printf("랭킹 2등 ");
	gotoxy(20, 20);
	printf("랭킹 3등 ");
	gotoxy(20, 25);
	printf("뒤로가기 ");
}

void RankUI(void)
{
	int X = 16, Y = 10;
	int test;
	Rankprintscreen();
	gotoxy(X, Y);
	printf(">");
	while (1) {
		test = _getch();

		switch (test) {
		case UP: gotoxy(X, Y);
			if (Y <= 10) {
				break;
			}
			else {
				printf(" ");
				Y -= 5;
				gotoxy(X, Y);
				printf(">");
				break;
			}
		case DOWN: gotoxy(X, Y);
			if (Y >= 25) {
				break;
			}
			else {
				printf(" ");
				Y += 5;
				gotoxy(X, Y);
				printf(">");
				break;
			}
		case ENTER:
			if (Y == 10) {
				//1등 상세정보 출력
				Rankprintscreen();
				break;
			}
			else if (Y == 15) {
				//2등 상세정보 출력
				Rankprintscreen();
				break;
			}
			else if (Y == 20) {
				//3등 상세정보 출력
				Rankprintscreen();
				break;
			}
			else if (Y == 25) {
				//뒤로가기 입력
				return;
			}
		case ESC:
			return;
		}
		gotoxy(80, 38);
		printf("%2d %2d", X, Y); continue;
	}
	system("pause>nul");
	fflush(stdin);
}

const int dx[8] = { 0, 0, 1, 1, 1, -1, -1, -1 };
const int dy[8] = { 1, -1, 0, 1, -1, 0, 1, -1 };

bool isindexoutofboundsexception(int x, int y) {
	if (x < 0 || x > MAX_X || y < 0 || y > MAX_Y)
		return true;
	else
		return false;
}

bool bbbwPattern(int board[MAX_Y][MAX_X], int evex, int evey) {
	int dx[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

	int stone = board[evey][evex];

	// 8방향검사
	for (int direction = 0; direction < 8; ++direction) {
		int count = 1;  // 흑돌 카운트

		// 한 방향으로 계속 진행하며 동일한 돌이 연속되는지 검사
		for (int i = 1; i <= 2; ++i) {
			int nx = evex + dx[direction] * i;
			int ny = evey + dy[direction] * i;

			// 배열 범위를 벗어나거나, 검사하는 돌과 다른 돌이라면 중단
			if (nx < 0 || nx >= MAX_X || ny < 0 || ny >= MAX_Y || board[ny][nx] != stone)
				break;
			count++;
		}

		// count가 3이고(흑독3개) 다른한쪽이 흰돌이면 트루
		if (count == 3 && (board[evey - dy[direction]][evex - dx[direction]] != stone))
			return true;
	}
	return false;
}

bool bbPattern(int board[MAX_Y][MAX_X], int evex, int evey) {
	int dx[] = { 1, 1, 0, -1, 1, -1, 0, -1 };  // 가로, 세로, 대각선 검사
	int dy[] = { 0, 1, 1, 1, -1, -1, -1, 0 };

	int stone = BLACK;  // 흑돌
	for (int d = 0; d < 8; ++d) {
		int count = 0;
		for (int i = 1; i <= 2; ++i) {
			int nx = evex + dx[d] * i;
			int ny = evey + dy[d] * i;
			if (nx < 0 || nx >= MAX_X || ny < 0 || ny >= MAX_Y)
				break;
			if (board[ny][nx] == stone) {
				if (i == 2 && (ny == evex || nx == evey))
					break;  // 직전 돌의 위치인 경우 패턴 미완성
				++count;
			}
			else {
				break;
			}
		}
		if (count == 2)
			return true;
	}
	return false;
}

bool bbbPattern(int board[MAX_Y][MAX_X], int evex, int evey) {
	int dx[] = { 1, 1, 0, -1 };  // 가로, 세로, 대각선 방향 검사
	int dy[] = { 0, 1, 1, 1 };

	int stone = BLACK;  // 흑돌
	for (int d = 0; d < 4; ++d) {
		int count = 0;
		for (int i = -3; i <= 3; ++i) {
			int nx = evex + dx[d] * i;
			int ny = evey + dy[d] * i;
			if (nx < 0 || nx >= MAX_X || ny < 0 || ny >= MAX_Y)
				continue;
			if (board[ny][nx] == stone) {
				++count;
				if (count == 3)
					return true;
			}
			else {
				count = 0;
			}
		}
	}
	return false;
}

bool bbbbPattern(int board[MAX_Y][MAX_X], int evex, int evey) {
	int dx[] = { 1, 1, 0, -1 };  // 가로, 세로, 대각선 방향 검사
	int dy[] = { 0, 1, 1, 1 };

	int stone = BLACK;  // 흑돌
	for (int d = 0; d < 4; ++d) {
		int count = 0;
		for (int i = -4; i <= 4; ++i) {
			int nx = evex + dx[d] * i;
			int ny = evey + dy[d] * i;
			if (nx < 0 || nx >= MAX_X || ny < 0 || ny >= MAX_Y)
				continue;
			if (board[ny][nx] == stone) {
				++count;
				if (count == 4)
					return true;
			}
			else {
				count = 0;
			}
		}
	}
	return false;
}

bool bbbbbPattern(int board[MAX_Y][MAX_X], int evex, int evey) {
	int dx[] = { 1, 1, 0, -1 };  // 가로, 세로, 대각선 방향 검사
	int dy[] = { 0, 1, 1, 1 };

	int stone = BLACK;  // 흑돌
	for (int d = 0; d < 4; ++d) {
		int count = 0;
		for (int i = -5; i <= 5; ++i) {
			int nx = evex + dx[d] * i;
			int ny = evey + dy[d] * i;
			if (nx < 0 || nx >= MAX_X || ny < 0 || ny >= MAX_Y)
				continue;
			if (board[ny][nx] == stone) {
				++count;
				if (count == 5)
					return true;
			}
			else {
				count = 0;
			}
		}
	}
	return false;
}

int getWeight(int board[MAX_Y][MAX_X], int x, int y) {
	int w = 0;
	if (bbbwPattern(board, x, y)) {
		w = 10;
	}

	if (bbbwPattern(board, x, y)) {
		w = 20;
	}
	if (bbbbPattern(board, x, y)) {
		w = 30;
	}

	if (bbbbbPattern(board, x, y)) {
		w = 300;
	}
	return w;
}

// 알파가 큰거 베타가 작은거
int turn(int board[MAX_Y][MAX_X], int depth, int* a, int* b, int evex, int evey) {

	if (depth == 3)
		return getWeight(board, evex, evey);

	if (depth % 2 == 0) {  // ai turn
		int w = INT_MAX;
		for (int y = 0; y < MAX_Y; y++)  // for each child of node
		{
			for (int x = 0; x < MAX_X; x++) {
				int curStone = board[y][x];
				bool flag = false;

				if (curStone == EMPTY) {
					int deltax = 0, deltay = 0;
					for (int k = 0; k < 8; k++) {
						deltax = x + dx[k];
						deltay = y + dy[k];
						if (!isindexoutofboundsexception(deltax, deltay)) continue;
						if (board[deltay][deltax] != EMPTY) {
							flag = true;
							break;
						}
					}
					if (flag) {
						board[y][x] = BLACK;
						int w = turn(board, depth + 1, a, b, x, y);
						if (*a < w) {
							*a = w;
							if (depth == 0) {
								aix = x;
								aiy = y;
							}
						}
					}
				}
			}
		}
	}
	else {                              // player turn
		int w = INT_MIN;
		for (int y = 0; y < MAX_Y; y++)  // for each child of node
		{
			for (int x = 0; x < MAX_X; x++) {
				int curStone = board[y][x];
				bool flag = false;
				return getWeight(board, evex, evey);

				if (curStone == EMPTY) {
					int deltax = 0, deltay = 0;
					for (int k = 0; k < 8; k++) {
						deltax = x + dx[k];
						deltay = y + dy[k];
						if (!isindexoutofboundsexception(deltax, deltay)) continue;
						if (board[deltay][deltax] != EMPTY) {
							flag = true;
							break;
						}
					}

					if (flag) {
						board[y][x] = BLACK;
						w = min(w, turn(board, depth + 1, a, b, x, y));
						board[y][x] = EMPTY;
					}
				}
			}
		}
	}
}