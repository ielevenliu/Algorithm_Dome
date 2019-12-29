/*
* @Author: lwl
* @Date: 2019-12-29
* @Description: 折纸问题
*/

/*
*                1-d
*             /       \
*           2-d       2-u
*           /  \     /  \
*         3-d  3-u 3-d  3-u
*/

#include <iostream>
#include <vector>

using namespace std;

class CPaperFolding {
	void printProcess(int i, int n, bool b) {
		if (i > n) {
			return;
		}
		printProcess(i + 1, n, true);
		cout << (b == true ? "down" : "up") << " ";
		printProcess(i + 1, n, false);
	}
public:
	// 对应上面
	void paperFold1(int n) {
		printProcess(1, n, true);
	}

	vector<bool> paperFold2(int n) {
		vector<bool> resQ;
		if (n <= 0) {
			return resQ;
		}
		if (n == 1) {
			resQ.push_back(false);
			return resQ;
		}
		vector<bool> tmp = paperFold2(n - 1);
		size_t len = tmp.size();
		size_t cur = 0;
		while (cur != len) {
			resQ.push_back(tmp.at(cur++));
		}
		resQ.push_back(false);
		while (cur--) {
			resQ.push_back(!tmp.at(cur));
		}
		return resQ;
	}
};

int main() {
	int n = 4;
	CPaperFolding cPaperFold;
	// 方法一
	cout << "=== n paper folding order BiTree print: ===" << endl;
	cPaperFold.paperFold1(n);
	cout << endl;

	// 方法二 
	vector<bool> res = cPaperFold.paperFold2(n);
	cout << "=== n paper folding recursive print: ===" << endl;
	for (bool b : res) {
		cout << (b == false ? "down" : "up") << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}