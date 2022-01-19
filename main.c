#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 8 //배열의 개수 정의
#define SWAP(a,b) {int t; t= a; a=b; b=t;} //SWAP을 정의해 사용(selection, bubble sort 사용) - call by value

void ViewArr(int arr[])  { // 정렬과정을 보여주기 위한 함수
	for (int i = 0; i < MAX; i++) {
		printf(" %d", arr[i]);
	}
	printf("\n");
}

void swap(int* a, int* b) { // swap 함수(heap sort 사용) - call by reference
	int temp = *a;
	*a = *b;
	*b = temp;

}

void selection_sort(int arr[]) { //선택정렬 함수
	int i, j;
	int maxi;
	for (i = MAX; i > 1; i--) { //오름차순 for 문
		maxi = 0;
		for (j = 1; j < i; j++) {
			if (arr[maxi] < arr[j]) //arr[j]를 기준으로 arr[maxi]를 검사하여 arr[j]의 값 보다 작은 값을 발견하면 maxi=j가 된다.
			{
				maxi = j;
			}
		}
		SWAP(arr[maxi], arr[i - 1]); //내부 for문의 반복으로 가장 작은 값을 찾으면 순서를 바꾼다.
		ViewArr(arr); //선택정렬 과정을 보여주는 함수 호출
	}
}

void bubble_sort(int arr[]) { //버블정렬 함수
	int i, j;
	for (i = MAX-1; i > 0; i--) // 오름차순 for문
	{
		for (j = 0; j < i; j++)
		{
			if (arr[j] > arr[j+1])//arr[j]를 기준으로 arr[j+1] 검사하여 arr[j]의 값 보다 큰 값을 발견하면 swap을 해준다.
			{
				SWAP(arr[j], arr[j+1]); //SWAP 이용 call-by-value
				ViewArr(arr);//버블정렬 과정을 보여주는 함수 호출
			}
		}
	}
}

void insertion_sort(int arr[]) { //삽입정렬 함수
	int i, j,key;
	for (i = 1; i < MAX; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key) { //while문을 돌려 위 조건에 만족이 되면 arr[j] 값을 arr[j+1]에 대입
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
		ViewArr(arr); // 삽입정렬 과정을 보여주는 함수 호출
	}
}
void merge(int list[], int left, int mid, int right, int arr[]) { //병합정렬에 필요한 함수
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right) { // 분할정렬이 된 list의 합병 과정
		if (list[i] <= list[j])
			arr[k++] = list[i++];
		else
			arr[k++] = list[j++];
	}
	if (i > mid) { // 남아 있는 값들 복사
		for (l = j; l <= right; l++)
			arr[k++] = list[l];
	}
	else { // 남아 있는 값들 복사
		for (l = i; l <= mid; l++)
			arr[k++] = list[l];
	}
	for (l = left; l <= right; l++) { // 임시배열 list를 배열 list[]에 다시 복사
		list[l] = arr[l];
	}
}
void merge_sort(int list[], int left, int right, int arr[]) { // 병합 정렬
	int mid;

	if (left < right) { // right의 값이 left 값보다 클 때 
		mid = (left + right) / 2; // 중간에 위치한 값을 계산해 균등 분할
		merge_sort(list, left, mid, arr); // 앞 부분(왼쪽) 부분 리스트 정렬과정
		merge_sort(list, mid + 1, right, arr); // 뒷 부분(오른쪽) 부분 리스트 정렬과정
		merge(list, left, mid, right, arr);// 앞 부분 뒷 부분 병합하는 과정
		ViewArr(arr);//병합정렬 과정을 보여주는 함수
	}
}

