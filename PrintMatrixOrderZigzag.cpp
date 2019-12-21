/*
* @Author: lwl
* @Date: 2019-12-21
* @Description: “之”字打印矩阵
*/

#include <iostream>
#include <vector>

using namespace std;

class CZigzagPrintMatrix {
private:
	void print(vector<vector<int> >& mat, int aR, int aC, int bR, int bC, bool upToDown) {
		if (upToDown == true) {
			while (aR <= bR) {
				cout << mat.at(aR++).at(aC--) << " ";
			}
		}
		else if (upToDown == false) {
			while (bC <= aC) {
				cout << mat.at(bR--).at(bC++) << " ";
			}
		}
	}

public:
	void zigzagPrintMatrix(vector<vector<int> >& mat) {
		int aR = 0;
		int aC = 0;
		int bR = 0;
		int bC = 0;
		int r = mat.size() - 1;
		int c = mat.at(0).size() - 1;
		bool upToDown = false;
		while (aR <= r) {
			print(mat, aR, aC, bR, bC, upToDown);
			aR = aC == c ? (aR + 1) : aR; // 行的改变要放在列的前面以免受列改变的影响
			aC = aC == c ? aC : (aC + 1);
			bC = bR == r ? (bC + 1) : bC; // 列的改变要放在行的前面以免受行改变的影响
			bR = bR == r ? bR : (bR + 1);
			upToDown = !upToDown;
		}
	}
};

class CComparator {
private:
	vector<vector<int> > mat;
	CZigzagPrintMatrix zigzagPrintMat;

private:
	void generalMatrix() {
		vector<int> r1, r2, r3;
		for (int i = 0; i < 4; ++i) {
			r1.push_back(i + 1);
			r2.push_back(i + 5);
			r3.push_back(i + 9);
		}
		mat.push_back(r1);
		mat.push_back(r2);
		mat.push_back(r3);
	}

	void printMatrix() {
		int r = mat.size();
		int c = mat.at(0).size();
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				cout << mat.at(i).at(j) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

public:
	void runComparator() {
		generalMatrix();
		printMatrix();
		zigzagPrintMat.zigzagPrintMatrix(mat);
	}
};

int main() {
	CComparator comparator;
	comparator.runComparator();
	system("pause");
	return 0;
}