/*
* @Author: lwl
* @Date: 2020-01-02
* @Description: 并查集
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
	int val;
	Node(int value) {
		val = value;
	}
};

class CUnionFindSet {
private:
	unordered_map<Node*, Node*> fatherMap;
	unordered_map<Node*, int> sizeMap;

private:
	Node* findHeadNode(Node* node) {
		Node* res = nullptr;
		if (node != nullptr && fatherMap.count(node) > 0) {
			Node* father = (*fatherMap.find(node)).second;
			while (father != node) {
				node = father;
				father = (*fatherMap.find(node)).second;
			}
			res = node;
		}
		return res;
	}

public:
	void makeMap(vector<Node*>& nodes) {
		if (nodes.size() != 0) {
			for (Node* node : nodes) {
				fatherMap.insert(pair<Node*, Node*>(node, node));
				sizeMap.insert(pair<Node*, int>(node, 1));
			}
		}
	}

	bool isSameSet(Node* node1, Node* node2) {
		return findHeadNode(node1) == findHeadNode(node2);
	}

	void unionSet(Node* node1, Node* node2) {
		if (node1 != nullptr && node2 != nullptr) {
			Node* head1 = findHeadNode(node1);
			Node* head2 = findHeadNode(node2);
			if (head1 != head2) {
				int size1 = (*sizeMap.find(head1)).second;
				int size2 = (*sizeMap.find(head2)).second;
				if (size1 < size2) {
					(*sizeMap.find(head2)).second = size1 + size2;
					sizeMap.erase(head1);
					(*fatherMap.find(head1)).second = head2;
				}
				else {
					(*sizeMap.find(head1)).second = size1 + size2;
					sizeMap.erase(head2);
					(*fatherMap.find(head2)).second = head1;
				}
			}
		}
	}
};

class CTest {
private:
	CUnionFindSet unionFindSet;
	vector<Node*> nodes;

private:
	void generalNode() {
		nodes.push_back(new Node(1));
		nodes.push_back(new Node(2));
		nodes.push_back(new Node(3));
		nodes.push_back(new Node(4));
	}

public:
	~CTest() {
		if (nodes.size() != 0) {
			for (Node* cur : nodes) {
				delete cur;
			}
		}
	}

	void runTest() {
		generalNode();
		unionFindSet.makeMap(nodes);
		cout << "is-same-set: " << (unionFindSet.isSameSet(nodes.at(0), nodes.at(1)) == true ? "yes" : "no") << endl;
		unionFindSet.unionSet(nodes.at(0), nodes.at(1));
		cout << "is-same-set: " << (unionFindSet.isSameSet(nodes.at(0), nodes.at(1)) == true ? "yes" : "no") << endl;
	}
};

int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}