void quick_sort(int arr[], int start, int end) { // 퀵 정렬

	if (start >= end) { //sort의 원소가 1개인 경우
		return;
	}
	int pivot = start;
	int i = pivot + 1; // 왼쪽 부분 출발
	int j = end; // 오른쪽 부분 출발
	int temp;

	while (i <= j) { //pivot이 엇갈릴때까지 반복
		while (i <= end && arr[i] <= arr[pivot]) {
			i++;
		}
		while (j > start && arr[j] >= arr[pivot]) {
			j--;
		}
		if (i > j) { //pivot이 엇갈릴 때
			temp = arr[j];
			arr[j] = arr[pivot];
			arr[pivot] = temp;
		}
		else { // 그 외는 i번째와 j번째 swap해준다.
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}

	}
	quick_sort(arr, start, j - 1); //end 부분 계산
	quick_sort(arr, j + 1, end); // start 부분 계산
	ViewArr(arr);// 퀵정렬을 보여주는 함수


}
	void heapify(int arr[], int here, int size) { //힙의 모양으로 고치는 함수
		int left = here * 2 + 1;
		int right = here * 2 + 2;
		int max = here;
		if (left<size && arr[left]>arr[max]) // 위 조건을 만족하면
			max = left; // max 값은 left
		if (right< size && arr[right]>arr[max]) // 다음 조건을 만족하면
			max = right; // max 값은 right

		if (max != here) { // here 이 max값이 아니면 
			swap(&arr[here], &arr[max]); // swap해준다.
			heapify(arr, max, size);


		}
	}

	
	

void buildHeap(int arr[], int size) { //자식을 가지고 있는 노드가 어떤 인덱스를 알아보는 함수
	int i, j;
	for (i = size / 2 - 1; i >= 0; i--) { // 부모 노드 인덱스
		heapify(arr, i, size);
		for (j = 0; j < size; j++)
			printf(" %d", arr[j]); // 힙 노드가 만들어진 배열 출력
		printf("\n");

	}
}
void heapSort(int arr[],int size) { // 힙 정렬 함수
	int treeSize;
	buildHeap(arr, size); // 힙노드 호출(정렬이 되기 전)
	for (treeSize = size -1; treeSize >= 0; treeSize--) { // 정렬이 될때까지 위 과정을 반복
		swap(&arr[0], &arr[treeSize]); // 정렬 과정중 힙이 무너지면
		heapify(arr, 0, treeSize); // 다시 힙 노드를 만들어주는 함수 호출
		ViewArr(arr); // 힙 정렬 과정을 보여주는 함수
	}
}

int main() {

	int insertion_arr[MAX], bubble_arr[MAX], selection_arr[MAX],
		merge_arr[MAX], quick_arr[MAX], heap_arr[MAX];

	int arr[] = { 12,30,21,55,25,72,45,50 };

	for (int i = 0; i < MAX; i++) {
		selection_arr[i] = arr[i];
	}
	printf("선택정렬:\n");
	ViewArr(selection_arr);
	selection_sort(selection_arr); // 선택정렬 함수 호출
	ViewArr(selection_arr);
	printf("\n");

	for (int i = 0; i < MAX; i++) {
		bubble_arr[i] = arr[i];
	}
	printf("버블정렬:\n");
	ViewArr(bubble_arr);
	bubble_sort(bubble_arr); // 버블정렬 함수 호출
	ViewArr(bubble_arr);
	printf("\n");

	for (int i = 0; i < MAX; i++) {
		insertion_arr[i] = arr[i];
	}
	printf("삽입정렬:\n");
	printf("\n");
	insertion_sort(insertion_arr); // 삽입정렬 함수 호출
	ViewArr(insertion_arr);
	printf("\n");

	for (int i = 0; i < MAX; i++) {
		merge_arr[i] = arr[i];
	}
	printf("병합정렬:\n");
	printf("\n");
	merge_sort(arr, 0, MAX - 1, merge_arr); // 병합정렬 함수 호출
	ViewArr(merge_arr);
	printf("\n");

	for (int i = 0; i < MAX; i++) {
		quick_arr[i] = arr[i];
	}
	printf("퀵정렬:\n");
	printf("\n");
	ViewArr(quick_arr);
	quick_sort(quick_arr, 0, MAX - 1); // 퀵정렬 함수 호출
	ViewArr(quick_arr);
	printf("\n");

	for (int i = 0; i < MAX; i++) {
		heap_arr[i] = arr[i];
	}
	printf("힙정렬:\n");
	printf("\n");
	heapSort(heap_arr, MAX); // 힙정렬 함수 호출
	printf("\n");


	return 0;
}