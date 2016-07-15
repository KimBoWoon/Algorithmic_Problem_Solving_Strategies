//#include <iostream>
//#include <string>
//#include <vector>
//#include <string.h>
//#include <cstdio>
//#include <cstdlib>
//#include <cassert>
//#include <numeric>
//#include <algorithm>
//using namespace std;
//
//#pragma warning(disable:4996)
//
//const int coverType[4][3][2] = {
//	{ { 0, 0 }, { 1, 0 }, { 0, 1 } },
//	{ { 0, 0 }, { 0, 1 }, { 1, 1 } },
//	{ { 0, 0 }, { 1, 0 }, { 1, 1 } },
//	{ { 0, 0 }, { 1, 0 }, { 1, -1 } }
//};
//
//bool set(vector<vector<int> >& board, int y, int x, int type, int delta) {
//	bool ok = true;
//
//	for (int i = 0; i < 3; ++i) {
//		const size_t ny = y + coverType[type][i][0];
//		const size_t nx = x + coverType[type][i][1];
//
//		if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
//			ok = false;
//		else if ((board[ny][nx] += delta) > 1)
//			ok = false;
//	}
//
//	return ok;
//}
//
//int cover(vector<vector<int> >& board) {
//	int y = -1, x = -1;
//
//	for (size_t i = 0; i < board.size(); ++i) {
//		for (size_t j = 0; j < board[i].size(); ++j) {
//			if (board[i][j] == 0) {
//				y = i;
//				x = j;
//				break;
//			}
//			if (y != -1)
//				break;
//		}
//	}
//	if (y == -1)
//		return 1;
//
//	int ret = 0;
//
//	for (int type = 0; type < 4; ++type) {
//		if (set(board, y, x, type, 1))
//			ret += cover(board);
//		set(board, y, x, type, -1);
//	}
//	return ret;
//}
//
//int main() {
//	int testCase;
//
//	freopen("input.txt", "r", stdin);
//
//	cin >> testCase;
//
//	while (testCase--) {
//		int x = 0, y = 0, cnt = 0;
//		char temp = 0;
//		vector<vector<int> > board;
//
//		cin >> x >> y;
//
//		board.assign(x, vector<int>(y, 0));
//
//		assert(1 <= x && x <= 20);
//		assert(1 <= y && y <= 20);
//
//		for (int i = 0; i < x; ++i) {
//			for (int j = 0; j < y; ++j) {
//				cin >> temp;
//
//				if (temp == '#')
//					board[i][j] = 1;
//				else if (temp == '.') {
//					cnt++;
//					board[i][j] = 0;
//				}
//			}
//		}
//
//		assert(cnt <= 50);
//
//		if (cnt % 3 == 0)
//			cout << cover(board) << endl;
//		else
//			cout << 0 << endl;
//
//		board.clear();
//	}
//}

#include<numeric>
#include<algorithm>
#include<cassert>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// �־��� ĭ�� ���� �� �ִ� 4���� ���
// ����� �����ϴ� 3ĭ�� ����� ��ġ (dy,dx) �� ���
const int coverType[4][3][2] = {
	{ { 0, 0 }, { 1, 0 }, { 0, 1 } },
	{ { 0, 0 }, { 0, 1 }, { 1, 1 } },
	{ { 0, 0 }, { 1, 0 }, { 1, 1 } },
	{ { 0, 0 }, { 1, 0 }, { 1, -1 } } };

// board �� (y,x) �� type �� ������� ���ų�, ������ ����� ���ش�.
// delta = 1 �̸� ����, -1 �̸� ������ ����� ���ش�.
// ���� ����� ����� ������ ���� ��� (������ ������ �����ų�,
// ��ġ�ų�, ���� ĭ�� ���� ��) false �� ��ȯ�Ѵ�.
bool set(vector<vector<int> >& board, int y, int x, int type, int delta) {
	bool ok = true;
	for (int i = 0; i < 3; ++i) {
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];
		if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
			ok = false;
		else if ((board[ny][nx] += delta) > 1)
			ok = false;
	}
	return ok;
}

// board �� ��� �� ĭ�� ���� �� �ִ� ����� ���� ��ȯ�Ѵ�
// board[i][j] = 1 �̹� ���� ĭ Ȥ�� ���� ĭ
// board[i][j] = 0 ���� ������ ���� ĭ
int cover(vector<vector<int> >& board) {
	// ���� ä���� ���� ĭ �� ���� ���� ���ʿ� �ִ� ĭ�� ã�´�
	int y = -1, x = -1;
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j)
			if (board[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		if (y != -1) break;
	}
	// ���� ���: ��� ĭ�� ä������ 1�� ��ȯ�Ѵ�
	if (y == -1) return 1;

	int ret = 0;
	for (int type = 0; type < 4; ++type) {
		// ���� board[y][x] �� type ���·� ���� �� ������ ���ȣ���Ѵ�
		if (set(board, y, x, type, 1))
			ret += cover(board);
		// ������ ����� ġ���
		set(board, y, x, type, -1);
	}
	return ret;
}

int main() {
	int testCase;

	//freopen("input.txt", "r", stdin);

	cin >> testCase;

	while (testCase--) {
		int x = 0, y = 0, cnt = 0;
		char temp = 0;
		vector<vector<int> > board;

		cin >> x >> y;

		board.assign(x, vector<int>(y, 0));

		assert(1 <= x && x <= 20);
		assert(1 <= y && y <= 20);

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

		assert(cnt <= 50);

		if (cnt % 3 == 0)
			cout << cover(board) << endl;
		else
			cout << 0 << endl;

		board.clear();
	}
}