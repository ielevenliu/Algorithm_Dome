/*
*@Author: lwl
*@Date: 2019-12-18
*@Description: 这个题目是转圈打印矩阵
*              技巧：要建立矩阵的整体(宏观)意识，从整个矩阵出发一圈一圈打印，不局限于某一特定的矩阵
*/

#include <iostream>
#include <vector>

using namespace std;

class CSpiralPrintMat {
private:
	void printEdge(vector<vector<int> >& vec, int topR, int topC, int downR, int downC) {
		if (topR == downR) {
			while (topC <= downC) {
				cout << vec.at(topR).at(topC++) << " ";
			}
		}
		else if (topC == downC) {
			while (topR <= downR) {
				cout << vec.at(topR++).at(topC) << " ";
			}
		}
		else {
			int r = topR;
			int c = topC;
			while (topC < downC) {
				cout << vec.at(topR).at(topC++) << " ";
			}
			while (topR < downR) {
				cout << vec.at(topR++).at(downC) << " ";
			}
			while (c < downC) {
				cout << vec.at(downR).at(downC--) << " ";
			}
			while (r < downR) {
				cout << vec.at(downR--).at(c) << " ";
			}
		}
	}

public:
	void spiralPrintMat(vector<vector<int> >& vec) {
		int topR = 0;
		int topC = 0;
		int downR = vec.size() - 1;
		int downC = vec.at(0).size() - 1;
		while (topR <= downR && topC <= downC) {
			printEdge(vec, topR++, topC++, downR--, downC--);
		}
	}
};

class CTest {
private:
	vector<vector<int> > vec;

private:
	void generalMatrix() {
		vector<int> vec1, vec2, vec3, vec4;
		vec.push_back(vec1);
		vec.push_back(vec2);
		vec.push_back(vec3);
		vec.push_back(vec4);
		for (int i = 1; i <= 4; ++i) {
			vec.at(0).push_back(i);
			vec.at(1).push_back(i + 4);
			vec.at(2).push_back(i + 8);
			vec.at(3).push_back(i + 12);
		}
	}

public:
	void runTest() {
		generalMatrix();
		CSpiralPrintMat spiralPrint;
		spiralPrint.spiralPrintMat(vec);
	}
};

int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}