/*
* @Author: lwl
* @Date: 2020-01-10
* @Description: 增加最少的字符，是添加字符后的字符串包含两个原始串，主要是用KMP中获取next数组的方法
*/

#include <iostream>
#include <vector>

using namespace std;

class CShortRepeatTwice {
private:
	int getLastIndex(string& str) {
		if (str.length() == 1) {
			return 0;
		}
		vector<int> next;
		next.push_back(-1);
		next.push_back(0);
		int cur = 0;
		for (int i = 2; i <= str.length(); ++i) {
			if (str.at(i - 1) == str.at(cur)) {
				next.push_back(++cur);
			}
			else if (cur > 0) {
				cur = next.at(cur);
			}
			else {
				next.push_back(0);
			}
		}
		return next.at(next.size() - 1);
	}

public:
	void appendStr(string& str) {
		if (str.length() == 0) {
			return;
		}
		int index = getLastIndex(str);
		int len = str.length();
		str.append(str.substr(index, len - index));
	}
};

class CTest {
private:
	CShortRepeatTwice shortestRepeat;

public:
	void runTest() {
		string str1{ "a" };
		cout << "source string : " << str1.c_str();
		shortestRepeat.appendStr(str1);
		cout << " append string : " << str1.c_str() << endl;

		string str2{ "aa" };
		cout << "source string : " << str2.c_str();
		shortestRepeat.appendStr(str2);
		cout << " append string : " << str2.c_str() << endl;

		string str3{ "ab" };
		cout << "source string : " << str3.c_str();
		shortestRepeat.appendStr(str3);
		cout << " append string : " << str3.c_str() << endl;
	}
};

int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}