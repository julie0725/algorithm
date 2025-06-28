// 2022110151 이주연 
// 1-1 최소 최댓값 동시 찾기 문제 
// Minimum() 함수 & Maximum() 함수 이용 -> 최대 최소 찾기 (및 출력)
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

// 최소값 찾기 Minimum() 함수  
int Minimum(int A[], int n) {
	int i;
	// A[0]값이 가장 작다고 가정해 min에 넣어준 후,  
    int min = A[0];
    // n-1회 간 반복하며  (비교 과정) 
    for (i = 1; i < n; i++) {
    	// 만약 A[i]번쨰 값이 min보다도 더 작으면 A[i]값을 min에 넣어주기
		// (min값 업데이트)  
        if (A[i] < min)
            min = A[i];
    }
    return min; //최솟값 반환 
}

// 최대값 찾기 함수 Maximum()함수 - 최솟값 찾기 함수를 갖고 응용
int Maximum(int A[], int n) {
	int k; 
	// 들어온 A[]배열 중 A[0]값이 가장 작다고 가정한 후, min에 넣기 
    int max = A[0];
    // n-1회 간 반복하며 (비교 과정)  
    for (k = 1; k < n; k++) {
    	// 만약 max보다 더 큰 A[k]값이 있다면 max값을 A[k]값으로 업데이트 
        if (A[k] > max)
            max = A[k];
    }
    return max; //최댓값  반환  
}

int main() {
    int A[SIZE]; //1000
    int min, max;
    int i; 

    // random 시드 초기화하기  
    srand(time(NULL));

    // 1~100000 사이의 숫자 중에서 랜덤으로 1000개 생성해서-> 배열에 저장 
    for (i = 0; i < SIZE; i++) {
        A[i] = rand() % 100000 + 1;
    }

    // Minimum 함수와 Maximum 함수 각각 호출을 통해 최소값과 최대값 찾고
	// min, max에 저장  
    min = Minimum(A, SIZE);
    max = Maximum(A, SIZE);

    //  min, max 출력  
    printf("1-1 최소 최댓값 찾기 문제\n");
    printf("최소값: %d\n", min);
    printf("최대값: %d\n", max);

    return 0;
}

