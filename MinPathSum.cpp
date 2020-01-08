/*
* @Author: lwl
* @Date: 2020-01-08
* @Description: 最小的路径和
*/

#include <iostream>
#include <vector>

using namespace std;

class CMinPathSum {
	int pathSum1(vector<vector<int>>& matrix, int i, int j) {
		if (matrix.at(0).size() - 1 == j && matrix.size() - 1 == i) {
			return matrix.at(i).at(j);
		}
		else if (matrix.at(0).size() - 1 == j) {
			return matrix.at(i).at(j) + pathSum1(matrix, i + 1, j);
		}
		else if (matrix.size() - 1 == i) {
			return matrix.at(i).at(j) + pathSum1(matrix, i, j + 1);
		}
		else {
			int right = pathSum1(matrix, i, j + 1);
			int down = pathSum1(matrix, i + 1, j);
			return (right <= down ? right : down) + matrix.at(i).at(j);
		}
	}

	int pathSum2(vector<vector<int>>& matrix) {
		if (!matrix.empty()) {
			int row = matrix.size();
			int col = matrix.at(0).size();
			vector<vector<int>> dp(row, vector<int>(col, 0));
			dp.at(row - 1).at(col - 1) = matrix.at(row - 1).at(col - 1);
			for (int i = row - 2; i >= 0; --i) {
				dp.at(i).at(col - 1) = matrix.at(i).at(col - 1) + dp.at(i + 1).at(col - 1);
			}
			for (int j = col - 2; j >= 0; --j) {
				dp.at(row - 1).at(j) = matrix.at(row - 1).at(j) + dp.at(row - 1).at(j + 1);
			}
			for (int i = row - 2; i >= 0; --i) {
				for (int j = col - 2; j >= 0; --j) {
					dp.at(i).at(j) = matrix.at(i).at(j) + (dp.at(i + 1).at(j) >= dp.at(i).at(j + 1) ? dp.at(i).at(j + 1) : dp.at(i + 1).at(j));
				}
			}
			return dp.at(0).at(0);
		}
	}

public:
	void getminPathSum(vector<vector<int>>& matrix) {
		if (!matrix.empty()) {
			int res1 = pathSum1(matrix, 0, 0);
			int res2 = pathSum2(matrix);
			cout << "recur : " << res1 << endl;
			cout << "dp : " << res2 << endl;
		}
	}
};

int main() {
	vector<int> v1{ 1, 3, 5, 9 };
	vector<int> v2{ 8, 1, 3, 4 };
	vector<int> v3{ 5, 0, 6, 1 };
	vector<int> v4{ 8, 8, 4, 0 };
	vector<vector<int>> matrix{ v1, v2, v3, v4 };
	CMinPathSum minPathSum;
	minPathSum.getminPathSum(matrix);
	system("pause");
	return 0;
}