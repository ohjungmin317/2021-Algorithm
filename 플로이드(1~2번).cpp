#include<stdio.h>
#define V 7
#define INF 99999 // INF 수 => 무한대 수 초기화 값 정의
const int W[V+1][V+1] = {{0,0,0,0,0,0,0}, // 문제 1 ~ 2번 2차원 배열로 재정의
	{0,0,4,INF,INF,INF,10,INF},
	{0,3,0,INF,18,INF,INF,INF},
	{0,INF,6,0,INF,INF,INF,INF},
	{0,INF,5,15,0,2,19,5},
	{0,INF,INF,12,1,0,INF,INF},
	{0,INF,INF,INF,INF,INF,0,10},
	{0,INF,INF,INF,8,INF,INF,0} 
}; // 플로이드 탐색 2중배열 초기화

int D[V+1][V+1]; // D martrix선언
int P[V+1][V+1]; // p martrix선언

void floyd(int n, const int (*W)[V+1], int (*D)[V+1], int (*P)[V+1]) {// floyd라는 변수 이름을 가진 함수를 정의 해서 선언

	int i, j, k;
	for (i = 1; i <= n; i++) // matrix P 초기화
	{
		for (j = 1; j <= n; j++)
			P[i][j] = 0;
	}
			

	for (i = 1; i <=n ; i++) { // D == W
		for (j = 1; j <= n; j++) {
			D[i][j] = W[i][j];
		}
	}
	

	for (k = 1; k <= n; k++) // 거쳐가는 노드 
	{
		for (i = 1; i <=n; i++) // 출발하는 노드 
		{
			for (j = 1; j <=n; j++) // 도착하는 노드
			{
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}

void path(int q, int r) { // 최단경로를 보여주는 것을 출력하는 함수 
	printf("path(%d,%d) =%d\n", q, r, P[q][r]);
	if (P[q][r] != 0) { // 거쳐가는 경로가 0이 아닐 때 path 값 출력
		path(q, P[q][r]);
		printf("v%d \n", P[q][r]);
		path(P[q][r], r);
	}
	
}

int main(void) {
	floyd(V, W, D, P); //floyd 함수 호출
	printf("D\n");
	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			printf("%3d ", D[i][j]); // D matrix 출력
		}
		printf("\n");
	}
	printf("\n");

	printf("---------------------------\n");
	printf("\n");
	printf("P\n");

	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			printf("%3d ", P[i][j]); // P matrix 출력
		}
		printf("\n");
	}
	printf("\n");
	
	printf("---------------------------\n");

	printf("\n");

	path(7,3); // path 값 선언 7 ~ 3까지 가는 값 선언

	printf("\n");
	return 0;
}
