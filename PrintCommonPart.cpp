/*
* @Author: lwl
* @Date: 2019-12-22
* @Description: 打印两个有序链表的公共部分
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

class CPrintCommonPart {
public:
	void printCommonPartInterface(Node* head1, Node* head2) {
		while (head1 != nullptr && head2 != nullptr) {
			if (head1->val == head2->val) {
				cout << head1->val << " ";
				head1 = head1->next;
				head2 = head2->next;
			}
			else if (head1->val > head2->val) {
				head2 = head2->next;
			}
			else {
				head1 = head1->next;
			}
		}
		cout << endl;
	}
};

class CComparator {
private:
	Node* head1;
	Node* head2;
	CPrintCommonPart printCommonPart;

private:
	void generalList() {
		head1 = new Node(2);
		head1->next = new Node(3);
		head1->next->next = new Node(5);
		head1->next->next->next = new Node(6);

		head2 = new Node(1);
		head2->next = new Node(2);
		head2->next->next = new Node(5);
		head2->next->next->next = new Node(7);
		head2->next->next->next->next = new Node(8);
	}

	void printList() {
		Node* tmp1 = head1;
		while (tmp1 != nullptr) {
			cout << tmp1->val << " ";
			tmp1 = tmp1->next;
		}
		cout << endl;

		Node* tmp2 = head2;
		while (tmp2 != nullptr) {
			cout << tmp2->val << " ";
			tmp2 = tmp2->next;
		}
		cout << endl;
	}

public:
	~CComparator() {
		Node* tmp;
		while (head1 != nullptr) {
			tmp = head1;
			head1 = head1->next;
			delete tmp;
		}
		while (head2 != nullptr) {
			tmp = head2;
			head2 = head2->next;
			delete tmp;
		}
	}

	void runComparator() {
		generalList();
		printList();
		printCommonPart.printCommonPartInterface(head1, head2);
	}
};

int main() {
	CComparator comparator;
	comparator.runComparator();
	system("pause");
	return 0;
}