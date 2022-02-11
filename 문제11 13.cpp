#pragma warning (disable:4996)
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
int w[5] = { 2,12,42,10,7};
int W = 52;
int x[5] = { 0, };

int promising(int i, int col[]) { // n-queen�� ���� promising�Լ�
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

int estimate_n_queens(int n, int col[]) { // monte carlo�� ����ϴ� �Լ�
    int i, j, z;
    int m, mprod, numnodes;

    int* prom_children = (int*)calloc(n + 1, sizeof(int)); // �ڽ� ��� ���� rand �� ����

    int index = 0;
    int flag = 0;

    i = 0;
    numnodes = 1;
    m = 1;
    mprod = 1;

    while (m != 0 && i != n) { // ������ ��尡 ���ų� n���� ���ǿ� �� ������ ���� ������ �׶�  whlie���� ����
        mprod = mprod * m;
        numnodes = numnodes + mprod * n;
        i++;
        m = 0;

        for (z = 1; z <= n; z++)
            prom_children[z] = 0;
        for (j = 1; j <= n; j++) {
            col[i] = j;
            if (promising(i, col)) { // ������ �ڽĳ�尡 ���ʿ� ���� ���
                m++;
                for (z = 1; z <= n; z++)
                    if (prom_children[z] == 0) { // ������ �ڽ� ��尡 �����ʿ� ���� ���
                        prom_children[z] = j;
                        break;
                    }
            }
        }
        if (m != 0) { // ������ �ڽ� ��尡 ������ ���� �Ѵ� ���� ���
            for (z = 1; z <= n; z++) {
                if (prom_children[z] != 0)
                    index++;
            }
            flag = (rand() % index) + 1; // rand���� ���� ������ ���� �������� �����ϰ� �ȴ�.

            j = prom_children[flag];

            col[i] = j;
            index = 0;
        }
    }
    return numnodes; // numnodes���� ��ȯ�Ͽ� �� ������ �ݺ��ϰ� �Ѵ�.
}


void nqueen_mont() { // n-queen�� monte carlo�� �̿��� ���� ��� 
    int i, * col;
    int n = 8;
    srand((unsigned)time(NULL));

    int mon[20];
    int avg = 0;

    col = (int*)calloc(n + 1, sizeof(int));
    for (i = 0; i < 20; i++) {
        mon[i] = estimate_n_queens(n, col);
        printf("%d��° �õ� : %d\n", i + 1, mon[i]);
        avg += mon[i];
    }
    printf("\n");
    printf("��հ� : %d\n", avg / 20); // 20�� ���������� �ϴ� ���̱� ������ 20���� ������ ����� ���
    printf("\n");

    free(col);
}

bool promising1(int i, int weight, int total) { // sum of subsets�� ���� promising �Լ� 
    if (weight + total >= W && (weight == W || weight + w[i + 1] <= W)) // �˻��ϴ� ��尡 �������� �ƴ����� Ȯ�� 
        return 1;
    else
        return 0;
    //weight �̵��� �������� ����ġ�� ���ؼ� ����ϴ� ����
   //total: ����ġ�⿡ Ȱ���ϱ� ���ؼ� ���� w�� ��� ���� ���� �����ϴ� ����

}

void print() { // ������� ������ ����ϴ� �Լ� 
    int i;
    for (i = 0; i < 5; i++) {
        if (x[i] != 0) {
            printf("W=%d ", x[i]);
        }
    }
    printf("\n");
}

void sum_of_subset_cal(int i, int weight, int total) { //sum of subsets�� ���� ���°���Ʈ������ �������� �ƴ����� Ȯ���Ͽ��� ������ ���� �����ϰ� �ƴϸ� �ٽ� �ǵ��ư��� �Լ�
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

void sum_of_subset() { // sum of subset�� ���� �����ִ� �Լ�
    int num;
    int total = 0;
    int i;
    printf("W = 52 �϶� sum_of_subset ����:\n");

    for (i = 0; i < 5; i++) {
        total += w[i];
    }
    sum_of_subset_cal(-1, 0, total);

}

int main()
{ // ����� ���
    printf("���� 11��\n");
    printf("\n");
    nqueen_mont();
    printf("============================\n");
    printf("\n");
    printf("���� 13��\n");
    printf("\n");
    sum_of_subset();
    

}