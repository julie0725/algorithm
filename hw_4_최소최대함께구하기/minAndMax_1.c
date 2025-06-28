// 2022110151 ���ֿ� 
// 1-1 �ּ� �ִ� ���� ã�� ���� 
// Minimum() �Լ� & Maximum() �Լ� �̿� -> �ִ� �ּ� ã�� (�� ���)
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

// �ּҰ� ã�� Minimum() �Լ�  
int Minimum(int A[], int n) {
	int i;
	// A[0]���� ���� �۴ٰ� ������ min�� �־��� ��,  
    int min = A[0];
    // n-1ȸ �� �ݺ��ϸ�  (�� ����) 
    for (i = 1; i < n; i++) {
    	// ���� A[i]���� ���� min���ٵ� �� ������ A[i]���� min�� �־��ֱ�
		// (min�� ������Ʈ)  
        if (A[i] < min)
            min = A[i];
    }
    return min; //�ּڰ� ��ȯ 
}

// �ִ밪 ã�� �Լ� Maximum()�Լ� - �ּڰ� ã�� �Լ��� ���� ����
int Maximum(int A[], int n) {
	int k; 
	// ���� A[]�迭 �� A[0]���� ���� �۴ٰ� ������ ��, min�� �ֱ� 
    int max = A[0];
    // n-1ȸ �� �ݺ��ϸ� (�� ����)  
    for (k = 1; k < n; k++) {
    	// ���� max���� �� ū A[k]���� �ִٸ� max���� A[k]������ ������Ʈ 
        if (A[k] > max)
            max = A[k];
    }
    return max; //�ִ�  ��ȯ  
}

int main() {
    int A[SIZE]; //1000
    int min, max;
    int i; 

    // random �õ� �ʱ�ȭ�ϱ�  
    srand(time(NULL));

    // 1~100000 ������ ���� �߿��� �������� 1000�� �����ؼ�-> �迭�� ���� 
    for (i = 0; i < SIZE; i++) {
        A[i] = rand() % 100000 + 1;
    }

    // Minimum �Լ��� Maximum �Լ� ���� ȣ���� ���� �ּҰ��� �ִ밪 ã��
	// min, max�� ����  
    min = Minimum(A, SIZE);
    max = Maximum(A, SIZE);

    //  min, max ���  
    printf("1-1 �ּ� �ִ� ã�� ����\n");
    printf("�ּҰ�: %d\n", min);
    printf("�ִ밪: %d\n", max);

    return 0;
}

