#include<stdio.h>
#define INF 99999 /* INF 의 값 int가 나타낼 수 있는 범위를 벗어나면 안된다.*/
#define n 10
int W[n][n]{/*1,2,3번 문제에 대한 배열 초기화 <W 인접행렬식> */
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
/*prim 알고리즘에 사용되는 변수*/
int nearest1[n]; /*1번 문제에 대한 vi에서 가장 가까운 정점의 인덱스*/
int distance1[n];/*1번 문제에 대한 vi와 nearest[]를 잇는 이음선 가중치*/

int nearest2[n];/*2번 문제에 대한 vi에서 가장 가까운 정점의 인덱스*/
int distance2[n];/*2번 문제에 대한 VI와 nearest[]를 잇는 이음선 가중치*/

/*kruskal 정점을 나타낼 때 사용되는 변수*/
int show_vertex[n] = {1,2,3,4,5,6,7,8,9,10};
/*정점을 잇는 것을 보여주기 int형 배열 초기화*/

int min_vertex(int s) {/*최소 distance[v]값을 갖는 정점을 반환해주는 함수*/
	int vnear, i;
	for (i = 0; i < s; i++) {
		if (!nearest1[i]) {
			vnear = i;/*i의 값을 v의 값으로 누적*/
			break;
		}
	}
	for (i = 0; i < s; i++) {/*선택을 아직 하지 않는 간선들 중 최소 가중치 값을 갖는 정점을 찾는 함수*/
		if (!nearest1[i] && (distance1[i] < distance1[vnear]))
			vnear = i;
	}
	return (vnear);/*위 조건에 만족하면 return(v)로 반환*/

}
void prim(int s) { /* Prim 알고리즘 1번문제 시작점이 V1일 때*/
	int i, vnear, u;
	for (u = 0; u < n; u++)
		distance1[u] = INF;
	distance1[0] = 0; /*V1이 시작점으로 두고 하였을 때 조건 배열의 값은 (n-1)이기 때문에*/

	for (i = 0; i < n; i++) {
		u = min_vertex(n);
		nearest1[u] = -1;/*지나간 경로는 체크하여 -1의 값으로 반환*/

		if (distance1[u] == INF) return; /*경로가 정해저 있지 않는 것은 return 값으로 반환*/

		printf("V%d ", u+1);/*위의 경로를 출력 */

		for (vnear = 0; vnear < n; vnear++) {
			if (W[u][vnear] != INF) {
				if (!nearest1[vnear] && W[u][vnear] < distance1[vnear])
					distance1[vnear] = W[u][vnear];/*위의 값을 확인하여 갱신*/
			}
		}
	}
}
int min_vertex2(int s) { /* Prim 알고리즘 2번문제 시작점이 V8일 때*/
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
	distance2[7] = 0;/* V8이 시작점일 때 선언 */

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

void kruskal() { /*Kruskal 알고리즘*/
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
		/*간선에 대한 정보*/
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (W[i][j] != 0 && W[i][j] != -1 && W[i][j] != 100)
				{
					/*두 정점이 연결이 되었으면 값을 쌓는다.*/
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
		/*사이클이 발생하지 않으면 그래프에 포함*/
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
			/*최소 값을 정렬하여 보여주는 식*/
			printf("(V%d - V%d) : %d\n", show_vertex[a], show_vertex[b], min);
			/*MST를 이요하여 최소 비용의 간선의 길이를 구해주는 부분*/
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
	printf("최소 비용의 간선 길이: ");
	printf("%d\n", sum);
}
int main() {/*각 함수 호출 */
	printf("-Prim Algorithm-\n");
	printf("\n");
	printf("문제 1번\n");
	printf("\n");
	prim(n);
	printf("\n");

	printf("==============================\n");
	printf("\n");
	
	printf("문제 2번\n");
	printf("\n");
	prim2(n);
	printf("\n");

	printf("==============================\n");
	printf("\n");
	printf("-Kruskal Algorithm-\n");
	printf("\n");
	printf("문제 3번\n");
	printf("\n");
	kruskal();

}