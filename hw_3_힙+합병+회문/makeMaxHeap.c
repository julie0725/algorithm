// 2022110151 이주연  
// 힙 생성 (알고리즘2 사용)  
#include <stdio.h>

// 두 값을 switch하기 위해 만든 swap함수  
// x <-> y
void Swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// 힙 생성 함수  
void makeMaxHeap(int a[], int root, int lastNode) {
	//입력 : 배열 a[]와 root노드(i), lastNode(마지막 노드(즉 n-1))
	// root으로 들어온 i(즉, 부모노드)를 parent에 저장해두기  
    int parent = root;   
	//root에 있는 값을 rootValue로 저장   
    int rootValue = a[root];
    
    // index 계산하기 
    // - 왼쪽 자식 : (부모기준 * 2) + 1             
	//               **참고로 여기서 1을 더한 이유는 배열의 인덱스가 0부터 시작하기 때문에 이를 맞춰주고자 1을 더했습니다..  
	// - 오른쪽 자식 : 왼쪽 자식 기준 + 1 
	// - son : 자식 중에서 더 큰 값을 가진 노드의 'index'를 저장할 변수 
    int leftson = 2 * parent + 1;
    int rightson = leftson + 1;
    int son;

    // 자식이 있는 경우 ( 즉, 왼쪽 자식이 배열 안에 있는 경우에만) 다음을 반복적으로  시행  
    while (leftson <= lastNode) {
    	// 1)  "왼쪽자식 값 vs 오른쪽 자식 값 비교해서 -> 더 큰 값을 son에 저장" 
    	// 만약, 오른쪽 자식이 있고(rightson <=lastNode: 즉, lastNodd범위 내에 있고)
		// 왼쪽 자식 값 < 오른쪽 자식 값 인 경우 -> son에 오른쪽 자식을 저장  
        if (rightson <= lastNode && a[leftson] < a[rightson])
            son = rightson;
        // 그렇지 않은 경우, son에는 왼쪽 자식이 저장
        else
            son = leftson;

		// 2) 현재 부모노드 값 vs (자식 노드 중 큰 값이 저장된) son값을 비교해 -> 
		//         - 자식값이 더 큰 경우 : 자리 바꾸기 (자식값이 부모 자리에 가도록)   
        if (rootValue < a[son]) {
        	// (부모 값 < 자식 값 일때)  자식 값을 부모 자리에 넣고,  
            a[parent] = a[son];
            //자식을 new 부모로 설정해주고,  
            parent = son;
            //new 부모를 기준으로 자식 인덱스(왼쪽 자식, 오른쪽 자식)를 다시 계산한다.  
            // 참고로 배열 인덱스가 0부터 시작하니 여기서도 leftson을 2*parent 후 1을 더해줬다. (즉 보정했다!) 
            leftson = 2 * parent + 1;
            rightson = leftson + 1;
        } else break; //if (자식 값 <= 부모 값) -> 더이상 내려가며 비교할 필요x므로 반복 끝 
    }
    // 반복문이 끝난 후, 처음에 저장해둔 부모 값(rootVlue) 적절한 위치에 다시 넣어주기
    // 자식 값을 계속 끌어올려 생긴 빈자리에 원래의 부모 값 내려 넣어주기 
    a[parent] = rootValue;
}

// 단순 배열 출력용 (단계별로 확인하는 용도)  
void printArray(int a[], int n) {
	int i; 
    for ( i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n\n");
}

int main() {
    int a[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int n = 10;
    int i;
	
	//먼저, 초기 상태의 배열(initial array)출력하기  
    printf("초기 배열 A : ");
    printArray(a, n);
    printf("-----------\n") ;


    // i가  n/2 - 1 부터 0까지 감소하며  각 subtree를 최대 힙으로 만들 수 있도록 makeMaxHeap 호출
	// 이때, 힙 생성 과정을 단계별로 보기 위해
	// 힙 생성 함수(==makeMaxHeap 함수) 호출 후, 현재 배열 상태(printArray함수 호출)를 출력  
    for (i = n/2 - 1; i >= 0; i--) {
        printf("i = %d일 때:\n", i);
        //힙 생성 함수 호출  
        makeMaxHeap(a, i, n - 1);
        //현재 배열 상태 출력을 위해 printArray호출  (가독성을 위해 printArray 함수로 따로 처리했습니다.)  
        printf("배열 상태: ");
        printArray(a, n);
    }

    // 생성된 힙 일차원 배열로 출력하기
	printf("-----------\n") ;  
    printf("\n최종생성된 힙: "); 
    printArray(a, n);
    return 0;
}


