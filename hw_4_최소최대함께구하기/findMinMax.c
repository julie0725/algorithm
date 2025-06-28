//2022110151 ���ֿ�
// 1-2 �ּ� �ִ� ���� ã�� ���� 
// FindMinMax() �Լ��� �̿� -> ���ÿ� �ּҰ� �ִ밪 ã�� (�� ���) 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000 // �迭 ũ�� 1000���� ����  

// ���ÿ� �ּ�+�ִ밪�� ã�� FindMinMax()�Լ�  
void FindMinMax(int A[], int n, int *Minimum, int *Maximum) {
    int i, Smaller, Larger;
    *Minimum = A[0];
    *Maximum = A[0];
    
    // 1���� n-1����
	// (2ĭ���� �� ���� �ݺ��ϸ�) i ������ i+1��° ���� ����  
    for (i = 1; i < n - 1; i += 2) {
    	// �� �� �� ���� �� -> Smaller��
		// �� �� �� ū ���� -> Larger �� ������ ��,  
        if (A[i] < A[i + 1]) {
            Smaller = A[i];
            Larger = A[i + 1];
        } else {
            Smaller = A[i + 1];
            Larger = A[i];
        }
        // ���� Minimum ������ ����� Smaller ���� �� ������ 
		// Smallerr������ Minimum ���� ������Ʈ �Ѵ�.  
        if (Smaller < *Minimum) 
			*Minimum = Smaller;
        // �̿� ���������� ���� Maximum ������ Larger ���� �� ū ��� 
		// �� ū ���� Larger ������ Maximum���� ������Ʈ�Ѵ�.  
        if (Larger > *Maximum) 
			*Maximum = Larger;
    }

    // ���� n�� Ȧ�� ���� ���,�̶��� ������ ���� ��
    if (n % 2 == 0) {
        if (A[n - 1] < *Minimum) 
			*Minimum = A[n - 1];
        if (A[n - 1] > *Maximum) 
			*Maximum = A[n - 1];
    }
}

int main() {
    int A[SIZE];
    int min, max;
    int i;

    // random �õ� �ʱ�ȭ�ϱ�  
    srand(time(NULL));

    // 1~100000 ������ ���� �߿��� �������� 1000�� �����ؼ�-> �迭�� ���� 
    for (i = 0; i < SIZE; i++) {
        A[i] = rand() % 100000 + 1;
    }

    // FindMinMax�� ȣ���� �ּҰ��� �ִ밪�� ������ �ƴ� ���ÿ� ã��
    FindMinMax(A, SIZE, &min, &max);

    // ��� ���
    printf("1-2 �ּ� �ִ� ���� ã�� ����(FindMinMax)\n");
    printf("�ּҰ�: %d\n", min);
    printf("�ִ밪: %d\n", max);

    return 0;
}

