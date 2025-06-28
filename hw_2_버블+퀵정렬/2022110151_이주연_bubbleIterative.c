//2022110151 ���ֿ�  
//1-1 Bubble sort ���ȯ(iterative.ver)
#include <stdio.h>

// >>1.iterative<< ���� ����
void bubbleSort(int A[], int n) {
    int sorted = 0; // ���� ���� Ȯ���ϱ� ���� ��
    
	
	int round = 0;   // ���� �ܰ� ǥ��(���� �ȵ� �ʱ� ���� Round 0���� �ܰ躰�� ���ĵ� ����� ������ �� !)
 	int i, k, j;
 	
    while (!sorted) {
        sorted = 1; // �⺻������ ���ĵǾ��ٰ� ����
        printf("Round %d: ", round);
        for (k = 0; k < n; k++)
                printf("%d ", A[k]);
        printf("\n");

        for (i = 1; i < n; i++) {
            if (A[i - 1] > A[i]) {  // ���� ��Ұ� ũ�� swap(�ٲٱ�)
                int temp = A[i - 1];
                A[i - 1] = A[i];
                A[i] = temp;
                sorted = 0;
            }
        }
        round++; // �����ʺ��� �ϳ��� ���ĵ� �� Ȯ���ϱ� ���� round ����
    }

    printf("Sorted Array: ");
    for (j = 0; j < n; j++)
            printf("%d ", A[j]);
    printf("\n");
}

int main() {
    int A[] = { 30, 20, 40, 10, 5, 10, 30, 15 };
    int n = sizeof(A) / sizeof(A[0]);

    bubbleSort(A, n);
    return 0;
}
