#include <iostream>
#include <string>
#include <vector>
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

vector<int> kmpSearch(const string &H, const string &N) {
	int n = H.size(), m = N.size();
	vector<int> ret;
	vector<int> pi = getPartialMatch(N);
	int begin = 0, matched = 0;

	while (begin <= n - m) {
		if (matched < m && H[begin + matched] == N[matched]) {
			++matched;
			if (matched == m) {
				ret.push_back(begin);
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

	return ret;
}

vector<int> getPrefixSuffix(const string& s) {
	vector<int> ret, pi = getPartialMatch(s);
	int k = s.size();

	while (k > 0) {
		ret.push_back(k);
		k = pi[k - 1];
	}

	return ret;
}

int main() {
    string a, b;

	cin >> a >> b;

    vector<int> v = getPrefixSuffix(a + b);

	for (int i = v.size() - 1; i >= 0; i--) {
		printf("%d ", v[i]);
	}
}