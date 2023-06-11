
#include "omok.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

//gotoxy
void gotoxy(int x, int y);
void textcolor(int color_number);
void incursor(int n);

Omokboard* playUI(int select);
void RankUI(void);	//랭킹창 UI
void RankEasyHardUI(void);	//랭킹 난이도 선택
void selectAIuser(void); //AI대전 user대전 선택
void record(void); //기록

void printOmokboard(int x, int y);
void titlescreen(void);
void RankEasyHardprintscreen(void);
void Rankprintscreen(void);
void selectAIuserscreen(void);
void recordscreen(void);
void printboardrecord(Omokboard* record);

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

extern int aix, aiy; //ai 변수


Omokboard* playUI(int select) {

	Omokboard* play;
	int X, Y, cursor, check, finish, a, b; //gotoxy와 관련된 변수
	int player = WHITE; //현재 돌을 놓는 플레이어 기록 변수
	a = 0;
	b = 0;

	play = (Omokboard*)malloc(sizeof(Omokboard));	//오목판 기록 메모리 할당
	for (int i = 0; i < MAX_Y; i++)			//오목판 기록 초기화
	{
		for (int j = 0; j < MAX_X; j++)
			play->board[i][j] = 0;
	}

	printOmokboard(StartpointX, StartpointY);			//오목판 UI불러오기
	X = StartpointX;
	Y = StartpointY;
	gotoxy(X, Y);
	if (player == BLACK)
		DRAW_BLACK;
	else if (player == WHITE)
		DRAW_WHITE;

	while (1) {
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
			gotoxy(0, 5);
			for (int i = 0; i < MAX_Y; i++)
			{
				for (int j = 0; j < MAX_X; j++)
					printf("%d ", play->board[i][j]);
				printf("\n");
			}
			if (player == WHITE)
				player = BLACK;
			else if (player == BLACK)
				player = WHITE;
			finish = checkGameStatus(play->board);
			if (finish == BLACK)
			{
				gotoxy(0, 0);
				printf("BLACK");
				return play;
			}
			else if (finish == WHITE)
			{
				gotoxy(0, 0);
				printf("WHITE");
				return play;
			}

			//AI모드 추가
			if (select == 1)
			{
				gotoxy(0, 20);
				turn(play->board, 0, &a, &b, (X - StartpointX) / 2, Y - StartpointY);

				gotoxy((aix * 2) + StartpointX, aiy + StartpointY);
				DRAW_BLACK;

				putstone(play, aix, aiy, BLACK);
				gotoxy(0, 5);
				for (int i = 0; i < MAX_Y; i++)
				{
					for (int j = 0; j < MAX_X; j++)
						printf("%d ", play->board[i][j]);
					printf("\n");
				}
				finish = checkGameStatus(play->board);
				if (finish == BLACK)
				{
					gotoxy(0, 0);
					printf("BLACK");
					return play;
				}
				else if (finish == WHITE)
				{
					gotoxy(0, 0);
					printf("WHITE");
					return play;
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

//┌│┐─└ ┘┬ ┴ ┼├ ┤
void printOmokboard(int x, int y) {
	int X = x;
	int Y = y;
	system("mode con cols=92 lines=40");
	system("cls");
	gotoxy(X, Y);
	printf("┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐");
	for (int i = 0; i < MAX_Y - 2; i++) {
		Y += 1;
		gotoxy(X, Y);
		printf("├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤");
	}
	Y += 1;
	gotoxy(X, Y);
	printf("└─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘");
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

void titlescreen(void) {
	system("mode con cols=92 lines=40");
	system("cls");
	incursor(0);
	gotoxy(0, 0);
	printf("\n\n\n\n");
	printf("		       ●●●●●                 ●●●●●●●   \n");
	printf("		     ●          ●               ●          ●   \n");
	printf("		    ●            ●              ●          ●   \n");
	printf("		     ●          ●               ●●●●●●●   \n");
	printf("		       ●●●●●                       ●         \n");
	printf("		                               ●●●●●●●●●●\n");
	printf("		           ●                                      \n");
	printf("		           ●                    ●●●●●●●●  \n");
	printf("		  ●●●●●●●●●●                         ●  \n");
	printf("                                                               ●\n");


	gotoxy(36, 18);
	printf("1. 대전 선택");
	gotoxy(36, 20);
	printf("2.   기록");
	gotoxy(36, 22);
	printf("3.   랭킹\n");
}

void title()
{
	int test;
	int X = 34, Y = 18;
	titlescreen();
	gotoxy(X, Y);
	printf(">");

	while (1) {
		test = _getch();
		switch (test) {
		case UP: gotoxy(X, Y);
			if (Y <= 18)
				break;
			printf(" ");
			Y -= 2;
			gotoxy(X, Y);
			printf(">");
			break;
		case DOWN: gotoxy(X, Y);
			if (Y >= 22)
				break;
			printf(" ");
			Y += 2;
			gotoxy(X, Y);
			printf(">");
			break;
		case ENTER: gotoxy(X, Y);
			if (Y == 18) {
				selectAIuser();
				titlescreen();
				gotoxy(X, Y);
				printf(">");
				break;
			}
			else if (Y == 20) {
				record();
				titlescreen();
				gotoxy(X, Y);
				printf(">");
				break;
			}
			else if (Y == 22) {
				break;
			}
		case ESC:
			return;
		}
	}
}

void recordscreen(void) {
	int y = 15;
	system("cls");

	gotoxy(0, 0);
	printf("\n\n");
	printf("          ●●●●    ●●●●     ●●●       ●●●     ●●●●    ●●●  \n");
	printf("          ●     ●   ●          ●     ●    ●    ●    ●     ●   ●    ●\n");
	printf("          ●●●●    ●●●●   ●           ●      ●   ●●●●    ●    ●\n");
	printf("          ●  ●      ●          ●     ●    ●    ●    ●  ●      ●    ●\n");
	printf("          ●    ●    ●●●●     ●●●       ●●●     ●    ●    ●●●  \n");

	gotoxy(10, y);
	for (int i = 0; i < 5; i++)
	{
		printf("%d. 경기 이름: 		경기 결과: 		경기 시간:  \n", i + 1);
		y += 2;
		gotoxy(10, y);
	}
	gotoxy(10, 25);
	printf("뒤로가기\n");
}

void record()
{
	Rank arr[5] = { 0 };
	int test;
	int X = 8, Y = 15;
	recordscreen();

	gotoxy(X, Y);
	printf(">");

	while (1) {
		test = _getch();
		switch (test) {
		case UP: gotoxy(X, Y);
			if (Y <= 15)
				break;
			printf(" ");
			Y -= 2;
			gotoxy(X, Y);
			printf(">");
			break;
		case DOWN: gotoxy(X, Y);
			if (Y >= 25)
				break;
			printf(" ");
			Y += 2;
			gotoxy(X, Y);
			printf(">");
			break;
		case ENTER: gotoxy(X, Y);
			if (Y == 25)
				return;

		case ESC:
			return;
		}
	}
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