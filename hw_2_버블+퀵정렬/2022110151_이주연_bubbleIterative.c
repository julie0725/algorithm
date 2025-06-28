//2022110151 이주연  
//1-1 Bubble sort 비순환(iterative.ver)
#include <stdio.h>

// >>1.iterative<< 버블 정렬
void bubbleSort(int A[], int n) {
    int sorted = 0; // 정렬 여부 확인하기 위한 용
    
	
	int round = 0;   // 정렬 단계 표시(정렬 안된 초기 상태 Round 0부터 단계별로 정렬된 모습을 보여줄 것 !)
 	int i, k, j;
 	
    while (!sorted) {
        sorted = 1; // 기본적으로 정렬되었다고 가정
        printf("Round %d: ", round);
        for (k = 0; k < n; k++)
                printf("%d ", A[k]);
        printf("\n");

        for (i = 1; i < n; i++) {
            if (A[i - 1] > A[i]) {  // 앞의 요소가 크면 swap(바꾸기)
                int temp = A[i - 1];
                A[i - 1] = A[i];
                A[i] = temp;
                sorted = 0;
            }
        }
        round++; // 오른쪽부터 하나씩 정렬된 걸 확인하기 위해 round 증가
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
