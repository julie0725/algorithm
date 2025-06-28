//2022110151 ���ֿ� 
//1-2 Bubble sort ��ȯ(recursive.ver)
#include <stdio.h>

void bubbleSortRecursive(int A[], int n, int totalSize) {
    if (n == 1) return; // ������ �Ϸ�Ǿ����� ����

    int sorted = 1; // �⺻������ ���ĵǾ��ٰ� �����ϱ�
    int j,i,temp;

    printf("Checking round: ");
    for (j = 0; j < totalSize; j++) // �׻� ��ü �迭�� ����ϵ��� �ϱ�
        printf("%d ", A[j]);
    printf("\n");

    for (i = 1; i < n; i++) {
        if (A[i - 1] > A[i]) {  //���ؼ� ���� ��Ұ� ũ�� �ٲٱ�(swap)
            temp = A[i - 1];
            A[i - 1] = A[i];
            A[i] = temp;
            sorted = 0;
        }
    }

    if (sorted) return; // ������ �Ϸ�Ǿ����� �����ϱ�

    //Recursive(���)�Լ� ȣ���ؼ� ���� ����ϱ�
    bubbleSortRecursive(A, n - 1, totalSize); // totalSize�� ����!
}

int main() {
    printf("Recursive ver. - Bubble Sort\n");

    int A[] = {30, 20, 40, 10, 5, 10, 30, 15};
    int n = sizeof(A) / sizeof(A[0]);
    int k;

    bubbleSortRecursive(A, n, n); // �迭 ũ�� ����

    printf("Sorted Array: ");
    for (k = 0; k < n; k++)
        printf("%d ", A[k]);
    printf("\n");

    return 0;
}
