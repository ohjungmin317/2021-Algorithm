#pragma warning (disable:4996)
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
int w[5] = { 2,12,42,10,7};
int W = 52;
int x[5] = { 0, };

int promising(int i, int col[]) { // n-queen에 대한 promising함수
    int k;
    int bswitch;

    k = 1;
    bswitch = 1;
    while (k < i && bswitch) {
        if (col[i] == col[k] || abs(col[i] - col[k]) == i - k)
            bswitch = 0;
        k++;

    }
    return bswitch;
}

int estimate_n_queens(int n, int col[]) { // monte carlo를 사용하는 함수
    int i, j, z;
    int m, mprod, numnodes;

    int* prom_children = (int*)calloc(n + 1, sizeof(int)); // 자식 노드 값에 rand 값 선언

    int index = 0;
    int flag = 0;

    i = 0;
    numnodes = 1;
    m = 1;
    mprod = 1;

    while (m != 0 && i != n) { // 유망한 노드가 없거나 n값이 조건에 다 만족을 하지 않으면 그때  whlie문을 실행
        mprod = mprod * m;
        numnodes = numnodes + mprod * n;
        i++;
        m = 0;

        for (z = 1; z <= n; z++)
            prom_children[z] = 0;
        for (j = 1; j <= n; j++) {
            col[i] = j;
            if (promising(i, col)) { // 유망한 자식노드가 왼쪽에 있을 경우
                m++;
                for (z = 1; z <= n; z++)
                    if (prom_children[z] == 0) { // 유망한 자식 노드가 오른쪽에 있을 경우
                        prom_children[z] = j;
                        break;
                    }
            }
        }
        if (m != 0) { // 유망한 자식 노드가 오른쪽 왼쪽 둘다 있을 경우
            for (z = 1; z <= n; z++) {
                if (prom_children[z] != 0)
                    index++;
            }
            flag = (rand() % index) + 1; // rand값을 돌려 오른쪽 왼쪽 랜덤값을 선택하게 된다.

            j = prom_children[flag];

            col[i] = j;
            index = 0;
        }
    }
    return numnodes; // numnodes값을 반환하여 위 과정을 반복하게 한다.
}


void nqueen_mont() { // n-queen을 monte carlo를 이용한 것을 출력 
    int i, * col;
    int n = 8;
    srand((unsigned)time(NULL));

    int mon[20];
    int avg = 0;

    col = (int*)calloc(n + 1, sizeof(int));
    for (i = 0; i < 20; i++) {
        mon[i] = estimate_n_queens(n, col);
        printf("%d번째 시도 : %d\n", i + 1, mon[i]);
        avg += mon[i];
    }
    printf("\n");
    printf("평균값 : %d\n", avg / 20); // 20번 임의추출을 하는 것이기 때문에 20개로 나눠서 평균을 계산
    printf("\n");

    free(col);
}

bool promising1(int i, int weight, int total) { // sum of subsets에 대한 promising 함수 
    if (weight + total >= W && (weight == W || weight + w[i + 1] <= W)) // 검사하는 노드가 유망한지 아닌지를 확인 
        return 1;
    else
        return 0;
    //weight 이동한 가지들은 가중치를 더해서 계산하는 변수
   //total: 가지치기에 활용하기 위해서 집합 w의 모든 원소 합을 저장하는 변수

}

void print() { // 결과값과 과정을 출력하는 함수 
    int i;
    for (i = 0; i < 5; i++) {
        if (x[i] != 0) {
            printf("W=%d ", x[i]);
        }
    }
    printf("\n");
}

void sum_of_subset_cal(int i, int weight, int total) { //sum of subsets에 대해 상태공간트리에서 유망한지 아닌지를 확인하여서 맞으면 값을 선택하고 아니면 다시 되돌아가는 함수
    if (promising1(i, weight, total)) {
        if (W == weight)
            print();
        else {
            x[i + 1] = w[i + 1];
            sum_of_subset_cal(i + 1, weight + w[i + 1], total - w[i + 1]);
            x[i + 1] = 0;
            sum_of_subset_cal(i + 1, weight, total - w[i + 1]);
        }
    }
}

void sum_of_subset() { // sum of subset의 값을 보여주는 함수
    int num;
    int total = 0;
    int i;
    printf("W = 52 일때 sum_of_subset 값은:\n");

    for (i = 0; i < 5; i++) {
        total += w[i];
    }
    sum_of_subset_cal(-1, 0, total);

}

int main()
{ // 결과값 출력
    printf("문제 11번\n");
    printf("\n");
    nqueen_mont();
    printf("============================\n");
    printf("\n");
    printf("문제 13번\n");
    printf("\n");
    sum_of_subset();
    

}