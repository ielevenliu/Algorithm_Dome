/*
* @Author: lwl
* @Date: 2020-01-15
* @Description: 烽火对数量问题(一个烽火台可以向左或向右看到不比它高的烽火台，问可以构成多少烽火对)
*               基本思路是矮的找高的，高的不找矮的
*               高度没有重复的情况：先找到最高和次高，除了最高和次高其余的都可以找到两对组合，加上最高和次高这一对，公式为 (n - 2) * 2 + 1
*               高度有重复的情况：先找到第一个最高的烽火台的索引，利用单调栈找到找其他烽火台左右两边最近比它们高的烽火台，弹出结算
*/

#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

class CBeaconTowerPair {
private:
	int getNextIndex(int curIndex, int len) {
		return curIndex == (len - 1) ? 0 : (curIndex + 1);
	}

	int getArrangeNum(int n) {
		return n * (n - 1) / 2;
	}

public:
	int getBeaconTowerPairNum(vector<int>& arr) {
		if (arr.size() <= 1) {
			return arr.size();
		}
		return 2 * arr.size() - 3;
	}

	int getBeaconTowerPairNum(vector<int>& arr, bool isRepeat) {
		int len = arr.size();
		if (len <= 1) {
			return len;
		}
		if (isRepeat == false) {
			return getBeaconTowerPairNum(arr);
		}
		int maxIndex = 0;
		for (int i = 1; i < len; ++i) {
			maxIndex = arr.at(maxIndex) >= arr.at(i) ? maxIndex : i;
		}
		stack<list<int>*> index;
		index.push(new list<int>(1, maxIndex));
		int curIndex = getNextIndex(maxIndex, len);
		int pairNum = 0;
		while (curIndex != maxIndex) {
			while (arr.at(index.top()->front()) < arr.at(curIndex)) {
				list<int>* curList = index.top();
				index.pop();
				pairNum += getArrangeNum(curList->size()) + curList->size() * 2;
				delete curList;
			}
			if (arr.at(index.top()->front()) != arr.at(curIndex)) {
				index.push(new list<int>(1, curIndex));
			}
			else {
				index.top()->push_front(curIndex);
			}
			curIndex = getNextIndex(curIndex, len);
		}
		while (!index.empty()) {
			list<int>* curList = index.top();
			index.pop();
			pairNum += getArrangeNum(curList->size());
			pairNum += index.empty() ?
				0 : (index.size() >= 2 || index.top()->size() >= 2 ? curList->size() * 2 : curList->size());
			delete curList;
		}
		return pairNum;
	}
};

class CTest {
private:
	CBeaconTowerPair beaconTowerPair;

public:
	void runTest() {
		vector<int> arr1{ 3, 2, 6, 5, 4, 7 };
		int pairNum1 = beaconTowerPair.getBeaconTowerPairNum(arr1);
		cout << "pair number of arr1(no repeat) is : " << pairNum1 << endl << endl;

		vector<int> arr2{ 3, 2, 2, 6, 5, 4, 4, 4, 7 };
		int pairNum2 = beaconTowerPair.getBeaconTowerPairNum(arr2, true);
		cout << "pair number of arr2(has repeat) is : " << pairNum2 << endl << endl;
	}
};

int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}