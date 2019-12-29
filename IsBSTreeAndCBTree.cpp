/*
* @Author: lwl
* @Date: 2019-12-29
* @Deacription: 判断是是否是二叉搜索树、是否是完全二叉树
*/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

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

class CIsBSTreeAndCBTree {
public:
	bool isBSTree(Node* node) {
		bool isBST = true;
		stack<Node*> sNode;
		int preVal = INT_MIN;
		while (!sNode.empty() || node != nullptr) {
			if (node != nullptr) {
				sNode.push(node);
				node = node->left;
			}
			else {
				node = sNode.top();
				sNode.pop();
				if (preVal > node->val) {
					isBST = false;
					break;
				}
				preVal = node->val;
				node = node->right;
			}
		}
		return isBST;
	}

	bool isCBTree(Node* node) {
		bool isCBT = true;
		if (node != nullptr) {
			queue<Node*> qNode;
			qNode.push(node);
			bool beaf = false;
			while (!qNode.empty()) {
				node = qNode.front();
				qNode.pop();
				if ((node->left == nullptr && node->right != nullptr) || 
					beaf && (node->left != nullptr || node->right != nullptr)) {
					isCBT = false;
					break;
				}
				if (node->left != nullptr) {
					qNode.push(node->left);
				}
				if (node->right != nullptr) {
					qNode.push(node->right);
				}
				else {
					beaf = true;
				}
			}
		}
		return isCBT;
	}
};

class CTest {
private:
	CIsBSTreeAndCBTree isBSTAndCBT;

private:
	Node* generalBitree(vector<int>& in, int inL, int inR, vector<int>& order, int orderL, int orderR) {
		Node* node = nullptr;
		if (inL <= inR && orderL <= orderR) {
			int mid = inL;
			while (mid <= inR) {
				if (in.at(mid) == order.at(orderR)) {
					break;
				}
				++mid;
			}
			node = new Node(in.at(mid));
			node->left = generalBitree(in, inL, mid - 1, order, orderL, orderL + mid - 1 - inL);
			node->right = generalBitree(in, mid + 1, inR, order, orderL + mid - inL, orderR - 1);
		}
		return node;
	}

	void printBitree(Node* node) {
		if (node != nullptr) {
			printBitree(node->left);
			cout << node->val << " ";
			printBitree(node->right);
		}
	}

public:
	void runTest(vector<int>& in, vector<int>& order) {
		Node* head = generalBitree(in, 0, in.size() - 1, order, 0, order.size() - 1);
		cout << "order traversal Bitree: " << endl;
		printBitree(head);
		cout << endl;
		cout << "is BSTree ? :  " << (isBSTAndCBT.isBSTree(head) == true ? "yes" : "no") << endl;
		cout << "is CBTree ? :  " << (isBSTAndCBT.isCBTree(head) == true ? "yes" : "no") << endl;
	}
};

int main() {
	vector<int> in{ 1, 2, 3, 4, 5, 6 };
	vector<int> order{ 1, 3, 2, 5, 6, 4 };
	CTest test;
	test.runTest(in, order);
	system("pause");
	return 0;
}