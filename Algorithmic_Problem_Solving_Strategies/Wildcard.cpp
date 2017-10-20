#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

// -1�� ���� ���� ������ �ʾ����� �ǹ��Ѵ�.
// 1�� �ش� �Էµ��� ���� �������� �ǹ��Ѵ�.
// 0�� �ش� �Էµ��� ���� �������� ������ �ǹ��Ѵ�.
int cache[101][101];
// ���ϰ� ���ڿ�
string W, S;
vector<string> v;

int testCase, n;

// ���ϵ�ī�� ���� w�� ���ڿ� s�� �����Ǵ��� ���θ� ��ȯ�Ѵ�.
bool match(const string& w, const string& s) {
	// w[pos]�� s[pos]�� ���� ������.
	int pos = 0;
	while (pos < s.size() && pos < w.size() && (w[pos] == '?' || w[pos] == s[pos])) {
		++pos;
		// ���̻� ������ �� ������ �� while���� �������� Ȯ���Ѵ�.
		// 2. ���� ���� �����ؼ� ���� ��� : ���ڿ��� ������� ������
		if (pos == w.size()) {
			return pos == s.size();
		}
		// 4. *�� ������ ���� ��� : *�� �� ���ڸ� �����ؾ� ���� ��� ȣ���ϸ鼭 Ȯ���Ѵ�.
		if (w[pos] == '*') {
			for (int skip = 0; pos + skip <= s.size(); ++skip) {
				if (match(w.substr(pos + 1), s.substr(pos + skip))) {
					return true;
				}
			}
		}
	}
	// �� ���� ��쿡�� ��� �������� �ʴ´�.
	return false;
}

//// ���ϵ�ī�� ���� W[w..]�� ���ڿ� S[s..]�� �����Ǵ��� ���θ� ��ȯ�Ѵ�.
//bool matchMemoized(int w, int s) {
//	// �޸������̼�
//	int& ret = cache[w][s];
//	if (ret != -1) {
//		return ret;
//	}
//	// W[w]�� S[s]�� ���� ������.
//	while (s < S.size() && w < W.size() && (W[w] == '?' || W[w] == S[s])) {
//		++w;
//		++s;
//	}
//	// ���̻� ������ �� ������ �� while���� �������� Ȯ���Ѵ�.
//	// 2. ���� ���� �����ؼ� ���� ��� : ���ڿ��� ������� ��
//	if (w == W.size()) {
//		return ret = (s == S.size());
//	}
//	// 4. *�� ������ ���� ��� : *�� �� ���ڸ� �����ؾ� ���� ��� ȣ���ϸ鼭 Ȯ���Ѵ�.
//	if (W[w] == '*') {
//		for (int skip = 0; skip + s <= S.size(); ++skip) {
//			if (matchMemoized(w + 1, s + skip)) {
//				return ret = 1;
//			}
//		}
//	}
//	// 3. �̿��� ��쿡�� ��� �������� �ʴ´�.
//	return ret = 0;
//}

// ���ϵ�ī�� ���� W[w..]�� ���ڿ� S[s..]�� �����Ǵ��� ���θ� ��ȯ�Ѵ�.
bool matchMemoized(int w, int s) {
	// �޸������̼�
	int& ret = cache[w][s];
	if (ret != -1) {
		return ret;
	}
	// W[w]�� S[s]�� ���� ������.
	if (s < S.size() && w < W.size() && (W[w] == '?' || W[w] == S[s])) {
		return ret = matchMemoized(w + 1, s + 1);
	}
	// ���̻� ������ �� ������ �� while���� �������� Ȯ���Ѵ�.
	// 2. ���� ���� �����ؼ� ���� ��� : ���ڿ��� ������� ��
	if (w == W.size()) {
		return ret = (s == S.size());
	}
	// 4. *�� ������ ���� ��� : *�� �� ���ڸ� �����ؾ� ���� ��� ȣ���ϸ鼭 Ȯ���Ѵ�.
	if (W[w] == '*') {
		if (matchMemoized(w + 1, s) || (s < S.size() && matchMemoized(w, s + 1))) {
			return ret = 1;
		}
	}
	// 3. �̿��� ��쿡�� ��� �������� �ʴ´�.
	return ret = 0;
}

int main() {
	ifstream cin("input.txt");

	cin >> testCase;

	while (testCase--) {
		cin >> W >> n;

		for (int i = 0; i < n; i++) {
			cin >> S;

			memset(cache, -1, sizeof(cache));

			/*if (match(W, S)) {
				v.push_back(S);
			}*/
			if (matchMemoized(0, 0)) {
				v.push_back(S);
			}
		}
		sort(v.begin(), v.end());
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << endl;
		}
		v.clear();
	}
}