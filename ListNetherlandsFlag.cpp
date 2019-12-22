/*
* @Author: lwl
* @Date: 2019-12-22
* @Description: 将单向链表按某值划分成左边小、中间相等、右边大的形式(不改变原链表中节点的相对位置)，
*               时间复杂度请达到O(N)，额外空间复杂度请达到O(1)
*/

#include <iostream>

using namespace std;

struct Node {
	int val;
	Node* next;
	Node(int value) {
		val = value;
		next = nullptr;
	}
};

class CListNetherlandsFlag {
public:
	void partition(Node** head, int pivot) {
		if (*head == nullptr || (*head)->next == nullptr) {
			return;
		}
		Node* curNode = *head;
		Node* smallStart = nullptr;
		Node* smallEnd = nullptr;
		Node* equalStart = nullptr;
		Node* equalEnd = nullptr;
		Node* largeStart = nullptr;
		Node* largeEnd = nullptr;
		while (curNode != nullptr) {
			if (curNode->val < pivot) {
				if (smallStart == nullptr && smallEnd == nullptr) {
					smallStart = curNode;
					smallEnd = curNode;
				}
				else {
					smallEnd->next = curNode;
					smallEnd = smallEnd->next;
				}
			}
			else if (curNode->val == pivot) {
				if (equalStart == nullptr && equalEnd == nullptr) {
					equalStart = curNode;
					equalEnd = curNode;
				}
				else {
					equalEnd->next = curNode;
					equalEnd = equalEnd->next;
				}
			}
			else {
				if (largeStart == nullptr && largeEnd == nullptr) {
					largeStart = curNode;
					largeEnd = curNode;
				}
				else {
					largeEnd->next = curNode;
					largeEnd = largeEnd->next;
				}
			}
			curNode = curNode->next;
		}
		if (smallStart == nullptr) {
			if (equalStart == nullptr) {
				largeEnd->next = nullptr;
				*head = largeStart;
			}
			else {
				largeEnd->next = nullptr;
				equalEnd->next = largeStart;
				*head = equalStart;
			}
		}
		else {
			if (equalStart == nullptr) {
				smallEnd->next = largeStart;
			}
			else {
				smallEnd->next = equalStart;
				equalEnd->next = largeStart;
			}
			largeEnd->next = nullptr;
			*head = smallStart;
		}
	}
};

class CComparator {
private:
	int pivot;
	Node* head;
	CListNetherlandsFlag listNetherlandsFlag;

private:
	void generalList() {
		head = new Node(9);
		head->next = new Node(0);
		head->next->next = new Node(4);
		head->next->next->next = new Node(4);
		head->next->next->next->next = new Node(5);
		head->next->next->next->next->next = new Node(1);
	}

	void printList() {
		Node* cur = head;
		while (cur != nullptr) {
			cout << cur->val << " ";
			cur = cur->next;
		}
		cout << endl;
	}

public:
	CComparator(int k) :
		pivot(k) 
	{ head = nullptr; }

	~CComparator() {
		Node* tmp = nullptr;
		while (head != nullptr) {
			tmp = head;
			head = head->next;
			delete tmp;
		}
	}

	void runComparator() {
		generalList();
		printList();
		listNetherlandsFlag.partition(&head, pivot);
		printList();
	}
};

int main() {
	int pivot = 4;
	CComparator comparator(pivot);
	comparator.runComparator();
	system("pause");
	return 0;
}