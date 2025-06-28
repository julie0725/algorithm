//2022110151 이주연
// 2. 돌 꺼내기 문제 (승패 결정) - dynamic programming 이용 

#include <stdio.h>

#define M 10 //왼쪽 상자 돌 최대 기수
#define N 7  //오른쪽 상자 돌 최대 기수 
#define MAX 101  //배열크기 넉넉하게 잡은 용도 

char R[MAX][MAX]; // 왼쪽 i, 오른쪽 j일 때 win / lose 결과 저장하는 table 용도 

// Dynamic Programming 이용해서 돌을 꺼낸다고 할 때 영희/ 철수 누가 이기는지 알려주기기
void checkStone(int m, int n) {
	int i,j;
	
    R[0][0] = 'L'; // 돌이 아예 없으면 이길 수 없으니-> lose 

    // 1) 왼쪽 상자만 돌 있는 경우 이전전 상태에 따라 승패가 결정되므로 
    for (i = 1; i <= m; i++) {
        if (R[i-1][0] == 'W') { // 만약 상대방이 이길 수 있는 곳이라면 
            R[i][0] = 'L';      // 영희는 Lose
        } else {
            R[i][0] = 'W';      //반대의 경우 상대가 졌던 상태라면 영희는 Win
        }
    }

    // 2) 오른쪽 상자에만 돌 있는 경우 
    for (j = 1; j <= n; j++) {  // 위 방식과 비슷한 로직직
        if (R[0][j-1] == 'W') {
            R[0][j] = 'L';
        } else {
            R[0][j] = 'W';
        }
    }

    // 3) 양쪽 모두 돌이 경우 
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            // R[i-1][j]: 왼쪽에서 돌 하나 꺼냈을 때 
            // R[i][j-1]: 오른쪽에서 하나 돌 하나 꺼냈을 때 
            // R[i-1][j-1]: 양쪽에서 하나씩 꺼냈을 때   
            // 이 세가지 경우 모두 철수가 이기게 된다면
            // 어떤 방법으로 돌을 꺼내든 상대가 이기기 때문에 영희는 짐 (Lose) 
            if (R[i-1][j-1] == 'W' && R[i-1][j] == 'W' && R[i][j-1] == 'W') {
                R[i][j] = 'L';
            } else {  // 반대로 철수가 돌 꺼낸 후 한 경우에라도 lose가 되면 -> 영희는 이길 수 있게 됨
                R[i][j] = 'W';
            }
        }
    }
    
}

int main() {
    int m = M;
	int n = N;
	
	int i,j;
    

    checkStone(m, n); // table을 만들어준다! 돌 개수에 따라 영희/ 철수 누가 이기는지 알려주기기 
    
    printf("2022110151 이주연- 알고리즘 과제(돌 꺼내기 승패)\n\n");
    printf("When m = %d, n = %d\n", m, n);
    if (R[m][n] == 'W') // m과 n에 따라 W라고 적혀져 있으면 영희가 이긴 것! -> 결과 출력
        printf("=> 영희 Win! \n");
    else // L이라고 적혀져 있는 경우 영희가 진 것이므로 -> 철수 win 출력 
        printf("=> 철수 Win (영희 Lose)\n");

    // 승패 테이블이 어떻게 구성되어 있는지 확인하고 점검하기 위한 용도로 만들어봤습니다!
    // 무시해주셔도 됩니다!!!
    // 열 출력 
    printf("\n--- WIn/lose checking table(R[m][n]) ---\n");
    printf("m\\n |"); // 행 m 열 n
    for (j = 0; j <= n; ++j) 
        printf("%3d", j);  // 0~7 숫자 출력력
    printf("\n----|"); // 단순 구분선 (----)
    for (j = 0; j <= n; ++j)  
        printf("---");
    printf("\n");

    // 행 출력 
    for (i = 0; i <= m; ++i) {
        printf("%3d |", i); // 0~10 숫자 출력 
        for (j = 0; j <= n; ++j) {
            printf("%3c", R[i][j]);  // 각 행과 열에 따른 승패결과(W/L) 출력
        }
        printf("\n");
    }

    return 0;
}

