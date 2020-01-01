/*
* @Author: lwl
* @Date: 2020-01-01
* @Description: µ∫Œ Ã‚
*/

#include <iostream>
#include <vector>

using namespace std;

class CNumOfIslands {
private:
	void infect(vector<vector<int>>& mat, int x, int y) {
		if (x < 0 || x >= mat.at(0).size() || y < 0 || y >= mat.size() || 
			mat.at(y).at(x) != 1) {
			return;
		}
		mat.at(y).at(x) = 2;
		infect(mat, x, y - 1);
		infect(mat, x, y + 1);
		infect(mat, x - 1, y);
		infect(mat, x + 1, y);
	}

public:
	int numOfislands(vector<vector<int>>& mat) {
		if (mat.size() == 0 || mat.at(0).size() == 0) {
			return 0;
		}
		int yVal = mat.size() - 1;
		int xVal = mat.at(0).size() - 1;
		int islandsNum = 0;
		for (int i = 0; i <= yVal; ++i) {
			for (int j = 0; j <= xVal; ++j) {
				if (mat.at(i).at(j) == 1) {
					++islandsNum;
					infect(mat, j, i);
				}
			}
		}
		return islandsNum;
	}
};

class CTest {
private:
	CNumOfIslands islands;

public:
	void runTest(vector<vector<int>>& mat) {
		cout << "Number-Of-Islands: " << islands.numOfislands(mat) << endl;
	}
};

int main() {
	vector<int> vec1{ 0, 0, 1, 0, 1, 0 };
	vector<int> vec2{ 1, 1, 1, 0, 1, 0 };
	vector<int> vec3{ 1, 0, 0, 1, 0, 0 };
	vector<int> vec4{ 0, 0, 0, 0, 0, 0 };
	vector<vector<int>> mat;
	mat.push_back(vec1);
	mat.push_back(vec2);
	mat.push_back(vec3);
	mat.push_back(vec4);
	CTest test;
	test.runTest(mat);
	system("pause");
	return 0;
}