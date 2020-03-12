#include <cstdio>
#include <algorithm>
#include <memory.h>
using namespace std;

// 입력이 32비트 부호 있는 정수의 모든 값을 가질 수 있으므로
// 인위적인 최소치는 64비트여야 한다
int t, n, m;
int A[101], B[101];
int cache[101][101];
const long long NEGINF = numeric_limits<long long>::min();

// min(A[idxA], B[idxB]), max(A[idxA], B[idxB])로 시작하는
// 합친 증가 부분 수열의 최대 길이를 반환한다
// 단 idxA == idxB == -1 혹은 A[idxA] != B[idxB]라고 가정한다
int jlis(int idxA, int idxB) {
    // 메모이제이션
    int& ret = cache[idxA + 1][idxB + 1];

    if (ret != -1) {
        return ret;
    }

    // A[idxA], B[idxB]가 이미 존재하므로 2개는 항상 있다
    ret = 2;

    long long a = (idxA == -1 ? NEGINF : A[idxA]);
    long long b = (idxB == -1 ? NEGINF : B[idxB]);
    long long maxElement = max(a, b);

    // 다음 원소를 찾는다
    for (int nextA = idxA + 1; nextA < n; nextA++) {
        if (maxElement < A[nextA]) {
            ret = max(ret, jlis(nextA, idxB) + 1);
        }
    }

    for (int nextB = idxB + 1; nextB < m; nextB++) {
        if (maxElement < B[nextB]) {
            ret = max(ret, jlis(idxA, nextB) + 1);
        }
    }

    return ret;
}

int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);

        memset(cache, -1, sizeof(cache));

        for (int i = 0; i < n; i++) {
            scanf("%d", &A[i]);
        }

        for (int i = 0; i < m; i++) {
            scanf("%d", &B[i]);
        }

        printf("%d\n", jlis(-1, -1) - 2);
    }
}