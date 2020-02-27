#include <cstdio>
using namespace std;

int t, n, l;
int arr[1002];

int main() {
	scanf("%d", &t);

	while (t--) {
		double answer = 2e9;

		scanf("%d %d", &n, &l);

		scanf("%d", &arr[1]);
		for (int i = 2; i <= n; i++) {
			int x;
			scanf("%d", &x);
			arr[i] = arr[i - 1] + x;
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; l + i + j <= n; j++) {
				double value = (double) (arr[l + j + i] - arr[i]) / (double) (l + j);
				if (answer > value) {
					answer = value;
				}
			}
		}

		printf("%.8lf\n", answer);
	}
}




// #include <cstdlib>
// #include <cstdio>

// #pragma warning(disable:4996)

// int main() {
// 	int testCase = 0;

// 	scanf("%d", &testCase);
	
// 	while (testCase--) {
// 		int n = 0, l = 0;
// 		int* arr;

// 		scanf("%d %d", &n, &l);

// 		arr = (int*)malloc(n * sizeof(int));

// 		for (int i = 0; i < n; i++)
// 			scanf("%d", &arr[i]);

// 		int start = 0;
// 		int size = 1;
// 		int step = l;
// 		double minAvg = 9999999.9, newAvg = 0;

// 		for (int i = 0; i < n - l + 1; i++) {
// 			for (int j = 0; j < n - l + size; j++) {
// 				int sum = 0;

// 				for (int k = start; k < start + step; k++) {
// 					sum += arr[k];
// 				}
// 				newAvg = (double)sum / (double)step;

// 				if (minAvg > newAvg)
// 					minAvg = newAvg;

// 				if (start <= n - step)
// 					start++;
// 			}
// 			start = 0;
// 			size--;
// 			step++;
// 		}
// 		printf("%.11f\n", minAvg);
// 	}
// }