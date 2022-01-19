#include<stdio.h>
#define MAX_SIZE 100 // 배열SIZE 정의

int Binarysearch(int arr[], int searchNum, int low, int high) // Binarysearch에 대한 함수 변수 선언
{
	int mid;

	while (low <= high) // 반복문 실행 
	{
		mid = (low + high) / 2; // mid 값 정의

		if (arr[mid] < searchNum)
			low = mid + 1; // mid값 보다 찾는 수가 크면
 		else if (arr[mid] > searchNum)
			high = mid - 1; // mid값 보다 찾는 수가 작으면
		else
			return mid; // mid의 값이 찾는 수와 같으면 반환		
	}
	return -1; // 찾는 값이 아예 없으면 -1로 반환
 }

int recursive_Binarysearch(int arr[], int searchNum, int low, int high) // recursive_Binarysearch에 대한 함수 변수 선언
{
		
	int mid;
	
	if (low > high)
		return -1; // 찾는 값이 없을 시에 -1로 반환 

		mid = (low + high) / 2; // mid 값 정의

		if (arr[mid] < searchNum)
			return recursive_Binarysearch(arr, searchNum, mid + 1, high); // mid 값보다 찾는 수가 크면 low = mid + 1 재귀함수값 반환
		else if (arr[mid] > searchNum)
			return recursive_Binarysearch(arr, searchNum, low, mid - 1); // mid 값보다 찾는 수가 작으면 right = mid - 1 재귀함수값 반환
		else
			return mid; // mid 값이 찾는 수면 mid 값으로 반환
	
}
	


int main() // 이진탐색(반복문을 이용한 이진탐색 + 재귀호출을 통한 이진탐색에 대한 값 입력 및 출력)
{
	int n;
	int arr[MAX_SIZE];
	printf("저장할 배열의 갯수를 입력하시오: ");
	scanf("%d\n", &n); // 저장할 배열의 개수 입력

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]); // 지정된 배열의 개수에서 입력된 값을 받아 저장
	}

	int searchNum;
	printf("============반복문을 통한 이진탐색============\n");
	printf("찾을 숫자를 입력하시오: ");
	scanf("%d", &searchNum); // 찾고자 하는 수 입력
	int index = Binarysearch(arr, searchNum, 0, n - 1); //반복문을 통한 이진탐색 함수 호출
	if (index == -1) 
		printf("실패\n"); // index의 값이 -1이 호출되었을때 
	else 
		printf("%d\n", index + 1); // 그 외것은 [index + 1 == 배열의 위치]출력

	printf("============재귀호출을 통한 이진탐색============\n");
	printf("찾을 숫자를 입력하시오: ");
	scanf("%d", &searchNum); // 찾고자 하는 수 입력
	index = recursive_Binarysearch(arr, searchNum, 0, n - 1); // 재귀호출을 통한 함수 호출
	if (index == -1) // index의 값이 -1이 호출되었을때
		printf("실패\n");
	else
		printf("%d\n", index + 1); // 그 외것은 [index + 1 == 배열의 위치]출력
	}

