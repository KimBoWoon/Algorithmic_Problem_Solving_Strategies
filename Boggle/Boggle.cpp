#include <iostream>
using namespace std;

#pragma warning(disable:4996)

#define MAX_SIZE 5

int main() {
	int testCase;

	freopen("input.txt", "r", stdin);

	cin >> testCase;

	while (testCase--) {
		char boggle[MAX_SIZE][MAX_SIZE] = { 0 };

		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				cin >> boggle[i][j];
			}
		}
	}
}