/*
*@Author: lwl
*@Date: 2019-12-18
*@Description: 这是牛客左神的将过得猫狗队列问题，题目的描述太长了，在基础班第三节的第四题
*/

#include <iostream>
#include <string>
#include <queue>

using namespace std;

class CPet {
private:
	string petType;

public:
	CPet(string typeStr) {
		this->petType = typeStr;
	}

	virtual string getPetType() {
		return this->petType;
	}
};

class CDog : public CPet {
public:
	CDog() : CPet("dog") { }

public:
	virtual string getPetType() {
		return "dog";
	}
};

class CCat : public CPet {
public:
	CCat() : CPet("cat") { }

public:
	virtual string getPetType() {
		return "cat";
	}
};

class CDogMember {
private:
	CDog* petDog;
	int count;

public:
	CDogMember(int count, CDog* dog) :
		petDog(dog),
		count(count) 
	{ }

	~CDogMember() {
		delete petDog;
	}

public:
	int getCount() {
		return this->count;
	}
};

class CCatMember {
private:
	CCat* petCat;
	int count;

public:
	CCatMember(int count, CCat* cat) :
		petCat(cat),
		count(count) 
	{ }

	~CCatMember() {
		delete petCat;
	}

public:
	int getCount() {
		return this->count;
	}
};

class CEnterQueue {
private:
	queue<CDogMember*> dogQ;
	queue<CCatMember*> catQ;
	int count;

private:
	void printDog() {
		cout << "dog" << endl;
		CDogMember* dogMem = dogQ.front();
		dogQ.pop();
		delete dogMem;
	}

	void printCat() {
		cout << "cat" << endl;
		CCatMember* catMem = catQ.front();
		catQ.pop();
		delete catMem;
	}

public:
	CEnterQueue() {
		count = 0;
	}

	~CEnterQueue() {
		while (!dogQ.empty()) {
			CDogMember* dog = dogQ.front();
			dogQ.pop();
			delete dog;
		}

		while (!catQ.empty()) {
			CCatMember* cat = catQ.front();
			catQ.pop();
			delete cat;
		}
	}

public:
	void add(CPet* pet) {
		if (pet->getPetType() == "dog") {
			dogQ.push(new CDogMember(count++, dynamic_cast<CDog*>(pet)));
		}
		else if (pet->getPetType() == "cat") {
			catQ.push(new CCatMember(count++, dynamic_cast<CCat*>(pet)));
		}
		else {
			throw string("input dog or cat !");
		}
	}

	void pollAll() {
		if (!dogQ.empty() && !catQ.empty()) {
			if (dogQ.front()->getCount() < catQ.front()->getCount()) {
				printDog();
			}
			else {
				printCat();
			}
		}
		else if (!dogQ.empty()) {
			printDog();
		}
		else if (!catQ.empty()){
			printCat();
		}
		else {
			throw string("cat and dog queue is empty");
		}
	}

	void pollDog() {
		printDog();
	}

	void pollCat() {
		printCat();
	}

public:
	bool isEmpty() {
		return (dogQ.empty() && catQ.empty());
	}

	bool isDogEmpty() {
		return dogQ.empty();
	}

	bool isCatEmpty() {
		return catQ.empty();
	}
};

class CTest {
private:
	CEnterQueue petQ;
	bool res;

public:
	CTest() {
		res = false;
	}

public:
	void runTest() {
		res = petQ.isEmpty();
		cout << (res == true ? "pet queue is empty" : "pet queue is no empty") << endl;

		res = petQ.isDogEmpty();
		cout << (res == true ? "dog queue is empty" : "dog queue is no empty") << endl;

		res = petQ.isCatEmpty();
		cout << (res == true ? "cat queue is empty" : "cat queue is no empty") << endl;

		petQ.add(dynamic_cast<CPet*>(new CDog));
		petQ.add(dynamic_cast<CPet*>(new CCat));
		petQ.add(dynamic_cast<CPet*>(new CDog));
		petQ.add(dynamic_cast<CPet*>(new CDog));
		petQ.add(dynamic_cast<CPet*>(new CCat));

		res = petQ.isEmpty();
		cout << (res == true ? "pet queue is empty" : "pet queue is no empty") << endl;

		res = petQ.isDogEmpty();
		cout << (res == true ? "dog queue is empty" : "dog queue is no empty") << endl;

		res = petQ.isCatEmpty();
		cout << (res == true ? "cat queue is empty" : "cat queue is no empty") << endl;

		petQ.pollAll();
		petQ.pollCat();
		petQ.pollDog();
		while (!petQ.isEmpty()) {
			petQ.pollAll();
		}

		res = petQ.isEmpty();
		cout << (res == true ? "pet queue is empty" : "pet queue is no empty") << endl;

		res = petQ.isDogEmpty();
		cout << (res == true ? "dog queue is empty" : "dog queue is no empty") << endl;

		res = petQ.isCatEmpty();
		cout << (res == true ? "cat queue is empty" : "cat queue is no empty") << endl;

	}
};


int main() {
	CTest test;
	test.runTest();
	system("pause");
	return 0;
}