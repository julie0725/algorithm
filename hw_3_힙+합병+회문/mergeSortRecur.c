// 2022110151 ���ֿ�
// merge sort  ��� ����  
#include <stdio.h>
#define SIZE 10 // �迭 ũ�� �����ϱ�  

// �迭 ��ü�� ���(������ ���� ���� Ȯ���ϱ� ���� ��) 
void printFullArray(int A[]) {
    int i;
    for (i = 0; i < SIZE; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// Merge �Լ� 
// : �� ���� ���ĵ� �κ� �迭�� �պ��ϴ� �Լ�
//  - left pointer�� left~mid����, right pointer��  mid+1 ~ right���� �����̸�
//    �� ���� ���� b[]��� ���� �迭�� �־��� �� ! 
//    �� ��, ���������� �ٽ� a[]�迭�� �������� �� ! 
void Merge(int A[], int Left, int Mid, int Right) { 
	// �ӽ� �迭 ���� b[] ����   
	// left pointer, right pointer ���� (�����͸� �Űܰ��� ������ ���� ��!)  
	// ����(��, B �迭) ��� ��ġ�� �����͸� �������� ��Ÿ���� ���� BufPtr ����  
    int B[SIZE];  
    int LeftPtr = Left, RightPtr = Mid + 1;
    int BufPtr = 0;  // B �迭�� �׻� 0���� ����
    int i;

    // �պ�(merge) ���� 
    // ���� ������ left pointer�� mid�� ������ ������ && right pointer�� right�� ������ ������ ���� 
    while (LeftPtr <= Mid && RightPtr <= Right) {
    	// ���ʰ� �������� ���� �� ���� ���� ����(B[])�� �����ϱ�  
        if (A[LeftPtr] < A[RightPtr])
            B[BufPtr++] = A[LeftPtr++];
        else
            B[BufPtr++] = A[RightPtr++];
    }
	
	// ���� ������ ����(B[])�� ����    
    while (LeftPtr <= Mid)  
        B[BufPtr++] = A[LeftPtr++];

    while (RightPtr <= Right)
        B[BufPtr++] = A[RightPtr++];

    // ������ ���� + B ���� �迭�� ����ϱ�  
    printf("Merge(%d,%d,%d)\n", Left, Mid, Right);
    printf("B[%d:%d]: ", Left, Right);
    for (i = 0; i < BufPtr; i++)  // B �迭�� 0���� ���
        printf("%d ", B[i]);
    printf("\n");

    // ���������� A �迭�� �ٽ� ���� (B �迭�� 0���� �����ϴ� �ε��� ���߱�)
    for (i = 0; i < BufPtr; i++)
        A[Left + i] = B[i];  // A �迭�� Left���� B�� ���� ����!

    // ���: ���� A �迭 ����
    printf("A �迭 ����: ");
    printFullArray(A);
    printf("\n");
}

// ��� MergeSort �Լ�  
void MergeSort(int A[], int Left, int Right) {
	// ���� �� �� �̻��̸�  
    if (Left < Right) {
    	// �迭�� �߰��� ã�� 
        int Mid = (Left + Right) / 2;
        // ���� �迭�� �����ϰ�  
        MergeSort(A, Left, Mid);
        // ������ �迭�� �����ϰ� 
        MergeSort(A, Mid + 1, Right);
        // �պ��Ѵ� (merge ��, ��ģ��)  
        Merge(A, Left, Mid, Right);
    }
}

// ���� �Լ� 
int main() {
	// �迭 ���� 
    int A[SIZE] = {30, 20, 40, 35, 5, 50, 45, 10, 25, 15};
    int i;
	
	// �ʱ� �迭 ��� 
    printf("Merge Sort (��� ver.)\n");
    printf("�ʱ� �迭: ");
    printFullArray(A);
    printf("\n");

	// MergeSort �Լ��� ȣ���� ���� 
    MergeSort(A, 0, SIZE - 1);

	// ���� ���ĵ� ��� ����ϱ�   
    printf("���� ���� ���: ");
    printFullArray(A);

    return 0;
}

