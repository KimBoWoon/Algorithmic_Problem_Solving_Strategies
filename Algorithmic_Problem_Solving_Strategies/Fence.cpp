#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

#pragma warning(disable: 4996)

int testCase, n;
int fence[20001];
// vector<int> fence;

// O(n^2)
// ������ ���̸� ���� �迭h[]�� �־��� �� �簢���� �ִ� �ʺ� ��ȯ�Ѵ�.
int bruteForce() {
	int ret = 0;

	// ������ ��� left, right ������ ��ȸ�Ѵ�.
	for (int left = 0; left < n; left++) {
		int minHeight = fence[left];

		for (int right = left; right < n; right++) {
			minHeight = min(minHeight, fence[right]);
			ret = max(ret, (right - left + 1) * minHeight);
		}
	}

	return ret;
}

// O(nlgn)
// fence[left...right] �������� ã�Ƴ� �� �ִ� ���� ū �簢���� ���̸� ��ȯ�Ѵ�.
int solve(int left, int right) {
	// ���� ��� : ���ڰ� �ϳ��ۿ� ���� ���
	if (left == right) {
		return fence[left];
	}
	// [left, mid], [mid + 1, right]�� �� �������� ������ �����Ѵ�.
	int mid = (left + right) / 2;
	// ������ ������ ��������
	int ret = max(solve(left, mid), solve(mid + 1, right));
	// �κ� ���� 3 : �� �κп� ��� ��ġ�� �簢�� �� ���� ū ���� ã�´�.
	int lo = mid, hi = mid + 1;
	int height = min(fence[lo], fence[hi]);
	// [mid, mid + 1]�� �����ϴ� �ʺ� 2�� �簢���� ����Ѵ�.
	ret = max(ret, height * 2);
	// �簢���� �Է� ��ü�� ���� ������ Ȯ���� ������.
	while (left < lo || hi < right) {
		// �׻� ���̰� �� ���� ������ Ȯ���Ѵ�.
		if (hi < right && (lo == left || fence[lo - 1] < fence[hi + 1])) {
			hi++;
			height = min(height, fence[hi]);
		}
		else {
			lo--;
			height = min(height, fence[lo]);
		}
		// Ȯ���� �� �簢���� ����
		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%d", &testCase);

	while (testCase--) {
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%d", &fence[i]);
			/*int x;
			scanf("%d", &x);
			fence.push_back(x);*/
		}

		// printf("%d\n", bruteForce());
		printf("%d\n", solve(0, n - 1));
		// fence.clear();
		memset(fence, 0, sizeof(int) * 20001);
	}
}