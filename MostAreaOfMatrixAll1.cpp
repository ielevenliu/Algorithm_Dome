/*
* @Author: lwl
* @Date: 2020-01-14
* @Description: 在一个'0'和'1'构成的matrix中，找到由'1'构成的矩形的最大面积
*/

#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

class CTest {
private:
	int process(vector<int>& h) {
		if (h.empty()) {
			return 0;
		}
		stack<list<int>*> index;
		int len = h.size();
		int i = 0;
		int max = 0;
		while (i < len) {
			while (!index.empty() && h.at(index.top()->front()) > h.at(i)) {
				list<int>* curIndex = index.top();
				index.pop();
				int preIndex = index.empty() ? -1 : index.top()->front();
				max = max < (i - preIndex - 1) * h.at(curIndex->front()) ?
					(i - preIndex - 1) * h.at(curIndex->front()) : max;
				delete curIndex;
			}
			if (index.empty() || h.at(index.top()->front()) != h.at(i)) {
				index.push(new list<int>(1, i++));
			}
			else {
				index.top()->push_front(i++);
			}
		}
		while (!index.empty()) {
			list<int>* curIndex = index.top();
			index.pop();
			int preIndex = index.empty() ? -1 : index.top()->front();
			max = max < (len - preIndex - 1) * h.at(curIndex->front()) ?
				(len - preIndex - 1) * h.at(curIndex->front()) : max;
			delete curIndex;
		}
		return max;
	}

	int getRectMaxArea(vector<vector<int>>& mat) {
		if (mat.empty()) {
			return 0;
		}
		int maxArea = 0;
		vector<int> h(mat.at(0).size(), 0);
		for (int row = 0; row < mat.size(); ++row) {
			for (int col = 0; col < mat.at(0).size(); ++col) {
				h.at(col) = mat.at(row).at(col) == 0 ? 0 : (h.at(col) + 1);
			}
			int area = process(h);
			maxArea = maxArea > area ? maxArea : area;
		}
		return maxArea;
	}

public:
	void runTest(vector<vector<int>>& mat) {
		int maxArea = getRectMaxArea(mat);
		cout << "all 1 max area of matrix : " << maxArea << endl << endl;
	}
};

int main() {
	vector<int> r1{ 1, 0, 1, 0, 1 };
	vector<int> r2{ 1, 1, 1, 1, 0 };
	vector<int> r3{ 1, 1, 1, 1, 1 };
	vector<vector<int>> matrix{ r1, r2, r3 };
	CTest test;
	test.runTest(matrix);
	system("pause");
	return 0;
}