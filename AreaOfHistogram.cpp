/*
* @Author: lwl
* @Date: 2020-01-14
* @Description: 计算直方图圆柱可拼接成的最大矩形面积
*/

#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

class CAreaOfHistogram {
public:
	int getMostAreaNoRepeat(vector<int>& histogram) {
		if (histogram.empty()) {
			return 0;
		}
		stack<int> hei;
		int len = histogram.size();
		int i = 0;
		int maxArea = 0;
		while (i < len) {
			while (!hei.empty() && histogram.at(hei.top()) > histogram.at(i)) {
				int index = hei.top();
				hei.pop();
				int preIndex = hei.empty() ? -1 : hei.top();
				maxArea = maxArea < (i - preIndex - 1) * histogram.at(index) ?
					(i - preIndex - 1) * histogram.at(index) : maxArea;
			}
			hei.push(i++);
		}
		while (!hei.empty()) {
			int index = hei.top();
			hei.pop();
			int preIndex = hei.empty() ? -1 : hei.top();
			maxArea = maxArea < (len - preIndex - 1) * histogram.at(index) ?
				(len - preIndex - 1) * histogram.at(index) : maxArea;
		}
		return maxArea;
	}

	int getMostAreaHasReapeat(vector<int>& histogram) {
		if (histogram.empty()) {
			return 0;
		}
		int maxArea = 0;
		stack<list<int>*> hei;
		int len = histogram.size();
		int i = 0;
		while (i < len) {
			while (!hei.empty() && histogram.at(hei.top()->front()) > histogram.at(i)) {
				list<int>* index = hei.top();
				hei.pop();
				int preIndex = hei.empty() ? -1 : hei.top()->front();
				maxArea = maxArea < (i - preIndex - 1) * histogram.at(index->front()) ?
					(i - preIndex - 1) * histogram.at(index->front()) : maxArea;
				delete index;
			}
			if (hei.empty() || histogram.at(hei.top()->front()) != histogram.at(i)) {
				hei.push(new list<int>(1, i++));
			}
			else {
				hei.top()->push_front(i++);
			}
		}
		while (!hei.empty()) {
			list<int>* index = hei.top();
			hei.pop();
			int preIndex = hei.empty() ? -1 : hei.top()->front();
			maxArea = maxArea < (len - preIndex - 1) * histogram.at(index->front()) ?
				(len - preIndex - 1) * histogram.at(index->front()) : maxArea;
			delete index;
		}
		return maxArea;
	}
};

class CTest {
private:
	CAreaOfHistogram areaOfHistogram;

public:
	void runTest() {
		vector<int> histogram1{ 4, 3, 2, 5, 6, 7 };
		int res1 = areaOfHistogram.getMostAreaNoRepeat(histogram1);
		cout << "no repeat area : " << res1 << endl << endl;
		vector<int> histogram2{ 4, 3, 3, 2, 5, 2, 2, 6 };
		int res2 = areaOfHistogram.getMostAreaHasReapeat(histogram2);
		cout << "has repeat area : " << res2 << endl << endl;
	}
};

int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}