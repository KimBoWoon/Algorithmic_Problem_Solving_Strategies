#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int testCase;

void normalize(vector<int>& num) {
	num.push_back(0);
	// �ڸ��� �ø��� ó���Ѵ�
	for (int i = 0; i < num.size(); i++) {
		if (num[i] < 0) {
			int borrow = (abs(num[i]) + 9) / 10;
			num[i + 1] -= borrow;
			num[i] += borrow * 10;
		}
		else if (num[i] > 0) {
			num[i + 1] += num[i] / 10;
			num[i] %= 10;
		}
	}
	if (num.back() == 0) num.pop_back();
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			c[i + j] += a[i] * b[j];
		}
	}
	/*normalize(c);*/
	return c;
}

void addTo(vector<int>& a, const vector<int>& b, int k) {
	a.resize(max(a.size(), b.size() + k));
	for (int i = 0; i < b.size(); i++) {
		a[i + k] += b[i];
	}
	/*normalize(a);*/
}

void subFrom(vector<int>& a, const vector<int>& b) {
	a.resize(max(a.size(), b.size()) + 1);
	for (int i = 0; i < b.size(); i++) {
		a[i] -= b[i];
	}
	/*normalize(a);*/
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();
	// a �� b ���� ª�� ��� ���� �ٲ۴�
	if (an < bn) {
		return karatsuba(b, a);
	}
	// ���� ���: a �� b �� ��� �ִ� ���
	if (an == 0 || bn == 0) {
		return vector<int>();
	}
	// ���� ���: a �� ���� ª�� ��� O(n^2) �������� �����Ѵ�.
	if (an <= 50) {
		return multiply(a, b);
	}

	int half = an / 2;
	// a �� b �� �ؿ��� half �ڸ��� �������� �и��Ѵ�
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
	// z2 = a1 * b1
	vector<int> z2 = karatsuba(a1, b1);
	// z0 = a0 * b0
	vector<int> z0 = karatsuba(a0, b0);
	// a0 = a0 + a1;
	addTo(a0, a1, 0);
	// b0 = b0 + b1
	addTo(b0, b1, 0);
	// z1 = (a0 * b0) - z0 - z2;
	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);
	// ret = z0 + z1 * 10^half + z2 * 10^(half*2)
	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);
	return ret;
}

//string toString(vector<int> a) {
//	string ret;
//	while (a.size() > 1 && a.back() == 0) a.pop_back();
//	for (int i = 0; i < a.size(); i++)
//		ret += char('0' + a[a.size() - 1 - i]);
//	return ret;
//}
//
//vector<int> fromString(const string& s) {
//	vector<int> ret;
//	for (int i = 0; i < s.size(); i++)
//		ret.push_back(s[i] - '0');
//	reverse(ret.begin(), ret.end());
//	return ret;
//}

int hugs(const string& members, const string& fans) {
	int n = members.size(), m = fans.size();
	vector<int> a(n), b(m);

	for (int i = 0; i < n; i++) {
		a[i] = (members[i] == 'M');
	}
	for (int i = 0; i < m; i++) {
		b[m - i - 1] = (fans[i] == 'M');
	}

	// karatsuba �˰��򿡼� �ڸ� �ø��� �����Ѵ�.
	vector<int> c = karatsuba(a, b);
	int allHugs = 0;
	for (int i = n - 1; i < m; i++) {
		if (c[i] == 0) {
			++allHugs;
		}
	}

	return allHugs;
}

int main() {
	ifstream cin("input.txt");

	cin >> testCase;

	while (testCase--) {
		string x, y;

		cin >> x >> y;

		cout << hugs(x, y) << endl;
	}
}