#include<stdio.h>
#include<iostream>
#include<set>
#include<map>
#include <climits>
#define N 4
using namespace std;
int main(void) {
	int W_p[5][5] = { { 0,  0,  0,  0,  0 }, //5�� ������� ���� 1��° ����� ������ �� �ʱ�ȭ���ִ� ��
	{ 0,  0,  2, 9, 9999 },
	{ 0,  1,  0,  6,  4 },
	{ 0,  9999, 7,  0, 8 },
	{ 0,  6,  3,  9999,  0 }, };

	set<int> sub[8]; //      ���İ��� ���ÿ� ���� �κ����յ��� ���� set
					 // ���İ��� ���ð� 1���϶��� �κ����� �ʱ�ȭ
	sub[1].insert(2); sub[2].insert(3); sub[3].insert(4);
	// ���İ��� ���ð� 2���϶��� �κ����� �ʱ�ȭ
	sub[4].insert(2); sub[4].insert(3);
	sub[5].insert(2); sub[5].insert(4);
	sub[6].insert(3); sub[6].insert(4);
	//���İ��� ���ð� 3���϶��� �κ����� �ʱ�ȭ
	sub[7].insert(2); sub[7].insert(3); sub[7].insert(4);


	map<pair<int, set<int>>, int>D; //��� D, map���� ����
									//     map< pair< ���۳�� , ���κ�����>, �׶��� �ּҰ� >
	int min = INT_MAX / 10; // �ּҰ��� ����Ǵ� int��. + 1 / 10 �� ��� INF������ ����

				
	for (int i = 2; i <= N; i++) { //���İ��� ���ð� �������϶� ���� �ʱ�ȭ
		D.insert(make_pair(make_pair(i, sub[0]), W_p[i][1]));
	}
	for (int s = 1; s < 8; s++) { //���İ��� ���ÿ� ���� 15��
		for (int i = 2; i <= N; i++) { // ���� ��� ���� 2���� 4���� 
			if (sub[s].count(i) == 1) // �κ����տ� ���� ��尡 �ִ� ��� �Ѿ
				continue;
			min = INT_MAX; //small �� �ٽ� �ʱ�ȭ(�ݺ��Ҷ����� �ʱ�ȭ�ؾ���)
			for (int j = 2; j <= N; j++) { //���İ��� ����(�κ�����)�� ���ؼ� �ϳ��� ���鼭 ��.

				if (sub[s].count(j) == 0) //�κ����տ� j���� ������ ������ ���� �ʴ´�.
					;
				else {
					sub[s].erase(j); // �κ����տ��� j�� ���� W[i][j] + D[A -(A1,Aj)�� ���ؼ�.)
					if (min > W_p[i][j] + D[make_pair(j, sub[s])]) {
						min = W_p[i][j] + D[make_pair(j, sub[s])]; //���� ���� ���� small�� ����.
						sub[s].insert(j); // ���빰�� �ٽ� �߰�. 
						D[make_pair(i, sub[s])] = min; //D[i][A-(A1)] �� small �� ����.
					}
					sub[s].insert(j); // ���빰�� �ٽ� �߰�.
				}
			}
		}
	}


	//D[1]�� ���ؼ� ���� ������ ���� �˰���� ����. �ٸ� i���� 1�� ����
	for (int s = 1; s <= 7; s++) {
		min = INT_MAX;
		for (int j = 2; j <= N; j++) {
			if (sub[s].count(j) == 0)
				;
			else {
				sub[s].erase(j); // �� ���빰�� �����.
				if (min > W_p[1][j] + D.find(make_pair(j, sub[s]))->second) {
					min = W_p[1][j] + D.find(make_pair(j, sub[s]))->second;
					sub[s].insert(j); // ���빰�� �ٽ� �߰�.
					D[make_pair(1, sub[s])] = min;
				}
				sub[s].insert(j); // ���빰�� �ٽ� �߰�.
			}
		}
	}
	printf("Traveling salesman person algorithm\n");
	printf("\n");
	printf("D[2]���� D[4]���� ��� \n\n");
	//D[2]���� D[4]����.��¿� ���� �κ�. 
	for (int i = 2; i <= N; i++) {
		for (int s = 0; s <= 7; s++) {
			if (sub[s].count(i) == 0) {
				printf("D[%d][", i);
				for (set<int> ::iterator it = sub[s].begin(); it != sub[s].end(); it++) {
					printf("%d ", *it);
				}
				printf("] = %d \n", D[make_pair(i, sub[s])]);
			}
		}
	}

	printf("\nD[1]�� ���� ��� \n\n");
	//D[1] ���
	for (int s = 0; s <= 7; s++) {
		int i = 1;
		if (sub[s].count(i) == 0) {
			printf("D[%d][", i);
			for (set<int> ::iterator it = sub[s].begin(); it != sub[s].end(); it++) {
				printf("%d ", *it);
			}
			printf("] = %d \n", D[make_pair(i, sub[s])]);
		}


	}
	printf("\n");
	return 0;
}
