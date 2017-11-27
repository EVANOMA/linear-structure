#include<iostream>
using namespace std;

#include "eightqueen.h"
using namespace eightqueen;

int main() {
	int L = 8, W = 8;
	Queen q1(L, W);
	int i = 0;
	for (int j = 0;j < W;++j) {
		//�ȷ����һ�еĽڵ�
		coordinate c(0, j);
		q1.put(c);
		if (find(q1))
			q1.clear();
		else {
			q1.out(c);//ɾ���׸�Ԫ�أ���һ�У�
			cout << "can't find in (0, " << j << " )" << endl;
		}
	}
	q1.count();
	return 0;
}
