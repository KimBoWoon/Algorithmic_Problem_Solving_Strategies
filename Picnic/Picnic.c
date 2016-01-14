#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#pragma warning(disable:4996)

int areFriends[10][10];

int countPairingsWrong(int n, int taken[10]) {
	int finished = 1;
	int i, j;

	for (i = 0; i < n; ++i) {
		if (!taken[i])
			finished = 0;
	}
	if (finished)
		return 1;
	int ret = 0;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			if (!taken[i] && !taken[j] && areFriends[i][j]) {
				taken[i] = taken[j] = 1;
				ret += countPairingsWrong(n, taken);
				taken[i] = taken[j] = 0;
			}
		}
	}
	return ret;
}

int countPairings(int n, int taken[10]) {
	int firstFree = -1;
	int pairWith, i;

	for (i = 0; i < n; ++i) {
		if (!taken[i]) {
			firstFree = i;
			break;
		}
	}
	if (firstFree == -1)
		return 1;
	int ret = 0;
	for (pairWith = firstFree + 1; pairWith < n; ++pairWith) {
		if (!taken[pairWith] && areFriends[firstFree][pairWith]) {
			taken[firstFree] = taken[pairWith] = 1;
			ret += countPairings(n, taken);
			taken[firstFree] = taken[pairWith] = 0;
		}
	}
	return ret;
}

int main() {
	int testCase;
	LARGE_INTEGER start, end, frequency;

	QueryPerformanceFrequency(&frequency);

	freopen("input.txt", "r", stdin);

	scanf("%d", &testCase);

	while (testCase--) {
		int taken[10];
		int i, n, m;

		QueryPerformanceCounter(&start);
		scanf("%d %d", &n, &m);

		memset(areFriends, 0, sizeof(int) * 10 * 10);
		memset(taken, 0, sizeof(int) * 10);

		for (i = 0; i < m; ++i) {
			int a, b;
			scanf("%d %d", &a, &b);
			areFriends[a][b] = 1;
			areFriends[b][a] = 1;
		}
		printf("%d\n", countPairings(n, taken));
		QueryPerformanceCounter(&end);

		printf("Time : %f\n", ((double)end.QuadPart - (double)start.QuadPart) / (double)frequency.QuadPart);
	}
}