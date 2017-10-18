#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#pragma warning(disable:4996)

#define MAX_SIZE 8
#define INF 99999

int n;
double dist[MAX_SIZE][MAX_SIZE] = { 0 };

double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength) {
	if (path.size() == n)
		return currentLength + dist[path[0]][path.back()];

	double ret = INF;

	for (int next = 0; next < n; ++next) {
		if (visited[next])
			continue;

		int here = path.back();
		path.push_back(next);
		visited[next] = true;

		double cand = shortestPath(path, visited, currentLength + dist[here][next]);

		ret = min(ret, cand);
		visited[next] = false;
		path.pop_back();
	}

	return ret;
}

int main() {
	int testCase = 0;

	freopen("input.txt", "r", stdin);

	cin >> testCase;

	while (testCase--) {
		vector<int> path(MAX_SIZE);
		vector<bool> visited(MAX_SIZE);

		cin >> n;

		cout << fixed;
		cout.precision(10);

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				cin >> dist[i][j];
		}

		cout << shortestPath(path, visited, 0) << endl;
	}
}

//#include<stdio.h>
//#include<memory.h>
//#include<algorithm>
//using namespace std;
//
//double d[8][8];
//int n;
//int p[8];
//double r = 0;
//
//void path(int index);
//
//int main() {
//	int loop;
//
//	freopen("input.txt", "r", stdin);
//
//	scanf(" %d", &loop);
//
//	for (int i = 0; i < loop; i++) {
//		scanf(" %d", &n);
//		memset(d, (double)0, sizeof(d));
//
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				scanf("%lf", &d[i][j]);
//			}
//		}
//
//		for (int i = 0; i < n; i++)
//			p[i] = i;
//
//		double min = 99999;
//
//		do {
//			r = 0;
//			path(0);
//			min = (r < min) ? r : min;
//		} while (next_permutation(p, p + n));
//
//		printf("%.10lf\n", min);
//	}
//
//	return 0;
//}
//
//void path(int index) {
//	if (index != n - 1) {
//		r = r + d[p[index]][p[index + 1]];
//		index++;
//		path(index);
//	}
//}