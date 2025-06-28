//2022110151 ���ֿ� 
//2-2 Quick sort ���ȯ(stack.ver) 
//�ϼ�   
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10 // �迭 ũ�� �����ϱ� 
#define STACK_SIZE 100 // ���� ũ�� �����ϱ� 

// swap �Լ�: a <-> b �� �ٲٱ� 
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// partition �Լ� (��������) : �迭�� pivot�� �������� ������ pivot�� ���� ��ġ�� ��ȯ�� �� !  
int partition(int a[], int left, int right, int step) {
	//�Է�: �迭a[], left, right, step(�ܰ� Ȯ���ϱ� ���� �뵵) 
    int pivot = a[right]; // ������ ��Ҹ� pivot(���ذ�)���� ����
    int i = left - 1;     // i�� pivot���� ū ������ �� ���� ����Ŵ 
    int j;

	//pivot���� ū ������ ��������, ���� ������ ���������� �̵���Ű��  
    for (j = left; j < right; j++) {
        if (a[j] >= pivot) { // �������� �����̹Ƿ� ">="�� ������ ������ ������ 
            i++;
            swap(&a[i], &a[j]);
        }
    }
    
    swap(&a[i + 1], &a[right]);  // pivot�� ���� ��ġ�� �̵���Ű�� 

    // �ܰ躰 ��� 
    printf("[STEP %d] Pivot:%d �� ", step, pivot);
    for (j = 0; j < MAX_SIZE; j++) {
        printf("%d ", a[j]);
    }
    printf("\n");

    return i + 1; //pivot�� ���� ��ġ�� �����ϱ� 
}

// Quick sort �Լ� (���ȯ�� ver.) : Stack ����� ����! 
void quick_sort_iterative(int a[], int left, int right) {
	//�Է� : �迭 a[], left, right 
    int stack[STACK_SIZE]; // ���� �迭 �����ϱ� (left�� right�� ������ ���� ������ ��) 
    int top = -1; //������ �ֻ�� ��ġ��  ��Ÿ���� ���� �뵵 
    int step = 1; // �ܰ躰�� ����� �����ֱ��  

    // ���ÿ� �ʱ� ����(left, right)�� �����ϱ�  
    stack[++top] = left;
    stack[++top] = right;

    // ������ ������� �ʴ� ��� ������ �ݺ��ؼ� ����  
    while (top >= 0) {
        right = stack[top--];  // ������ ������ ��������  
        left = stack[top--];   // ������ ������ ��������  
        
        int q = partition(a, left, right, step++);  //pivot�� ������ �迭�� �����ϱ� 

        // ������ �κ��� �迭�� ���ÿ� push�ϱ�  (ū �� ���� ó���ϵ��� �ϱ� ���ؼ� ���� �ٲ�!) 
        if (q + 1 < right) {
            stack[++top] = q + 1;
            stack[++top] = right;
        }
        
        // ���� �κ��� �迭 ���ÿ� push�ϱ�  
        if (q - 1 > left) {
            stack[++top] = left;
            stack[++top] = q - 1;
        }
    }
}

int main() {
    int a[MAX_SIZE];
    int i, k;

    srand(time(NULL)); //���� �ʱ�ȭ�ϱ�  

	// �ߺ� ���� ���� �����ϱ�
    int used[100001] = {0}; // 1~100000 ���� �� ����ߴ��� Ȯ�� �뵵
    for (k = 0; k < MAX_SIZE;) {
        int num = rand() % 100000 + 1; // 1~100000 ���� ���� ����
        if (!used[num]) { //���� ������ ���� ���(�ߺ����� ���� ���)���� ����
            a[k++] = num;
            used[num] = 1;
        }
    }
    
    printf("Quick Sort - 2. Not Recursive(stack Ȱ��) ver.\n");
    // ���� �� �迭 ���
    printf("���� �� �迭: ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    // stack�� Ȱ���� ���ȯ Quick sort iterative �Լ��� ȣ���� ����  
    quick_sort_iterative(a, 0, MAX_SIZE - 1); //********** ������ �κ�

	// ���� �� �迭 ��� (��������)
    printf("���� �� �迭 (��������): ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}

