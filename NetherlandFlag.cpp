/*
*@Author: lwl
*@Date:   2019-12-08
*@Description: 荷兰国旗问题
*/

#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

class CNetherlandsFlag {
private:
	int maxValue;
	int maxSize;
	int target;
	vector<int> vec;

public:
	CNetherlandsFlag(int maxVal, int size, int num) :
		maxValue(maxVal),
		maxSize(size),
		target(num)
	{ }

	void GenerateArr() {
		srand(time(0));
		while (maxSize--) {
			vec.push_back(rand() % maxValue);
		}
	}

	void Swap(int n1, int n2) {
		int tmp = vec.at(n1);
		vec.at(n1) = vec.at(n2);
		vec.at(n2) = tmp;
	}

	void PrintData() {
		if (vec.size() == 0) {
			return;
		}
		vector<int>::iterator it = vec.begin();
		while (it != vec.end()) {
			cout << *it++ << " ";
		}
	}

	void NetherlandsFlag() {
		int left = -1;
		int right = vec.size();
		int index = 0;
		while (index < right) {
			if (vec.at(index) < target) {
				Swap(++left, index++);
			}
			else if (vec.at(index) < target) {
				Swap(--right, index);
			}
			else {
				index++;
			}
		}
	}

	void NetherlandsFlagInterface() {
		GenerateArr();
		PrintData();
		cout << endl;
		NetherlandsFlag();
		PrintData();
		cout << endl;
	}
};

int main() {
	CNetherlandsFlag netherlands(100, 10, 50);
	netherlands.NetherlandsFlagInterface();
	system("pause");
	return 0;
}