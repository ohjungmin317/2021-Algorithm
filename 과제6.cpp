#include<stdio.h>
#define INF 99999 /* INF �� �� int�� ��Ÿ�� �� �ִ� ������ ����� �ȵȴ�.*/
#define n 10
int W[n][n]{/*1,2,3�� ������ ���� �迭 �ʱ�ȭ <W ������Ľ�> */
	{0,32,INF,17,INF,INF,INF,INF,INF,INF},
	{32,0,INF,INF,45,INF,INF,INF,INF,INF},
	{INF,INF,0,18,INF,INF,5,INF,INF,INF},
	{17,INF,18,0,10,INF,INF,3,INF,INF},
	{INF,45,INF,10,0,28,INF,INF,25,INF},
	{INF,INF,INF,INF,28,0,INF,INF,INF,6},
	{INF,INF,5,INF,INF,INF,0,59,INF,INF},
	{INF,INF,INF,3,INF,INF,59,0,4,INF},
	{INF,INF,INF,INF,25,INF,INF,4,0,12},
	{INF,INF,INF,INF,INF,6,INF,INF,12,0}
};
/*prim �˰��� ���Ǵ� ����*/
int nearest1[n]; /*1�� ������ ���� vi���� ���� ����� ������ �ε���*/
int distance1[n];/*1�� ������ ���� vi�� nearest[]�� �մ� ������ ����ġ*/

int nearest2[n];/*2�� ������ ���� vi���� ���� ����� ������ �ε���*/
int distance2[n];/*2�� ������ ���� VI�� nearest[]�� �մ� ������ ����ġ*/

/*kruskal ������ ��Ÿ�� �� ���Ǵ� ����*/
int show_vertex[n] = {1,2,3,4,5,6,7,8,9,10};
/*������ �մ� ���� �����ֱ� int�� �迭 �ʱ�ȭ*/

int min_vertex(int s) {/*�ּ� distance[v]���� ���� ������ ��ȯ���ִ� �Լ�*/
	int vnear, i;
	for (i = 0; i < s; i++) {
		if (!nearest1[i]) {
			vnear = i;/*i�� ���� v�� ������ ����*/
			break;
		}
	}
	for (i = 0; i < s; i++) {/*������ ���� ���� �ʴ� ������ �� �ּ� ����ġ ���� ���� ������ ã�� �Լ�*/
		if (!nearest1[i] && (distance1[i] < distance1[vnear]))
			vnear = i;
	}
	return (vnear);/*�� ���ǿ� �����ϸ� return(v)�� ��ȯ*/

}
void prim(int s) { /* Prim �˰��� 1������ �������� V1�� ��*/
	int i, vnear, u;
	for (u = 0; u < n; u++)
		distance1[u] = INF;
	distance1[0] = 0; /*V1�� ���������� �ΰ� �Ͽ��� �� ���� �迭�� ���� (n-1)�̱� ������*/

	for (i = 0; i < n; i++) {
		u = min_vertex(n);
		nearest1[u] = -1;/*������ ��δ� üũ�Ͽ� -1�� ������ ��ȯ*/

		if (distance1[u] == INF) return; /*��ΰ� ������ ���� �ʴ� ���� return ������ ��ȯ*/

		printf("V%d ", u+1);/*���� ��θ� ��� */

		for (vnear = 0; vnear < n; vnear++) {
			if (W[u][vnear] != INF) {
				if (!nearest1[vnear] && W[u][vnear] < distance1[vnear])
					distance1[vnear] = W[u][vnear];/*���� ���� Ȯ���Ͽ� ����*/
			}
		}
	}
}
int min_vertex2(int s) { /* Prim �˰��� 2������ �������� V8�� ��*/
	int vnear, i;
	for (i = 0; i < s; i++) {
		if (!nearest2[i]) {
			vnear = i;
			break;
		}
	}
	for (i = 0; i < s; i++) {
		if (!nearest2[i] && (distance2[i] < distance2[vnear]))
			vnear = i;
	}
	return (vnear);

}
void prim2(int s) {
	int i, vnear, u;
	for (u = 0; u < n; u++)
		distance2[u] = INF;
	distance2[7] = 0;/* V8�� �������� �� ���� */

	for (i = 0; i < n; i++) {
		u = min_vertex2(n);
		nearest2[u] = -1;

		if (distance2[u] == INF) return;

		printf("V%d ", u+1);

		for (vnear = 0; vnear < n; vnear++) {
			if (W[u][vnear] != INF) {
				if (!nearest2[vnear] && W[u][vnear] < distance2[vnear])
					distance2[vnear] = W[u][vnear];
			}
		}
	}
}

void kruskal() { /*Kruskal �˰���*/
	int min, i, j, p, a, b, temp, temp2, cycletime, sum;
	int v[n];

	p = n;
	sum = 0;


	for (i = 0; i < n; i++)
		v[i] = 1;
	for (temp = 0; temp < n - 1;)
	{
		min = INF;
		cycletime = 0;
		/*������ ���� ����*/
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (W[i][j] != 0 && W[i][j] != -1 && W[i][j] != 100)
				{
					/*�� ������ ������ �Ǿ����� ���� �״´�.*/
					if (min > W[i][j])
					{
						min = W[i][j];
						a = i;
						b = j;
					}
				}
			}
		}
		for (i = 0; i < n; i++)
		{
			if (W[a][i] == -1 && W[i][b] == -1)
			{
				W[a][b] = -1;
				W[b][a] = -1;

			}
		}
		/*����Ŭ�� �߻����� ������ �׷����� ����*/
		if (v[a] == -1 && v[b] == -1)
			for (i = 0; i < n; i++)
			{
				if (W[a][i] == -1 && W[i][b] == -1)
				{
					cycletime = 1;
					break;
				}
			}
		if (cycletime == 0)
		{
			/*�ּ� ���� �����Ͽ� �����ִ� ��*/
			printf("(V%d - V%d) : %d\n", show_vertex[a], show_vertex[b], min);
			/*MST�� �̿��Ͽ� �ּ� ����� ������ ���̸� �����ִ� �κ�*/
			v[a] = -1;
			v[b] = -1;
			W[a][b] = -1;
			W[b][a] = -1;
			sum = sum + min;
			temp++;
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				for (temp2 = 0; temp2 < n; temp2++)
				{
					if (W[i][temp2] == -1 && W[temp2][j] == -1)
					{
						W[i][j] = -1;
						W[j][i] = -1;
					}
				}
			}
		}
	}
	printf("�ּ� ����� ���� ����: ");
	printf("%d\n", sum);
}
int main() {/*�� �Լ� ȣ�� */
	printf("-Prim Algorithm-\n");
	printf("\n");
	printf("���� 1��\n");
	printf("\n");
	prim(n);
	printf("\n");

	printf("==============================\n");
	printf("\n");
	
	printf("���� 2��\n");
	printf("\n");
	prim2(n);
	printf("\n");

	printf("==============================\n");
	printf("\n");
	printf("-Kruskal Algorithm-\n");
	printf("\n");
	printf("���� 3��\n");
	printf("\n");
	kruskal();

}