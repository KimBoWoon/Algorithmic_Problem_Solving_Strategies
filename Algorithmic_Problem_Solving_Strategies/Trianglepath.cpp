#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#pragma warning(disable: 4996)

#define MAX_NUMBER 100

int testCase, n, maxSum;
int triangle[101][101], cache[101][101], cache2[101][101][MAX_NUMBER * 100 + 1];

// MAX_NUMBER : �� ĭ�� �� ������ �ִ�ġ
// (y, x) ��ġ���� �������� ���� ���� ���ڵ��� ���� sum �� ��
// �� �Ʒ��ٱ��� �������鼭 ���� �� �ִ� �ִ� ��θ� ��ȯ�Ѵ�.
int path1(int y, int x, int sum) {
	// ���� ��� : �� �Ʒ� �ٱ��� �������� ���
	if (y == n - 1) {
		return sum + triangle[y][x];
	}
	// �޸������̼�
	int& ret = cache2[y][x][sum];
	if (ret != -1) {
		return ret;
	}
	sum += triangle[y][x];
	return ret = max(path1(y + 1, x + 1, sum), path1(y + 1, x, sum));
}

// (y, x) ��ġ���� �� �Ʒ��ٱ��� �������鼭 ���� �� �ִ� �ִ� ����� ���� ��ȯ�Ѵ�.
int path2(int y, int x) {
	// ���� ���
	if (y == n - 1) {
		return triangle[y][x];
	}
	// �޸������̼�
	int& ret = cache[y][x];
	if (ret != -1) {
		return ret;
	}
	return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) + triangle[y][x];
}

int main() {
	freopen("input.txt", "r", stdin);

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

		//printf("%d\n", path1(0, 0, 0));
		printf("%d\n", path2(0, 0));

		////cache[0][0] = max(triangle[0][0] + triangle[1][0], triangle[0][0] + triangle[1][1]);
		//cache[0][0] = triangle[0][0];
		//for (int i = 1; i < n; i++) {
		//	for (int j = 0; j < i + 1; j++) {
		//		cache[i][j] = max(cache[i - 1][j] + triangle[i][j], cache[i - 1][j] + triangle[i][j + 1]);
		//	}
		//}

		//for (int i = 0; i < n; i++) {
		//	if (cache[n - 1][i] > maxSum) {
		//		maxSum = cache[n - 1][i];
		//	}
		//}
		//printf("%d\n", maxSum);
	}
}