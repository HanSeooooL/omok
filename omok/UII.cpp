#include "omok.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <time.h>

//gotoxy

void gotoxy(int x, int y)	//gotoxy
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void textcolor(int color_number)	//���� ��
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

void errors(char* msg) {
	gotoxy(0, 0);
	printf("Error: %s", msg);
	exit(1);
}

void playUI(int select);	//���� �÷���ȭ��
void finishedgameUI(Omokboard result); //����� ���� ���
void RankUI(void);	//��ŷâ UI
//void RankEasyHardUI(void);	��ŷ ���̵� ����
void selectAIuser(void); //AI���� user���� ����
void record(void); //����ڴ��� ���

void gameoverAIUI(void);	//AI���ӿ���
void finishedgameAIUI(Omokboard gameresult, double duration);	//AIŬ����� ��ŷ���

void printOmokboard(int x, int y);	//���񺸵� ����Ʈ
void titlescreen(void);				//Ÿ��Ʋȭ�� ����Ʈ
//void RankEasyHardprintscreen(void);	//�����ϵ� ����
void Rankprintscreen(Rank* arr, int n);	//��ŷ ����ȭ�� ����Ʈ
void selectAIuserscreen(void);	//����ڴ��� AI���� ����ȭ�� ����Ʈ
void finishedgamescreen(int who);	//����ڴ��� ���� ������ �� ȭ�� ����Ʈ
void recordscreen(int n, Record gameRecords[], int numRecords);	//����ڴ��� ��� ȭ�� ����Ʈ
void printboardrecord(Omokboard* record);	//��ϵǾ��ִ� ������ ����Ʈ

const int dx[8] = { 0, 0, 1, 1, 1, -1, -1, -1 };
const int dy[8] = { 1, -1, 0, 1, -1, 0, 1, -1 };

int aix = 0, aiy = 0; //ai ����

void finishedgamescreen(int who)
{
	system("cls");

	if (who == BLACK) {
		gotoxy(40, 15);
		printf("�� �� ��!");
	}
	else if (who == WHITE) {
		gotoxy(40, 15);
		printf("�� �� ��!");
	}
}

void finishedgameUI(Omokboard gameresult) {
	int test;
	int i = 0;
	Record res;
	res.result = gameresult;
	finishedgamescreen(checkGameStatus(gameresult.board));
	gotoxy(40, 30);
	printf("Player 1: ");
	scanf("%s", res.name1);
	finishedgamescreen(checkGameStatus(gameresult.board));
	gotoxy(40, 30);
	fflush(stdin);
	printf("Player 2: ");
	res.who = checkGameStatus(gameresult.board);
	scanf("%s", res.name2);
	
	saveResultToFile(&res, 1);
}
void gameoverAIUI() {
	system("cls");
	gotoxy(40, 15);
	printf("Game Over");


	_getch();
}

void finishedgameAIUI(Omokboard gameresult, double duration) {
	Rank res;
	res.time = duration;
	res.result = gameresult;
	system("cls");
	gotoxy(40, 15);
	printf("��     ��!");
	gotoxy(40, 30);
	printf("Player  : ");
	scanf("%s", res.name);

	RankfileSave(res);
}


