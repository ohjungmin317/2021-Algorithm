#include<stdio.h>
#define MAX_SIZE 100 // �迭SIZE ����

int Binarysearch(int arr[], int searchNum, int low, int high) // Binarysearch�� ���� �Լ� ���� ����
{
	int mid;

	while (low <= high) // �ݺ��� ���� 
	{
		mid = (low + high) / 2; // mid �� ����

		if (arr[mid] < searchNum)
			low = mid + 1; // mid�� ���� ã�� ���� ũ��
 		else if (arr[mid] > searchNum)
			high = mid - 1; // mid�� ���� ã�� ���� ������
		else
			return mid; // mid�� ���� ã�� ���� ������ ��ȯ		
	}
	return -1; // ã�� ���� �ƿ� ������ -1�� ��ȯ
 }

int recursive_Binarysearch(int arr[], int searchNum, int low, int high) // recursive_Binarysearch�� ���� �Լ� ���� ����
{
		
	int mid;
	
	if (low > high)
		return -1; // ã�� ���� ���� �ÿ� -1�� ��ȯ 

		mid = (low + high) / 2; // mid �� ����

		if (arr[mid] < searchNum)
			return recursive_Binarysearch(arr, searchNum, mid + 1, high); // mid ������ ã�� ���� ũ�� low = mid + 1 ����Լ��� ��ȯ
		else if (arr[mid] > searchNum)
			return recursive_Binarysearch(arr, searchNum, low, mid - 1); // mid ������ ã�� ���� ������ right = mid - 1 ����Լ��� ��ȯ
		else
			return mid; // mid ���� ã�� ���� mid ������ ��ȯ
	
}
	


int main() // ����Ž��(�ݺ����� �̿��� ����Ž�� + ���ȣ���� ���� ����Ž���� ���� �� �Է� �� ���)
{
	int n;
	int arr[MAX_SIZE];
	printf("������ �迭�� ������ �Է��Ͻÿ�: ");
	scanf("%d\n", &n); // ������ �迭�� ���� �Է�

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]); // ������ �迭�� �������� �Էµ� ���� �޾� ����
	}

	int searchNum;
	printf("============�ݺ����� ���� ����Ž��============\n");
	printf("ã�� ���ڸ� �Է��Ͻÿ�: ");
	scanf("%d", &searchNum); // ã���� �ϴ� �� �Է�
	int index = Binarysearch(arr, searchNum, 0, n - 1); //�ݺ����� ���� ����Ž�� �Լ� ȣ��
	if (index == -1) 
		printf("����\n"); // index�� ���� -1�� ȣ��Ǿ����� 
	else 
		printf("%d\n", index + 1); // �� �ܰ��� [index + 1 == �迭�� ��ġ]���

	printf("============���ȣ���� ���� ����Ž��============\n");
	printf("ã�� ���ڸ� �Է��Ͻÿ�: ");
	scanf("%d", &searchNum); // ã���� �ϴ� �� �Է�
	index = recursive_Binarysearch(arr, searchNum, 0, n - 1); // ���ȣ���� ���� �Լ� ȣ��
	if (index == -1) // index�� ���� -1�� ȣ��Ǿ�����
		printf("����\n");
	else
		printf("%d\n", index + 1); // �� �ܰ��� [index + 1 == �迭�� ��ġ]���
	}

