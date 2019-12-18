/*
*@Author: lwl
*@Date:   2019-12-07
*@Description: C++ 实现冒泡排序 & 选择排序 & 插入排序
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

// Sorting algorithm
class CSortingAlgorithm1 {
private:
	void Swap(vector<int>& vec, int i, int j) {
		vec.at(i) = vec.at(i) ^ vec.at(j);
		vec.at(j) = vec.at(i) ^ vec.at(j);
		vec.at(i) = vec.at(i) ^ vec.at(j);
	}

public:
	void BubbleSortingInterface(vector<int>& vec) {
		int len = vec.size();
		if (len <= 1) {
			return;
		}
		for (int i = len - 1; i > 0; --i) {
			for (int j = 0; j < i; ++j) {
				if (vec.at(j) > vec.at(j + 1)) {
					Swap(vec, j, j + 1);
				}
			}
		}
	}

	void SelectSortingInterface(vector<int>& vec) {
		int len = vec.size();
		if (len <= 0) {
			return;
		}
		for (int i = 0; i < len; ++i) {
			int min = i;
			for (int j = i + 1; j < len; ++j) {
				if (vec.at(min) > vec.at(j)) {
					min = j;
				}
			}
			if (min != i) {
				Swap(vec, i, min);
			}
		}
	}

	void InsertSortingInterface(vector<int>& vec) {
		int len = vec.size();
		if (len <= 1) {
			return;
		}
		for (int i = 1; i < len; ++i) {
			for (int j = i; j > 0; --j) {
				if (vec.at(j) < vec.at(j - 1)) {
					Swap(vec, j, j - 1);
				}
			}
		}
	}
};

// comparator
class CComparator : public CSortingAlgorithm1 {
private:
	int maxValue;
	int maxSize;
	int compareTime;

private:
	vector<int> GenerateArr() {
		vector<int> vec;
		for (int i = 0; i < this->maxSize; i++) {
			vec.push_back(rand() % this->maxValue);
		}
		return vec;
	}

	bool IsEqual(vector<int>& vec1, vector<int>& vec2) {
		if (vec1.size() != vec2.size()) {
			return false;
		}
		vector<int>::iterator it1 = vec1.begin();
		vector<int>::iterator it2 = vec2.begin();
		while (it1 != vec1.end()) {
			if (*it1++ != *it2++) {
				return false;
			}
		}
		return true;
	}

	void ComparatorMethod(vector<int>& vec) {
		sort<vector<int>::iterator>(vec.begin(), vec.end());
	}

	void PrintData(vector<int>& vec) {
		if (vec.size() == 0) {
			return;
		}
		vector<int>::iterator it = vec.begin();
		while (it != vec.end()) {
			cout << *it++ << " ";
		}
		cout << endl;
	}

public:
	CComparator(int maxVal, int size, int time) :
		maxValue(maxVal),
		maxSize(size),
		compareTime(time)
	{ }

	void RunComparator() {
		srand(time(0));
		while (compareTime--) {
			vector<int> vec = GenerateArr();
			vector<int> vecCopy = vec;
			ComparatorMethod(vecCopy);
			BubbleSortingInterface(vec);  // Test bubble sort
			//SelectSortingInterface(vec);  // Test select sort
			//InsertSortingInterface(vec);  // Test insert sort
			if (!IsEqual(vec, vecCopy)) {
				throw string("false!");
			}
		}
		cout << "OK" << endl;
	}
};

int main() {
	CComparator comparator(100, 100, 1000);
	comparator.RunComparator();
	system("pause");
	return 0;
}