// 2022110151 이주연
// 1. dynamic programming 최소 동전 개수 문제  

#include <stdio.h>

#define MAX_M 100 // 배열 크기를 크게 설정, 만들 수 있는 최대 금액을 위해 
#define INF 9999  // for문으로 값을 비교해 더 작은 값으로 업데이트하기 위해 필요한 초기값 설정 

// 동전 교환 함수 
void dynamicChange(int M, int c[], int d) {
    int numCoin[MAX_M];     // numCoin[i]: i원을 만들기 위한 필요한 최소 동전 개수numCoin)을 저장
    int coinUsed[MAX_M];   // coinUsed[i]: i원을 만들 때 마지막으로 사용한 동전(coinUsed)을 저장
    int i, j;

    // 1) numCoin, used 배열 초기화
    // - numCoin: 아주 큰 값 ( 후에 값을 비교해 더 작은 값으로 업데이트 하기 위해 필요한 초기 값)
    // - used : i원 만들 떄 마지막으로 사용한 동전이 무엇인지 (e.g. 1인지 3인지 5인지) 알려주기 위한 용도
    // e.g. numCoin[j - coin] + 1  vs numCoin[j]  -> 더 작은 값으로 업데이트
    for (i = 0; i <= M; i++) {
        numCoin[i] = INF; 
        coinUsed[i] = -1; // 아직은 어떤 동전을 썼는지 모르므로 비어있다는 의미를 나타내기 위해 -1 사용
    }
    numCoin[0] = 0;  // 0원은 동전 0개 가지고 만든 것 

    // 2)
    // 한번 동전을 사용할 때 
    for (i = 0; i < d; i++) {
        int coin = c[i]; // (1원 3원 5원 중 지금 사용하려고 하는 동전 의미) 
        // (e.g. 지금 사용할 동전coin)이 5원이면 ->  "5원 가지고 금액을 만들어보기") 
        
        // coin ~ M까지 
        // 현재 coin(e.g.5원)을 기준으로  만들 수 있는 모든 금액(j) 확인하기 
        for (j = coin; j <= M; j++) {
            // numCoin[j-coin] + 1  vs numCoin[j] 값 비교해서 더 작은 값으로 업데이트 
            // 새로운 방법          vs 기존 방법 
            // 비교해서 둘 중 동전을 덜 쓴 경우(더 적은 개수 사용)로 값을 업데이트하기 
            if (numCoin[j - coin] + 1 < numCoin[j]) {
                // numCoin[j - coin] + 1 (새로운 방법)이 동전 개수를 더 적게 쓰므로,
                // 기존 방법(numCoin[j])을 더 작은 값으로 업데이트
                numCoin[j] = numCoin[j - coin] + 1;
                // j원 만들 때 어떤 동전(coin) 썼는지 기록하기(나중에 확인할 수 있도록)
                coinUsed[j] = coin;
            }
        }
    }

    // 3) 어떤 동전 조합 (e.g.1원 3원 5원 갖고 만들기 )을 이용해 만들었는지 출력하기
    printf("실제 사용한 동전들 (usedCoin): ");
    int amount = M; // 거꾸로 따라가기 위해서 현재 금액을 M부터 시작!

    while (amount > 0 && coinUsed[amount] != -1) {
        printf("%d원 ", coinUsed[amount]); // 마지막에 사용한 동전 출력하기 e.g. 3원이면 3원
        amount -= coinUsed[amount]; // 방금 쓴 동전만큼 금액 줄이기 
    }
    printf("\n");

    // 4) 최소 동전 개수 (numCoin) 출력하기 
    if (numCoin[M] != INF)
        printf("사용한 최소 동전 개수 (numCoin): %d개\n", numCoin[M]);
    else
        printf("해당 금액을 만들 수 없음.\n");
}

int main() {
    // 1,3,5원으로 11원 만들 것 -> 이때 동전 최소한으로 사용! 
    int c[] = {1, 3, 5}; // 교환하기 이해 사용할 동전 조합:  1원 3원 5원
    int d = 3;           // 동전 개수 (1,3,5원 -> 총 3개)
    int M = 11;          // 만들고 싶은 금액 : 11원 
    int i;
	
	printf("2022110151 이주연 - 알고리즘 과제(동전 교환 최소 개수)\n\n"); 
	printf("%d원을 만들기 위해 사용할 동전(들) c = [ ", M );
	for (i = 0; i < d; i++){
		printf("%d원 ", c[i]);
	}
	
	printf("]\n\n");
	
    // 0) 호출 -> 동전 교환 실행들 
    dynamicChange(M, c, d);

    return 0;
}

