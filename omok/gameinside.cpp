#include "omok.h"
#include <limits.h>
#include <math.h>
#include <Windows.h>
#include <stdbool.h>
#include <stdio.h>


extern void gotoxy(int x, int y);
bool bbbbbPattern(int board[MAX_Y][MAX_X], int evex, int evey);
bool bbbbPattern(int board[MAX_Y][MAX_X], int evex, int evey);
bool bbPattern(int board[MAX_Y][MAX_X], int evex, int evey);
bool bbbwPattern(int board[MAX_Y][MAX_X], int evex, int evey);

int checkGameStatus(int board[MAX_Y][MAX_X]) {
	// ���� ���� üũ
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X - 4; j++) {
			if (board[i][j] != EMPTY &&
				board[i][j] == board[i][j + 1] &&
				board[i][j] == board[i][j + 2] &&
				board[i][j] == board[i][j + 3] &&
				board[i][j] == board[i][j + 4]) {
				return board[i][j]; // �¸��� �÷��̾� ��ȯ
			}
		}
	}

	// ���� ���� üũ
	for (int i = 0; i < MAX_X - 4; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			if (board[i][j] != EMPTY &&
				board[i][j] == board[i + 1][j] &&
				board[i][j] == board[i + 2][j] &&
				board[i][j] == board[i + 3][j] &&
				board[i][j] == board[i + 4][j]) {
				return board[i][j]; // �¸��� �÷��̾� ��ȯ
			}
		}
	}

	// �밢�� ���� üũ (���� ������ ������ �Ʒ���)
	for (int i = 0; i < MAX_Y - 4; i++) {
		for (int j = 0; j < MAX_X - 4; j++) {
			if (board[i][j] != EMPTY &&
				board[i][j] == board[i + 1][j + 1] &&
				board[i][j] == board[i + 2][j + 2] &&
				board[i][j] == board[i + 3][j + 3] &&
				board[i][j] == board[i + 4][j + 4]) {
				return board[i][j]; // �¸��� �÷��̾� ��ȯ
			}
		}
	}

	// �밢�� ���� üũ (������ ������ ���� �Ʒ���)
	for (int i = 0; i < MAX_X - 4; i++) {
		for (int j = 4; j < MAX_Y; j++) {
			if (board[i][j] != EMPTY &&
				board[i][j] == board[i + 1][j - 1] &&
				board[i][j] == board[i + 2][j - 2] &&
				board[i][j] == board[i + 3][j - 3] &&
				board[i][j] == board[i + 4][j - 4]) {
				return board[i][j]; // �¸��� �÷��̾� ��ȯ
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

int checkcanstone(Omokboard* play, int x, int y, int direction)	//������ ���⿡�� ���� �� �ִ� ������ ��ġ������ �Ÿ� ��ȯ (-1��ȯ�� ���ڸ� ����)
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

void putstone(Omokboard* play, int x, int y, int player) {			//�� ���� ��ġ ���
	play->board[y - StartpointY][(x - StartpointX) / 2] = player;
}

bool bbbwPattern(int board[MAX_Y][MAX_X], int evex, int evey) {
	int dx[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

	int stone = board[evey][evex];

	// 8����˻�
	for (int direction = 0; direction < 8; ++direction) {
		int count = 1;  // �浹 ī��Ʈ

		// �� �������� ��� �����ϸ� ������ ���� ���ӵǴ��� �˻�
		for (int i = 1; i <= 2; ++i) {
			int nx = evex + dx[direction] * i;
			int ny = evey + dy[direction] * i;

			// �迭 ������ ����ų�, �˻��ϴ� ���� �ٸ� ���̶�� �ߴ�
			if (nx < 0 || nx >= MAX_X || ny < 0 || ny >= MAX_Y || board[ny][nx] != stone)
				break;
			count++;
		}

		// count�� 3�̰�(�浶3��) �ٸ������� ���̸� Ʈ��
		if (count == 3 && (board[evey - dy[direction]][evex - dx[direction]] != stone))
			return true;
	}
	return false;
}

bool bbPattern(int board[MAX_Y][MAX_X], int evex, int evey) {
	int dx[] = { 1, 1, 0, -1, 1, -1, 0, -1 };  // ����, ����, �밢�� �˻�
	int dy[] = { 0, 1, 1, 1, -1, -1, -1, 0 };

	int stone = BLACK;  // �浹
	for (int d = 0; d < 8; ++d) {
		int count = 0;
		for (int i = 1; i <= 2; ++i) {
			int nx = evex + dx[d] * i;
			int ny = evey + dy[d] * i;
			if (nx < 0 || nx >= MAX_X || ny < 0 || ny >= MAX_Y)
				break;
			if (board[ny][nx] == stone) {
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
	int dx[] = { 1, 1, 0, -1 };  // ����, ����, �밢�� ���� �˻�
	int dy[] = { 0, 1, 1, 1 };

	int stone = BLACK;  // �浹
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
	int dx[] = { 1, 1, 0, -1 };  // ����, ����, �밢�� ���� �˻�
	int dy[] = { 0, 1, 1, 1 };

	int stone = BLACK;  // �浹
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
	int dx[] = { 1, 1, 0, -1 };  // ����, ����, �밢�� ���� �˻�
	int dy[] = { 0, 1, 1, 1 };

	int stone = BLACK;  // �浹
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

bool isindexoutofboundsexception(int x, int y) {
	if (x < 0 || x > MAX_X || y < 0 || y > MAX_Y)
		return true;
	else
		return false;
}

int getWeight(int board[MAX_Y][MAX_X], int x, int y) {
	int w = 0;

	if (bbbwPattern(board, x, y)) {
		w = 10;
	}
	if (bbbwPattern(board, x, y)) {
		w = 200;
	}
	if (bbbbPattern(board, x, y)) {
		w = 3000;
	}
	if (bbbbbPattern(board, x, y)) {
		w = 40000;
	}
	return w;
}


/*
int minimax(int board[MAX_Y][MAX_X], int depth, int maximizingPlayer, int x, int y) {
	// ���� ���� ���� �Ǵ� �ִ� Ž�� ���� ���� ��, ���� ���� ������ ���� ��ȯ
	int gameStatus = checkGameStatus(board); // ���� ���� ���� Ȯ��
	if (gameStatus != 0 || depth == 0) {
		return getWeight(board, x, y); // AI�� ������ ����Ͽ� ��ȯ
	}

	if (maximizingPlayer) { // AI�� ������ ���
		int maxEval = -1000; // AI�� ������ �ִ밪 �ʱ�ȭ
		for (int i = 0; i < MAX_Y; i++) {
			for (int j = 0; j < MAX_X; j++) {
				if (board[i][j] == EMPTY) { // ����ִ� ��ġ�� AI�� ���� ���ƺ��ϴ�.
					board[i][j] = BLACK; // AI�� ���� ����
					gotoxy(0, 5);
					for (int i = 0; i < MAX_Y; i++)
					{
						for (int j = 0; j < MAX_X; j++)
							printf("%d ", board[i][j]);
						printf("\n");
					}
					int eval = minimax(board, depth - 1, 0, j, i); // ��������� ���� ������ �÷��̾��� ������ �� Ž��
					// �ִ밪 ����
					if (eval > maxEval) {
						maxEval = eval; // �� ū ������ maxEval ����
					}
					//printf("%d ", maxEval);
					// ���� ������� ��������
					board[i][j] = EMPTY;
				}
			}
		}
		return maxEval; // AI�� ������ �ִ밪 ��ȯ
	}

	else { // �÷��̾��� ������ ���
		int minEval = 1000; // �÷��̾ ������ �ּҰ� �ʱ�ȭ
		for (int i = 0; i < MAX_Y; i++) {
			for (int j = 0; j < MAX_X; j++) {
				if (board[i][j] == EMPTY) { // ����ִ� ��ġ�� �÷��̾��� ���� ���ƺ��ϴ�.
					board[i][j] = WHITE; // �÷��̾��� ���� ����
					gotoxy(0, 5);
					for (int i = 0; i < MAX_Y; i++)
					{
						for (int j = 0; j < MAX_X; j++)
							printf("%d ", board[i][j]);
						printf("\n");
					}
					int eval = minimax(board, depth - 1, 1, j, i); // ��������� ���� ������ AI�� ������ �� Ž��
					// �ּҰ� ����
					if (eval < minEval) {
						minEval = eval; // �� ���� ������ minEval ����
					}
					//printf("%d ", minEval);
					// ���� ������� ��������
					board[i][j] = EMPTY;
				}
			}
		}
		return minEval; // �÷��̾ ������ �ּҰ� ��ȯ
	}
}
*/

int compare(const void* a, const void* b)
{
	Rank num1 = *(Rank*)a;
	Rank num2 = *(Rank*)b;

	if (num1.time < num2.time)
		return -1;

	if (num1.time > num2.time)
		return 1;

	return 0;
}