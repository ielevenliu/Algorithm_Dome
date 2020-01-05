/*
* @Author: lwl
* @Date: 2020-01-05
* @Description: 一块金条切成两半，是需要花费和长度数值一样的铜板的，一群人想整分整块金条，怎么分最省铜板？
*               这是一个哈夫曼编码问题
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class CLessMoney {
private:
	priority_queue<int, vector<int>, greater<int>> pQ;

private:
	void generalHead(vector<int>& costs) {
		for (int cost : costs) {
			pQ.push(cost);
		}
	}

	void printHead() {
		while (!pQ.empty()) {
			cout << pQ.top() << " ";
			pQ.pop();
		}
	}

public:
	int lessMoney(vector<int>& costs) {
		generalHead(costs);
		int sum = 0;
		int preSum = 0;
		while (pQ.size() >= 2) {
			sum += pQ.top();
			pQ.pop();
			sum += pQ.top();
			pQ.pop();
			pQ.push(sum - preSum);
			preSum = sum;
		}
		return sum;
	}
};

class CTest {
private:
	CLessMoney money;

public:
	void runTest(vector<int>& costs) {
		cout << "less money is:  " << money.lessMoney(costs) << endl;
	}
};

int main() {
	vector<int> costs{ 10, 20, 30, 60 };
	CTest test;
	test.runTest(costs);
	system("pause");
	return 0;
}