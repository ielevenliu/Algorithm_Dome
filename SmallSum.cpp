/*
*@Author: lwl
*@Date: 2019-12-08
*@Description: small sum
*/

#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

// Small sum
class CSmallSum {
private:
	int sum;

private:
	void Merge(vector<int>&vec, int left, int mid, int right) {
		int lTmp = left;
		int rStart = mid + 1;
		vector<int> vecTmp;
		while (lTmp <= mid && rStart <= right) {
			sum += vec.at(lTmp) < vec.at(rStart) ? vec.at(lTmp) * (right - rStart + 1) : 0;
			vecTmp.push_back(vec.at(lTmp) < vec.at(rStart) ? vec.at(lTmp++) : vec.at(rStart++));
		}
		while (lTmp <= mid) {
			vecTmp.push_back(vec.at(lTmp++));
		}
		while (rStart <= right) {
			vecTmp.push_back(vec.at(rStart++));
		}
		int i = 0;
		while (left <= right) {
			vec.at(left++) = vecTmp.at(i++);
		}
	}

	void SmallSum(vector<int>& vec, int left, int right) {
		if (left == right) {
			return;
		}
		int mid = left + ((right - left) >> 1);
		SmallSum(vec, left, mid);
		SmallSum(vec, mid + 1, right);
		Merge(vec, left, mid, right);
	}

public:
	CSmallSum() {
		this->sum = 0;
	}

	int SmallSumInterface(vector<int>& vec) {
		if (vec.size() > 0) {
			SmallSum(vec, 0, vec.size() - 1);
		}
		return this->sum;
	}
};

// comparator
class CComparator : public CSmallSum {
private:
	int compareTime;
	int maxSize;
	int maxValue;
	int smallSum;

private:
	vector<int> GenerateArr() {
		srand(time(0));
		vector<int> tmp;
		while (maxSize--) {
			tmp.push_back(rand() % maxValue);
		}
		return tmp;
	}

	int ComparatorMethod(vector<int>& vecCopy) {
		int len = vecCopy.size();
		for (int i = 1; i < len; i++) {
			for (int j = 0; j < i; j++) {
				this->smallSum += vecCopy.at(j) < vecCopy.at(i) ? vecCopy.at(j) : 0;
			}
		}
		return this->smallSum;
	}

public:
	CComparator(int maxVal, int size, int time) :
		compareTime(time),
		maxSize(size),
		maxValue(maxVal) 
	{ this->smallSum = 0; }

	void RunComparator() {
		vector<int> vec = GenerateArr();
		vector<int> vecCopy = vec;
		if (vec.size() <= 0) {
			cout << "Input must be greater than zero!" << endl;
			return;
		}
		ComparatorMethod(vecCopy) == SmallSumInterface(vec) ? 
			cout << "OK" << endl : cout << "false" << endl;
	}
};

int main() {
	CComparator comparator(100, 100, 1000);
	comparator.RunComparator();
	system("pause");
	return 0;
}
