// 2022110151 이주연 
// 2. 순차 탐색 vs 이진 탐색 (각각 실행)  -> 결과 비교 (성능 차이 분석)  
#include <stdio.h>

#define N 32  // 배열 크기 >= 16 (이상) 설정 (2씩 증가한 정렬된 값 저장용)


//구조체 선언하기 ( key 값을 저장하기 위한 용도!)
typedef struct {
    int key;  
} Element;

// 구조체 배열 선언하기 : 인덱스 1~N까지 a[]
Element a[N + 1]; 

int n = N;  //  전역변수로 사용하기 위해 단순 복사  


// 1. 순차 탐색-----------------------------------------------------------------------
int sequential(int k, int* count) {
	int i = 1;

	// 만약 i가 배열 안에 있고, k 즉, 찾는 대상을 아직 못 찾았다면 (key와 k값이 다를 때)
	while ((i < n + 1) && (a[i].key != k)) {
		i++; // i 하나 증가시켜 다시 찾고
		(*count)++; // 비교횟수도 하나 증가시키기
	}

    if (i <= n) {
        return i;  // 찾았으면 위치 i 리턴하고 (탐색 성공시) 
    } else {
        return 0;  // 못 찾았다면 0 리턴하기 (탐색 실패시)  
    }
}


// 2. 이진 탐색 -----------------------------------------------------------------------
// 기본 알고리즘 : mid값을 기준으로 탐색 범위를 반으로 나누기  
//                   mid
//                /     \ 
//   low ~ mid-1(왼)    mid+1 ~ high (오) 
int binary(int k, int* count) {
	// 트리 형태로 분할 하기 위해 설정한 인덱스
	// 탐색 대상되는 데이터의 시작 위치와 끝 위치 가리킴 
	int low, high, mid; 
    low = 1;         
    high = n;        

    // low <= high 동안: 즉, 탐색 가능한 범위일 때 (low>high면 탐색키가 존재하지 않으므로) 
    while (low <= high) {
        mid = (low + high) / 2;  // 중간 위치를 계산하고, 
        (*count)++;             // 비교 횟수를 증가한 다음  
		 
		 //mid를 기준으로  
        if (k == a[mid].key) // 1) 만약 값이 mid값이면 바로 인덱스를 리턴하고
            return mid;     
        if (k < a[mid].key)  // 2) 찾는 값이 mid 값보다 작으면 
            high = mid - 1;  //    왼쪽 부분으로 가서 탐색하고 ( 탐색 범위 축소) 
        if (k > a[mid].key)  // 3) 찾는 값이 mid 값보다 크면
            low = mid + 1;   //    오른쪽 부분으로 가서 탐색하기 (탐색 범위 축소) 
    }

    return 0;  // 못 찾았을 경우에는 0리턴하기 
}

int main() {
	int i; 
	
    // 0. 배열 초기화하기 ( 2, 4, 6, ..., 64 ) 오름차순 정렬된 상태로 
    for (i = 1; i <= N; i++) {
        a[i].key = i * 2;  // key값을 2씩 증가하여 저장
    }

    int searchSubject = 60;         // 탐색할 대상 값
    int seqCount = 0;       // 순차 탐색 비교 횟수 저장용
    int binCount = 0;       // 이진 탐색 비교 횟수 저장용

    // 1. 순차 탐색하기 -------------------------------------------- 
    int seqIndex = sequential(searchSubject,&seqCount);

    // 2. 이진 탐색하기 -------------------------------------------- 
    int binIndex = binary(searchSubject,&binCount);

    // 순차 탐색 결과 출력  
    if (seqIndex) {
        printf("1. 순차 탐색: %d번째 위치에서 찾았습니다! 비교횟수: %d회\n\n", seqIndex, seqCount);
    } else {
        printf("1. 순차 탐색: %d를 찾지 못했습니다. 비교횟수: %d회\n\n", searchSubject,seqCount);
    }

    // 이진 탐색 결과 출력
    if (binIndex) {
        printf("2. 이진 탐색: %d번째 위치에서 찾았습니다! 비교횟수: %d회\n", binIndex, binCount);
    } else {
        printf("2. 이진 탐색: %d를 찾지 못했습니다. 비교횟수: %d회\n", searchSubject, binCount);
    }

    return 0;  // 프로그램 종료
}

