//2022110151 이주연 
//1-2 Bubble sort 순환(recursive.ver)
#include <stdio.h>

void bubbleSortRecursive(int A[], int n, int totalSize) {
    if (n == 1) return; // 정렬이 완료되었으면 종료

    int sorted = 1; // 기본적으로 정렬되었다고 가정하기
    int j,i,temp;

    printf("Checking round: ");
    for (j = 0; j < totalSize; j++) // 항상 전체 배열을 출력하도록 하기
        printf("%d ", A[j]);
    printf("\n");

    for (i = 1; i < n; i++) {
        if (A[i - 1] > A[i]) {  //비교해서 앞의 요소가 크면 바꾸기(swap)
            temp = A[i - 1];
            A[i - 1] = A[i];
            A[i] = temp;
            sorted = 0;
        }
    }

    if (sorted) return; // 정렬이 완료되었으면 종료하기

    //Recursive(재귀)함수 호출해서 정렬 계속하기
    bubbleSortRecursive(A, n - 1, totalSize); // totalSize는 유지!
}

int main() {
    printf("Recursive ver. - Bubble Sort\n");

    int A[] = {30, 20, 40, 10, 5, 10, 30, 15};
    int n = sizeof(A) / sizeof(A[0]);
    int k;

    bubbleSortRecursive(A, n, n); // 배열 크기 전달

    printf("Sorted Array: ");
    for (k = 0; k < n; k++)
        printf("%d ", A[k]);
    printf("\n");

    return 0;
}
