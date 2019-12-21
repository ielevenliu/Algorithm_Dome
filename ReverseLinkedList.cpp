/*
* @Author: lwl
* @Date: 2019-12-21
* @Description: 实现单向链表和双向链表的反转
*/

#include <iostream>

using namespace std;

struct sNode {
	int val;
	sNode* next;
	sNode(int value) {
		val = value;
		next = nullptr;
	}
};

struct dNode {
	int val;
	dNode* last;
	dNode* next;
	dNode(int value) {
		val = value;
		last = nullptr;
		next = nullptr;
	}
};

class CReverseList {
public:
	void reverseSingleList(sNode** sHead) {
		sNode* after = nullptr;
		sNode* pre = nullptr;
		while (*sHead != nullptr) {
			after = (*sHead)->next;
			(*sHead)->next = pre;
			pre = (*sHead);
			(*sHead) = after;
		}
		(*sHead) = pre;
	}

	void reverseDoubleList(dNode** dHead) {
		dNode* after = nullptr;
		dNode* pre = nullptr;
		while (*dHead != nullptr) {
			after = (*dHead)->next;
			(*dHead)->next = pre;
			(*dHead)->last = after;
			pre = (*dHead);
			(*dHead) = after;
		}
		pre->last = nullptr;
		*dHead = pre;
	}
};

class CComparator {
private:
	sNode* sHead;
	dNode* dHead;
	CReverseList reverseList;

private:
	void generalSingleList() {
		sHead = new sNode(0);
		sHead->next = new sNode(1);
		sHead->next->next = new sNode(2);
		sHead->next->next->next = new sNode(3);
		sHead->next->next->next->next = new sNode(4);
		sHead->next->next->next->next->next = nullptr;
	}

	void generalDoubleList() {
		dHead = new dNode(0);
		dHead->next = new dNode(1);
		dHead->next->last = dHead;
		dHead->next->next = new dNode(2);
		dHead->next->next->last = dHead->next;
		dHead->next->next->next = new dNode(3);
		dHead->next->next->next->last = dHead->next->next;
		dHead->next->next->next->next = new dNode(4);
		dHead->next->next->next->next->last = dHead->next->next->next;
	}

	void printSingleList() {
		sNode* head = sHead;
		cout << "print single list: " << endl;
		while (head != nullptr) {
			cout << head->val << " ";
			head = head->next;
		}
		cout << endl;
	}

	void printDoubleList() {
		dNode* head = dHead;
		cout << "print double list: " << endl;
		while (head != nullptr) {
			cout << head->val << " ";
			head = head->next;
		}
		cout << endl;

		head = dHead;
		while (head->next != nullptr) {
			head = head->next;
		}
		cout << "print double list: " << endl;
		while (head != nullptr) {
			cout << head->val << " ";
			head = head->last;
		}
		cout << endl;
	}

public:
	~CComparator() {
		if (sHead != nullptr) {
			sNode* head = sHead;
			sNode* tmp = nullptr;
			sHead = nullptr;
			while (head != nullptr) {
				tmp = head;
				head = head->next;
				delete tmp;
			}
		}
		if (dHead != nullptr) {
			dNode* head = dHead;
			dNode* tmp = nullptr;
			dHead = nullptr;
			while (head != nullptr) {
				tmp = head;
				head = head->next;
				delete tmp;
			}
		}
	}

	void runComparator() {
		generalSingleList();
		printSingleList();
		generalDoubleList();
		printDoubleList();
		reverseList.reverseSingleList(&sHead);
		printSingleList();
		reverseList.reverseDoubleList(&dHead);
		printDoubleList();
	}
};

int main() {
	CComparator comparator;
	comparator.runComparator();
	system("pause");
	return 0;
}