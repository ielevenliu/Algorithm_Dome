/*
*@Author: lwl
*@Date: 2019-12-12
*@Description: 1. 用固定长度的数组实现栈
*              2. 用固定长度的数组实现队列
*              3. O(1)的时间复杂度获得栈的最小值
*              4. 用栈实现队列
*              5. 用队列实现栈
*/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <time.h>
using namespace std;

class CMyStack {
private:
	int stackSize;
	int index;
	int *stackData;

public:
	CMyStack(int stackLength) : 
		stackSize(stackLength)	{
		index = 0;
		stackData = new int[stackSize];
	}

	~CMyStack() {
		delete[] stackData;
	}

	int StackMyTop() {
		if (index == 0) {
			throw string("stack is empty");
		}
		return stackData[index - 1];
	}

	void StackMyPush(int value) {
		if (index == stackSize) {
			throw string("stack is full");
		}
		stackData[index++] = value;
	}

	void StackMyPop() {
		if (index == 0) {
			throw string("stack is empty");
		}
		index--;
	}
};

class CMyQueue {
	int queueSize;
	int length;
	int end;
	int start;
	int* queueData;

public:
	CMyQueue(int queueLength) :
		queueSize(queueLength)	{
		end = 0;
		start = 0;
		length = 0;
		queueData = new int[queueSize];
	}
	~CMyQueue() {
		delete[] queueData;
	}

	int QueueMyFront() {
		if (length == 0) {
			throw string("queue is empty");
		}
		return queueData[start];
	}

	void QueueMyPush(int value) {
		if (length == queueSize) {
			throw string("queue is full");
		}
		queueData[end++] = value;
		length++;
		end = end == queueSize ? 0 : end;
	}

	void QueueMyPop() {
		if (length == 0) {
			throw string("queue  is empty");
		}
		length--;
		start++;
		start = start == queueSize ? 0 : start;
	}
};

class CGetMin {
private:
	stack<int> data;
	stack<int> min;

public:
	void MinPushInterface(int value) {
		if (min.empty() == true || min.top() > value) {
			min.push(value);
		}
		else {
			int tmp = min.top();
			min.push(tmp);
		}
		data.push(value);
	}

	int MinTopInterface() {
		if (data.size() == 0) {
			throw string("stack is empty");
		}
		return data.top();
	}

	void MinPopInterface() {
		if (data.size() == 0) {
			throw string("stack is empty");
		}
		data.pop();
		min.pop();
	}

	int GetMinInterface() {
		if (min.size() == 0) {
			throw string("stack is empty");
		}
		return min.top();
	}
};

class CStackToQueue {
private:
	stack<int> queueData;
	stack<int> queueHelp;

private:
	void QDataToHelp() {
		if (queueData.empty()) {
			throw string("queue is empty");
		}
		else {
			while (!queueData.empty()) {
				queueHelp.push(queueData.top());
				queueData.pop();
			}
		}
	}

public:
	void PushToQueueInterface(int value) {
		queueData.push(value);
	}

	int FrontFromQueueInterface() {
		if (queueHelp.empty()) {
			QDataToHelp();
		}
		return queueHelp.top();
	}

	void PopFromQueueInterface() {
		if (queueHelp.empty()) {
			QDataToHelp();
		}
		queueHelp.pop();
	}
};

class QueueToStack {
private:
	queue<int> stackData;
	queue<int> stackHelp;

private:
	void Swap() {
		queue<int> tmp = stackData;
		stackData = stackHelp;
		stackHelp = tmp;
	}

	void SDataToHelp() {
		while (stackData.size() != 1) {
			stackHelp.push(stackData.front());
			stackData.pop();
		}
	}

public:
	void PushToStackInterface(int value) {
		stackData.push(value);
	}

	int TopFromStackInterface() {
		if (stackData.empty()) {
			throw string("stack is empty");
		}
		SDataToHelp();
		int tmp = stackData.front();
		stackHelp.push(stackData.front());
		stackData.pop();
		Swap();
		return tmp;
	}

	void PopFromStackInterface() {
		if (stackData.empty()) {
			throw string("stack is empty");
		}
		SDataToHelp();
		stackData.pop();
		Swap();
	}
};

class CTest : public CMyStack, CMyQueue, CGetMin, CStackToQueue, QueueToStack {
public:
	CTest(int size) : 
		CMyStack(size), 
		CMyQueue(size) {
		srand(time(0));
	}

	void RunTest() {
		cout << "==== 用固定长度的数组实现栈 ====" << endl;
		try {
			for (int i = 3; i >= 0; i--) {
				StackMyPush(i);
			}
		}
		catch (string e) {
			cout << e << endl;
			cout << StackMyTop() << " ";
			StackMyPop();
			StackMyPush(3);
			for (int i = 0; i < 3; i++) {
				cout << StackMyTop() << " ";
				StackMyPop();
			}
		}
		cout << endl << "=============================" << endl;

		cout << "==== 用固定长度的数组实现队列 ====" << endl;
		try {
			for (int j = 3; j >= 0; j--) {
				QueueMyPush(j);
			}
		}
		catch (string e) {
			cout << e << endl;
			cout << QueueMyFront() << " ";
			QueueMyPop();
			QueueMyPush(3);
			for (int j = 0; j < 3; j++) {
				cout << QueueMyFront() << " ";
				QueueMyPop();
			}
		}
		cout << endl << "================================" << endl;

		cout << "==== O(1)的时间复杂度获得栈的最小值 ====" << endl;
		try {
			for (int k = 0; k < 10; k++) {
				MinPushInterface(rand() % 10);
				cout << MinTopInterface() << " " << GetMinInterface() << " ;";
			}
			cout << endl;
			for (int j = 0; j <= 10; j++) {
				MinPopInterface();
			}
		}
		catch (string e) {
			cout << e;
		}
		cout << endl << "==========================================" << endl;

		cout << "==== 用栈实现队列 ====" << endl;
		for (int i = 3; i > 0; i--) {
			PushToQueueInterface(i);
		}
		for (int j = 0; j < 3; j++) {
			cout << FrontFromQueueInterface() << " ";
			PopFromQueueInterface();
		}
		cout << endl << "======================" << endl;

		cout << "==== 用队列实现栈 ====" << endl;
		for (int i = 3; i > 0; i--) {
			PushToStackInterface(i);
		}
		for (int j = 0; j < 3; j++) {
			cout << TopFromStackInterface() << " ";
			PopFromStackInterface();
		}
		cout << endl << "======================" << endl;
	}
};

int main() {
	CTest test(3);
	test.RunTest();
	system("pause");
	return 0;
}