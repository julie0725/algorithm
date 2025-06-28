//2022110151 ���ֿ� 
//2-1 Quick sort ��ȯ(recursive.ver)
//�ϼ�!
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10 // �迭 ũ�� ���� 


int step = 1; //recursive�� ���� ������ step�� ���������� ���� 

// swap �Լ�: a <-> b �� �ٲٱ� 
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// partition �Լ�: �迭�� pivot�� �������� ������ pivot�� ���� ��ġ ��ȯ
int partition(int a[], int left, int right) {
    int pivot = a[left]; // ù ��° ��Ҹ� pivot���� ����
    int i = left + 1, j = right;
    int k; 

    while (1) {
        while (i <= j && a[i] > pivot) i++; // �������� �����̹Ƿ� ū �� ã��
        while (i <= j && a[j] < pivot) j--; // ���� �� ã��

        if (i > j) break; // �����Ͱ� �������� ����
        swap(&a[i], &a[j]); // �� ��ȯ
    }

    swap(&a[left], &a[j]); // pivot�� ���� ��ġ�� �̵�

    // �ܰ躰 ���
    printf("[STEP %d] Pivot:%d �� ", step++, pivot);
    for (k = 0; k < MAX_SIZE; k++) {
        printf("%d ", a[k]);
    }
    printf("\n");

    return j; // pivot�� ���� ��ġ ��ȯ
}

// Quick sort �Լ� (���ver. )
void quick_sort(int a[], int left, int right) {
    if (left < right) {
        int q = partition(a, left, right);
		quick_sort(a, left, q - 1);
		quick_sort(a, q + 1, right);
    }
}

int main() {
    int a[MAX_SIZE];
    int i, k;

    srand(time(NULL)); //���� �ʱ�ȭ�ϱ�  

    // �ߺ� ���� ���� �����ϱ�  
    int used[100001] = {0};  // 1~100000 ���� �� ����ߴ��� Ȯ�� �뵵 
    for (k = 0; k < MAX_SIZE;) {
        int num = rand() % 100000 + 1;  // 1~100000 ���� ���� ����
        if (!used[num]) {  //���� ������ ���� ���(�ߺ����� ���� ���)���� ����
            a[k++] = num;
            used[num] = 1;
        }
    }
    
    printf("Quick Sort - 1. Recursive(���) ver.\n");
    // ���� �� �迭 ���
    printf("���� �� �迭: ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    // Quick sort �Լ� ȣ���ؼ� ���� 
    quick_sort(a, 0, MAX_SIZE - 1);

    // ���� �� �迭 ��� (������������)  
    printf("���� �� �迭 (��������): ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}

