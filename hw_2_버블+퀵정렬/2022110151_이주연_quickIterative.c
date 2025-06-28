//2022110151 이주연 
//2-2 Quick sort 비순환(stack.ver) 
//완성   
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10 // 배열 크기 설정하기 
#define STACK_SIZE 100 // 스택 크기 설정하기 

// swap 함수: a <-> b 값 바꾸기 
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// partition 함수 (내림차순) : 배열을 pivot을 기준으로 나누고 pivot의 최종 위치를 반환할 것 !  
int partition(int a[], int left, int right, int step) {
	//입력: 배열a[], left, right, step(단계 확인하기 위한 용도) 
    int pivot = a[right]; // 마지막 요소를 pivot(기준값)으로 설정
    int i = left - 1;     // i는 pivot보다 큰 값들의 끝 지점 가리킴 
    int j;

	//pivot보다 큰 값들은 왼쪽으로, 작은 값들은 오른쪽으로 이동시키기  
    for (j = left; j < right; j++) {
        if (a[j] >= pivot) { // 내림차순 정렬이므로 ">="한 값들을 앞으로 보내기 
            i++;
            swap(&a[i], &a[j]);
        }
    }
    
    swap(&a[i + 1], &a[right]);  // pivot을 최종 위치로 이동시키기 

    // 단계별 출력 
    printf("[STEP %d] Pivot:%d → ", step, pivot);
    for (j = 0; j < MAX_SIZE; j++) {
        printf("%d ", a[j]);
    }
    printf("\n");

    return i + 1; //pivot의 최종 위치를 리턴하기 
}

// Quick sort 함수 (비순환적 ver.) : Stack 사용해 구현! 
void quick_sort_iterative(int a[], int left, int right) {
	//입력 : 배열 a[], left, right 
    int stack[STACK_SIZE]; // 스택 배열 생성하기 (left랑 right를 저장해 나눠 관리할 것) 
    int top = -1; //스택의 최상단 위치를  나타내기 위한 용도 
    int step = 1; // 단계별로 출력해 보여주기용  

    // 스택에 초기 범위(left, right)를 저장하기  
    stack[++top] = left;
    stack[++top] = right;

    // 스택이 비어있지 않는 경우 다음을 반복해서 실행  
    while (top >= 0) {
        right = stack[top--];  // 오른쪽 범위를 가져오기  
        left = stack[top--];   // 왼쪽의 범위를 가져오기  
        
        int q = partition(a, left, right, step++);  //pivot을 가지고 배열을 분할하기 

        // 오른쪽 부분의 배열을 스택에 push하기  (큰 값 먼저 처리하도록 하기 위해서 순서 바꿈!) 
        if (q + 1 < right) {
            stack[++top] = q + 1;
            stack[++top] = right;
        }
        
        // 왼쪽 부분의 배열 스택에 push하기  
        if (q - 1 > left) {
            stack[++top] = left;
            stack[++top] = q - 1;
        }
    }
}

int main() {
    int a[MAX_SIZE];
    int i, k;

    srand(time(NULL)); //난수 초기화하기  

	// 중복 없이 난수 생성하기
    int used[100001] = {0}; // 1~100000 사이 수 사용했는지 확인 용도
    for (k = 0; k < MAX_SIZE;) {
        int num = rand() % 100000 + 1; // 1~100000 범위 난수 생성
        if (!used[num]) { //값이 사용되지 않은 경우(중복되지 않은 경우)에만 저장
            a[k++] = num;
            used[num] = 1;
        }
    }
    
    printf("Quick Sort - 2. Not Recursive(stack 활용) ver.\n");
    // 정렬 전 배열 출력
    printf("정렬 전 배열: ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    // stack을 활용한 비순환 Quick sort iterative 함수를 호출해 실행  
    quick_sort_iterative(a, 0, MAX_SIZE - 1); //********** 수정된 부분

	// 정렬 후 배열 출력 (내림차순)
    printf("정렬 후 배열 (내림차순): ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}

