#include<stdio.h>
#define V 7
#define INF 99999 // INF �� => ���Ѵ� �� �ʱ�ȭ �� ����
const int W[V+1][V+1] = {{0,0,0,0,0,0,0}, // ���� 1 ~ 2�� 2���� �迭�� ������
	{0,0,4,INF,INF,INF,10,INF},
	{0,3,0,INF,18,INF,INF,INF},
	{0,INF,6,0,INF,INF,INF,INF},
	{0,INF,5,15,0,2,19,5},
	{0,INF,INF,12,1,0,INF,INF},
	{0,INF,INF,INF,INF,INF,0,10},
	{0,INF,INF,INF,8,INF,INF,0} 
}; // �÷��̵� Ž�� 2�߹迭 �ʱ�ȭ

int D[V+1][V+1]; // D martrix����
int P[V+1][V+1]; // p martrix����

void floyd(int n, const int (*W)[V+1], int (*D)[V+1], int (*P)[V+1]) {// floyd��� ���� �̸��� ���� �Լ��� ���� �ؼ� ����

	int i, j, k;
	for (i = 1; i <= n; i++) // matrix P �ʱ�ȭ
	{
		for (j = 1; j <= n; j++)
			P[i][j] = 0;
	}
			

	for (i = 1; i <=n ; i++) { // D == W
		for (j = 1; j <= n; j++) {
			D[i][j] = W[i][j];
		}
	}
	

	for (k = 1; k <= n; k++) // ���İ��� ��� 
	{
		for (i = 1; i <=n; i++) // ����ϴ� ��� 
		{
			for (j = 1; j <=n; j++) // �����ϴ� ���
			{
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}

void path(int q, int r) { // �ִܰ�θ� �����ִ� ���� ����ϴ� �Լ� 
	printf("path(%d,%d) =%d\n", q, r, P[q][r]);
	if (P[q][r] != 0) { // ���İ��� ��ΰ� 0�� �ƴ� �� path �� ���
		path(q, P[q][r]);
		printf("v%d \n", P[q][r]);
		path(P[q][r], r);
	}
	
}

int main(void) {
	floyd(V, W, D, P); //floyd �Լ� ȣ��
	printf("D\n");
	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			printf("%3d ", D[i][j]); // D matrix ���
		}
		printf("\n");
	}
	printf("\n");

	printf("---------------------------\n");
	printf("\n");
	printf("P\n");

	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			printf("%3d ", P[i][j]); // P matrix ���
		}
		printf("\n");
	}
	printf("\n");
	
	printf("---------------------------\n");

	printf("\n");

	path(7,3); // path �� ���� 7 ~ 3���� ���� �� ����

	printf("\n");
	return 0;
}
