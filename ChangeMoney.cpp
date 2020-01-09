/*
* @Author: lwl
* @Date: 2020-01-09
* @Description: 递归和动态规划实现找零问题
*/

#include <iostream>
#include <vector>

using namespace std;

class CChangeMoney {
private:
	bool changeMoney1(vector<int>& arr, int aim, int sum, int i) {
		if (arr.size() == i) {
			return aim == sum;
		}
		return changeMoney1(arr, aim, sum, i + 1) || changeMoney1(arr, aim, sum + arr.at(i), i + 1);
	}

	bool changeMoney2(vector<int>& arr, int aim) {
		if (!arr.empty()) {
			int len = arr.size();
			int sum = 0;
			for (int i : arr) {
				sum += i;
			}
			if (sum < aim) {
				return false;
			}
			else if (sum == aim) {
				return true;
			}
			else {
				vector<vector<bool>> dp(len + 1, vector<bool>(sum + 1, false));
				dp.at(len).at(aim) = true;
				for (int i = len - 1; i >= 0; --i) {
					for (int j = 0; j <= sum; ++j) {
						int index = (j + arr.at(i)) > sum ? j : (j + arr.at(i));
						dp.at(i).at(j) = dp.at(i + 1).at(j) || dp.at(i + 1).at(index);
					}
				}
				return dp.at(0).at(0);
			}
		}
	}

public:
	void isArrHasAim(vector<int>& arr, int aim) {
		if (!arr.empty()) {
			bool res1 = changeMoney1(arr, aim, 0, 0);
			cout << "recur : " << (res1 ? "OK" : "false") << endl;
			bool res2 = changeMoney2(arr, aim);
			cout << "dp : " << (res2 ? "OK" : "false") << endl;
		}
	}
};

class CTest {
private:
	CChangeMoney changeMoney;

public:
	void runTest() {
		vector<int> arr{ 1, 4, 5, 6, 7, 8 };
		int aim = 12;
		changeMoney.isArrHasAim(arr, aim);
	}
};

int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}