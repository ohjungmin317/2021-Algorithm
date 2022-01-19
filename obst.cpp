#include<stdio.h>


float p[7] = { NULL, 0.05, 0.15, 0.05, 0.35, 0.05, 0.35 }; // �� index���� Ȯ��

float sum(int begin, int end) // ������ ������ Ȯ���� ���ϴ� �Լ�
{
	float sum = 0;
	for (int i = begin; i <= end; i++)
	{
		sum += p[i];
	}
	return sum;
}

void optbinarysearchtree(int n, int** R) //optimal search binary tree�� ���ϴ� �Լ�
{
	int i, j, k, diagonal;
	float** A = new float* [n + 2];
	float min;
	for (int s = 0; s < n + 2; s++)
		A[s] = new float[n + 1];
	// ��� ���� �ʴ� ���� ó��
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

	// ���� �����ϰ� ���� ������ �÷����鼭 ��� Ž�� Ƚ���� �ּ��� ���� ���ϱ�

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
					R[i][j] = k; // �ּ� ���� �ִ� ��
				}
			}
			A[i][j] = min;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
		printf("   [%d][%d]: %4.3f", i, j, A[i][j]); // ��� Ž�� ���� ����� ��
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
	for (int i = 1; i <= n; i++) //root ��� ���� ����� ��
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


