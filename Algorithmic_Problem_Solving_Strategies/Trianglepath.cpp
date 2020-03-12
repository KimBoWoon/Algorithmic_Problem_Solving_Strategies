#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX_NUMBER 100

int testCase, n, maxSum;
int triangle[101][101], cache[101][101], cache2[101][101][MAX_NUMBER * 100 + 1];

// MAX_NUMBER : 한 칸에 들어갈 숫자의 최대치
// (y, x) 위치까지 내려오기 전에 만난 숫자들의 합이 sum 일 때
// 맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로를 반환한다.
int path1(int y, int x, int sum) {
	// 기저 사례 : 맨 아래 줄까지 도달했을 경우
	if (y == n - 1) {
		return sum + triangle[y][x];
	}
	// 메모이제이션
	int& ret = cache2[y][x][sum];
	if (ret != -1) {
		return ret;
	}
	sum += triangle[y][x];
	return ret = max(path1(y + 1, x + 1, sum), path1(y + 1, x, sum));
}

// (y, x) 위치부터 맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로의 합을 반환한다.
int path2(int y, int x) {
	// 기저 사례
	if (y == n - 1) {
		return triangle[y][x];
	}
	// 메모이제이션
	int& ret = cache[y][x];
	if (ret != -1) {
		return ret;
	}
	return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) + triangle[y][x];
}

int bottomUp(int x, int y) {
	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			cache[i][j] = triangle[i][j] + max(cache[i - 1][j], cache[i - 1][j - 1]);
		}
	}

	int answer = 0;
	for (int i = 0; i < n; i++) {
		answer = max(answer, cache[n - 1][i]);
	}
	
	return answer;
}

int main() {
	scanf("%d", &testCase);

	while (testCase--) {
		scanf("%d", &n);

		memset(cache, -1, sizeof(cache));
		memset(cache2, -1, sizeof(cache2));
		memset(triangle, 0, sizeof(triangle));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i + 1; j++) {
				scanf("%d", &triangle[i][j]);
			}
		}

		// printf("%d\n", path1(0, 0, 0));
		// printf("%d\n", path2(0, 0));
		cache[0][0] = triangle[0][0];
		printf("%d\n", bottomUp(0, 0));

		// cache[0][0] = max(triangle[0][0] + triangle[1][0], triangle[0][0] + triangle[1][1]);
		// cache[0][0] = triangle[0][0];
		// for (int i = 1; i < n; i++) {
		// 	for (int j = 0; j < i + 1; j++) {
		// 		cache[i][j] = max(cache[i - 1][j] + triangle[i][j], cache[i - 1][j] + triangle[i][j + 1]);
		// 	}
		// }

		// for (int i = 0; i < n; i++) {
		// 	if (cache[n - 1][i] > maxSum) {
		// 		maxSum = cache[n - 1][i];
		// 	}
		// }
		// printf("%d\n", maxSum);
	}
}