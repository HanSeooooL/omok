#include "omok.h"
#include <limits.h>
#include <math.h>
#include <Windows.h>
#include <stdbool.h>
#include <stdio.h>

bool bbbbbPattern(int board[MAX_Y][MAX_X], int evex, int evey);
bool bbbbPattern(int board[MAX_Y][MAX_X], int evex, int evey);
bool bbPattern(int board[MAX_Y][MAX_X], int evex, int evey);
bool bbbwPattern(int board[MAX_Y][MAX_X], int evex, int evey);
int getWeight(int board[MAX_Y][MAX_X], int x, int y);
bool isindexoutofboundsexception(int x, int y);

const int dx[8] = { 0, 0, 1, 1, 1, -1, -1, -1 };
const int dy[8] = { 1, -1, 0, 1, -1, 0, 1, -1 };

int aix = 0, aiy = 0; //ai 변수

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
	for (int i = 0; i < MAX_X - 4; i++) {
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

void checkstartstone(Omokboard* play, int* x, int* y) {
	while (1) {
		//gotoxy(0, 20);
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

void putstone(Omokboard* play, int x, int y, int player) {			//돌 놓은 위치 기록
	play->board[y - StartpointY][(x - StartpointX) / 2] = player;
}

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
						board[y][x] = EMPTY;
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
}

/*int minimax(int board[MAX_Y][MAX_X], int depth, int maximizingPlayer) {
	// 게임 종료 조건 또는 최대 탐색 깊이 도달 시, 현재 보드 상태의 점수 반환
	int gameStatus = checkGameStatus(board); // 현재 게임 상태 확인
	if (gameStatus != 0 || depth == 0) {
		return calculateScore(board, AI); // AI의 점수를 계산하여 반환
	}

	if (maximizingPlayer) { // AI의 차례인 경우
		int maxEval = -1000; // AI가 선택한 최대값 초기화
		for (int i = 0; i < MAX_Y; i++) {
			for (int j = 0; j < MAX_X; j++) {
				if (board[i][j] == EMPTY) { // 비어있는 위치에 AI의 돌을 놓아봅니다.
					board[i][j] = AI; // AI의 돌을 놓음
					int eval = minimax(board, depth - 1, 0); // 재귀적으로 다음 차례의 플레이어의 최적의 수 탐색
					// 최대값 선택
					if (eval > maxEval) {
						maxEval = eval; // 더 큰 값으로 maxEval 갱신
					}
					// 보드 원래대로 돌려놓기
					board[i][j] = EMPTY;
				}
			}
		}
		return maxEval; // AI가 선택한 최대값 반환
	}
	else { // 플레이어의 차례인 경우
		int minEval = 1000; // 플레이어가 선택한 최소값 초기화
		for (int i = 0; i < MAX_Y; i++) {
			for (int j = 0; j < MAX_X; j++) {
				if (board[i][j] == EMPTY) { // 비어있는 위치에 플레이어의 돌을 놓아봅니다.
					board[i][j] = PLAYER; // 플레이어의 돌을 놓음
					int eval = minimax(board, depth - 1, 1); // 재귀적으로 다음 차례의 AI의 최적의 수 탐색
					// 최소값 선택
					if (eval < minEval) {
						minEval = eval; // 더 작은 값으로 minEval 갱신
					}
					// 보드 원래대로 돌려놓기
					board[i][j] = EMPTY;
				}
			}
		}
		return minEval; // 플레이어가 선택한 최소값 반환
	}
}*/