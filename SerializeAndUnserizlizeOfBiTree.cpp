/*
* @Author: lwl
* @Date: 2019-12-29
* @Description: 实现二叉树前序、中序、后序的序列化和前序的反序列化
*/

#include <iostream>
#include <vector>
#include <string>
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

class CSerializeBiTree {
public:
	string RecurPreSerial(Node* node) {
		if (node == nullptr) {
			return string("#_");
		}
		string str;
		str.append(to_string(node->val) + "_");
		str.append(RecurPreSerial(node->left));
		str.append(RecurPreSerial(node->right));
		return str;
	}

	string RecurInSerial(Node* node) {
		if (node == nullptr) {
			return string("#_");
		}
		string str;
		str.append(RecurInSerial(node->left));
		str.append(to_string(node->val) + "_");
		str.append(RecurInSerial(node->right));
		return str;
	}

	string RecurOrderSerial(Node* node) {
		if (node == nullptr) {
			return string("#_");
		}
		string str;
		str.append(RecurOrderSerial(node->left));
		str.append(RecurOrderSerial(node->right));
		str.append(to_string(node->val) + "_");
		return str;
	}

	string serialByLevel(Node* node) {
		if (node == nullptr) {
			return string("#_");
		}
		string str;
		queue<Node*> qNode;
		qNode.push(node);
		while (!qNode.empty()) {
			node = qNode.front();
			qNode.pop();
			if (node == nullptr) {
				str.append("#_");
			}
			else {
				str.append(to_string(node->val) + "_");
				qNode.push(node->left);
				qNode.push(node->right);
			}
		}
		return str;
	}
};

class CReserializeBiTree {
private:
	Node* reserialByPre(queue<string>& strQ) {
		Node* head = nullptr;
		if (!strQ.empty()) {
			string cur = strQ.front();
			strQ.pop();
			if (cur != "#") {
				head = new Node(stoi(cur));
				head->left = reserialByPre(strQ);
				head->right = reserialByPre(strQ);
			}
		}
		return head;
	}

public:
	Node* reserialByPreStr(string& str) {
		if (str.empty()) {
			return nullptr;
		}
		queue<string> strQ;
		size_t len = str.size();
		size_t cur = 0;
		while (cur < len) {
			size_t pos = str.find("_", cur);
			strQ.push(str.substr(cur, pos - cur));
			cur = pos + 1;
		}
		return reserialByPre(strQ);
	}
};

class CComparator {
private:
	int pre[7] = { 1, 2, 4, 3, 5, 7, 6 };
	int in[7] = { 2, 4, 1, 7, 5, 3, 6 };
	int order[7] = { 4, 2, 7, 5, 6, 3, 1 };
	vector<int> vPre;
	vector<int> vIn;
	vector<int> vOrder;

	Node* head;
	CSerializeBiTree serialize;
	CReserializeBiTree reserialize;

private:
	void generalVce() {
		for (int i = 0; i < 7; ++i) {
			vPre.push_back(pre[i]);
			vIn.push_back(in[i]);
			vOrder.push_back(order[i]);
		}
	}

	Node* generalBiTreeWithPreIn(int preL, int preR, int inL, int inR) {
		Node* node = nullptr;
		if (preL <= preR && inL <= inR) {
			int mid = inL;
			for (; mid <= inR; ++mid) {
				if (vIn.at(mid) == vPre.at(preL)) {
					break;
				}
			}
			node = new Node(vIn.at(mid));
			node->left = generalBiTreeWithPreIn(preL + 1, preL + mid - inL, inL, mid - 1);
			node->right = generalBiTreeWithPreIn(preL + mid - inL + 1, preR, mid + 1, inR);
		}
		return node;
	}

	Node* generalBiTreeWithInOrder(int inL, int inR, int orderL, int orderR) {
		Node* node = nullptr;
		if (inL <= inR && orderL <= orderR) {
			int mid = inL;
			for (; mid <= inR; ++mid) {
				if (vIn.at(mid) == vOrder.at(orderR)) {
					break;
				}
			}
			node = new Node(vIn.at(mid));
			node->left = generalBiTreeWithInOrder(inL, mid - 1, orderL, orderL + mid - inL - 1);
			node->right = generalBiTreeWithInOrder(mid + 1, inR, orderL + mid - inL, orderR - 1);
		}
		return node;
	}

	void printPreBiTree(Node* node) {
		if (node != nullptr) {
			cout << node->val << " ";
			printPreBiTree(node->left);
			printPreBiTree(node->right);
		}
	}

	void printInBiTree(Node* node) {
		if (node != nullptr) {
			printInBiTree(node->left);
			cout << node->val << " ";
			printInBiTree(node->right);
		}
	}

	void printOrderBiTree(Node* node) {
		if (node != nullptr) {
			printOrderBiTree(node->left);
			printOrderBiTree(node->right);
			cout << node->val << " ";
		}
	}

	void destoryBiTree(Node* node) {
		if (node != nullptr) {
			destoryBiTree(node->left);
			destoryBiTree(node->right);
			delete node;
		}
	}

public:
	CComparator() :
		head(nullptr)
	{ }

	~CComparator() {
		destoryBiTree(head);
	}

	void runTest() {
		generalVce();
		// head = generalBiTreeWithPreIn(0, vPre.size() - 1, 0, vIn.size() - 1);
		head = generalBiTreeWithInOrder(0, vIn.size() - 1, 0, vOrder.size() - 1);
		cout << "pre-traversal: ";
		printPreBiTree(head);
		cout << endl;
		cout << "in-traversal: ";
		printInBiTree(head);
		cout << endl;
		cout << "order-traversal: ";
		printOrderBiTree(head);
		cout << endl;

		string preStr = serialize.RecurPreSerial(head);
		cout << "recur-pre-serial: " << preStr << endl;

		string inStr = serialize.RecurInSerial(head);
		cout << "recur-in-serial: " << inStr << endl;

		string orderStr = serialize.RecurOrderSerial(head);
		cout << "recur-order-serial: " << orderStr << endl;

		string levelStr = serialize.serialByLevel(head);
		cout << "level-serial: " << levelStr << endl;

		cout << "reserial-by-pre: ";
		Node* node = reserialize.reserialByPreStr(preStr);
		printPreBiTree(node);
		destoryBiTree(node);
		cout << endl;
	}
};

int main() {
	CComparator comparator;
	comparator.runTest();
	system("pause");
	return 0;
}