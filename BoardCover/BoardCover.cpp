#include <iostream>
#include <vector>
#include <string.h>
#include <cstdio>
#include <cstdlib>
using namespace std;

#pragma warning(disable:4996)

#define MAX_SIZE 21

const int coverType[4][3][2] = {
	{ { 0, 0 }, { 1, 0 }, { 0, 1 } },
	{ { 0, 0 }, { 0, 1 }, { 1, 1 } },
	{ { 0, 0 }, { 1, 0 }, { 1, 1 } },
	{ { 0, 0 }, { 1, 0 }, { 1, -1 } }
};

bool set(vector<vector<int> >& board, int y, int x, int type, int delta) {
	bool ok = true;

	for (int i = 0; i < 3; ++i) {
		const size_t ny = y + coverType[type][i][0];
		const size_t nx = x + coverType[type][i][1];

		if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
			ok = false;
		else if ((board[ny][nx] += delta) > 1)
			ok = false;
	}

	return ok;
}

int cover(vector<vector<int> >& board) {
	int y = -1, x = -1;

	for (size_t i = 0; i < board.size(); ++i) {
		for (size_t j = 0; j < board[i].size(); ++j) {
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

	for (int type = 0; type < 4; ++type) {
		if (set(board, y, x, type, 1))
			ret += cover(board);
		set(board, y, x, type, -1);
	}
	return ret;
}

int main() {
	int testCase;

	freopen("input.txt", "r", stdin);

	cin >> testCase;

	while (testCase--) {
		int x, y, cnt = 0;
		char temp = 0;
		vector<vector<int> > board;
		board.assign(MAX_SIZE, vector<int>(MAX_SIZE, 1));

		cin >> x >> y;

		for (int i = 0; i < x; ++i) {
			for (int j = 0; j < y; ++j) {
				cin >> temp;
				
				if (temp == '#')
					board[i][j] = 1;
				else if (temp == '.') {
					cnt++;
					board[i][j] = 0;
				}
			}
		}
		if (cnt % 3 == 0)
			cout << cover(board) << endl;
		else
			cout << 0 << endl;
	}
}