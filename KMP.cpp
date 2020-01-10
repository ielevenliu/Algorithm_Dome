/*
* @Author: lwl
* @Date: 2020-01-10
* @Description: KMP算法
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CKMP {
	vector<int>* getNextArr(string& str2) {
		vector<int>* nextArr = new vector<int>;
		nextArr->push_back(-1);
		if (str2.length() == 1) {
			return nextArr;
		}
		nextArr->push_back(0);
		int len = str2.length();
		int cur = 0;
		for (int i = 2; i < len; ++i) {
			if (str2.at(cur) == str2.at(i - 1)) {
				nextArr->push_back(++cur);
			}
			else if (cur > 0) {
				cur = nextArr->at(cur);
			}
			else {
				nextArr->push_back(0);
			}
		}
		return nextArr;
	}

public:
	int getIndexOf(string& str1, string& str2) {
		if (str1.length() < str2.length() ||
			str1.length() == 0 || str2.length() == 0) {
			return -1;
		}
		vector<int>* next = getNextArr(str2);
		int i1 = 0;
		int i2 = 0;
		while (i1 < str1.length() && i2 < str2.length()) {
			if (str1.at(i1) == str2.at(i2)) {
				++i1;
				++i2;
			}
			else if (i2 == 0) {
				++i1;
			}
			else {
				i2 = next->at(i2);
			}
		}
		return i2 == str2.length() ? (i1 - i2) : -1;
	}
};

int main() {
	string str1{ "abcabcababaccc" };
	string str2{ "ababa" };
	CKMP kmp;
	int index = kmp.getIndexOf(str1, str2);
	cout << "match index : " << index << endl;
	system("pause");
	return 0;
}
