//2022110151 이주연 
//2-1 Quick sort 순환(recursive.ver)
//완성!
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10 // 배열 크기 설정 


int step = 1; //recursive로 인해 꼬여서 step을 전역변수로 설정 

// swap 함수: a <-> b 값 바꾸기 
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// partition 함수: 배열을 pivot을 기준으로 나누고 pivot의 최종 위치 반환
int partition(int a[], int left, int right) {
    int pivot = a[left]; // 첫 번째 요소를 pivot으로 설정
    int i = left + 1, j = right;
    int k; 

    while (1) {
        while (i <= j && a[i] > pivot) i++; // 내림차순 정렬이므로 큰 값 찾기
        while (i <= j && a[j] < pivot) j--; // 작은 값 찾기

        if (i > j) break; // 포인터가 엇갈리면 종료
        swap(&a[i], &a[j]); // 값 교환
    }

    swap(&a[left], &a[j]); // pivot을 최종 위치로 이동

    // 단계별 출력
    printf("[STEP %d] Pivot:%d → ", step++, pivot);
    for (k = 0; k < MAX_SIZE; k++) {
        printf("%d ", a[k]);
    }
    printf("\n");

    return j; // pivot의 최종 위치 반환
}

// Quick sort 함수 (재귀ver. )
void quick_sort(int a[], int left, int right) {
    if (left < right) {
        int q = partition(a, left, right);
		quick_sort(a, left, q - 1);
		quick_sort(a, q + 1, right);
    }
}

int main() {
    int a[MAX_SIZE];
    int i, k;

    srand(time(NULL)); //난수 초기화하기  

    // 중복 없이 난수 생성하기  
    int used[100001] = {0};  // 1~100000 사이 수 사용했는지 확인 용도 
    for (k = 0; k < MAX_SIZE;) {
        int num = rand() % 100000 + 1;  // 1~100000 범위 난수 생성
        if (!used[num]) {  //값이 사용되지 않은 경우(중복되지 않은 경우)에만 저장
            a[k++] = num;
            used[num] = 1;
        }
    }
    
    printf("Quick Sort - 1. Recursive(재귀) ver.\n");
    // 정렬 전 배열 출력
    printf("정렬 전 배열: ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    // Quick sort 함수 호출해서 실행 
    quick_sort(a, 0, MAX_SIZE - 1);

    // 정렬 후 배열 출력 (내림차순으로)  
    printf("정렬 후 배열 (내림차순): ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}

