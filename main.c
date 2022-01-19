#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 8 //�迭�� ���� ����
#define SWAP(a,b) {int t; t= a; a=b; b=t;} //SWAP�� ������ ���(selection, bubble sort ���) - call by value

void ViewArr(int arr[])  { // ���İ����� �����ֱ� ���� �Լ�
	for (int i = 0; i < MAX; i++) {
		printf(" %d", arr[i]);
	}
	printf("\n");
}

void swap(int* a, int* b) { // swap �Լ�(heap sort ���) - call by reference
	int temp = *a;
	*a = *b;
	*b = temp;

}

void selection_sort(int arr[]) { //�������� �Լ�
	int i, j;
	int maxi;
	for (i = MAX; i > 1; i--) { //�������� for ��
		maxi = 0;
		for (j = 1; j < i; j++) {
			if (arr[maxi] < arr[j]) //arr[j]�� �������� arr[maxi]�� �˻��Ͽ� arr[j]�� �� ���� ���� ���� �߰��ϸ� maxi=j�� �ȴ�.
			{
				maxi = j;
			}
		}
		SWAP(arr[maxi], arr[i - 1]); //���� for���� �ݺ����� ���� ���� ���� ã���� ������ �ٲ۴�.
		ViewArr(arr); //�������� ������ �����ִ� �Լ� ȣ��
	}
}

void bubble_sort(int arr[]) { //�������� �Լ�
	int i, j;
	for (i = MAX-1; i > 0; i--) // �������� for��
	{
		for (j = 0; j < i; j++)
		{
			if (arr[j] > arr[j+1])//arr[j]�� �������� arr[j+1] �˻��Ͽ� arr[j]�� �� ���� ū ���� �߰��ϸ� swap�� ���ش�.
			{
				SWAP(arr[j], arr[j+1]); //SWAP �̿� call-by-value
				ViewArr(arr);//�������� ������ �����ִ� �Լ� ȣ��
			}
		}
	}
}

void insertion_sort(int arr[]) { //�������� �Լ�
	int i, j,key;
	for (i = 1; i < MAX; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key) { //while���� ���� �� ���ǿ� ������ �Ǹ� arr[j] ���� arr[j+1]�� ����
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
		ViewArr(arr); // �������� ������ �����ִ� �Լ� ȣ��
	}
}
void merge(int list[], int left, int mid, int right, int arr[]) { //�������Ŀ� �ʿ��� �Լ�
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right) { // ���������� �� list�� �պ� ����
		if (list[i] <= list[j])
			arr[k++] = list[i++];
		else
			arr[k++] = list[j++];
	}
	if (i > mid) { // ���� �ִ� ���� ����
		for (l = j; l <= right; l++)
			arr[k++] = list[l];
	}
	else { // ���� �ִ� ���� ����
		for (l = i; l <= mid; l++)
			arr[k++] = list[l];
	}
	for (l = left; l <= right; l++) { // �ӽù迭 list�� �迭 list[]�� �ٽ� ����
		list[l] = arr[l];
	}
}
void merge_sort(int list[], int left, int right, int arr[]) { // ���� ����
	int mid;

	if (left < right) { // right�� ���� left ������ Ŭ �� 
		mid = (left + right) / 2; // �߰��� ��ġ�� ���� ����� �յ� ����
		merge_sort(list, left, mid, arr); // �� �κ�(����) �κ� ����Ʈ ���İ���
		merge_sort(list, mid + 1, right, arr); // �� �κ�(������) �κ� ����Ʈ ���İ���
		merge(list, left, mid, right, arr);// �� �κ� �� �κ� �����ϴ� ����
		ViewArr(arr);//�������� ������ �����ִ� �Լ�
	}
}

