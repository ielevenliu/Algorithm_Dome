/*
* @Author: lwl
* @Date: 2019-12-29
* @Description: 判断是否是平衡二叉树
*/

#include <iostream>
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

class CIsBalanceBitree {
private:
	struct Msg {
		int h;
		bool isBal;
		Msg(int height, bool balance) {
			h = height;
			isBal = balance;
		}
	};

private:
	Msg getBitreeHeight(Node* node) {
		if (node == nullptr) {
			return Msg(0, true);
		}
		Msg lMsg = getBitreeHeight(node->left);
		Msg rMsg = getBitreeHeight(node->right);
		if (lMsg.isBal == false || rMsg.isBal == false || 
			(lMsg.h >= rMsg.h ? (lMsg.h - rMsg.h) : (rMsg.h - lMsg.h)) > 1) {
			return Msg(0, false);
		}
		return Msg((lMsg.h >= rMsg.h ? (lMsg.h + 1) : (rMsg.h + 1)), true);
	}

public:
	bool isBalance(Node* node) {
		if (node == nullptr) {
			return true;
		}
		return getBitreeHeight(node).isBal;
	}
};

class CTest {
private:
	CIsBalanceBitree isBalanceBitree;

private:
	void destroyBitree(Node* node) {
		if (node != nullptr) {
			destroyBitree(node->left);
			destroyBitree(node->right);
			delete node;
		}
	}

private:
	Node* generalBitree(vector<int>& pre, int preL, int preR, vector<int>& in, int inL, int inR) {
		Node* node = nullptr;
		if (preL <= preR && inL <= inR) {
			int mid = inL;
			while (mid <= inR) {
				if (in.at(mid) == pre.at(preL)) {
					break;
				}
				++mid;
			}
			node = new Node(in.at(mid));
			node->left = generalBitree(pre, preL + 1, preL + mid - inL, in, inL, mid - 1);
			node->right = generalBitree(pre, preL + mid - inL + 1, preR, in, mid + 1, inR);
		}
		return node;
	}

	void printBitree(Node* node) {
		if (node != nullptr) {
			cout << node->val << " ";
			printBitree(node->left);
			printBitree(node->right);
		}
	}

public:
	void runTest(vector<int>& pre, vector<int>& in) {
		Node* head = generalBitree(pre, 0, pre.size() - 1, in, 0, in.size() - 1);
		cout << "pre-print:  ";
		printBitree(head);
		cout << endl;
		cout << "isBalance ? : " << (isBalanceBitree.isBalance(head) == true ? "OK" : "No") << endl;
		destroyBitree(head);
	}
};

int main() {
	vector<int> pre{ 1, 2, 4, 8, 5, 3, 6, 7 };
	vector<int> in{ 8, 4, 2, 5, 1, 6, 3, 7 };
	CTest test;
	test.runTest(pre, in);
	system("pause");
	return 0;
}
