/*
*@Author: lwl(参考牛客左神Java代码)
*@Date: 2019-12-07
*@Description: C++ 实现归并排序 & 快速排序 & 堆排序
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <time.h>
using namespace std;

// Sorting algorithm
class CSortingAlgorithm2 {
private:
	void Merge(vector<int>& vec, int left, int mid, int right) {
		vector<int> tmp;
		int midTmp = mid + 1;
		int leftTmp = left;
		while (leftTmp <= mid && midTmp <= right) {
			tmp.push_back(vec.at(leftTmp) < vec.at(midTmp) ? vec.at(leftTmp++) : vec.at(midTmp++));
		}
		while (leftTmp <= mid) {
			tmp.push_back(vec.at(leftTmp++));
		}
		while (midTmp <= right) {
			tmp.push_back(vec.at(midTmp++));
		}
		int i = 0;
		while (left <= right) {
			vec.at(left++) = tmp.at(i++);
		}
	}

	void MergeSorting(vector<int>& vec, int left, int right) {
		if (left == right) {
			return;
		}
		int mid = left + ((right - left) >> 1);
		MergeSorting(vec, left, mid);
		MergeSorting(vec, mid + 1, right);
		Merge(vec, left, mid, right);
	}

	void Swap(vector<int>& vec, int n1, int n2) {
		int tmp = vec.at(n1);
		vec.at(n1) = vec.at(n2);
		vec.at(n2) = tmp;
	}

	void QuickSorting(vector<int>& vec, int left, int right) {
		if (left < right) {
			int randIndex = (rand() % (right - left + 1)) + left;
			Swap(vec, right, randIndex);
			int index = left;
			int small = index - 1;
			int large = right;
			while (index < large) {
				if (vec.at(index) < vec.at(right)) {
					Swap(vec, ++small, index++);
				}
				else if (vec.at(index) == vec.at(right)) {
					index++;
				}
				else {
					Swap(vec, --large, index);
				}
			}
			Swap(vec, index, right);
			QuickSorting(vec, left, small);
			QuickSorting(vec, large + 1, right);
		}
	}

	void HeapInsert(vector<int>& vec, int index) {
		while (vec.at(index) > vec.at((index - 1) / 2)) {
			Swap(vec, index, (index - 1) / 2);
			index = (index - 1) / 2;
		}
	}

	void Heapify(vector<int>& vec, int index, int size) {
		int left = index * 2 + 1;
		while (left < size) {
			int largest = (left + 1) < size && vec.at(left + 1) > vec.at(left) ? (left + 1) : left;
			largest = vec.at(index) > vec.at(largest) ? index : largest;
			if (largest == index) {
				break;
			}
			Swap(vec, index, largest);
			index = largest;
			left = index * 2 + 1;
		}
	}

	void HeapSorting(vector<int>& vec) {
		for (size_t i = 0; i < vec.size(); i++) {
			HeapInsert(vec, i);
		}
		int size = vec.size();
		Swap(vec, 0, --size);
		while (size > 0) {
			Heapify(vec, 0, size);
			Swap(vec, 0, --size);
		}
	}

public:
	void MergeSortingInterface(vector<int>& vec) {
		if (vec.size() <= 1) {
			return;
		}
		MergeSorting(vec, 0, vec.size() - 1);
	}

	void QuickSortingInterface(vector<int>& vec) {
		if (vec.size() > 1) {
			QuickSorting(vec, 0, vec.size() - 1);
		}
	}

	void HeapSortingInterface(vector<int>& vec) {
		if (vec.size() > 1) {
			HeapSorting(vec);
		}
	}
};

// comparator
class CComparator : public CSortingAlgorithm2 {
private:
	int maxValue;
	int maxSize;
	int compareTime;

public:
	CComparator(int maxVal, int size, int time) :
		maxValue(maxVal),
		maxSize(size),
		compareTime(time)
	{ }

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

	void RunComparator() {
		srand(time(0));
		while (compareTime--) {
			vector<int> vec = GenerateArr();
			vector<int> vecCopy = vec;
			ComparatorMethod(vecCopy);
			MergeSortingInterface(vec); // Test marge sort
			//QuickSortingInterface(vec); // Test quicksort
			//HeapSortingInterface(vec);  // Test heap sort
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