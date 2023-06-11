// omok.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
#include <stdio.h>
#include <Windows.h>
#include "omok.h"

int main() {
	//RankEasyHardUI();
	//printOmokboard();
	//playUI();
	selectAIuser();
	return 0;
}
/*
Omokboard* playUI(int select) {

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
		for (int i = 0; i < MAX_Y; i++)
		{
			for (int j = 0; j < MAX_X; j++)
				printf("%d ", play->board[i][j]);
			printf("\n");
		} 
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
				gotoxy(0, 0);
				printf("NO\n");
				turn(play -> board, 0, 0, 0, (X - StartpointX) / 2, Y - StartpointY);

				gotoxy((aix * 2) + StartpointX, aiy + StartpointY);
				DRAW_BLACK;
				putstone(play, aix, aiy, BLACK);

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
*/

/*bool isindexoutofboundsexception(int x, int y) {
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
		printf("AI\n");
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
		printf("P\n");
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
						board[y][x] = WHITE;
						w = min(w, turn(board, depth + 1, a, b, x, y));
						board[y][x] = EMPTY;
					}
				}
			}
		}
	}
} */