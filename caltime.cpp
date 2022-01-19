#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 20000
#define SWAP(a,b) {float t; t= a; a=b; b=t;}

void ViewArr(float arr[]) {
	for (int i = 0; i < MAX; i++) {
		printf(" %.3f", arr[i]);
	}
	printf("\n");
}

void swap(float* a, float* b) {
	float temp = *a;
	*a = *b;
	*b = temp;

}
void selection_sort(float arr[]) {
	int i, j;
	int maxi;
	for (i = MAX; i > 1; i--) {
		maxi = 0;
		for (j = 1; j < i; j++) {
			if (arr[maxi] < arr[j])
			{
				maxi = j;
			}
		}
		SWAP(arr[maxi], arr[i - 1]);

	}
}


void bubble_sort(float arr[]) {
	int i, j;
	float temp;
	for (i = 0; i < MAX - 1; i++)
	{
		for (j = 0; j < MAX - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void insertion_sort(float arr[]) {
	int j;
	float key;
	for (int i = 1; i < MAX; i++) {
		key = arr[i];
		j = i - 1;
		for (j = i - 1; j >= 0 && arr[j] > key; j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;

	}
}
void merge(float list[], int left, int mid, int right, float arr[]) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			arr[k++] = list[i++];
		else
			arr[k++] = list[j++];
	}
	if (i > mid) {
		for (l = j; l <= right; l++)
			arr[k++] = list[l];
	}
	else {
		for (l = i; l <= mid; l++)
			arr[k++] = list[l];
	}
	for (l = left; l <= right; l++) {
		list[l] = arr[l];
	}
}
void merge_sort(float list[], int left, int right, float arr[]) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid, arr);
		merge_sort(list, mid + 1, right, arr);
		merge(list, left, mid, right, arr);

	}
}
void quick_sort(float arr[], int start, int end){
	
if (start >= end) {
		return;
	}
	int pivot = start;
	int i = pivot + 1;
	int j = end;
	float temp;

	while (i <= j) {
		while (i <= end && arr[i] <= arr[pivot]) {
			i++;
		}
		while (j > start && arr[j] >= arr[pivot]) {
			j--;
		}
		if (i > j) {
			temp = arr[j];
			arr[j] = arr[pivot];
			arr[pivot] = temp;
		}
		else {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}

	}
	quick_sort(arr, start, j - 1);
	quick_sort(arr, j + 1, end);

}

void heapify(float arr[], int here, int size) {
	int left = here * 2 + 1;
	int right = here * 2 + 2;
	int max = here;
	if (left<size && arr[left]>arr[max])
		max = left;
	if (right< size && arr[right]>arr[max])
		max = right;

	if (max != here) {
		swap(&arr[here], &arr[max]);
		heapify(arr, max, size);


	}
}

void buildHeap(float arr[], int size) {
	int i, j;
	for (i = MAX / 2 - 1; i >= 0; i--) {
		heapify(arr, i, size);

	}
}
void heapSort(float arr[], int size) {
	int treeSize;
	buildHeap(arr, size);
	for (treeSize = MAX - 1; treeSize >= 0; treeSize--) {
		swap(&arr[0], &arr[treeSize]);
		heapify(arr, 0, treeSize);
	}
}


int main() {

	clock_t start_time, end_time; // ����ð��� �����ϱ� ���� ����
	float arr[MAX], insertion_arr[MAX], bubble_arr[MAX], selection_arr[MAX],
		merge_arr[MAX], quick_arr[MAX], heap_arr[MAX], res_time;

	printf("���� :"); // ���� ����
	for (int i = 0; i < MAX; i++) { //���� ���� arr�� �־��ش�.
		arr[i] = rand() % 100 / 100.0 + rand() % 2 - 1; //rand()���� ���� Seed ���� �־ ���� �� ���� �����ǵ��� <-1 ~ 1 ������ ���� ��>
		printf(" %.3f", arr[i]);
	}
	printf("\n\n");
	printf("N�� �� = %d\n", sizeof(arr) / sizeof(arr[MAX]));
	printf("\n\n");

	for (int i = 0; i < MAX; i++) { //selection_arr�� �־���
		selection_arr[i] = arr[i];
	}
	printf("�������� : \n");
	start_time = clock(); // selection ���� ���۽ð�
	selection_sort(selection_arr);
	end_time = clock(); // selection ���� ����ð�
	res_time = (float)(end_time - start_time) / CLOCKS_PER_SEC; // �������� ����ð��� ���
	printf("***** time : %f ******\n\n", res_time);


	for (int i = 0; i < MAX; i++) { //bubble_arr�� �־���
		bubble_arr[i] = arr[i];
	}
	printf("�������� : \n");
	start_time = clock(); //bubble ���� ���۽ð�
	bubble_sort(bubble_arr);
	end_time = clock(); // bubble ���� ����ð�
	res_time = (float)(end_time - start_time) / CLOCKS_PER_SEC; // �������� ����ð��� ���
	printf("***** time : %f ******\n\n", res_time);

	for (int i = 0; i < MAX; i++) { // insertion_arr�� �־���
		insertion_arr[i] = arr[i];
	}
	printf("�������� : \n");
	start_time = clock(); // insertion ���� ���۽ð�
	insertion_sort(insertion_arr);
	end_time = clock(); // insertion ���� ����ð�
	res_time = (float)(end_time - start_time) / CLOCKS_PER_SEC; // �������� ����ð��� ���
	printf("***** time : %f ******\n\n", res_time);



	for (int i = 0; i < MAX; i++) { // merge_arr�� �־���
		merge_arr[i] = arr[i];
	}
	printf("�������� : \n");
	start_time = clock(); //merge ���� ���۽ð�
	merge_sort(arr, 0, MAX - 1, merge_arr);
	end_time = clock(); //merge ���� ����ð�
	res_time = (float)(end_time - start_time) / CLOCKS_PER_SEC; // �������� ����ð��� ���
	printf("***** time : %f ******\n\n", res_time);

	for (int i = 0; i < MAX; i++) { //quick_arr�� �־���
		quick_arr[i] = arr[i];
	}
	printf("������ : \n");
	start_time = clock(); // quick ���� ���۽ð�
	quick_sort(quick_arr, 0, MAX - 1);
	end_time = clock(); // quick ���� ����ð�
	res_time = (float)(end_time - start_time) / CLOCKS_PER_SEC; // ������ ����ð��� �����
	printf("***** time : %f ******\n\n", res_time);

	for (int i = 0; i < MAX; i++) { //heap_arr�� �־���
		heap_arr[i] = arr[i];
	}
	printf("������ : \n");
	start_time = clock(); // heap ���� ���۽ð�
	heapSort(heap_arr, MAX);
	end_time = clock(); // heap ���� ����ð�
	res_time = (float)(end_time - start_time) / CLOCKS_PER_SEC; // ������ ����ð��� �����
	printf("***** time : %f ******\n\n", res_time);


	return 0;
}