/*
* @Author: lwl
* @Date: 2019-12-22
* @Description: 判断一个链表是否为回文结构
*/

#include <iostream>
#include <stack>

using namespace std;

struct Node {
	int val;
	Node* next;
	Node(int value) {
		val = value;
		next = nullptr;
	}
};

class CIsPalineroomList {
public:
	// 时间复杂度达到O(N)，额外空间复杂度达到O(1)
	bool isPalineroom_1(Node* head) {
		bool res = true;
		if (head == nullptr || head->next == nullptr) {
			return res;
		}
		Node* low = head;
		Node* fast = head;
		while (fast->next != nullptr && fast->next->next != nullptr) {
			low = low->next;
			fast = fast->next->next;
		}
		Node* pre = low;
		Node* cur = low->next;
		Node* after = nullptr;
		low->next = nullptr;
		while (cur != nullptr) {
			after = cur->next;
			cur->next = pre;
			pre = cur;
			cur = after;
		}
		cur = pre;
		while (head != nullptr) {
			if (head->val != pre->val) {
				res = false;
				break;
			}
			head = head->next;
			pre = pre->next;
		}
		pre = nullptr;
		while (cur != low) {
			after = cur->next;
			cur->next = pre;
			pre = cur;
			cur = after;
		}
		low->next = pre;
		return res;
	}

	// 时间复杂度达到O(N)，额外空间复杂度达到O(N)，额外空间为 N/2
	bool isPalineroom_2(Node* head) {
		bool res = true;
		if (head == nullptr || head->next == nullptr) {
			return res;
		}
		Node* low = head;
		Node* fast = head;
		stack<int> s;
		while (fast->next != nullptr && fast->next->next != nullptr) {
			low = low->next;
			fast = fast->next->next;
		}
		Node* cur = low;
		while (cur != nullptr) {
			s.push(cur->val);
			cur = cur->next;
		}
		while (head != low->next) {
			if (head->val != s.top()) {
				res = false;
				break;
			}
			head = head->next;
			s.pop();
		}
		return res;
	}

	// 时间复杂度达到O(N)，额外空间复杂度达到O(N)，额外空间为 N
	bool isPalineroom_3(Node* head) {
		bool res = true;
		if (head == nullptr || head->next == nullptr) {
			return res;
		}
		stack<int> s;
		Node* cur = head;
		while (cur != nullptr) {
			s.push(cur->val);
			cur = cur->next;
		}
		cur = head;
		while (cur != nullptr) {
			if (cur->val != s.top()) {
				res = false;
				break;
			}
			cur = cur->next;
			s.pop();
		}
		return res;
	}
};

class CComparator {
private:
	Node* head;
	CIsPalineroomList isPalineroomList;

private:
	void generalList() {
		head = new Node(1);
		head->next = new Node(2);
		head->next->next = new Node(3);
		head->next->next->next = new Node(2);
		head->next->next->next->next = new Node(1);
	}

	void printList() {
		Node* tmp = head;
		while (tmp != nullptr) {
			cout << tmp->val << " ";
			tmp = tmp->next;
		}
		cout << endl;
	}

public:
	void runComparator() {
		generalList();
		printList();
		bool res = isPalineroomList.isPalineroom_2(head);
		printList();
		cout << (res ? "is palineroom" : "no palineroom") << endl;
	}
};

int main() {
	CComparator comparator;
	comparator.runComparator();
	system("pause");
	return 0;
}
