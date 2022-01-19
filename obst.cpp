#include<stdio.h>


float p[7] = { NULL, 0.05, 0.15, 0.05, 0.35, 0.05, 0.35 }; // 각 index값의 확률

float sum(int begin, int end) // 정해진 구간이 확률을 더하는 함수
{
	float sum = 0;
	for (int i = begin; i <= end; i++)
	{
		sum += p[i];
	}
	return sum;
}

void optbinarysearchtree(int n, int** R) //optimal search binary tree를 구하는 함수
{
	int i, j, k, diagonal;
	float** A = new float* [n + 2];
	float min;
	for (int s = 0; s < n + 2; s++)
		A[s] = new float[n + 1];
	// 계산 하지 않는 구간 처리
	for (i = 1; i <= n; i++)
	{
		A[i][i - 1] = 0;
		A[i][i] = p[i];
		A[0][i - 1] = 0;


		R[i][i] = i;
		R[i][i - 1] = 0;
		R[0][i - 1] = 0;

	}
	A[0][n] = 0;
	A[n + 1][n] = 0;

	R[0][n] = 0;
	R[n + 1][n] = 0;

	// 구간 변경하고 구간 간격을 늘려가면서 평균 탐색 횟수가 최소인 구간 구하기

	for (diagonal = 1; diagonal <= n - 1; diagonal++)
	{
		for (i = 1; i <= n - diagonal; i++)
		{
			j = i + diagonal;
			min = A[i][i - 1] + A[i + 1][j] + sum(i, j);
			for (k = i; k <= j; k++)
			{
				if (min >= A[i][k - 1] + A[k + 1][j] + sum(i, j))
				{
					min = A[i][k - 1] + A[k + 1][j] + sum(i, j);
					R[i][j] = k; // 최소 값을 주는 값
				}
			}
			A[i][j] = min;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
		printf("   [%d][%d]: %4.3f", i, j, A[i][j]); // 평균 탐색 값을 기록한 값
		printf("\n");
		
		}
		
	}
	for (int s = 0; s < n + 2; s++)
		delete[]A[s];
}

int main()
{
	int n = sizeof(p) / sizeof(float) - 1;

	int** R = new int* [n + 2];

	for (int i = 0; i < n + 2; i++)
	{
		R[i] = new int[n + 1];
	}
	printf("<A>\n");

	optbinarysearchtree(n, R);

	printf("----------------------\n");

	printf("<R>\n");
	for (int i = 1; i <= n; i++) //root 노드 값을 기록한 값
	{
		for (int j = i; j <= n; j++)
		{
			printf("   [%d][%d]: %3d",i,j, R[i][j]);
			printf("\n");

		}
		
	}
	printf("\n");
	printf("[IF] -> [ELSE] -> [CASE] -> [END] -> [THEN] -> [OF]");
	for (int i = 0; i < n + 2; i++) {
		delete[]R[i];

		return 0;
	}
}


