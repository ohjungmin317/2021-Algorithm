#pragma warning (disable: 4996) // scanf 사용시 에러 방지
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 9999

int TSP(int n, int** W, int** D, int i, int A, int** P) {//D[i][A] 값을 구해서 리턴하는 함수
	int m;
	int min = MAX;
	int temp;

	if (A == 0) { //A가 공집합일 때
		return W[i][1];
	}
	else { //A가 공집합이 아닐 때
		for (m = 0; m <= n - 2; ++m) {

			//A가 1인 곳을 찾아 알고리즘을 실행
			if ((1 << m) & A) {
				temp = W[i][m + 2] + TSP(n, W, D, m + 2, A - (1 << m), P);
				if (min > temp) {
					min = temp;

					//P[i][A] = 2개의 값이 나왔을 때 최소값을 저장
					P[i][A] = m + 2;
				}
			}
		}
	}
	return min;
}

int main() {

	int i, j;
	int n; // 정점의 갯수
	int inf = MAX;
	// inf MAX 값으로 반환


	printf("n값을 입력해주세요: ");
	scanf("%d", &n);

	int** W = (int**)malloc(sizeof(int*) * (n + 1)); // W martrix의 값 
	for (i = 0; i <= n; ++i)
		W[i] = (int*)malloc(sizeof(int) * (n + 1));

	int** D = (int**)malloc(sizeof(int*) * (n + 1));
	for (i = 0; i <= n; ++i)
		D[i] = (int*)malloc(sizeof(int) * (1 << n));
	//bit 연산자를 이용하여 공간을 확보 한 후 계산

	int** P = (int**)malloc(sizeof(int*) * (n + 1));
	for (i = 0; i <= n; ++i)
		P[i] = (int*)malloc(sizeof(int) * (1 << n));

	printf("\n");
	printf("matrix 값을 입력해주세요.\n");

	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			scanf("%d", &W[i][j]); // 배열 값 입력
		}
		printf("\n");
	}

	
	//A는 앞으로 방문해야할 정점의 집합
	
	int A = 0;
	for (i = 0; i <= n - 2; ++i) {
		A += (1 << i);
	}

	//Length = D[1][V - {v1}]에 대한 계산 
	int Length = TSP(n, W, D, 1, A, P);
	int path;

	//최소경로 출력
	printf("\n");
	printf("------------------------------\n");
	printf("최소경로: v1 -> ");

	path = P[1][A];
	printf("v%d -> ", path);
	for (i = 0; i < n - 2; ++i) {
		A -= 1 << (path - 2);
		path = P[path][A];
		printf("v%d -> ", path);
	}
	//최소경로 값 출력 
	printf("v1\n");
	printf("\n");
	printf("최소경로의 길이는 %d입니다.\n", Length);

	return 0;
}