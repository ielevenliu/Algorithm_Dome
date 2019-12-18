/*
*@Author: lwl
*@Date: 2019-12-16
*@Description: 实现了二分查找(含对数器)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

class CBinarySearch {

private:
	void vecSort(vector<int>& vec) {
		sort(vec.begin(), vec.end());
	}
	
public:
	void binarySearch(vector<int>& arrA, vector<int>& arrB, vector<int>& res) {
		if (arrA.size() != 0 && arrB.size() != 0) {
			vecSort(arrA);
			for (int i : arrB) {
				int left = 0;
				int right = arrA.size() - 1;
				while (left <= right) {
					int mid = left + ((right - left) >> 1);
					if (arrA.at(mid) == i) {
						res.push_back(i);
						break;
					}
					else if (arrA.at(mid) > i) {
						right = mid - 1;
					}
					else {
						left = mid + 1;
					}
				}
			}
		}
	}
};

class CComparator : public CBinarySearch {
private:
	int max;
	int testTime;
	int size;

	void generalRandomArr(vector<int>& vec) {
		for (int i = 0; i < size; ++i) {
			vec.at(i) = rand() % (max + 1);
		}
	}

	void printArr(vector<int>& vec) {
		for (int i : vec) {
			cout << i << " ";
		}
		cout << endl;
	}

	void rightMethod(vector<int>& copyA, vector<int>& copyB, vector<int>& copyRes) {
		if (copyA.size() != 0 && copyB.size() != 0) {
			for (int i : copyB) {
				for (int j : copyA) {
					if (i == j) {
						copyRes.push_back(j);
						break;
					}
				}
			}
		}
	}

	bool isEqual(vector<int>& res, vector<int>& copyRes) {
		return equal(res.begin(), res.end(), copyRes.begin(), copyRes.end());
	}

public:
	CComparator(int valueMax, int testTime, int valueSize) :
		max(valueMax),
		testTime(testTime),
		size(valueSize)
	{ srand(time(0)); }

	void RunComparator() {
		bool success = true;
		while (testTime--) {
			vector<int> arrA(size);
			vector<int> arrB(size);
			generalRandomArr(arrA);
			generalRandomArr(arrB);
			vector<int> copyA = arrA;
			vector<int> copyB = arrB;
			vector<int> res;
			vector<int> copyRes;
			binarySearch(arrA, arrB, res);
			rightMethod(copyA, copyB, copyRes);
			success = success && isEqual(res, copyRes);
		}
		cout << (success ? "nice" : "false") << endl;
	}
};

int main() {
	int max = 100;
	int time = 50000;
	int size = 100;
	CComparator comparator(max, time, size);
	comparator.RunComparator();
	system("pause");
	return 0;
}