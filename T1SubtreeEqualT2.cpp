/*
* @Author: lwl
* @Date: 2020-01-10
* @Description: 二叉树T1是否包含二叉树T2
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
	int val;
	Node* left;
	Node* right;
	Node(int value) {
		val = value;
		left = nullptr;
		right = nullptr;
	}
};

class CKMP {
private:
	vector<int>* getNextArr(string& str2) {
		vector<int>* nextArr = new vector<int>;
		nextArr->push_back(-1);
		if (str2.length() == 1) {
			return nextArr;
		}
		nextArr->push_back(0);
		int len = str2.length();
		int cur = 0;
		for (int i = 2; i < len; ++i) {
			if (str2.at(cur) == str2.at(i - 1)) {
				nextArr->push_back(++cur);
			}
			else if (cur > 0) {
				cur = nextArr->at(cur);
			}
			else {
				nextArr->push_back(0);
			}
		}
		return nextArr;
	}

public:
	bool getIndexOf(string& str1, string& str2) {
		if (str1.length() < str2.length() || str1.length() == 0 || str2.length() == 0) {
			return -1;
		}
		vector<int>* next = getNextArr(str2);
		int i1 = 0;
		int i2 = 0;
		while (i1 < str1.length() && i2 < str2.length()) {
			if (str1.at(i1) == str2.at(i2)) {
				++i1;
				++i2;
			}
			else if (i2 == 0) {
				++i1;
			}
			else {
				i2 = next->at(i2);
			}
		}
		delete next;
		return i2 == str2.length() ? true : false;
	}
};

class CTest {
private:
	CKMP kmp;

private:
	void generalTree(Node* &t1, Node* &t2) {
		t1 = new Node(1);
		t1->left = new Node(2);
		t1->right = new Node(3);
		t1->left->left = new Node(4);
		t1->left->right = new Node(5);
		t1->right->left = new Node(6);
		t1->right->right = new Node(7);
		t1->left->left->right = new Node(8);
		t1->left->right->left = new Node(9);

		t2 = new Node(2);
		t2->left = new Node(4);
		t2->right = new Node(5);
		t2->left->right = new Node(8);
		t2->right->left = new Node(9);
	}

	void serialByPre(Node* t, string& str) {
		if (t == nullptr) {
			str.append("#_");
			return;
		} 
		str.append(to_string(t->val) + "_");
		serialByPre(t->left, str);
		serialByPre(t->right, str);
	}

public:
	void runTest() {
		Node* t1 = nullptr;
		Node* t2 = nullptr;
		generalTree(t1, t2);
		string str1;
		string str2;
		serialByPre(t1, str1);
		serialByPre(t2, str2);
		bool res = kmp.getIndexOf(str1, str2);
		cout << (res ? "contain" : "no contain") << endl;
	}
};

int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}
