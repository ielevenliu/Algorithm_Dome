/*
* @Author: lwl
* @Date: 2020-01-05
* @Description: 一块金条切成两半，是需要花费和长度数值一样的铜板的，一群人想整分整块金条，怎么分最省铜板？
*               含对数器版本
*/

#include <iostream>
#include <queue>
#include <vector>
#include <time.h>

using namespace std;

class CLessMoney {
private:
	void swap(vector<int>& heap, size_t index1, size_t index2) {
		int tmp = heap.at(index1);
		heap.at(index1) = heap.at(index2);
		heap.at(index2) = tmp;
	}

	vector<int>* generalHeap(vector<int>& costs) {
		vector<int>* heap = new vector<int>;
		for (int cost : costs) {
			heapInsert(*heap, cost);
		}
		return heap;
	}

	void heapInsert(vector<int>& heap, int cost) {
		int size = heap.size();
		heap.push_back(cost);
		while (heap.at((size - 1) / 2) > heap.at(size)) {
			swap(heap, (size - 1) / 2, size);
			size = (size - 1) / 2;
		}
	}

	int heapify(vector<int>& heap) {
		int tmp = heap.front();
		int index = heap.size() - 1;
		swap(heap, 0, index);
		heap.pop_back();
		int size = heap.size() - 1;
		index = 0;
		int left = index * 2 + 1;
		while (left <= size) {
			left = (left + 1) <= size && heap.at(left) > heap.at(left + 1) ? left + 1 : left;
			left = heap.at(index) > heap.at(left) ? left : index;
			if (index == left) {
				break;
			}
			swap(heap, index, left);
			index = left;
			left = index * 2 + 1;
		}
		return tmp;
	}

public:
	int lessMoney(vector<int>& costs) {
		vector<int>* heap = generalHeap(costs);
		int sum = 0;
		int cur = 0;
		while ((*heap).size() >= 2) {
			cur = heapify(*heap) + heapify(*heap);
			sum += cur;
			heapInsert(*heap, cur);
		}
		delete heap;
		return sum;
	}
};

class CTest {
private:
	unsigned int maxSize;
	unsigned int maxVal;
	unsigned int times;
	CLessMoney lessCost;

private:
	priority_queue<int, vector<int>, greater<int>>* generalHeap(vector<int>& costs) {
		auto priorityQ = new priority_queue<int, vector<int>, greater<int>>;
		if (!costs.empty()) {
			for (int i : costs) {
				(*priorityQ).push(i);
			}
		}
		return priorityQ;
	}

	int rightMethod(priority_queue<int, vector<int>, greater<int>>& priorityQ) {
		int totalCost = 0;
		int cur = 0;
		while (priorityQ.size() >= 2) {
			cur += priorityQ.top();
			priorityQ.pop();
			cur += priorityQ.top();
			priorityQ.pop();
			totalCost += cur;
			priorityQ.push(cur);
			cur = 0;
		}
		return totalCost;
	}

	vector<int>* generalRandomArr() {
		vector<int>* costs = new vector<int>;
		unsigned int size = rand() % maxSize;
		while (size--) {
			(*costs).push_back(rand() % maxVal);
		}
		return costs;
	}

public:
	CTest(unsigned int maxSize, unsigned int maxValue, unsigned int times) :
		maxSize(maxSize),
		maxVal(maxValue),
		times(times)
	{ 
		srand(time(0)); 
	}

	void runTest() {
		bool success = true;
		while (times--) {
			vector<int>* costs = generalRandomArr();
			vector<int> copyCosts = (*costs);
			auto priorityQ = generalHeap(*costs);
			int res = rightMethod(*priorityQ);
			delete costs;
			delete priorityQ;
			int copyRes = lessCost.lessMoney(copyCosts);
			success = success && (res == copyRes ? true : false);
		}
		cout << (success == true ? "OK" : "false") << endl;
	}
};

int main() {
	unsigned int maxSize = 100;
	unsigned int maxValue = 100;
	unsigned int times = 50000;
	CTest test(maxSize, maxValue, times);
	test.runTest();
	system("pause");
	return 0;
}