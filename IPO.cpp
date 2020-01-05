/*
* @Author: lwl
* @Date: 2010-01-05
* @Description: 做项目最后获得的最大钱数(IPO问题)
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
	int cost;
	int profit;
	Node(int c, int p) {
		cost = c;
		profit = p;
	}
};

class CCostLess {
public:
	bool operator()(const Node* n1, const Node* n2) const {
		return ( n1->cost > n2->cost );
	}
};

class CProfitGreater {
public:
	bool operator()(const Node* n1, const Node* n2) const {
		return (n1->profit < n2->profit);
	}
};

class CIPO {
private:
	priority_queue<Node*, vector<Node*>, CCostLess> costsQ;
	priority_queue<Node*, vector<Node*>, CProfitGreater> profitsQ;

private:
	void generalCostsHeap(vector<int>& costs, vector<int>& profits) {
		int len = costs.size();
		while (len--) {
			costsQ.push(new Node(costs.at(len), profits.at(len)));
		}
	}

public:
	int getIPO(vector<int>& costs, vector<int>& profits, int k, int m) {
		generalCostsHeap(costs, profits);
		Node* cur = nullptr;
		while (k > 0) {
			while (!costsQ.empty() && costsQ.top()->cost <= m) {
				profitsQ.push(costsQ.top());
				costsQ.pop();
			}
			if (!profitsQ.empty()) {
				cur = profitsQ.top();
				profitsQ.pop();
				m += cur->profit;
				delete cur;
				--k;
			}
			else {
				break;
			}
		}
		while (!costsQ.empty()) {
			cur = costsQ.top();
			costsQ.pop();
			delete cur;
		}
		while (!profitsQ.empty()) {
			cur = profitsQ.top();
			profitsQ.pop();
			delete cur;
		}
		return m;
	}
};

class CTest {
private:
	CIPO IPO;

public:
	void runTest(vector<int>& costs, vector<int>& profits, int k, int m) {
		cout << "Get most money is : " << IPO.getIPO(costs, profits, k, m) << endl;
	}
};

int main() {
	vector<int> costs{ 100, 10, 50, 70, 200, 60 };
	vector<int> profits{ 30, 2, 40, 20, 150, 50 };
	int k = 5;
	int m = 90;
	CTest test;
	test.runTest(costs, profits, k, m);
	system("pause");
	return 0;
}