#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 8 //�迭�� ���� ����
#define SWAP(a,b) {float t; t= a; a=b; b=t;}  //SWAP�� ������ ���(selection, bubble sort ���) - call by value

void ViewArr(float arr[]) { // ���İ����� �����ֱ� ���� �Լ�
	for (int i = 0; i <MAX; i++) {
		printf(" %.3f", arr[i]);
	}
	printf("\n");
}

void swap(float* a, float* b) {  // swap �Լ�(heap sort ���) - call by reference
	float temp = *a;
	*a = *b;
	*b = temp;

}
void selection_sort(float arr[]) { //�������� �Լ�
	int i, j;
	int maxi;
	for (i = MAX; i > 1; i--) { //�������� for ��
		maxi = 0;
		for (j = 1; j < i; j++) { //arr[j]�� �������� arr[maxi]�� �˻��Ͽ� arr[j]�� �� ���� ���� ���� �߰��ϸ� maxi=j�� �ȴ�.
			if (arr[maxi] < arr[j]) 
			{
				maxi = j;
			}
		}
		SWAP(arr[maxi], arr[i - 1]); //���� for���� �ݺ����� ���� ���� ���� ã���� ������ �ٲ۴�.
		ViewArr(arr); //�������� ������ �����ִ� �Լ� ȣ��
	}
}


void bubble_sort(float arr[]) { //�������� �Լ�
	int i, j;
	float temp;
	for (i = 0; i<MAX -1; i++) // �������� for��
	{
		for (j = 0; j < MAX-1-i; j++)
		{
			if (arr[j] > arr[j + 1]) //arr[j]�� �������� arr[j+1] �˻��Ͽ� arr[j]�� �� ���� ū ���� �߰��ϸ� swap�� ���ش�.
			{
				temp = arr[j]; // bubblesort swap �ϴ� ����
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				ViewArr(arr); //�������� ������ �����ִ� �Լ� ȣ��
			}
		}
	}
}

void insertion_sort(float arr[]) { //�������� �Լ�
	int j;
	float key;
	for (int i = 1; i < MAX; i++) {
		key = arr[i];
		j = i - 1;
		for (j = i - 1; j>=0 && arr[j]>key; j--) { //for���� ���� �� ���ǿ� ������ �Ǹ� arr[j] ���� arr[j+1]�� ����
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
		ViewArr(arr); // �������� ������ �����ִ� �Լ� ȣ��
	}
}
void merge(float list[], int left, int mid, int right, float arr[]) { //�������Ŀ� �ʿ��� �Լ�
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
	if (i > mid) {  // ���� �ִ� ���� ����
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
void merge_sort(float list[], int left, int right, float arr[]) { // ���� ����
	int mid;
	
	if (left < right) { // right�� ���� left ������ Ŭ �� 
		mid = (left + right) / 2; // �߰��� ��ġ�� ���� ����� �յ� ����
		merge_sort(list, left, mid,arr); // �� �κ�(����) �κ� ����Ʈ ���İ���
		merge_sort(list, mid + 1, right,arr); // �� �κ�(������) �κ� ����Ʈ ���İ���
		merge(list, left, mid,  right, arr); // �� �κ� �� �κ� �����ϴ� ����
		ViewArr(arr); //�������� ������ �����ִ� �Լ�
	}
}
void quick_sort(float arr[], int start, int end) { // �� ����

	if (start >= end) { //sort�� ���Ұ� 1���� ���
		return;
	}
	int pivot = start;
	int i = pivot + 1; // ���� �κ� ���
	int j = end; // ������ �κ� ���
	float temp;

	while (i <= j) {
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
	ViewArr(arr); // �������� �����ִ� �Լ�
	
	
}
void heapify(float arr[], int here, int size) { //���� ������� ��ġ�� �Լ�
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

void buildHeap(float arr[],int size) { //�ڽ��� ������ �ִ� ��尡 � �ε����� �˾ƺ��� �Լ�
	int i, j;
	for (i = MAX / 2 - 1; i >= 0; i--) { // �θ� ��� �ε���
		heapify(arr, i, size);
		for (j = 0; j < MAX; j++)
			printf(" %.3f", arr[j]); // �� ��尡 ������� �迭 ���
		printf("\n\n");

	}
}
void heapSort(float arr[], int size) { // �� ���� �Լ�
	int treeSize;
	buildHeap(arr, size); // ����� ȣ��(������ �Ǳ� ��)
	for(treeSize = MAX-1; treeSize >= 0; treeSize--) { // ������ �ɶ����� �� ������ �ݺ�
		swap(&arr[0], &arr[treeSize]); // ���� ������ ���� ��������
		heapify(arr, 0, treeSize); // �ٽ� �� ��带 ������ִ� �Լ� ȣ��
		ViewArr(arr); // �� ���� ������ �����ִ� �Լ�
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