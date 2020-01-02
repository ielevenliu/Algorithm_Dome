/*
* @Author: lwl
* @Date: 2020-01-02
* @Decsription: 前缀树
*/

#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int path;
	int end;
	Node* arr[26];
	Node(int p, int e) {
	    path = p;
		end = e;
		for (int i = 0; i < 26; ++i) {
			arr[i] = nullptr;
		}
	}
};

class CTrieTree {
private:
	Node* root;

private:
	void deleteList(Node* nodes) {
		for (int i = 0; i < 26; ++i) {
			if (nodes->arr[i] != nullptr) {
				Node* cur = nodes->arr[i];
				nodes->arr[i] = nullptr;
				while (cur != nullptr) {
					deleteList(cur);
					delete cur;
				}
			}
		}
	}

public:
	CTrieTree() : root(new Node(0, 0)) 
	{ }

	void insertTrieTree(string word) {
		if (!word.empty()) {
			Node* cur = root;
			size_t len = word.length();
			const char* ch = word.c_str();
			while (len--) {
				cur->arr[*ch - 'a'] = cur->arr[*ch - 'a'] == nullptr ? (new Node(0, 0)) : cur->arr[*ch - 'a'];
				cur->path++;
				cur = cur->arr[*ch - 'a'];
				++ch;
			}
			cur->end++;
		}
	}

	void deleteWord(string word) {
		if (!word.empty()) {
			if (searchTrieTree(word)) {
				Node* cur = root;
				size_t len = word.length();
				const char* ch = word.c_str();
				while (len--) {
					if (cur->path == 1) {
						deleteList(cur);
						break;
					}
					cur->path--;
					cur = cur->arr[(*ch++) - 'a'];
				}
				if (++len == 0) {
					cur->end--;
				}
			}
		}
	}

	bool searchTrieTree(string word) {
		bool isHas = false;
		if (!word.empty()) {
			Node* cur = root;
			size_t len = word.length();
			const char* ch = word.c_str();
			while (len--) {
				if (cur->arr[*ch - 'a'] == nullptr) {
					break;
				}
				cur = cur->arr[*ch - 'a'];
				++ch;
			}
			if (++len == 0 && cur->end > 0) {
				isHas = true;
			}
		}
		return isHas;
	}

	int prefixNum(string pre) {
		int num = 0;
		if (!pre.empty()) {
			size_t len = pre.length();
			const char* ch = pre.c_str();
			Node* cur = root;
			while (len--) {
				if (cur == nullptr) {
					num = 0;
					break;
				}
				num = cur->path;
				cur = cur->arr[(*ch++) - 'a'];
			}
		}
		return num;
	}
};

class CTest {
private:
	CTrieTree trieTree;

public:
	void runTest() {
		cout << "has liu: " << (trieTree.searchTrieTree(string("liu")) == true ? "y" : "n") << endl;
		trieTree.insertTrieTree(string("liu"));
		cout << "has liu: " << (trieTree.searchTrieTree(string("liu")) == true ? "y" : "n") << endl;
		trieTree.insertTrieTree(string("liu"));
		cout << "li prefixNum: " << trieTree.prefixNum(string("li")) << endl;
		trieTree.deleteWord(string("liu"));
		trieTree.insertTrieTree(string("liuw"));
		trieTree.insertTrieTree(string("liuwen"));
		trieTree.insertTrieTree(string("liuwenlong"));
		cout << "li prefixNum: " << trieTree.prefixNum(string("li")) << endl;
	}
};

int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}
