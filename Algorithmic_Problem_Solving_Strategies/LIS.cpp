#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int t, n;
int cache[501], S[501];

int lis(const vector<int>& v) {
    if (v.empty()) {
        return 0;
    }

    int ret = 0;

    for (int i = 0; i < v.size(); i++) {
        vector<int> temp;

        for (int j = i + 1; j < v.size(); j++) {
            if (v[i] < v[j]) {
                temp.push_back(v[j]);
            }

            ret = max(ret, 1 + lis(temp));
            // int value = 1 + lis(temp);
            // if (ret < value) {
            //     ret = value;
            // }
        }
    }

    return ret;
}

int lis2(int start) {
    int& ret = cache[start];

    if (ret != -1) {
        return ret;
    }

    ret = 1;

    for (int next = start + 1; next < n; next++) {
        if (S[start] < S[next]) {
            ret = max(ret, lis2(next) + 1);
        }
    }

    return ret;
}

int lis3(int start) {
    int& ret = cache[start + 1];

    if (ret != -1) {
        return ret;
    }

    ret = 1;

    for (int next = start + 1; next < n; next++) {
        if (start == -1 || S[start] < S[next]) {
            ret = max(ret, lis3(next) + 1);
        }
    }

    return ret;
}

void lis4(int& idx, int value) {
    // value값이 마지막 값보다 크면 뒤에 삽입
    if (idx == 0 || (idx > 0 && S[idx - 1] <= value)) {
        S[idx++] = value;
        return;
    }

    // 아니면 이분탐색을 시작하여 최적의 위치 탐색
    // lower_bound(start, end, target)을 사용할 수도 있다
    // target보다 큰 가장 작은 정수를 찾아 교체한다
    int start = 0, end = idx - 1;

    while (start <= end) {
        int mid = (start + end) / 2;

        if (S[mid] < value) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    // 값을 대체
    S[end + 1] = value;
}

int main() {
    scanf("%d", &t);

    while (t--) {
        int idx = 0;
        vector<int> v;
        memset(S, 0, sizeof(S));
        memset(cache, -1, sizeof(cache));

        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            // int x;
            // scanf("%d", &x);
            // v.push_back(x);
            scanf("%d", &S[i]);
        }

        // printf("%d\n", lis(v) + 1);
        // int maxLen = 0;
        // for (int begin = 0; begin < n; begin++) {
        //     maxLen = max(maxLen, lis2(begin));
        // }
        // printf("%d\n", maxLen);
        // printf("%d\n", lis3(-1) - 1);
        idx = 0;
        for (int i = 0; i < n; i++) {
            lis4(idx, S[i]);
        }
        printf("%d\n", idx);
        for (int i = 0; i < idx; i++) {
            printf("%d ", S[i]);
        }
        printf("\n");
    }
}