void playUI(int select) {

	Omokboard* play;
	int X, Y, cursor, check, finish, a, b; //gotoxy�� ���õ� ����
	int player = WHITE; //���� ���� ���� �÷��̾� ��� ����
	clock_t starttime, finishtime;
	double duration;
	a = 0;
	b = 0;

	play = (Omokboard*)malloc(sizeof(Omokboard));	//������ ��� �޸� �Ҵ�
	for (int i = 0; i < MAX_Y; i++)			//������ ��� �ʱ�ȭ
	{
		for (int j = 0; j < MAX_X; j++)
			play->board[i][j] = 0;
	}

	printOmokboard(StartpointX, StartpointY);			//������ UI�ҷ�����
	X = StartpointX;
	Y = StartpointY;
	if (select == 1)
	{
		starttime = clock();
		putstone(play, (7 * 2) + StartpointX, 7 + StartpointY, BLACK);
		gotoxy((7 * 2) + StartpointX, 7 + StartpointY);
		DRAW_BLACK;
	}
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
			printf(" ");
			gotoxy(X, Y);
			if (Y == StartpointY) {
				if (X == StartpointX) {
					printf("��");
				}
				else
					printf("��");
			}
			else if (Y == EndpointY) {
				if (X == StartpointX) {
					printf("��");
				}
				else
					printf("��");
			}
			else {
				if (X == StartpointX)
					printf("��");
				else
					printf("��");
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
			printf(" ");
			gotoxy(X, Y);
			if (Y == StartpointY) {
				if (X == EndpointX) {
					printf("��");
				}
				else
					printf("��");
			}
			else if (Y == EndpointY) {
				if (X == EndpointX) {
					printf("��");
				}
				else
					printf("��");
			}
			else {
				if (X == EndpointX)
					printf("��");
				else
					printf("��");
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
			printf(" ");
			gotoxy(X, Y);
			if (X == StartpointX) {
				if (Y == StartpointY) {
					printf("��");
				}
				else
					printf("��");
			}
			else if (X == EndpointX) {
				if (Y == StartpointY) {
					printf("��");
				}
				else
					printf("��");
			}
			else {
				if (Y == StartpointY)
					printf("��");
				else
					printf("��");
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
			printf(" ");
			gotoxy(X, Y);
			if (X == StartpointX) {
				if (Y == EndpointY)	//���� �Ʒ� �𼭸�
					printf("��");
				else
					printf("��");	//���� ��
			}
			else if (X == EndpointX) {
				if (Y == EndpointY)	//������ �Ʒ� �𼭸�
					printf("��");
				else
					printf("��");	//������ ��
			}
			else {
				if (Y == EndpointY)
					printf("��");
				else
					printf("��");
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
			finish = checkGameStatus(play->board);
			if (select == 0) {
				if (finish == WHITE)
				{
					gotoxy(0, 0);
					finishedgameUI(*play);
					return;
				}
				if (finish == BLACK)
				{
					gotoxy(0, 0);
					finishedgameUI(*play);
					return;
				}
			}

			//AI��� �߰�
			if (select == 1)
			{
				if (finish == WHITE)
				{
					gotoxy(0, 0);
					finishtime = clock();
					duration = (double)(finishtime - starttime) / CLOCKS_PER_SEC;
					finishedgameAIUI(*play, duration);
					return;
				}
				gotoxy(0, 20);
				turn(play->board, 0, (X - StartpointX) / 2, Y - StartpointY);
				//minimax(play->board, 4, 1, (X - StartpointX) / 2, Y - StartpointY);
				//printf("aix : %d aiy : %d", aix, aiy);
				gotoxy((aix * 2) + StartpointX, aiy + StartpointY);
				DRAW_BLACK;
				putstone(play, (aix * 2) + StartpointX, aiy + StartpointY, BLACK);
				finish = checkGameStatus(play->board);
				if (finish == BLACK)
				{
					gotoxy(0, 0);
					printf("BLACK");
					gameoverAIUI();
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

		case ESC:
			return;
		}
		//gotoxy(80, 38);
		//printf("%2d %2d", X, Y);
		//continue;
	}
}

/*
void playAIUI() {
	Omokboard* play;
	int X, Y, cursor, check, finish, a, b; //gotoxy�� ���õ� ����
	int player = WHITE; //���� ���� ���� �÷��̾� ��� ����
	a = 0;
	b = 0;

	play = (Omokboard*)malloc(sizeof(Omokboard));	//������ ��� �޸� �Ҵ�
	for (int i = 0; i < MAX_Y; i++)			//������ ��� �ʱ�ȭ
	{
		for (int j = 0; j < MAX_X; j++)
			play->board[i][j] = 0;
	}

	printOmokboard(StartpointX, StartpointY);			//������ UI�ҷ�����
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
					printf("��");
				}
				else
					printf("��");
			}
			else if (Y == EndpointY) {
				if (X == StartpointX) {
					printf("��");
				}
				else
					printf("��");
			}
			else {
				if (X == StartpointX)
					printf("��");
				else
					printf("��");
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
					printf("��");
				}
				else
					printf("��");
			}
			else if (Y == EndpointY) {
				if (X == EndpointX) {
					printf("��");
				}
				else
					printf("��");
			}
			else {
				if (X == EndpointX)
					printf("��");
				else
					printf("��");
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
					printf("��");
				}
				else
					printf("��");
			}
			else if (X == EndpointX) {
				if (Y == StartpointY) {
					printf("��");
				}
				else
					printf("��");
			}
			else {
				if (Y == StartpointY)
					printf("��");
				else
					printf("��");
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
				if (Y == EndpointY)	//���� �Ʒ� �𼭸�
					printf("��");
				else
					printf("��");	//���� ��
			}
			else if (X == EndpointX) {
				if (Y == EndpointY)	//������ �Ʒ� �𼭸�
					printf("��");
				else
					printf("��");	//������ ��
			}
			else {
				if (Y == EndpointY)
					printf("��");
				else
					printf("��");
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
			finish = checkGameStatus(play->board);
			if (finish == BLACK)
			{
				gotoxy(0, 0);
				printf("BLACK");
				finishedgameUI(*play);
				exit(1);
			}
			else if (finish == WHITE)
			{
				gotoxy(0, 0);
				printf("WHITE");
				finishedgameUI(*play);
				exit(1);
			}

			gotoxy(0, 20);
			turn(play->board, 0, (X - StartpointX) / 2, Y - StartpointY);
			//minimax(play->board, 4, 1, (X - StartpointX) / 2, Y - StartpointY);
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
				gameoverAIUI();
				fflush(stdin);
				return;
			}
			else if (finish == WHITE)
			{
				gotoxy(0, 0);
				printf("WHITE");
				finishedgameUI(*play);
					return;
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
*/
//���������� ���� �� ���� ��
void printOmokboard(int x, int y) {
	int X = x;
	int Y = y;
	system("mode con cols=92 lines=40");
	system("cls");
	gotoxy(X, Y);
	printf("����������������������������������������������������������");
	for (int i = 0; i < MAX_Y - 2; i++) {
		Y += 1;
		gotoxy(X, Y);
		printf("����������������������������������������������������������");
	}
	Y += 1;
	gotoxy(X, Y);
	printf("����������������������������������������������������������");
}

/*
void RankEasyHardprintscreen() {
	system("mode con cols=92 lines=40");
	system("cls");
	gotoxy(20, 15);
	printf("EASY");
	gotoxy(72, 15);
	printf("HARD");
	gotoxy(46, 25);
	printf("�ڷΰ���");
}
*/

void selectAIuserscreen(void) {
	system("mode con cols=92 lines=40");
	system("cls");
	gotoxy(31, 15);
	printf("User");
	gotoxy(62, 15);
	printf("AI");
	gotoxy(46, 25);
	printf("�ڷΰ���");
}

void selectAIuser(void) {
	system("cls");
	int X = 29, Y = 15;
	int test, select;
	selectAIuserscreen();
	gotoxy(X, Y);
	printf(">");
	while (1) {
		test = _getch();
		switch (test) {
		case LEFT: gotoxy(X, Y);
			printf(" ");
			X = 29;
			Y = 15;
			gotoxy(X, Y);
			printf(">");
			break;
		case RIGHT: gotoxy(X, Y);
			printf(" ");
			X = 60;
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
			if (X == 29) {
				select = 0;	//�������� ����
				playUI(select);
				return;
			}
			else if (X == 60) {
				select = 1;	//AI���� ����
				playUI(select);
				return;
			}
			else if (X == 44) {
				return;
			}
		case ESC:
			return;
		}
		//gotoxy(80, 38);
		//printf("%2d %2d", X, Y); continue;
	}
	system("pause>nul");
	fflush(stdin);
}
/*
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
		//gotoxy(80, 38);
		//printf("%2d %2d", X, Y); continue;
	}
	system("pause>nul");
	fflush(stdin);
}
*/

void Rankprintscreen(Rank *arr, int n) {
	int i;
	system("mode con cols=92 lines=40");
	system("cls");
	for (i = 0; i < 3 && i < n; i++) {
		gotoxy(20, 10 + (i * 5));
		printf("��ŷ %d�� : %s %lf��", i + 1, (arr + i)->name, (arr + i)->time);
	}

	gotoxy(20, 25);
	printf("�ڷΰ��� ");
}

void RankUI(void)
{
	int X = 16, Y = 10, n = 0;
	int test;
	Rank arr[3], *besor = NULL;
	besor = RankfileLead(besor, &n);

	qsort(besor, n, sizeof(Rank), compare);
	for (int i = 0; i < 3; i++) {
		arr[i] = besor[i];
	}
	Rankprintscreen(arr, n);
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
				//1�� ������ ���
				printboardrecord(&(besor[0].result));
				Rankprintscreen(arr, n);
				gotoxy(X, Y);
				printf(">");
				break;
			}
			else if (Y == 15) {
				//2�� ������ ���
				printboardrecord(&(besor[1].result));
				Rankprintscreen(arr, n);
				gotoxy(X, Y);
				printf(">");
				break;
			}
			else if (Y == 20) {
				//3�� ������ ���
				printboardrecord(&(besor[2].result));
				Rankprintscreen(arr, n);
				gotoxy(X, Y);
				printf(">");
				break;
			}
			else if (Y == 25) {
				//�ڷΰ��� �Է�
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
	system("title ����");
	system("cls");
	incursor(0);
	/*
	gotoxy(0, 0);
	printf("\n\n\n\n");
	printf("		       �ܡܡܡܡ�                 �ܡܡܡܡܡܡ�   \n");
	printf("		     ��          ��               ��          ��   \n");
	printf("		    ��            ��              ��          ��   \n");
	printf("		     ��          ��               �ܡܡܡܡܡܡ�   \n");
	printf("		       �ܡܡܡܡ�                       ��         \n");
	printf("		                               �ܡܡܡܡܡܡܡܡܡ�\n");
	printf("		           ��                                      \n");
	printf("		           ��                    �ܡܡܡܡܡܡܡ�  \n");
	printf("		  �ܡܡܡܡܡܡܡܡܡ�                         ��  \n");
	printf("                                                               ��\n");
	*/

	gotoxy(48, 12);
	printf("�� ��");

	gotoxy(46, 18);
	printf("1. ���� ����");
	gotoxy(46, 20);
	printf("2.   ���");
	gotoxy(46, 22);
	printf("3.   ��ŷ\n");
}

void title()
{
	int test;
	int X = 44, Y = 18;
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
				RankUI();
				titlescreen();
				gotoxy(X, Y);
				printf(">");
				break;
			}
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

	for (ry = 0; ry < MAX_Y; ry++) {
		for (rx = 0; rx < MAX_X; rx++) {
			if (record->board[ry][rx] == BLACK) {
				gotoxy(rx * 2 + x, ry + y);
				DRAW_BLACK;
			}
			else if (record->board[ry][rx] == WHITE) {
				gotoxy(rx * 2 + x, ry + y);
				DRAW_WHITE;
			}
		}
	}
	_getch();
}

// ���İ� ū�� ��Ÿ�� ������
int turn(int board[MAX_Y][MAX_X], int depth, int evex, int evey) {
	if (depth == 3)
		return getWeight(board, evex, evey);

	int maxw = INT_MIN;
	int minw = INT_MAX;
	if (depth % 2 == 0) {  // ai turn

		//printf("AI\n");
		for (int y = 1; y < MAX_Y; y++)  // for each child of node
		{
			for (int x = 1; x < MAX_X; x++) {
				int curStone = board[y][x];
				bool flag = false;

				if (curStone == EMPTY) {
					int deltax = 0, deltay = 0;
					for (int k = 0; k < 8; k++) {
						deltax = x + dx[k];
						deltay = y + dy[k];
						if (!isindexoutofboundsexception(deltax, deltay)) {
							if (board[deltay][deltax] != EMPTY) {
								flag = true;
								break;
							}
						}
					}
					if (flag) {
						board[y][x] = BLACK;
						int ww = turn(board, depth + 1, x, y);
						minw = min(minw, ww);
						if (maxw < ww) {
							maxw = ww;
							aix = x;
							aiy = y;
						}
						board[y][x] = EMPTY;
					}
				}
			}
		}
	}
	else {  // player turn

		//printf("P\n");
		for (int y = 1; y < MAX_Y; y++)  // for each child of node
		{
			for (int x = 1; x < MAX_X; x++) {
				int curStone = board[y][x];
				bool flag = false;

				if (curStone == EMPTY) {
					int deltax = 0, deltay = 0;
					for (int k = 0; k < 8; k++) {
						deltax = x + dx[k];
						deltay = y + dy[k];
						if (!isindexoutofboundsexception(deltax, deltay)) {
							if (board[deltay][deltax] != EMPTY) {
								flag = 1;
								break;
							}
						}
					}
					if (flag) {
						board[y][x] = WHITE;
						int ww = turn(board, depth + 1, x, y);
						maxw = max(maxw, ww);
						minw = min(minw, ww);
						board[y][x] = EMPTY;
					}
				}
			}
		}
		//printf("w : %d\n", minw);
		return minw;
	}
}

void record()
{
	Record* arr = NULL;
	int test, numRecords = 0, n = 0;
	int X = 8, Y = 15;
	arr = loadResultFromFile(arr, &numRecords);
	recordscreen(n, arr, numRecords);

	gotoxy(X, Y);
	printf(">");

	while (1) {
		test = _getch();
		switch (test) {
		case UP: gotoxy(X, Y);
			printf(" ");
			if (Y <= 15 && n != 0) {
				n = n - 1;
				recordscreen(n, arr, numRecords);
				X = 8; Y = 15;
				gotoxy(X, Y);
				printf(">");
			}
			else if (Y <= 15 && n == 0) {
				X = 8; Y = 15;
				gotoxy(X, Y);
				break;
			}
			printf(" ");
				Y -= 2;
				gotoxy(X, Y);
				printf(">");
			break;
		case DOWN: gotoxy(X, Y);
			printf(" ");
			if (Y >= 25) {
				n = n + 1;
				recordscreen(n, arr, numRecords);
				X = 8; Y = 15;
				gotoxy(X, Y);
				printf(">");
			}
			printf(" ");
				Y += 2;
				gotoxy(X, Y);
				printf(">");
				break;
		case ENTER: gotoxy(X, Y);
			if (Y == 15) {
				printboardrecord(&(arr[n * 5].result));
				recordscreen(n, arr, numRecords);
				gotoxy(X, Y);
				printf(">");
				break;
			}
			else if (Y == 17) {
				printboardrecord(&(arr[n * 5 + 1].result));
				recordscreen(n, arr, numRecords);
				gotoxy(X, Y);
				printf(">");
				break;
			}
			else if (Y == 19) {
				printboardrecord(&(arr[n * 5 + 2].result));
				recordscreen(n, arr, numRecords);
				gotoxy(X, Y);
				printf(">");
				break;
			}
			else if (Y == 21) {
				printboardrecord(&(arr[n * 5 + 3].result));
				recordscreen(n, arr, numRecords);
				gotoxy(X, Y);
				printf(">");
				break;
			}
			else if (Y == 23) {
				printboardrecord(&(arr[n * 5 + 4].result));
				recordscreen(n, arr, numRecords);
				gotoxy(X, Y);
				printf(">");
				break;
			}
			else if (Y == 25) {
				return;
			}

		case ESC:
			return;
		}
	}
}

void recordscreen(int n, Record gameRecords[], int numRecords) {
	int y = 15;
	char win[20];
	system("cls");

	//gotoxy(0, 0);
	//printf("\n\n");
	//printf("          �ܡܡܡ�    �ܡܡܡ�     �ܡܡ�       �ܡܡ�     �ܡܡܡ�    �ܡܡ�  \n");
	//printf("          ��     ��   ��          ��     ��    ��    ��    ��     ��   ��    ��\n");
	//printf("          �ܡܡܡ�    �ܡܡܡ�   ��           ��      ��   �ܡܡܡ�    ��    ��\n");
	//printf("          ��  ��      ��          ��     ��    ��    ��    ��  ��      ��    ��\n");
	//printf("          ��    ��    �ܡܡܡ�     �ܡܡ�       �ܡܡ�     ��    ��    �ܡܡ�  \n");

	gotoxy(10, y);

	for (int i = n * 5; i < (n + 1) * 5 && i < numRecords; i++)
	{
		if ((gameRecords + i)->who == 1) {
			strcpy(win, "BLACK");
		}

		else if ((gameRecords + i)->who == 2) {
			strcpy(win, "WHITE");
		}
		printf("%d. ��� �̸�: %s %s	��� ���: %s   \n", i + 1, (gameRecords + i) -> name1, (gameRecords + i) -> name2, win);
		y += 2;
		gotoxy(10, y);
	}
	gotoxy(10, 25);
	printf("�ڷΰ���\n");
}