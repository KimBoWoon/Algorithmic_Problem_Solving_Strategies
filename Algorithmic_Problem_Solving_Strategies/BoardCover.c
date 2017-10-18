#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

#define MAX_SIZE 20

const int coverType[4][3][2] = {
	{ { 0, 0 }, { 1, 0 }, { 0, 1 } },
	{ { 0, 0 }, { 0, 1 }, { 1, 1 } },
	{ { 0, 0 }, { 1, 0 }, { 1, 1 } },
	{ { 0, 0 }, { 1, 0 }, { 1, -1 } }
};
int board[MAX_SIZE][MAX_SIZE];

int set(int board[MAX_SIZE][MAX_SIZE], int x, int y, int type, int delta) {
	int ok = 1, i;

	for (i = 0; i < 3; ++i) {
		const int nx = x + coverType[type][i][1];
		const int ny = y + coverType[type][i][0];

		if (ny < 0 || ny >= y || nx < 0 || nx >= x)
			ok = 0;
		else if ((board[ny][nx] += delta) > 1)
			ok = 0;
	}

	return ok;
}

int cover(int board[MAX_SIZE][MAX_SIZE], int row, int col) {
	int y = -1, x = -1;
	int i, j, type;

	for (i = 0; i < col; ++i) {
		for (j = 0; j < row; ++j) {
			if (board[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
			if (y != -1)
				break;
		}
	}
	if (y == -1)
		return 1;

	int ret = 0;

	for (type = 0; type < 4; ++type) {
		if (set(board, row, col, type, 1))
			ret += cover(board, row, col);
		set(board, row, col, type, -1);
	}
	return ret;
}

int main() {
	int testCase;

	freopen("input.txt", "r", stdin);

	scanf("%d", &testCase);

	while (testCase--) {
		int x, y, i, j;
		char temp = 0;

		memset(board, 0, sizeof(int) * MAX_SIZE * MAX_SIZE);

		scanf("%d %d", &x, &y);

		for (i = 0; i < x; ++i) {
			for (j = 0; j < y; ++j) {
				scanf("%c", &temp);

				if (temp == '#')
					board[i][j] = 1;
				else if (temp == '.')
					board[i][j] = 0;
			}
		}
		cover(board, x, y);
	}
}