/*
* @Author: lwl
* @Date: 2020-01-05
* @Description: 一个数据流中，随时可以取得中位数
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <time.h>

using namespace std;

class CMedian {
private:
	priority_queue<int, vector<int>, less<int>> bigHeap;
	priority_queue<int, vector<int>, greater<int>> smallHeap;

private:
	void modifyHeap() {
		if ((bigHeap.size() > smallHeap.size()
			? (bigHeap.size() - smallHeap.size()) : (smallHeap.size() - bigHeap.size())) == 2) {
			if (bigHeap.size() > smallHeap.size()) {
				smallHeap.push(bigHeap.top());
				bigHeap.pop();
			}
			else {
				bigHeap.push(smallHeap.top());
				smallHeap.pop();
			}
 		}
	}

public:
	void addValue(int value) {
		if (bigHeap.empty()) {
			bigHeap.push(value);
			return;
		}
		if (bigHeap.top() >= value) {
			bigHeap.push(value);
		}
		else {
			if (smallHeap.empty()) {
				smallHeap.push(value);
				return;
			}
			if (smallHeap.top() > value) {
				bigHeap.push(value);
			}
			else {
				smallHeap.push(value);
			}
		}
		modifyHeap();
	}

	int getMedian() {
		if (bigHeap.size() + smallHeap.size() == 0) {
			return 0;
		}
		if (bigHeap.size() == smallHeap.size()) {
			return (bigHeap.top() + smallHeap.top()) / 2;
		}
		else if (bigHeap.size() > smallHeap.size()) {
			return bigHeap.top();
		}
		else {
			return smallHeap.top();
		}
	}
};

class CTest {
private:
	int maxVal;
	int times;
	CMedian median;

private:
	int getArrMedian(vector<int>& arr) {
		int med = 0;
		size_t len = arr.size();
		if (len > 0) {
			sort(arr.begin(), arr.end());
			med = len % 2 == 0 ? ((arr.at(len / 2 - 1) + arr.at(len / 2)) / 2) : arr.at(len / 2);
		}
		return med;
	}

public:
	CTest(int maxValue, int times) :
		maxVal(maxValue),
		times(times)
	{
		srand(time(0));
	}

	void runTest() {
		bool success = true;
		int cur = 0;
		vector<int> arr;
		while (times--) {
			cur = rand() % maxVal;
			arr.push_back(cur);
			int testRes = getArrMedian(arr);
			median.addValue(cur);
			int res = median.getMedian();
			if (testRes != res) {
				res = res;
			}
			success = success && (testRes == res ? true : false);
		}
		cout << (success == true ? "OK" : "false") << endl;
	}
};

int main() {
	int maxValue = 100;
	int times = 10000;
	CTest test(maxValue, times);
	test.runTest();
	system("pause");
	return 0;
}