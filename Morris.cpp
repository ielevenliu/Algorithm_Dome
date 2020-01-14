/*
* @Author: lwl
* @Date: 2020-01-14
* @Description: Morris 前序 & 中序 & 后序遍历
*               Morris遍历流程 1. 当前节点(cur)的左子树不为空，当前节点的左子树的最右节点(mostRight)
*                                 1.1 如果mostRight->right指向空，使其指向当前节点(mostRight->right = cur)，当前节点左移(cur = cur->left)
*                                 1.2 如果mostRight->right指向当前节点，使其指向空(mostRight->right = nullptr)，当前节点右移(cur = cur->right)
*                              2. 当前节点(cur)的左子树为空，直接右移(cur = cur->right)
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

class CMorris {
private:
	void reverse(Node* node) {
		if (node == nullptr) {
			return;
		}
		Node* cur = node;
		Node* pre = nullptr;
		Node* next = nullptr;
		while (cur != nullptr) {
			next = cur->right;
			cur->right = pre;
			pre = cur;
			cur = next;
		}
		cur = pre;
		while (cur != nullptr) {
			cout << cur->val << " ";
			cur = cur->right;
		}
		cur = pre;
		pre = nullptr;
		while (cur != nullptr) {
			next = cur->right;
			cur->right = pre;
			pre = cur;
			cur = next;
		}
	}

public:
	void morrisPre(Node* head) {
		if (head == nullptr) {
			return;
		}
		Node* cur = head;
		Node* mostRight = nullptr;
		while (cur != nullptr) {
			if (cur->left != nullptr) {
				mostRight = cur->left;
				while (mostRight->right != nullptr && mostRight->right != cur) {
					mostRight = mostRight->right;
				}
				if (mostRight->right == nullptr) {
					cout << cur->val << " ";
					mostRight->right = cur;
					cur = cur->left;
					continue;
				}
				else {
					mostRight->right = nullptr;
				}
			}
			else {
				cout << cur->val << " ";
			}
			cur = cur->right;
		}
	}

	void morrisIn(Node* head) {
		if (head == nullptr) {
			return;
		}
		Node* cur = head;
		Node* mostRight = nullptr;
		while (cur != nullptr) {
			if (cur->left != nullptr) {
				mostRight = cur->left;
				while (mostRight->right != nullptr && mostRight->right != cur) {
					mostRight = mostRight->right;
				}
				if (mostRight->right == nullptr) {
					mostRight->right = cur;
					cur = cur->left;
					continue;
				}
				else {
					mostRight->right = nullptr;
				}
			}
			cout << cur->val << " ";
			cur = cur->right;
		}
	}

	void morrisPost(Node* head) {
		if (head == nullptr) {
			return;
		}
		Node* cur = head;
		Node* mostRight = nullptr;
		while (cur != nullptr) {
			if (cur->left != nullptr) {
				mostRight = cur->left;
				while (mostRight->right != nullptr && mostRight->right != cur) {
					mostRight = mostRight->right;
				}
				if (mostRight->right == nullptr) {
					mostRight->right = cur;
					cur = cur->left;
					continue;
				}
				else {
					mostRight->right = nullptr;
					reverse(cur->left);
				}
			}
			cur = cur->right;
		}
		reverse(head);
	}
};

class CTest {
private:
	CMorris morris;

private:
	Node* createBitree(vector<int>& pre, int preL, int preR, vector<int>& in, int inL, int inR) {
		if (preL > preR || inL > inR) {
			return nullptr;
		}
		int mid = inL;
		while (mid <= inR) {
			if (in.at(mid) == pre.at(preL)) {
				break;
			}
			++mid;
		}
		Node* node = new Node(in.at(mid));
		node->left = createBitree(pre, preL + 1, preL + mid - inL, in, inL, mid - 1);
		node->right = createBitree(pre, preL + mid - inL + 1, preR, in, mid + 1, inR);
		return node;
	}

	Node* gerenalBitree(vector<int>& pre, vector<int>& in) {
		if (pre.size() == 0 || in.size() == 0 || pre.size() != in.size()) {
			return nullptr;
		}
		return createBitree(pre, 0, pre.size() - 1, in, 0, in.size() - 1);
	}

	void printPreTraversal(Node* node) {
		if (node == nullptr) {
			return;
		}
		cout << node->val << " ";
		printPreTraversal(node->left);
		printPreTraversal(node->right);
	}

	void printInTraversal(Node* node) {
		if (node == nullptr) {
			return;
		}
		printInTraversal(node->left);
		cout << node->val << " ";
		printInTraversal(node->right);
	}

	void destroyBitree(Node* node) {
		if (node == nullptr) {
			return;
		}
		destroyBitree(node->left);
		destroyBitree(node->right);
		delete node;
	}

public:
	void runTest(vector<int>& pre, vector<int>& in) {
		Node* head = gerenalBitree(pre, in);

		cout << "print pre traversal : " << endl;
		printPreTraversal(head);
		cout << endl << endl;

		cout << "print in traversal : " << endl;
		printInTraversal(head);
		cout << endl << endl;

		cout << "morris pre traversal : " << endl;
		morris.morrisPre(head);
		cout << endl << endl;

		cout << "morris in traversal : " << endl;
		morris.morrisIn(head);
		cout << endl << endl;

		cout << "morris post traversal : " << endl;
		morris.morrisPost(head);
		cout << endl << endl;

		destroyBitree(head);
	}
};

int main() {
	vector<int> pre{ 1, 2, 4, 3, 5, 7, 6 };
	vector<int> in{ 2, 4, 1, 7, 5, 3, 6 };
	CTest test;
	test.runTest(pre, in);
	system("pause");
	return 0;
}