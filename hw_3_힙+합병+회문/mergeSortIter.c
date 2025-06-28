//2022110151 ���ֿ�
// �պ� ���� NOT recursive ver. 
#include <stdio.h>
#define SIZE 10  // �迭 ũ��

// �迭 ��ü ���
void printFullArray(int A[]) {
    int i;
    for (i = 0; i < SIZE; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// ���� �Լ� (��ġ�� �Լ� * ���⼭ ���� �߻�)  
void Merge(int A[], int Left, int Mid, int Right) {
	// ���� (�ӽ�) �迭 
    int B[SIZE]; 
    int i;
    //  pointer (left, right) ����(�������ֱ�) 
    int LeftPtr = Left;
    int RightPtr = Mid + 1;
    int BufPtr = Left;

    // ���� 
	// ���⼭ left pointer�� left~mid����, right pointer�� mid+1 ~ right���� �����̸�
	// ���� ��   
    while (LeftPtr <= Mid && RightPtr <= Right) {
    	// ���� leftpointer�� ����Ű�� ���� �� ���� ��� ���ۿ� A[LeftPtr++] �� ����
		//** ���� �� pointer�� ++ (������ ������ �̵� ) 
        if (A[LeftPtr] < A[RightPtr])
            B[BufPtr++] = A[LeftPtr++];
        // �ݴ��� ��� ���ۿ�  A[RightPtr++]�� ����  
        else
            B[BufPtr++] = A[RightPtr++];
    }
	
	// ���� �� ���ۿ� ����  
    while (LeftPtr <= Mid)
        B[BufPtr++] = A[LeftPtr++];
    while (RightPtr <= Right)
        B[BufPtr++] = A[RightPtr++];

    // ���յ� ������ ����ϱ�  
    printf("Merge(%d,%d,%d)\n", Left, Mid, Right);

    // ���� �ܰ迡�� ��µ� B �迭 ��ü ���� ��� ( �ܰ� Ȯ���ϱ� ����) 
    printf("B ��ü: ");
    for (i = 0; i < SIZE; i++) {
        if (i >= Left && i <= Right)
            printf("%d ", B[i]);
        else
            printf("_ ");
    }
    printf("\n");

    // ����������, ����� A�� ����
    for (i = Left; i <= Right; i++)
        A[i] = B[i];

    //���� ����� �ݿ��� A �迭 ��ü ���¸� ����� �����ֱ�  
    printf("A �迭 ����: ");
    printFullArray(A);
    printf("\n");
}

// ����� Merge Sort
// : width�� ������
// ���� ��� -> �� ū ������� ���� 
void MergeSortNonRecursive(int A[], int n) {
    int width, i;

    // width�� ���� ��ĥ(merge��)  ����� ũ�� 
	// ���� 1��¥�� ���Һ��� ����  
    for (width = 1; width < n; width *= 2) {
    	// a�迭 ��ü�� 2*width �������� ���� ������� ��ĥ �� 
        for (i = 0; i < n; i += 2 * width) {
            int Left = i; // ���� ��� ���� �ε��� 
            int Mid = i + width - 1; // // ���� ����� �� �ε��� (ũ�� width)
            int Right = i + 2 * width - 1; // ������ ����� �� �ε��� (ũ�� width)
			
			// ���� mid�� �迭 ũ�⸦ �Ѿ�� 
			// ������ ������ ����� �����Ƿ� �ǳʶٱ� 
            if (Mid >= n)
                continue;
            // ���� right�� �迭 ũ�⸦ �Ѿ�� �迭 �� �ε����� �����ϱ�  
            if (Right >= n)
                Right = n - 1;
             // ���� �Լ� ȣ�⸦ ȣ���ؼ� A[Left: Mid]�� A[Mid+1:Right]�� �����ϱ�  
            Merge(A, Left, Mid, Right);
        }
    }
}

// ���� �Լ�
int main() {
    int A[SIZE] = {30, 20, 40, 35, 5, 50, 45, 10, 25, 15};

    printf("Merge Sort (���X ver.)\n");
    printf("�ʱ� �迭: ");
    printFullArray(A);
    printf("\n");
	
	//�պ� ���� �Լ� ȣ�� 
    MergeSortNonRecursive(A, SIZE);

    printf("���� ���� ���: ");
    printFullArray(A);

    return 0;
}

