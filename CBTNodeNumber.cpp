/*
* @Author: lwl
* @Date: 2020-01-01
* @Deacription: 计算完全二叉树节点个数，要求时间复杂度小于 O(N), N 是节点个数
*/

#include <iostream>
#include <vector>
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

class CCBTNodeNum {
private:
	int getBitreeHeight(Node* node) {
		int height = 0;
		while (node != nullptr) {
			++height;
			node = node->left;
		}
		return height;
	}

public:
	int CBTNodeNum(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		int leftH = getBitreeHeight(node->left);
		int rightH = getBitreeHeight(node->right);
		if (leftH == rightH) {
			return static_cast<int>(pow(2, leftH)) + CBTNodeNum(node->right);
		}
		else {
			return static_cast<int>(pow(2, rightH)) + CBTNodeNum(node->left);
		}
	}
};

class CTest {
private:
	CCBTNodeNum nodeNum;

private:
	Node* generalBitree(vector<int>& pre, int preL, int preR, vector<int>& in, int inL, int inR) {
		Node* node = nullptr;
		if (preL <= preR && inL <= inR) {
			int mid = inL;
			while (mid <= inR) {
				if (pre.at(preL) == in.at(mid)) {
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
		cout << "traversal-by-level:  ";
		if (node != nullptr) {
			queue<Node*> qNode;
			qNode.push(node);
			while (!qNode.empty()) {
				node = qNode.front();
				qNode.pop();
				cout << node->val << " ";
				if (node->left != nullptr) {
					qNode.push(node->left);
				}
				if (node->right != nullptr) {
					qNode.push(node->right);
				}
			}
		}
		cout << endl;
	}

	void destroyBitree(Node* node) {
		if (node != nullptr) {
			destroyBitree(node->left);
			destroyBitree(node->right);
			delete node;
		}
	}

public:
	void runTest(vector<int>& pre, vector<int>& in) {
		Node* head = generalBitree(pre, 0, pre.size() - 1, in, 0, in.size() - 1);
		printBitree(head);
		cout << "node-number: " << nodeNum.CBTNodeNum(head) << endl;
		destroyBitree(head);
	}
};

int main() {
	vector<int> pre{ 1, 2, 4, 8, 9, 5, 3, 6, 7 };
	vector<int> in{ 8, 4, 9, 2, 5, 1, 6, 3, 7 };
	CTest test;
	test.runTest(pre, in);
	system("pause");
	return 0;
}