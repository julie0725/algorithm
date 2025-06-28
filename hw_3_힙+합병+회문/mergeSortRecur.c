// 2022110151 이주연
// merge sort  재귀 버전  
#include <stdio.h>
#define SIZE 10 // 배열 크기 정의하기  

// 배열 전체를 출력(눈으로 정렬 과정 확인하기 위한 용) 
void printFullArray(int A[]) {
    int i;
    for (i = 0; i < SIZE; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// Merge 함수 
// : 두 개의 정렬된 부분 배열을 합병하는 함수
//  - left pointer를 left~mid까지, right pointer를  mid+1 ~ right까지 움직이며
//    더 작은 값을 b[]라는 보조 배열에 넣어줄 것 ! 
//    그 후, 최종적으로 다시 a[]배열에 복사해줄 것 ! 
void Merge(int A[], int Left, int Mid, int Right) { 
	// 임시 배열 버퍼 b[] 설정   
	// left pointer, right pointer 설정 (포인터를 옮겨가며 값들을 비교할 것!)  
	// 버퍼(즉, B 배열) 어느 위치에 데이터를 저장할지 나타내기 위해 BufPtr 설정  
    int B[SIZE];  
    int LeftPtr = Left, RightPtr = Mid + 1;
    int BufPtr = 0;  // B 배열은 항상 0부터 시작
    int i;

    // 합병(merge) 과정 
    // 다음 과정이 left pointer가 mid에 도달할 때까지 && right pointer가 right에 도달할 때까지 진행 
    while (LeftPtr <= Mid && RightPtr <= Right) {
    	// 왼쪽과 오른쪽을 비교해 더 작은 값을 버퍼(B[])에 저장하기  
        if (A[LeftPtr] < A[RightPtr])
            B[BufPtr++] = A[LeftPtr++];
        else
            B[BufPtr++] = A[RightPtr++];
    }
	
	// 남은 값들은 버퍼(B[])에 저장    
    while (LeftPtr <= Mid)  
        B[BufPtr++] = A[LeftPtr++];

    while (RightPtr <= Right)
        B[BufPtr++] = A[RightPtr++];

    // 병합한 정보 + B 버퍼 배열을 출력하기  
    printf("Merge(%d,%d,%d)\n", Left, Mid, Right);
    printf("B[%d:%d]: ", Left, Right);
    for (i = 0; i < BufPtr; i++)  // B 배열을 0부터 출력
        printf("%d ", B[i]);
    printf("\n");

    // 최종적으로 A 배열에 다시 복사 (B 배열의 0부터 시작하는 인덱스 맞추기)
    for (i = 0; i < BufPtr; i++)
        A[Left + i] = B[i];  // A 배열의 Left부터 B의 값을 복사!

    // 출력: 현재 A 배열 상태
    printf("A 배열 상태: ");
    printFullArray(A);
    printf("\n");
}

// 재귀 MergeSort 함수  
void MergeSort(int A[], int Left, int Right) {
	// 값이 두 개 이상이면  
    if (Left < Right) {
    	// 배열의 중간을 찾아 
        int Mid = (Left + Right) / 2;
        // 왼쪽 배열을 정렬하고  
        MergeSort(A, Left, Mid);
        // 오른쪽 배열을 정렬하고 
        MergeSort(A, Mid + 1, Right);
        // 합병한다 (merge 즉, 합친다)  
        Merge(A, Left, Mid, Right);
    }
}

// 메인 함수 
int main() {
	// 배열 설정 
    int A[SIZE] = {30, 20, 40, 35, 5, 50, 45, 10, 25, 15};
    int i;
	
	// 초기 배열 출력 
    printf("Merge Sort (재귀 ver.)\n");
    printf("초기 배열: ");
    printFullArray(A);
    printf("\n");

	// MergeSort 함수를 호출해 정렬 
    MergeSort(A, 0, SIZE - 1);

	// 최종 정렬된 결과 출력하기   
    printf("최종 정렬 결과: ");
    printFullArray(A);

    return 0;
}

