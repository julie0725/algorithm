//2022110151 이주연
// 1-2 최소 최댓값 동시 찾기 문제 
// FindMinMax() 함수를 이용 -> 동시에 최소값 최대값 찾기 (및 출력) 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000 // 배열 크기 1000으로 설정  

// 동시에 최소+최대값을 찾는 FindMinMax()함수  
void FindMinMax(int A[], int n, int *Minimum, int *Maximum) {
    int i, Smaller, Larger;
    *Minimum = A[0];
    *Maximum = A[0];
    
    // 1부터 n-1까지
	// (2칸마다 한 번씩 반복하며) i 번쨰와 i+1번째 값을 비교해  
    for (i = 1; i < n - 1; i += 2) {
    	// 둘 중 더 작은 값 -> Smaller에
		// 둘 중 더 큰 값은 -> Larger 에 저장한 후,  
        if (A[i] < A[i + 1]) {
            Smaller = A[i];
            Larger = A[i + 1];
        } else {
            Smaller = A[i + 1];
            Larger = A[i];
        }
        // 기존 Minimum 값보다 저장된 Smaller 값이 더 작으면 
		// Smallerr값으로 Minimum 값을 업데이트 한다.  
        if (Smaller < *Minimum) 
			*Minimum = Smaller;
        // 이와 마찬가지로 기존 Maximum 값보다 Larger 값이 더 큰 경우 
		// 더 큰 값인 Larger 값으로 Maximum값을 업데이트한다.  
        if (Larger > *Maximum) 
			*Maximum = Larger;
    }

    // 만약 n이 홀수 개일 경우,이때는 마지막 값도 비교
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

    // random 시드 초기화하기  
    srand(time(NULL));

    // 1~100000 사이의 숫자 중에서 랜덤으로 1000개 생성해서-> 배열에 저장 
    for (i = 0; i < SIZE; i++) {
        A[i] = rand() % 100000 + 1;
    }

    // FindMinMax를 호출해 최소값과 최대값을 각각이 아닌 동시에 찾기
    FindMinMax(A, SIZE, &min, &max);

    // 결과 출력
    printf("1-2 최소 최댓값 동시 찾기 문제(FindMinMax)\n");
    printf("최소값: %d\n", min);
    printf("최대값: %d\n", max);

    return 0;
}

