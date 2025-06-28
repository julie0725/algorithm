// 2022110151 이주연
// heap Sort  
#include <stdio.h>

// 두 값을 switch하기 위해 만든 swap함수  
// x <-> y
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// 힙 생성 함수
// 가독성을 위해 heapSort코드 상에서 주석을 최대한 빼고자 노력했지만,알고리즘 설명을 위해
// 필요한 부분은 넣었습니다. 
void makeMaxHeap(int a[], int root, int lastNode) {
    //루트 노드 -> 부모 노드로 설정 
    int parent = root;
    int rootValue = a[root];

    // 자식 노드 설정 (배열 index는 0부터 시작하므로 보정을 위해 +1)
    int leftson = 2 * parent + 1;
    int rightson = leftson + 1;
    // 자식 노드(왼 vs 오) 중 큰 값 넣을 변수
    int son;

    while (leftson <= lastNode) {
        // 1) 자식 노드끼리 값 비교 -> 큰 값은 son에 넣기기
        if (rightson <= lastNode && a[leftson] < a[rightson])
            son = rightson;
        else
            son = leftson;

        // 2) 자식 노드 중 큰 값(son값) vs 부모 노드 비교 
        // 만약 자식 노드 값이 부모 노드 값보다 더 크면 
        if (rootValue < a[son]) {
            // (a) 자식을 부모 자리로, 
            a[parent] = a[son];
            parent = son;
            // (b) 그리고 자식 노드 다시 설정
            leftson = 2 * parent + 1;
            rightson = leftson + 1;
        } else break; //if (자식 값 <= 부모 값) -> 더이상 내려가며 비교할 필요x므로 반복 끝 
    }
    // 반복문이 끝난 후, 처음에 저장해둔 부모 값(rootVlue) 적절한 위치에 다시 넣어주기
    // 자식 값을 계속 끌어올려 생긴 빈자리에 원래의 부모 값 내려 넣어주기 
    a[parent] = rootValue; 
}

// 배열 출력 함수
void printArray(int a[], int n) {
	int i;
	
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// 힙 정렬 함수( 오름차순 정렬 ) 
void heapSort(int a[], int n) {
	int i;
	
    //  1) max 힙 생성(부모 >= 자식 ) 
    for (i = n / 2 - 1; i >= 0; i--) {
    	// i를 root로 하는 서브트리를 -> maxHeap최대 힙으로 만들기  
        makeMaxHeap(a, i, n - 1);
    }

    // 2) 힙에서  최댓값(root)를 꺼내 "맨 뒤"로 보내면서 정렬
	// 배열의 맨 뒤부터 시작해서 앞으로 가며 정렬되도록 반복문 사용  
    for (i = n - 1; i > 0; i--) {
    	// a[0]는 현재 heap의 root므로, 최댓값.
		// 이 최댓값(root) a[0]를 맨 뒤 값인 a[i]와 바꾸기  
        swap(&a[0], &a[i]);  
		
		// root를 제외한 나머지 부분 a[0]~a[i-1]을 가지고 다시 heap으로 복원시키기     
		// == 크기를 하나 줄인 상태에서 다시 최대 힙 만들기  
        makeMaxHeap(a, 0, i - 1);    
    }
}

int main() {
    int a[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int n = 10;
    int i;

    // 초기 배열 출력
    printf("초기 배열: ");
    printArray(a, n);
    //-----------------------------------
    
    // heapSort에서 정렬 전 makeMaxHeap을 호출해 힙을 생성했기 때문에 
	// 사실상 필요 없지만,
	// 생성된 힙구조를 눈으로 보며 배열이 어떻게 변했는지 파악하기 위해 
	// 호출해서 출력했습니다!
    for (i = n / 2 - 1; i >= 0; i--) {
        makeMaxHeap(a, i, n - 1);
    }
    // 생성된 힙 출력 
    printf("생성된 힙: ");
    printArray(a, n);

    //------------------------------------
    // 힙 정렬 수행
    heapSort(a, n);
    // 정렬된 배열 출력
    printf("정렬된 배열: ");
    printArray(a, n);

    return 0;
}

