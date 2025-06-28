//2022110151 이주연
// 합병 정렬 NOT recursive ver. 
#include <stdio.h>
#define SIZE 10  // 배열 크기

// 배열 전체 출력
void printFullArray(int A[]) {
    int i;
    for (i = 0; i < SIZE; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// 병합 함수 (합치는 함수 * 여기서 정렬 발생)  
void Merge(int A[], int Left, int Mid, int Right) {
	// 버퍼 (임시) 배열 
    int B[SIZE]; 
    int i;
    //  pointer (left, right) 정의(설정해주기) 
    int LeftPtr = Left;
    int RightPtr = Mid + 1;
    int BufPtr = Left;

    // 병합 
	// 여기서 left pointer을 left~mid까지, right pointer를 mid+1 ~ right까지 움직이며
	// 값을 비교   
    while (LeftPtr <= Mid && RightPtr <= Right) {
    	// 만약 leftpointer가 가리키는 값이 더 작은 경우 버퍼에 A[LeftPtr++] 를 저장
		//** 저장 후 pointer를 ++ (포인터 옆으로 이동 ) 
        if (A[LeftPtr] < A[RightPtr])
            B[BufPtr++] = A[LeftPtr++];
        // 반대의 경우 버퍼에  A[RightPtr++]를 저장  
        else
            B[BufPtr++] = A[RightPtr++];
    }
	
	// 남은 값 버퍼에 저장  
    while (LeftPtr <= Mid)
        B[BufPtr++] = A[LeftPtr++];
    while (RightPtr <= Right)
        B[BufPtr++] = A[RightPtr++];

    // 병합된 구간을 출력하기  
    printf("Merge(%d,%d,%d)\n", Left, Mid, Right);

    // 병합 단계에서 출력된 B 배열 전체 상태 출력 ( 단계 확인하기 위해) 
    printf("B 전체: ");
    for (i = 0; i < SIZE; i++) {
        if (i >= Left && i <= Right)
            printf("%d ", B[i]);
        else
            printf("_ ");
    }
    printf("\n");

    // 최종적으로, 결과를 A에 복사
    for (i = Left; i <= Right; i++)
        A[i] = B[i];

    //병합 결과가 반영된 A 배열 전체 상태를 출력해 보여주기  
    printf("A 배열 상태: ");
    printFullArray(A);
    printf("\n");
}

// 비재귀 Merge Sort
// : width를 설정해
// 작은 블록 -> 더 큰 블록으로 병합 
void MergeSortNonRecursive(int A[], int n) {
    int width, i;

    // width는 현재 합칠(merge할)  블록의 크기 
	// 먼저 1개짜리 원소부터 시작  
    for (width = 1; width < n; width *= 2) {
    	// a배열 전체를 2*width 간격으로 나눠 순서대로 합칠 것 
        for (i = 0; i < n; i += 2 * width) {
            int Left = i; // 왼쪽 블록 시작 인덱스 
            int Mid = i + width - 1; // // 왼쪽 블록의 끝 인덱스 (크기 width)
            int Right = i + 2 * width - 1; // 오른쪽 블록의 끝 인덱스 (크기 width)
			
			// 만약 mid가 배열 크기를 넘어가면 
			// 병합할 오른쪽 블록이 없으므로 건너뛰기 
            if (Mid >= n)
                continue;
            // 만약 right가 배열 크기를 넘어가면 배열 끝 인덱스로 조정하기  
            if (Right >= n)
                Right = n - 1;
             // 병합 함수 호출를 호출해서 A[Left: Mid]와 A[Mid+1:Right]를 병합하기  
            Merge(A, Left, Mid, Right);
        }
    }
}

// 메인 함수
int main() {
    int A[SIZE] = {30, 20, 40, 35, 5, 50, 45, 10, 25, 15};

    printf("Merge Sort (재귀X ver.)\n");
    printf("초기 배열: ");
    printFullArray(A);
    printf("\n");
	
	//합병 정렬 함수 호출 
    MergeSortNonRecursive(A, SIZE);

    printf("최종 정렬 결과: ");
    printFullArray(A);

    return 0;
}

