/*
* @Author: lwl
* @Date: 2019-12-23
* @Description: 拷贝带有随机指针的链表，时间复杂度为 O(N)，空间复杂度为 O(1)
*/

#include <iostream>

using namespace std;

struct Node {
	int val;
	Node* next;
	Node* rand;
	Node(int value) {
		val = value;
		next = nullptr;
		rand = nullptr;
	}
};

class CCopyList {
public:
	Node* copyList(Node* head) {
		Node* newHead = nullptr;
		if (head != nullptr) {
			Node* cur = head;
			Node* after = nullptr;
			while (cur != nullptr) {
				after = cur->next;
				cur->next = new Node(cur->val);
				cur->next->next = after;
				cur = after;
			}
			cur = head;
			while (cur != nullptr) {
				cur->next->rand = cur->rand == nullptr ? nullptr : cur->rand->next;
				cur = cur->next->next;
			}
			newHead = head->next;
			cur = newHead;
			while (head != nullptr) {
				after = head->next->next;
				head->next = after;
				head = after;
				cur->next = after == nullptr ? nullptr : after->next;
				cur = cur->next;
			}
		}
		return newHead;
	}
};

class CComparator {
private:
	Node* head;
	CCopyList cpList;

private:
	void generalListWithRandom() {
		head = new Node(1);
		head->next = new Node(2);
		head->next->next = new Node(3);
		head->rand = head->next->next;
		head->next->rand = head;
	}

	void printList(Node* node) {
		while (node != nullptr) {
			cout << node->val << " ";
			node = node->next;
		}
		cout << endl;
	}

	void printRandomNode(Node* node) {
		while (node != nullptr) {
			cout << node->val << " ";
			if (node->rand != nullptr) {
				cout << node->rand->val;
			}
			cout << endl;
			node = node->next;
		}
	}

public:
	CComparator() {
		head = nullptr;
	}

	~CComparator() {
		Node* cur = nullptr;
		while (head != nullptr) {
			cur = head;
			head = head->next;
			delete cur;
		}
	}

	void runComparator() {
		generalListWithRandom();
		printList(head);
		printRandomNode(head);
		Node* newHead = cpList.copyList(head);
		printList(newHead);
		printRandomNode(newHead);
	}
};

int main() {
	CComparator comparator;
	comparator.runComparator();
	system("pause");
	return 0;
}