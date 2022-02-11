#include<stdio.h>
#include<iostream>
#include<set>
#include<time.h>
using namespace std;
bool promising(int i, int weight, int total, int W, int* w);
int estimate(int n, int W, int* w);
int main(void) {
	int w[7]; // 1 ~ 6���� ���� ���� �ִ� �迭
	int total = 0; // ��ü Ƚ�� �����ִ� ���� 0���� �ʱ�ȭ
	int estimate_value = 0; // return �� �������ַ��� ����
	srand(time(NULL)); // �������� �ֱ� ����
	w[0] = 0, w[1] = 2, w[2] = 10, w[3] = 13, w[4] = 17, w[5] = 22, w[6] = 42;
	printf("���� 14�� 17��\n");
	printf("\n");
	for (int i = 0; i < 20; i++) { // 20�� ���� �ϱ� ���� for�� ������
		estimate_value = estimate(6, 52, w);
		total += estimate_value;
		printf("%d��° ���� : %d\n", i + 1, estimate_value);
	}
	printf("\n");
	printf("\n");
	printf("��� : %d", total / 20);


}
int estimate(int n, int W, int* w) { // Monte Carlo �̿��ϱ� ���� �Լ�
	int weight = 0; // ���� ��ġ�� ���� ���� ���� 
	int total = 0;
	int i, flag;
	int m, mprod, numnodes;//������ �ڽ��� �� + �� ���ο� �ִ� ������ ����� �� + ���İ� ����� ��
	set<int> child;
	set<int> ::iterator it;
	i = 0; numnodes = 1; m = 1; mprod = 1;
	for (int i = 1; i < n + 1; i++) {
		total += w[i];
	}

	while (m != 0 && i != n) { // ������ ��尡 ���ų� n���� ���ǿ� �� ������ ���� ������ �׶�  whlie���� ����
		mprod = mprod * m;
		numnodes = numnodes + mprod * 2;
		i++;
		m = 0;
		child.clear();

		if (promising(i, weight + w[i], total - w[i], W, w)) { // ���� �ڽ��� ������ ��
			m++;
			child.insert(0);
		}
		if (promising(i, weight, total - w[i], W, w)) { // ������ �ڽ��� ������ ��
			m++;
			child.insert(1);
		}
		if (m != 0) { // �ڽ��� �Ѵ� ������ �� 
			it = child.begin();
			int childrand = rand() % child.size(); // �� �߿��� �������� �ؼ� ���� ���� ���ش�.
			for (int i = 0; i < childrand; i++) {
				it++;
			}
			flag = *it;
			if (!flag) { // �ڽ��� �Ѵ� �������� ���� �� ���� �־����� �ʴ´�
				weight = weight + w[i];
			}

			total = total - w[i];
		}
		child.clear();
	}
	return numnodes; // �� ���� ��� �ݺ� 
}
bool promising(int i, int weight, int total, int W, int* w) { // ������ �ڽ����� Ȯ���ϱ� ���� �Լ�
	return ((weight + total) >= W) && ((weight == W) || (weight + w[i + 1] <= W));
}