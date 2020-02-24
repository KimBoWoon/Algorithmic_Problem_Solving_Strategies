#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> getPartialMatch(const string &N) {
	int m = N.size();
	vector<int> pi(m, 0);
	int begin = 1, matched = 0;

	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		} else {
			if (matched == 0) {
				++begin;
			} else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}

	return pi;
}

int getPalindromize(const string& a, const string& b) {
	int n = a.size(), m = b.size();
    vector<int> pi = getPartialMatch(b);
    int begin = 0, matched = 0;

    while (begin < n) {
        if (matched < m && a[begin + matched] == b[matched]) {
            ++matched;

            if (begin + matched == n) {
                return matched;
            }
        } else {
            if (matched == 0) {
                ++begin;
            } else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }

    return 0;
}

int main() {
    int n;

    cin >> n;

    while (n--) {
        string str, rStr;

        cin >> str;

        rStr = str;
        reverse(rStr.begin(), rStr.end());

        printf("%ld\n", str.size() * 2 - getPalindromize(str, rStr));
    }
}