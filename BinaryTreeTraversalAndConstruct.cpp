/*
* @Author: lwl
* @Date: 2019-12-24
* @Description: 重建二叉树、二叉树的递归和非递归前序 & 中序 & 后序遍历、二叉树层序遍历
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int value) {
		val = value;
		left = nullptr;
		right = nullptr;
	}
};

class CTravelBiTree {
private:
	TreeNode* printNode(stack<TreeNode*>& sNode) {
		cout << sNode.top()->val << " ";
		TreeNode* tmpNode = sNode.top();
		sNode.pop();
		return tmpNode;
	}

public:
	// 递归遍历
	void preTraversalBiTreeInterface(TreeNode* treeNode) {
		if (treeNode != nullptr) {
			cout << treeNode->val << " ";
			preTraversalBiTreeInterface(treeNode->left);
			preTraversalBiTreeInterface(treeNode->right);
		}
	}

	void inTraversalBiTreeInterface(TreeNode* treeNode) {
		if (treeNode != nullptr) {
			inTraversalBiTreeInterface(treeNode->left);
			cout << treeNode->val << " ";
			inTraversalBiTreeInterface(treeNode->right);
		}
	}

	void orderTraversalBiTreeInterface(TreeNode* treeNode) {
		if (treeNode != nullptr) {
			orderTraversalBiTreeInterface(treeNode->left);
			orderTraversalBiTreeInterface(treeNode->right);
			cout << treeNode->val << " ";
		}
	}

public:
	// 非递归遍历
	void levelTraversalBiTreeInterface(TreeNode* treeNode) {
		cout << "Level-Traversal: ";
		if (treeNode != nullptr) {
			queue<TreeNode*> qNode;
			qNode.push(treeNode);
			while (!qNode.empty()) {
				TreeNode* tmpNode = qNode.front();
				qNode.pop();
				cout << tmpNode->val << " ";
				if (tmpNode->left) {
					qNode.push(tmpNode->left);
				}
				if (tmpNode->right) {
					qNode.push(tmpNode->right);
				}
			}
		}
		cout << endl;
	}

	void preTraversalBiTreeInterface(TreeNode* treeNode, bool noRecursive) {
		cout << "Unrecur-Pre-Traversal: ";
		if (treeNode != nullptr) {
			stack<TreeNode*> sNode;
			sNode.push(treeNode);
			while (!sNode.empty()) {
				treeNode = sNode.top();
				sNode.pop();
				cout << treeNode->val << " ";
				if (treeNode->right != nullptr) {
					sNode.push(treeNode->right);
				}
				if (treeNode->left != nullptr) {
					sNode.push(treeNode->left);
				}
			}
		}
		cout << endl;
	}

	void inTraversalBiTreeInterface(TreeNode* treeNode, bool noRecursive) {
		cout << "Unrecur-In-Traversal: ";
		stack<TreeNode*> sNode;
		while (!sNode.empty() || treeNode != nullptr) {
			if (treeNode != nullptr) {
				sNode.push(treeNode);
				treeNode = treeNode->left;
			}
			else {
				cout << sNode.top()->val << " ";
				treeNode = sNode.top()->right;
				sNode.pop();
			}
		}
		cout << endl;
	}

	// 非递归后序遍历，two stack
	void orderTraversalBiTreeInterface1(TreeNode* treeNode, bool noRecursive) {
		cout << "Unrecur-Order_Traversal: ";
		if (treeNode != nullptr) {
			stack<TreeNode*> sNode;
			stack<TreeNode*> help;
			sNode.push(treeNode);
			while (!sNode.empty()) {
				treeNode = sNode.top();
				help.push(treeNode);
				sNode.pop();
				if (treeNode->left != nullptr) {
					sNode.push(treeNode->left);
				}
				if (treeNode->right != nullptr) {
					sNode.push(treeNode->right);
				}
			}
			while (!help.empty()) {
				cout << help.top()->val << " ";
				help.pop();
			}
		}
		cout << endl;
	}

	// 非递归后序遍历，only one stack
	void orderTraversalBiTreeInterface2(TreeNode* treeNode, bool noRecursive) {
		cout << "Unrecur-Order-Traversal: ";
		stack<TreeNode*> sNode;
		TreeNode* prePrint = treeNode;
		while (!sNode.empty() || treeNode != nullptr) {
			if (treeNode != nullptr) {
				sNode.push(treeNode);
				treeNode = treeNode->left;
			}
			else {
				treeNode = sNode.top()->right;
				if (treeNode == nullptr) {
					prePrint = printNode(sNode);
				}
				else if (treeNode == prePrint){
					prePrint = printNode(sNode);
					treeNode = nullptr;
				}
			}
		}
		cout << endl;
	}

	// 非递归后序遍历，only one stack
	void orderTraversalBiTreeInterface3(TreeNode* treeNode, bool unRecur) {
		cout << "UnRecur-Order-Traversal: ";
		if (treeNode != nullptr) {
			stack<TreeNode*> sNode;
			sNode.push(treeNode);
			TreeNode* cur = nullptr;
			while (!sNode.empty()) {
				cur = sNode.top();
				if (cur->left != nullptr && cur->left != treeNode && cur->right != treeNode) {
					sNode.push(cur->left);
				}
				else if (cur->right != nullptr && cur->right != treeNode) {
					sNode.push(cur->right);
				}
				else {
					cout << cur->val << " ";
					sNode.pop();
					treeNode = cur;
				}
			}
		}
		cout << endl;
	}
};

class CConstructBiTree { 
private:
	TreeNode* root;

private:
	TreeNode* PreInToBiTree(vector<int>& pre, int preStart, int preEnd, vector<int>& in, int inStart, int inEnd) {
		if (preStart > preEnd || inStart > inEnd) {
			return nullptr;
		}
		int i = inStart;
		for (; i <= inEnd; i++) {
			if (pre.at(preStart) == in.at(i)) {
				break;
			}
		}
		TreeNode* node = new TreeNode(in.at(i));
		node->left = PreInToBiTree(pre, preStart + 1, preStart + (i - inStart), in, inStart, i - 1);
		node->right = PreInToBiTree(pre, preStart + (i - inStart) + 1, preEnd, in, i + 1, inEnd);
		return node;
	}

	TreeNode* InOrderToBiTree(vector<int>& in, int inStart, int inEnd, vector<int>& order, int orderStart, int orderEnd) {
		if (inStart > inEnd || orderStart > orderEnd) {
			return nullptr;
		}
		int i = inStart;
		for (; i <= inEnd; i++) {
			if (in.at(i) == order.at(orderEnd)) {
				break;
			}
		}
		TreeNode* node = new TreeNode(order.at(orderEnd));
		node->left = InOrderToBiTree(in, inStart, i - 1, order, orderStart, orderStart + i - 1 - inStart);
		node->right = InOrderToBiTree(in, i + 1, inEnd, order, orderStart + i - 1 - inStart + 1, orderEnd - 1);
		return node;
	}

public:
	CConstructBiTree() {
		root = nullptr;
	}

	TreeNode* PreInToBiTreeInterface(vector<int>& pre, vector<int>& in) {
		if (pre.size() == 0 || in.size() == 0 || pre.size() != in.size()) {
			return root;
		}
		return PreInToBiTree(pre, 0, pre.size() - 1, in, 0, in.size() - 1);
	}

	TreeNode* InOrderToBiTreeInterface(vector<int>& in, vector<int>& order) {
		if (in.size() == 0 || order.size() == 0 || in.size() != order.size()) {
			return root;
		}
		return InOrderToBiTree(in, 0, in.size() - 1, order, 0, order.size() - 1);
	}
};

class CTest : public CTravelBiTree, CConstructBiTree {
private:
	int pPre[8] = { 1, 2, 4, 3, 5, 7, 8, 6 };
	int pIn[8] = { 4, 2, 1, 7, 5, 8, 3, 6 };
	int pOrder[8] = { 4, 2, 7, 8, 5, 6, 3, 1 };
	vector<int> pre;
	vector<int> in;
	vector<int> order;

private:
	void DestroyBiTree(TreeNode* node) {
		if (node != nullptr) {
			DestroyBiTree(node->left);
			DestroyBiTree(node->right);
			delete node;
		}
	}

public:
	CTest() {
		for (int i = 0; i < 8; i++) {
			pre.push_back(pPre[i]);
			in.push_back(pIn[i]);
			order.push_back(pOrder[i]);
		}
	}

	void RunTest() {
		TreeNode* node = InOrderToBiTreeInterface(in, order);
		preTraversalBiTreeInterface(node);
		cout << endl;
		inTraversalBiTreeInterface(node);
		cout << endl;
		orderTraversalBiTreeInterface(node);
		cout << endl;
		cout << "====================================" << endl;
		preTraversalBiTreeInterface(node, true);
		inTraversalBiTreeInterface(node, true);
		orderTraversalBiTreeInterface1(node, true);
		orderTraversalBiTreeInterface2(node, true);
		orderTraversalBiTreeInterface3(node, true);
		cout << "====================================" << endl;
		levelTraversalBiTreeInterface(node);
		DestroyBiTree(node);
	}
};

int main() {
	CTest test;
	test.RunTest();
	system("pause");
	return 0;
}
