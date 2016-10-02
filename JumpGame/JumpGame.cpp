#include <iostream>
#include <memory.h>
//#include <Windows.h>
using namespace std;

//#pragma warning(disable:4996)

int n, board[101][101];
int cache[101][101];

bool jump(int y, int x) {
	if (y >= n || x >= n)
		return false;

	if (y == n - 1 && x == n - 1)
		return true;

	int jumpSize = board[y][x];

	return jump(y + jumpSize, x) || jump(y, x + jumpSize);
}

int jump2(int y, int x) {
	if (y >= n || x >= n)
		return 0;

	if (y == n - 1 && x == n - 1)
		return 1;

	int& ret = cache[y][x];

	if (ret != -1)
		return ret;

	int jumpSize = board[y][x];

	return ret = (jump2(y + jumpSize, x) || jump2(y, x + jumpSize));
}

int main() {
	int testCase;

	//freopen("input.txt", "r", stdin);

	cin >> testCase;

	while (testCase--) {
		//UINT64 computeCount = 0;
		//LARGE_INTEGER start_time, finish_time, liFrequency;
		//int result;

		//QueryPerformanceFrequency(&liFrequency);

		cin >> n;

		memset(board, 0, sizeof(int) * 101 * 101);
		memset(cache, -1, sizeof(int) * 101 * 101);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				cin >> board[i][j];
		}

		/*for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				cout << board[i][j] << " ";
			cout << endl;
		}

		cout << fixed;
		cout.precision(10);*/

		//QueryPerformanceCounter(&start_time);
		//result = jump(0, 0);
		//result = jump2(0, 0);
		//QueryPerformanceCounter(&finish_time);

		if (jump2(0, 0))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
		/*if (result)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;*/
		//cout << "Time : " << (double)(finish_time.QuadPart - start_time.QuadPart) / (double)liFrequency.QuadPart << endl;
	}
}