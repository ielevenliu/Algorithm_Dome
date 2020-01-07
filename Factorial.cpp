/*
* @Author: lwl
* @Date: 2020-01-07
* @Description: 求n!的结果
*/

#include <iostream>
#include <time.h>

using namespace std;

class CFactorial {
public:
	int factorial(int val) {
		if (val <= 1) {
			return 1;
		}
		return val * factorial(val - 1);
	}
};

class CComparator {
private:
	int maxVal;
	int times;
	CFactorial cFa;

private:
	int rightMethod(int val) {
		int result = 1;
		if (val > 1) {
			for (int i = 1; i <= val; ++i) {
				result *= i;
			}
		}
		return result;
	}

public:
	CComparator(int maxValue, int times) :
		maxVal(maxValue),
		times(times)
	{
		srand(time(0));
	}

	void runTest() {
		bool success = true;
		if (times > 0) {
			while (times--) {
				int val = rand() % maxVal;
				int res1 = rightMethod(val);
				int res2 = cFa.factorial(val);
				success = success && (res1 == res2);
			}
		}
		cout << (success == true ? "OK" : "false") << endl;
	}
};

int main() {
	int maxValue = 50;
	int times = 10000;
	CComparator comp(maxValue, times);
	comp.runTest();
	system("pause");
	return 0;
}
