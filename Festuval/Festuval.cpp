#include <cstdlib>
#include <cstdio>

#pragma warning(disable:4996)

int main() {
	int testCase = 0;

	scanf("%d", &testCase);
	
	while (testCase--) {
		int n = 0, l = 0;
		int* arr;

		scanf("%d %d", &n, &l);

		arr = (int*)malloc(n * sizeof(int));

		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);

		int start = 0;
		int size = 1;
		int step = l;
		double minAvg = 9999999.9, newAvg = 0;

		for (int i = 0; i < n - l + 1; i++) {
			for (int j = 0; j < n - l + size; j++) {
				int sum = 0;

				for (int k = start; k < start + step; k++) {
					sum += arr[k];
				}
				newAvg = (double)sum / (double)step;

				if (minAvg > newAvg)
					minAvg = newAvg;

				if (start <= n - step)
					start++;
			}
			start = 0;
			size--;
			step++;
		}
		printf("%.11f\n", minAvg);
	}
}