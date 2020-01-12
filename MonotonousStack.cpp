/*
* @Author: lwl
* @Date: 2020-01-12
* @Description: 单调栈结构 (1、数组可重复; 2、数组不可重复)
*/

#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

class CMonotonousStack {
public:
	void noRepeatProcess(vector<int>& arr) {
		if (arr.empty()) {
			return;
		}
		stack<int> s;
		for (int i = 0; i < arr.size(); ++i) {
			while (!s.empty() && s.top() < arr.at(i)) {
				int tmp = s.top();
				s.pop();
				if (s.empty()) {
					cout << "null-" << tmp << "-" << arr.at(i) << endl;
				}
				else {
					cout << s.top() << "-" << tmp << "-" << arr.at(i) << endl;
				}
			}
			s.push(arr.at(i));
		}
		while (!s.empty()) {
			int tmp = s.top();
			s.pop();
			if (s.empty()) {
				cout << "null-" << tmp << "-null" << endl;
			}
			else {
				cout << s.top() << "-" << tmp << "-null" << endl;
			}
		}
	}

	void hasRepaetProcess(vector<int>& arr) {
		if (arr.empty()) {
			return;
		}
		stack<list<int>*> sList;
		for (int i = 0; i < arr.size(); ++i) {
			while (!sList.empty() && sList.top()->front() < arr.at(i)) {
				list<int>* tmp = sList.top();
				sList.pop();
				if (sList.empty()) {
					while (!tmp->empty()) {
						cout << "null-" << tmp->front() << "-" << arr.at(i) << endl;
						tmp->pop_front();
					}
				}
				else {
					while (!tmp->empty()) {
						cout << sList.top()->front() << "-" << tmp->front() << "-" << arr.at(i) << endl;
						tmp->pop_front();
					}
				}
				delete tmp;
			}
			if (sList.empty() || sList.top()->front() > arr.at(i)) {
				sList.push(new list<int>(1, arr.at(i)));
			}
			else {
				sList.top()->push_front(arr.at(i));
			}
		}
		while (!sList.empty()) {
			list<int>* tmp = sList.top();
			sList.pop();
			if (sList.empty()) {
				while (!tmp->empty()) {
					cout << "null-" << tmp->front() << "-null" << endl;
					tmp->pop_front();
				}
			}
			else {
				while (!tmp->empty()) {
					cout << sList.top()->front() << "-" << tmp->front() << "-null" << endl;
					tmp->pop_front();
				}
			}
			delete tmp;
		}
	}
};

class CTest {
private:
	CMonotonousStack monoStack;

public:
	void runTest() {
		cout << "=========================" << endl;
		vector<int> arr1{ 4, 2, 5, 3, 1, 9, 8 };
		monoStack.noRepeatProcess(arr1);
		cout << endl << endl;

		cout << "=========================" << endl;
		vector<int> arr2{ 4, 4, 2, 5, 5, 7, 9, 0 };
		monoStack.hasRepaetProcess(arr2);
	}
};

int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}