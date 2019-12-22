/*
* @Author: lwl
* @Date: 2019-12-22
* @Description: 给定一个有N*M的整型矩阵matrix和一个整数K，matrix的每一行和每一 列都是排好序的。
*               实现一个函数，判断K是否在matrix中，时间复杂度为O(N+M)，额外空间复杂度为O(1)
*/

#include <iostream>
#include <vector>

using namespace std;

class CFindNum {
public:
	bool isComtainsUpToDown(vector<vector<int> >& mat, int k) {
		int r = 0;
		int c = mat.at(0).size() - 1;
		while (r <= (mat.size() - 1) && c >= 0) {
			if (mat.at(r).at(c) > k) {
				c--;
			}
			else if (mat.at(r).at(c) < k) {
				r++;
			}
			else {
				return true;
			}
		}
		return false;
	}
};

class CComparator {
private:
	int k;
	vector<vector<int> > mat;
	CFindNum findNum;

private:
	void generalMatrix() {
		int arr1[4] = { 0, 1, 2, 5 };
		int arr2[4] = { 2, 3, 4, 7 };
		int arr3[4] = { 4, 4, 4, 8 };
		int arr4[4] = { 6, 7, 7, 9 };
		vector<int> r1(arr1, arr1 + 4);
		vector<int> r2(arr2, arr2 + 4);
		vector<int> r3(arr3, arr3 + 4);
		vector<int> r4(arr4, arr4 + 4);
		mat.push_back(r1);
		mat.push_back(r2);
		mat.push_back(r3);
		mat.push_back(r4);
	}

public:
	CComparator(int num) :
		k(num)
	{ }

	void runComparator() {
		generalMatrix();
		bool res = findNum.isComtainsUpToDown(mat, k);
		cout << (res ? "is contains" : "no contains") << endl;
	}
};

int main() {
	int k = 6;
	CComparator comparator(k);
	comparator.runComparator();
	system("pause");
	return 0;
}