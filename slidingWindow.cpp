/*
* @Author: lwl
* @Date: 2020-01-12
* @Description: 窗口内最大值最小值的更新
*/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class CSlidingWindow {
public:
	void printWindowMax(vector<int>& arr, int winSize) {
		cout << "max of window : " << endl;
		if (arr.empty() || winSize < 1) {
			return;
		}
		deque<int> max;
		int r = 0;
		while (r < arr.size()) {
			while (!max.empty() && arr.at(max.back()) <= arr.at(r)) {
				max.pop_back();
			}
			max.push_back(r);
			if (++r >= winSize) {
				cout << arr.at(max.front()) << " ";
			}
		}
		cout << endl << endl;
	}

	void printWindowMin(vector<int>& arr, int winSize) {
		cout << "min of window : " << endl;
		if (arr.empty()) {
			return;
		}
		deque<int> min;
		int r = 0;
		while (r < arr.size()) {
			while (!min.empty() && arr.at(min.back()) >= arr.at(r)) {
				min.pop_back();
			}
			min.push_back(r);
			if (++r >= winSize) {
				cout << arr.at(min.front()) << " ";
			}
		}
		cout << endl << endl;
	}

	void getWindowMax(vector<int>& arr, vector<int>& resMax, int winSize) {
		if (arr.empty() || winSize < 1) {
			return;
		}
		deque<int> max;
		int r = 0;
		int l = 0;
		while (r < arr.size()) {
			while (!max.empty() && arr.at(max.back()) <= arr.at(r)) {
				max.pop_back();
			}
			max.push_back(r);
			if (++r >= winSize) {
				resMax.push_back(arr.at(max.front()));
				if (max.front() == l++) {
					max.pop_front();
				}
			}
		}
	}

	void getWindowMin(vector<int>& arr, vector<int>& resMin, int winSize) {
		if (arr.empty() || winSize < 1) {
			return;
		}
		deque<int> min;
		int r = 0;
		int l = 0;
		while (r < arr.size()) {
			while (!min.empty() && arr.at(min.back()) >= arr.at(r)) {
				min.pop_back();
			}
			min.push_back(r);
			if (++r >= winSize) {
				resMin.push_back(arr.at(min.front()));
				if (min.front() == l++) {
					min.pop_front();
				}
			}
		}
	}
};

class CTest {
private:
	CSlidingWindow slidingWin;

public:
	void runTest() {
		vector<int> arr{ 3, 5, 2, 7, 9, 5, 3, 8, 0 };
		slidingWin.printWindowMax(arr, 3);
		slidingWin.printWindowMin(arr, 3);
		vector<int> resMin;
		slidingWin.getWindowMin(arr, resMin, 3);
		if (!resMin.empty()) {
			cout << "min of window of size 3 : " << endl;
			for (int i : resMin) {
				cout << i << " ";
			}
			cout << endl << endl;
		}
		vector<int> resMax;
		slidingWin.getWindowMax(arr, resMax, 3);
		if (!resMax.empty()) {
			cout << "max of window of size 3 : " << endl;
			for (int i : resMax) {
				cout << i << " ";
			}
			cout << endl << endl;
		}
	}
};

int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}