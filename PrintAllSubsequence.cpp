/*
* @Author: lwl
* @Date: 2020-01-07
* @Description: 打印一个字符串的全部子序列，包括空字符串
*/

#include <iostream>
#include <string>

using namespace std;

class CPrintAllSubsequence {
private:
	void printAll(string& str, int i, string subStr) {
		if (i == str.length()) {
			cout << subStr << endl;
			return;
		}
		printAll(str, i + 1, subStr);
		printAll(str, i + 1, subStr + str.at(i));
	}

public:
	void printAllSub(string& str) {
		if (str.length() != 0) {
			printAll(str, 0, "");
		}
	}
};

int main() {
	CPrintAllSubsequence subseq;
	string str{"he"};
	subseq.printAllSub(str);
	system("pause");
	return 0;
}