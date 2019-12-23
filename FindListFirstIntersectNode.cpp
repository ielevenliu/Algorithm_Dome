/*
* @Author: lwl
* @Date: 2019-12-23
* @Description: 两个单链表相交的一系列问题
*               如果链表1的长度为N，链表2的长度为M，时间复杂度请达到 O(N+M)，额外空间复杂度请达到O(1)
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

class CFindFirstIntersectNode {
private:
	Node* getListFirstLoopNode(Node* head) {
		Node* low = head;
		Node* fast = head;
		do {
			if (fast == nullptr || fast->next == nullptr) {
				return nullptr;
			}
			low = low->next;
			fast = fast->next->next;
		} while (low != fast);
		fast = head;
		while (low != fast) {
			low = low->next;
			fast = fast->next;
		}
		return low;
	}

	Node* getNoLoopListIntersectNode(Node* head1, Node* head2) {
		Node* intersectNode = nullptr;
		Node* cur1 = head1;
		Node* cur2 = head2;
		int cnt1 = 0;
		int cnt2 = 0;
		while (cur1 != nullptr) {
			cnt1++;
			cur1 = cur1->next;
		}
		while (cur2 != nullptr) {
			cnt2++;
			cur2 = cur2->next;
		}
		cur1 = cnt1 >= cnt2 ? head1 : head2;
		cur2 = cur1 == head1 ? head2 : head1;
		int diff = cnt1 >= cnt2 ? (cnt1 - cnt2) : (cnt2 - cnt1);
		while (diff--) {
			cur1 = cur1->next;
		}
		while (cur1 != nullptr) {
			if (cur1 == cur2) {
				intersectNode = cur1;
				break;
			}
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		return intersectNode;
	}

	Node* getBothLoopListIntersectNode(Node* head1, Node* loop1, Node* head2, Node* loop2) {
		Node* intersectNode = nullptr;
		if (loop1 == loop2) {
			Node* cur1 = head1;
			Node* cur2 = head2;
			int cnt1 = 0;
			int cnt2 = 0;
			while (cur1 != loop1) {
				cnt1++;
				cur1 = cur1->next;
			}
			while (cur2 != loop2) {
				cnt2++;
				cur2 = cur2->next;
			}
			cur1 = cnt1 >= cnt2 ? head1 : head2;
			cur2 = cur1 == head1 ? head2 : head1;
			int diff = cnt1 >= cnt2 ? (cnt1 - cnt2) : (cnt2 - cnt1);
			while (diff--) {
				cur1 = cur1->next;
			}
			while (cur1 != loop1) {
				if (cur1 == cur2) {
					intersectNode = cur1;
					break;
				}
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
		}
		else {
			Node* cur = loop2->next;
			while (cur != loop2) {
				if (cur == loop1) {
					intersectNode = loop1;
					cout << loop2->val << endl;
					break;
				}
				cur = cur->next;
			}
		}
		return intersectNode;
	}

public:
	Node* findFirstIntersectNode(Node* head1, Node* head2) {
		Node* resNode = nullptr;
		if (head1 != nullptr && head2 != nullptr) {
			Node* loop1 = getListFirstLoopNode(head1);
			Node* loop2 = getListFirstLoopNode(head2);
			if (loop1 == nullptr && loop2 == nullptr) {
				resNode = getNoLoopListIntersectNode(head1, head2);
			}
			else if (loop1 != nullptr && loop2 != nullptr) {
				resNode = getBothLoopListIntersectNode(head1, loop1, head2, loop2);
			}
		}
		return resNode;
	}
};

class CComparator {
private:
	// 两条无环单链表相交的头
	Node* headNoLoop1;
	Node* headNoLoop2;
	// 两条有环单链表相交不在环上的头
	Node* headBothLoopOnList1;
	Node* headBothLoopOnList2;
	// 两条有环单链表相交在环上的头
	Node* headBothLoopOnLoop1;
	Node* HeadBothLoopOnLoop2;

	CFindFirstIntersectNode findIntersectNode;

private:
	void generalList() {
		// 1->2->3->4->5->6->7->nullptr
		headNoLoop1 = new Node(1);
		headNoLoop1->next = new Node(2);
		headNoLoop1->next->next = new Node(3);
		headNoLoop1->next->next->next = new Node(4);
		headNoLoop1->next->next->next->next = new Node(5);
		headNoLoop1->next->next->next->next->next = new Node(6);
		headNoLoop1->next->next->next->next->next->next = new Node(7);
		// 0->9->8->6->7->nullptr;
		headNoLoop2 = new Node(0);
		headNoLoop2->next = new Node(9);
		headNoLoop2->next->next = new Node(8); 
		headNoLoop2->next->next->next = headNoLoop1->next->next->next->next->next; // 8->6...

		// 1->2->3->4->5->6->7->4...
		headBothLoopOnList1 = new Node(1);
		headBothLoopOnList1->next = new Node(2);
		headBothLoopOnList1->next->next = new Node(3);
		headBothLoopOnList1->next->next->next = new Node(4);
		headBothLoopOnList1->next->next->next->next = new Node(5);
		headBothLoopOnList1->next->next->next->next->next = new Node(6);
		headBothLoopOnList1->next->next->next->next->next->next = new Node(7);
		headBothLoopOnList1->next->next->next->next->next->next->next = headBothLoopOnList1->next->next->next;
		// 0->9->8->2...
		headBothLoopOnList2 = new Node(0);
		headBothLoopOnList2->next = new Node(9);
		headBothLoopOnList2->next->next = new Node(8);
		headBothLoopOnList2->next->next->next = headBothLoopOnList1->next;

		// 1->2->3->4->5->6->7->4...
		headBothLoopOnLoop1 = new Node(1);
		headBothLoopOnLoop1->next = new Node(2);
		headBothLoopOnLoop1->next->next = new Node(3);
		headBothLoopOnLoop1->next->next->next = new Node(4);
		headBothLoopOnLoop1->next->next->next->next = new Node(5);
		headBothLoopOnLoop1->next->next->next->next->next = new Node(6);
		headBothLoopOnLoop1->next->next->next->next->next->next = new Node(7);
		headBothLoopOnLoop1->next->next->next->next->next->next->next = headBothLoopOnLoop1->next->next->next;
		// 0->9->8->6->7->4...
		HeadBothLoopOnLoop2 = new Node(0);
		HeadBothLoopOnLoop2->next = new Node(9);
		HeadBothLoopOnLoop2->next->next = new Node(8);
		HeadBothLoopOnLoop2->next->next->next = headBothLoopOnLoop1->next->next->next->next->next;
	}

public:
	CComparator() {
		headNoLoop1 = nullptr;
		headNoLoop2 = nullptr;
		headBothLoopOnList1 = nullptr;
		headBothLoopOnList2 = nullptr;
		headBothLoopOnLoop1 = nullptr;
		HeadBothLoopOnLoop2 = nullptr;
	}

	void runComparator() {
		generalList();
		Node* intersectNode = findIntersectNode.findFirstIntersectNode(headBothLoopOnLoop1, HeadBothLoopOnLoop2);
		cout << intersectNode->val << endl;
	}
};

int main() {
	CComparator comparator;
	comparator.runComparator();
	system("pause");
	return 0;
}