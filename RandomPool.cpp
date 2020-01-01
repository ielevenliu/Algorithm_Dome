/*
* @Author: lwl
* @Date: 2020-01-01
* @Description: 设计RandomPool结构，Insert、delete和getRandom方法的时间复杂度都是 O(1)
*/

#include <iostream>
#include <string>
#include <time.h>
#include <unordered_map>

using namespace std;

class CRandomPool {
private:
	int size;
	unordered_map<string, int> keyIndexMap;
	unordered_map<int, string> indexKeyMap;

public:
	CRandomPool() : size(0) {
		srand(time(0));
	}

	void poolInsert(string key) {
		keyIndexMap.insert(pair<string, int>(key, size));
		indexKeyMap.insert(pair<int, string>(size++, key));
	}

	void poolDelete(string key) {
		if (size > 0 && keyIndexMap.count(key) > 0) {
			int index = (*keyIndexMap.find(key)).second;
			keyIndexMap.erase(key);
			indexKeyMap.erase(index);
			keyIndexMap.insert(pair<string, int>((*indexKeyMap.find(--size)).second, index));
			indexKeyMap.insert(pair<int, string>(index, (*indexKeyMap.find(size)).second));
			keyIndexMap.erase((*indexKeyMap.find(size)).second);
			indexKeyMap.erase(size);
		}
	}

	string getRandom() {
		if (size <= 0) {
			return string("nullptr");
		}
		return (*indexKeyMap.find(rand() % size)).second;
	}
};

class CTest {
private:
	CRandomPool randomPool;

public:
	void runTest() {
		cout << randomPool.getRandom() << endl;
		randomPool.poolDelete("liu");
		randomPool.poolInsert("liu");
		randomPool.poolInsert("wen");
		randomPool.poolInsert("long");
		randomPool.poolDelete("liu1");
		int i = 10;
		while (i--) {
			cout << randomPool.getRandom() << endl;
		}
	}
};

int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}