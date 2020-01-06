/*
* @Author: lwl
* @Date: 2020-01-06
* @Description: 安排宣讲的日程，要求会议室进行的宣讲的场次最多
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Node {
	int start;
	int end;
	Node(int s, int e) {
		start = s;
		end = e;
	}
};

bool cmp(const Node* n1, const Node* n2) {
	return n1->end < n2->end;
}

class CTest {
private:
	void generalArr(vector<Node*>& arr) {
		arr.push_back(new Node(10, 12));
		arr.push_back(new Node(10, 11));
		arr.push_back(new Node(13, 15));
		arr.push_back(new Node(13, 14));
		arr.push_back(new Node(14, 16));
		arr.push_back(new Node(15, 17));
		arr.push_back(new Node(16, 17));
		arr.push_back(new Node(16, 18));
		arr.push_back(new Node(6, 7));
		arr.push_back(new Node(6, 8));
		arr.push_back(new Node(7, 9));
		arr.push_back(new Node(7, 8));
	}

	void bestArrange(vector<Node*>& arr) {
		vector<Node*>::iterator it = arr.begin();
		int preEnd = INT_MIN;
		while (it != arr.end()) {
			if (preEnd <= (*it)->start) {
				cout << (*it)->start << "--" << (*it)->end << endl;
				preEnd = (*it)->end;
			}
			++it;
		}
	}

	void destroyArr(vector<Node*>& arr) {
		for (Node* i : arr) {
			delete i;
		}
	}

public:
	void runTest() {
		vector<Node*> arr;
		generalArr(arr);
		sort(arr.begin(), arr.end(), cmp);
		bestArrange(arr);
		destroyArr(arr);
	}
};

int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}