void quick_sort(int arr[], int start, int end) { // �� ����

	if (start >= end) { //sort�� ���Ұ� 1���� ���
		return;
	}
	int pivot = start;
	int i = pivot + 1; // ���� �κ� ���
	int j = end; // ������ �κ� ���
	int temp;

	while (i <= j) { //pivot�� ������������ �ݺ�
		while (i <= end && arr[i] <= arr[pivot]) {
			i++;
		}
		while (j > start && arr[j] >= arr[pivot]) {
			j--;
		}
		if (i > j) { //pivot�� ������ ��
			temp = arr[j];
			arr[j] = arr[pivot];
			arr[pivot] = temp;
		}
		else { // �� �ܴ� i��°�� j��° swap���ش�.
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}

	}
	quick_sort(arr, start, j - 1); //end �κ� ���
	quick_sort(arr, j + 1, end); // start �κ� ���
	ViewArr(arr);// �������� �����ִ� �Լ�


}
	void heapify(int arr[], int here, int size) { //���� ������� ��ġ�� �Լ�
		int left = here * 2 + 1;
		int right = here * 2 + 2;
		int max = here;
		if (left<size && arr[left]>arr[max]) // �� ������ �����ϸ�
			max = left; // max ���� left
		if (right< size && arr[right]>arr[max]) // ���� ������ �����ϸ�
			max = right; // max ���� right

		if (max != here) { // here �� max���� �ƴϸ� 
			swap(&arr[here], &arr[max]); // swap���ش�.
			heapify(arr, max, size);


		}
	}

	
	

void buildHeap(int arr[], int size) { //�ڽ��� ������ �ִ� ��尡 � �ε����� �˾ƺ��� �Լ�
	int i, j;
	for (i = size / 2 - 1; i >= 0; i--) { // �θ� ��� �ε���
		heapify(arr, i, size);
		for (j = 0; j < size; j++)
			printf(" %d", arr[j]); // �� ��尡 ������� �迭 ���
		printf("\n");

	}
}
void heapSort(int arr[],int size) { // �� ���� �Լ�
	int treeSize;
	buildHeap(arr, size); // ����� ȣ��(������ �Ǳ� ��)
	for (treeSize = size -1; treeSize >= 0; treeSize--) { // ������ �ɶ����� �� ������ �ݺ�
		swap(&arr[0], &arr[treeSize]); // ���� ������ ���� ��������
		heapify(arr, 0, treeSize); // �ٽ� �� ��带 ������ִ� �Լ� ȣ��
		ViewArr(arr); // �� ���� ������ �����ִ� �Լ�
	}
}

int main() {

	int insertion_arr[MAX], bubble_arr[MAX], selection_arr[MAX],
		merge_arr[MAX], quick_arr[MAX], heap_arr[MAX];

	int arr[] = { 12,30,21,55,25,72,45,50 };

	for (int i = 0; i < MAX; i++) {
		selection_arr[i] = arr[i];
	}
	printf("��������:\n");
	ViewArr(selection_arr);
	selection_sort(selection_arr); // �������� �Լ� ȣ��
	ViewArr(selection_arr);
	printf("\n");

	for (int i = 0; i < MAX; i++) {
		bubble_arr[i] = arr[i];
	}
	printf("��������:\n");
	ViewArr(bubble_arr);
	bubble_sort(bubble_arr); // �������� �Լ� ȣ��
	ViewArr(bubble_arr);
	printf("\n");

	for (int i = 0; i < MAX; i++) {
		insertion_arr[i] = arr[i];
	}
	printf("��������:\n");
	printf("\n");
	insertion_sort(insertion_arr); // �������� �Լ� ȣ��
	ViewArr(insertion_arr);
	printf("\n");

	for (int i = 0; i < MAX; i++) {
		merge_arr[i] = arr[i];
	}
	printf("��������:\n");
	printf("\n");
	merge_sort(arr, 0, MAX - 1, merge_arr); // �������� �Լ� ȣ��
	ViewArr(merge_arr);
	printf("\n");

	for (int i = 0; i < MAX; i++) {
		quick_arr[i] = arr[i];
	}
	printf("������:\n");
	printf("\n");
	ViewArr(quick_arr);
	quick_sort(quick_arr, 0, MAX - 1); // ������ �Լ� ȣ��
	ViewArr(quick_arr);
	printf("\n");

	for (int i = 0; i < MAX; i++) {
		heap_arr[i] = arr[i];
	}
	printf("������:\n");
	printf("\n");
	heapSort(heap_arr, MAX); // ������ �Լ� ȣ��
	printf("\n");


	return 0;
}