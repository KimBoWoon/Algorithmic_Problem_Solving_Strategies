#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int testCase;

string reverse(string::iterator& iter) {
	char head = *iter;

	++iter;

	if (head == 'b' || head == 'w') {
		return string(1, head);
	}
	string upperLeft = reverse(iter);
	string upperRight = reverse(iter);
	string lowerLeft = reverse(iter);
	string lowerRight = reverse(iter);

	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main() {
	ifstream cin("input.txt");

	cin >> testCase;

	while (testCase--) {
		string quadtree;

		cin >> quadtree;

		string::iterator iter = quadtree.begin();

		string ans = reverse(iter);

		cout << ans << endl;
	}

	return 0;
}