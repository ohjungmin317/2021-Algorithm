#include<stdio.h>
#include<iostream>
#include<set>
#include<map>
#include <climits>
#define N 4
using namespace std;
int main(void) {
	int W_p[5][5] = { { 0,  0,  0,  0,  0 }, //5로 인접행렬 생성 1번째 행렬은 공집합 및 초기화해주는 값
	{ 0,  0,  2, 9, 9999 },
	{ 0,  1,  0,  6,  4 },
	{ 0,  9999, 7,  0, 8 },
	{ 0,  6,  3,  9999,  0 }, };

	set<int> sub[8]; //      거쳐가는 도시에 대한 부분집합들이 모인 set
					 // 거쳐가는 도시가 1개일때의 부분집합 초기화
	sub[1].insert(2); sub[2].insert(3); sub[3].insert(4);
	// 거쳐가는 도시가 2개일때의 부분집합 초기화
	sub[4].insert(2); sub[4].insert(3);
	sub[5].insert(2); sub[5].insert(4);
	sub[6].insert(3); sub[6].insert(4);
	//거쳐가는 도시가 3개일때의 부분집합 초기화
	sub[7].insert(2); sub[7].insert(3); sub[7].insert(4);


	map<pair<int, set<int>>, int>D; //행렬 D, map으로 구현
									//     map< pair< 시작노드 , 노드부분집합>, 그때의 최소값 >
	int min = INT_MAX / 10; // 최소값이 저장되는 int값. + 1 / 10 일 경우 INF값으로 본다

				
	for (int i = 2; i <= N; i++) { //거쳐가는 도시가 공집합일때 경우는 초기화
		D.insert(make_pair(make_pair(i, sub[0]), W_p[i][1]));
	}
	for (int s = 1; s < 8; s++) { //거쳐가는 도시에 대해 15번
		for (int i = 2; i <= N; i++) { // 시작 노드 도시 2부터 4까지 
			if (sub[s].count(i) == 1) // 부분집합에 시작 노드가 있는 경우 넘어감
				continue;
			min = INT_MAX; //small 값 다시 초기화(반복할때마다 초기화해야함)
			for (int j = 2; j <= N; j++) { //거쳐가는 도시(부분집합)에 대해서 하나씩 보면서 비교.

				if (sub[s].count(j) == 0) //부분집합에 j값이 없으면 시행을 하지 않는다.
					;
				else {
					sub[s].erase(j); // 부분집합에서 j를 지움 W[i][j] + D[A -(A1,Aj)를 위해서.)
					if (min > W_p[i][j] + D[make_pair(j, sub[s])]) {
						min = W_p[i][j] + D[make_pair(j, sub[s])]; //제일 작은 값을 small에 저장.
						sub[s].insert(j); // 내용물을 다시 추가. 
						D[make_pair(i, sub[s])] = min; //D[i][A-(A1)] 에 small 값 저장.
					}
					sub[s].insert(j); // 내용물을 다시 추가.
				}
			}
		}
	}


	//D[1]에 대해서 값을 구해줌 위의 알고리즘과 동일. 다만 i값이 1로 고정
	for (int s = 1; s <= 7; s++) {
		min = INT_MAX;
		for (int j = 2; j <= N; j++) {
			if (sub[s].count(j) == 0)
				;
			else {
				sub[s].erase(j); // 그 내용물을 지운다.
				if (min > W_p[1][j] + D.find(make_pair(j, sub[s]))->second) {
					min = W_p[1][j] + D.find(make_pair(j, sub[s]))->second;
					sub[s].insert(j); // 내용물을 다시 추가.
					D[make_pair(1, sub[s])] = min;
				}
				sub[s].insert(j); // 내용물을 다시 추가.
			}
		}
	}
	printf("Traveling salesman person algorithm\n");
	printf("\n");
	printf("D[2]부터 D[4]까지 출력 \n\n");
	//D[2]부터 D[4]까지.출력에 관한 부분. 
	for (int i = 2; i <= N; i++) {
		for (int s = 0; s <= 7; s++) {
			if (sub[s].count(i) == 0) {
				printf("D[%d][", i);
				for (set<int> ::iterator it = sub[s].begin(); it != sub[s].end(); it++) {
					printf("%d ", *it);
				}
				printf("] = %d \n", D[make_pair(i, sub[s])]);
			}
		}
	}

	printf("\nD[1]에 대한 출력 \n\n");
	//D[1] 출력
	for (int s = 0; s <= 7; s++) {
		int i = 1;
		if (sub[s].count(i) == 0) {
			printf("D[%d][", i);
			for (set<int> ::iterator it = sub[s].begin(); it != sub[s].end(); it++) {
				printf("%d ", *it);
			}
			printf("] = %d \n", D[make_pair(i, sub[s])]);
		}


	}
	printf("\n");
	return 0;
}
