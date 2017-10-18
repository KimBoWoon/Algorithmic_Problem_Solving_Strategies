#include <iostream>
#include <string>
using namespace std;

#pragma warning(disable:4996)

#define MAX_SIZE 5

char boggle[MAX_SIZE][MAX_SIZE] = { 0 };
//const int dx[8] = { -1, -1, -1, 1, 1, 1, 0, 0 };
//const int dy[8] = { -1, 0, 1, -1, 0, 1, -1, 1 };
const int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
const int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };

bool inRange(int x, int y) {
	if (y > 5 || y < 0 || x > 5 || x < 0)
		return false;
}

bool hasWord(int x, int y, const string& word) {
	if (!inRange(x, y))
		return false;
	if (boggle[x][y] != word[0])
		return false;
	if (word.size() == 1)
		return true;

	for (int direction = 0; direction < 8; ++direction) {
		int nextY = y + dy[direction], nextX = x + dx[direction];
		if (hasWord(nextX, nextY, word.substr(1)))
			return true;
	}
	return false;
}

int main() {
	int testCase;

	freopen("input.txt", "r", stdin);

	cin >> testCase;

	while (testCase--) {
		int wordCnt = 0;

		for (int i = 0; i < MAX_SIZE; ++i) {
			for (int j = 0; j < MAX_SIZE; ++j) {
				cin >> boggle[i][j];
			}
		}

		cin >> wordCnt;

		while (wordCnt--) {
			string word;
			bool flag = false;

			cin >> word;

			for (int x = 0; x < MAX_SIZE; ++x) {
				for (int y = 0; y < MAX_SIZE; ++y) {
					if (hasWord(x, y, word)) {
						flag = true;
						break;
					}
				}
				if (flag)
					break;
			}

			if (flag)
				cout << word << " YES" << endl;
			else
				cout << word << " NO" << endl;
		}
	}
}