#include <iostream>
#include <string>
#include <memory.h>
using namespace std;

#define MAX_SIZE 5

char boggle[MAX_SIZE][MAX_SIZE] = { 0 };
int cache[MAX_SIZE][MAX_SIZE][10] = { 0 };
const int dx[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
const int dy[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };

bool inRange(int x, int y) {
	return x >= 0 && x < MAX_SIZE && y >= 0 && y < MAX_SIZE;
}

int hasWord(int x, int y, int idx, string word) {
	if (idx >= word.size()) {
		return 1;
	}

	if (!inRange(x, y) || boggle[x][y] != word[idx]) {
		return 0;
	}

	int &ret = cache[x][y][idx];

	if (ret != -1) {
		return ret;
	}

	ret = 0;

	for (int direction = 0; direction < 8; ++direction) {
		int nextY = y + dy[direction], nextX = x + dx[direction], nextIdx = idx + 1;

		if (hasWord(nextX, nextY, nextIdx, word)) {
			ret = 1;
			return ret;
		}
	}
	return ret;
}

// bool hasWord(int x, int y, const string& word) {
// 	if (!inRange(x, y)) {
// 		return false;
// 	}
// 	if (boggle[x][y] != word[0]) {
// 		return false;
// 	}
// 	if (word.size() == 1) {
// 		return true;
// 	}

// 	if (cache[x][y][idx]) {
// 		return true;
// 	}

// 	for (int direction = 0; direction < 8; ++direction) {
// 		int nextY = y + dy[direction], nextX = x + dx[direction];

// 		if (hasWord(nextX, nextY, word.substr(1))) {
// 			return true;
// 		}
// 	}
// 	return false;
// }

bool solution(string word) {
	for (int x = 0; x < MAX_SIZE; ++x) {
		for (int y = 0; y < MAX_SIZE; ++y) {
			// if (hasWord(x, y, word)) {
			// 	flag = true;
			// 	break;
			// }
			if (hasWord(x, y, 0, word)) {
				return true;
			}
		}
	}

	return false;
}

int main() {
	int testCase;

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

			memset(cache, -1, sizeof(cache));

			cin >> word;

			if (solution(word)) {
				cout << word << " YES" << endl;
			} else {
				cout << word << " NO" << endl;
			}
		}
	}
}