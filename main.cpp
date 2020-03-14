#include <iostream>
#include <vector>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include "graphics.h"
#pragma comment(lib, "graphics.lib")
using namespace std;

int cntMoveSteps = 0;
int numOfDisks;
int delayTime = 200;

class Node {
public:
	int data;
	class Node* pNext;

	Node() { this->data = 0; this->pNext = NULL; }
	Node(int x) { this->data = x; this->pNext = NULL; }
	~Node() {};
};

class List {
public:
	Node* pHead;
	Node* pTail;

	List() { this->pHead = NULL; this->pTail = NULL; }
	~List() {
		delete this->pHead; this->pHead = NULL;
		delete this->pTail; this->pTail = NULL;
	}

	bool isEmpty() { return this->pHead == NULL; }

	void addHead(int x) {
		Node* p = new Node;
		p->data = x;

		if (this->isEmpty()) {
			this->pHead = p;
			this->pTail = p;
		}
		else {
			p->pNext = this->pHead;
			this->pHead = p;
		}
	}

	int removeHead() {
		int popNum = 0;
		if (!this->isEmpty()) {
			Node* p;
			p = this->pHead;
			popNum = p->data;

			this->pHead = this->pHead->pNext;

			delete p; p = NULL;
			if (this->pHead == NULL)
				this->pTail = NULL;
		}

		return popNum;
	}

	void initDisk(int n) {
		for (int i = n; i >= 1; i--) {
			this->addHead(i);
		}
	}

	int lengthOfList() {
		int cnt = 0;
		for (Node* p = this->pHead; p != NULL; p = p->pNext)
			cnt++;

		return cnt;
	}
};

class BGIdrawing {
public:
	void drawDisk(int order, int i, int posStack) {
		int height, width, x, y;
		height = (500 + 30 * numOfDisks) / 2;
		width = 300 * i / numOfDisks;
		posStack == 1 ? x = 200 : posStack == 2 ? x = 600 : x = 1000;
		y = height - 35 * order;

		setlinestyle(0, 0, 2);
		bar3d(x - width / 2, y, x + width / 2, y + 30, 10, 10);
		char str[2]; _itoa_s(i, str, 10);
		settextstyle(0, 0, 2); outtextxy(x, y, str);
	}

	void drawStack(List& A, int posStack) {
		int len = A.lengthOfList();
		for (Node* p = A.pHead; p != NULL; p = p->pNext) {
			setcolor(posStack == 1 ? 9 : posStack == 2 ? 12 : 14);
			this->drawDisk(len, p->data, posStack);
			len--;
		}
	}

	void drawAllStack(List& A, List& B, List& C) {
		cleardevice();
		settextstyle(0, 0, 3);
		setcolor(9);  outtextxy(200, 450, "A");
		setcolor(12); outtextxy(600, 450, "B");
		setcolor(14); outtextxy(1000, 450, "C");
		this->drawStack(A, 1);
		this->drawStack(B, 2);
		this->drawStack(C, 3);
	}
};

// A : ee8
// B : ee0
// C : ed8

BGIdrawing T;
List A;
List B;
List C;
List* x = &A;
List* y = &B;
List* z = &C;

string getPosition(List *pT) {
	if (pT == x) return "A";
	if (pT == y) return "B";
	if (pT == z) return "C";
}

void moveDisks(int disksToMove, List& A, List& B, List& C) {
	if (disksToMove != 0) {
		if (_kbhit()) system("pause");
		cntMoveSteps++;

		moveDisks(disksToMove - 1, A, C, B);

		int value = A.removeHead();
		C.addHead(value);
		cout << "\t" << getPosition(&A) << " -> " << getPosition(&C) << " .. Gia tri: " << value << endl;
		T.drawAllStack(*x, *y, *z); Sleep(500);

		moveDisks(disksToMove - 1, B, A, C);
	}
}


int main() {
	srand(time(NULL));
	initwindow(1200, 500);
	system("mode 35, 20");

	cout << "Nhap vao so luong dia ban dau : ";
	cin >> numOfDisks; cin.ignore();

	A.initDisk(numOfDisks);

	T.drawAllStack(A, B, C); Sleep(500);

	moveDisks(numOfDisks, A, B, C);

	cout << "Tong so buoc di chuyen : " << cntMoveSteps;

	getchar();
	closegraph();
	return 0;
}
