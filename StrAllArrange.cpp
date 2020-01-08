/*
* @Author: lwl
* @Date: 2020-01-08
* @Description: 1、打印一个字符串的全部排列 2、打印一个字符串的全部排列，要求不要出现重复的排列
*/

#include <iostream>
#include <unordered_set>

using namespace std;

class CPrintAllArrange {
private:
	void swap(string& str, int n1, int n2) {
		char tmp = str.at(n1);
		str.at(n1) = str.at(n2);
		str.at(n2) = tmp;
	}

	void printOfRepeat(string& str, int i) { // 可重复排序
		if (str.length() == i) {
			cout << str.c_str() << endl;
			return;
		}
		if (!str.empty()) {
			for (int j = i; j < str.length(); ++j) {
				swap(str, i, j);
				printOfRepeat(str, i + 1);
				// swap(str, i, j);
			}
		}
	}

	void printOfNoRepeat(string& str, int i) { // 不可重复
		if (str.length() == i) {
			cout << str.c_str() << endl;
			return;
		}
		unordered_set<char> set;
		for (int j = i; j < str.length(); ++j) {
			if (set.count(str.at(j)) == 0) {
				set.insert(str.at(j));
				swap(str, j, i);
				printOfNoRepeat(str, i + 1);
				swap(str, j, i);
			}
		}
	}

public:
	void printAllArrange(string& str) {
		string str1 = str;
		string str2 = str;
		cout << "Can be repeated " << endl;
		printOfRepeat(str1, 0);
		cout << endl;
		cout << "can't repeat " << endl;
		printOfNoRepeat(str2, 0);
	}
};

int main() {
	string str1{ "abc" };
	CPrintAllArrange printAllRange;
	printAllRange.printAllArrange(str1);
	cout << endl << "===========" << endl;
	string str2{ "acc" };
	printAllRange.printAllArrange(str2);
	system("pause");
	return 0;
}