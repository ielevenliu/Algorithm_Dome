/*
* @Author: lwl
* @Date: 2020-01-08
* @Description: 给你一个栈，请你逆序这个栈，不能申请额外的数据结构，只能使用递归函数
*/

#include <iostream>
#include <stack>
#include <queue>
#include <time.h>

using namespace std;

class CReverseStack {
private:
	void reverse(stack<int>& sTest) {
		if (!sTest.empty()) {
			int last = getLastElem(sTest);
			reverse(sTest);
			sTest.push(last);
		}
 	}

	int getLastElem(stack<int>& sTest) {
		int cur = sTest.top();
		sTest.pop();
		if (sTest.empty()) {
			return cur;
		}
		int last = getLastElem(sTest);
		sTest.push(cur);
		return last;
 	}

public:
	stack<int>& reverseStack(stack<int>& sTest) {
		if (!sTest.empty()) {
			reverse(sTest);
		}
		return sTest;
	}
};

class CComparator {
private:
	int maxVal;
	int maxSize;
	int times;
	CReverseStack reverse;

private:
	void rightMethod(stack<int>& sTest) {
		if (!sTest.empty()) {
			queue<int> q;
			while (!sTest.empty()) {
				q.push(sTest.top());
				sTest.pop();
			}
			while (!q.empty()) {
				sTest.push(q.front());
				q.pop();
			}
		}
	}

	bool isEqual(stack<int>& s1, stack<int>& s2) {
		if (s1.size() != s2.size()) {
			return false;
		}
		bool success = true;
		while (!s1.empty()) {
			success = success && (s1.top() == s2.top());
			s1.pop();
			s2.pop();
		}
		return success;
	}

	stack<int>* generalStack() {
		stack<int>* s = new stack<int>;
		int size = rand() % maxSize;
		while (size--) {
			s->push(rand() % maxVal);
		}
		return s;
	}

public:
	CComparator(int maxValue, int maxSize, int times) :
		maxVal(maxValue),
		maxSize(maxSize),
		times(times)
	{
		srand(time(0));
	}

	void runTest() {
		bool success = true;
		while (times--) {
			stack<int>* sTest = generalStack();
			stack<int> copyS = *sTest;
			reverse.reverseStack(*sTest);
			rightMethod(copyS);
			success = success && isEqual(*sTest, copyS);
			delete sTest;
		}
		cout << (success ? "OK" : "false") << endl;
	}
};

int main() {
	int maxValue = 100;
	int maxSize = 100;
	int times = 1000;
	CComparator compare(maxValue, maxSize, times);
	compare.runTest();
	system("pause");
	return 0;
}