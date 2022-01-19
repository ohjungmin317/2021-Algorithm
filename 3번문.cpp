#pragma warning (disable: 4996) // scanf ���� ���� ����
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 9999

int TSP(int n, int** W, int** D, int i, int A, int** P) {//D[i][A] ���� ���ؼ� �����ϴ� �Լ�
	int m;
	int min = MAX;
	int temp;

	if (A == 0) { //A�� �������� ��
		return W[i][1];
	}
	else { //A�� �������� �ƴ� ��
		for (m = 0; m <= n - 2; ++m) {

			//A�� 1�� ���� ã�� �˰����� ����
			if ((1 << m) & A) {
				temp = W[i][m + 2] + TSP(n, W, D, m + 2, A - (1 << m), P);
				if (min > temp) {
					min = temp;

					//P[i][A] = 2���� ���� ������ �� �ּҰ��� ����
					P[i][A] = m + 2;
				}
			}
		}
	}
	return min;
}

int main() {

	int i, j;
	int n; // ������ ����
	int inf = MAX;
	// inf MAX ������ ��ȯ


	printf("n���� �Է����ּ���: ");
	scanf("%d", &n);

	int** W = (int**)malloc(sizeof(int*) * (n + 1)); // W martrix�� �� 
	for (i = 0; i <= n; ++i)
		W[i] = (int*)malloc(sizeof(int) * (n + 1));

	int** D = (int**)malloc(sizeof(int*) * (n + 1));
	for (i = 0; i <= n; ++i)
		D[i] = (int*)malloc(sizeof(int) * (1 << n));
	//bit �����ڸ� �̿��Ͽ� ������ Ȯ�� �� �� ���

	int** P = (int**)malloc(sizeof(int*) * (n + 1));
	for (i = 0; i <= n; ++i)
		P[i] = (int*)malloc(sizeof(int) * (1 << n));

	printf("\n");
	printf("matrix ���� �Է����ּ���.\n");

	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			scanf("%d", &W[i][j]); // �迭 �� �Է�
		}
		printf("\n");
	}

	
	//A�� ������ �湮�ؾ��� ������ ����
	
	int A = 0;
	for (i = 0; i <= n - 2; ++i) {
		A += (1 << i);
	}

	//Length = D[1][V - {v1}]�� ���� ��� 
	int Length = TSP(n, W, D, 1, A, P);
	int path;

	//�ּҰ�� ���
	printf("\n");
	printf("------------------------------\n");
	printf("�ּҰ��: v1 -> ");

	path = P[1][A];
	printf("v%d -> ", path);
	for (i = 0; i < n - 2; ++i) {
		A -= 1 << (path - 2);
		path = P[path][A];
		printf("v%d -> ", path);
	}
	//�ּҰ�� �� ��� 
	printf("v1\n");
	printf("\n");
	printf("�ּҰ���� ���̴� %d�Դϴ�.\n", Length);

	return 0;
}