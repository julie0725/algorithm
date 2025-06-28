// 2022110151 이주연
// 1. 순차탐색  
#include <stdio.h>

#define N 10

//구조체 선언하기 ( key 값을 저장하기 위한 용도!)
typedef struct {
	int key; 
} Element;

// 구조체 배열 선언하기 : 인덱스 1~N까지 a[]
Element a[N + 1]; // +1을 한 이유는 1번 index부터 사용하기 위함! 

// 순차 탐색
int sequential(int k, int* count) {
	int i = 1;

	// 만약 i가 배열 안에 있고, k 즉, 찾는 대상을 아직 못 찾았다면 (key와 k값이 다를 때)
	while ((i < N + 1) && (a[i].key != k)) {
		i++; // i 하나 증가시켜 다시 찾고
		(*count)++; // 비교횟수도 하나 증가시키기
	}

    if (i <= N) {
        return i;  // 찾은 경우 위치 반환
    } else {
        return 0;  // 못 찾은 경우 0 반환
    }
}

int main() {
	int i;

	// 1. 배열의 key값 초기화 1 2 3 ~ N(=10) key값으로 넣어주기
	// ( 최악의 경우를 쉽게 보이기 위해 1 2 3 4 5 6 7 8 9 10 중
	// 가장 마지막에 위치한 10을 찾는 모습을 보여드릴 겁니다!  )
	for (i = 1; i <= N; i++) {
		a[i].key = i;
	}

	int searchSubject = 10;//찾고자 하는 대상
	int count = 0; //비교 횟수

    // 찾고자 하는 대상 (searchSubject)과 
    // 0으로 초기화된 비교 횟수(count)를 가지고 sequential함수 호출
    // 반환되는 i값을 index로 넣어주기 
    //(index는 여기 index번째에서 찾았음을 알려주기 위한 용도!!)
	int index = sequential(searchSubject, &count);

	//결과 출력
	printf("2022110151 이주연\n\n");
	printf("1. [순차 탐색] - Sequential search\n");
	if (index <= N) {
		printf("\n찾고자 하는 대상(searchSubject)이 %d일 때\n", searchSubject);
		printf("\n비교 횟수(count)는 %d번! (%d번 Index에서 찾았습니다)\n", count, index);
	}
	else {
		printf("탐색 실패ㅠㅠ비교횟수는 %d\n", count);
	}

	return 0;
}
