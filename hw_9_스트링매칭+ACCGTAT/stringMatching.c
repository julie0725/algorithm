//2022110151 이주연
// 문제 1. string matching 알고리즘 구현  

#include <stdio.h> //  입출력을 위한 헤더파일 (printf, fgets등 사용)
#include <time.h>  // 각 방식 별 수행시간을 측정& 출력하기 위한 헤더파일 (clock()와 CLOCKS_PER_SEC 사용) 
#include <stdlib.h> // 동적 메모리 할당을 위한 헤더파일 (malloc(), free())

#define MAX 1000   // 입력 받을 수 있는 문자열 최대 길이 설정정
#define Q 101   // 라빈카프(Rabin-Karp) 해시 계산용 소수수
#define D 256   // 문자 집합 크기, ASCII기준으론 256개

// 0. 문자열 길이 계산하기  
//    e.g. 문자열'abc' -> slen = 3
int slen(const char s[]) {
    int i = 0;
    // 문자열이 끝날 때('\0')까지 i++하며 문자열의 길이를 계산하기
    while (s[i] != '\0')
        i++;
    return i;// i에 담긴 문자열 길이를 리턴하기 
}

// 0.  fgets()로 읽은 문자열 끝의 '\n'문자를 '\0'로 바꾸기
//    e.g. "abc\n" -> "abc" 
// *fgets를해서 문자열을 읽을 경우 줄바꿈 '\n'이 생기기 때문에 이를 제거해주기
// trim은 깎아서 다듬는다는 의미를 있으니 줄바꿈 없애는 함수를를 trim함수로 표현했습니다. 
void trim(char s[]) {
    int i = 0;
    while (s[i] != '\0') { // 문자열을 돌면서 
        if (s[i] == '\n') {  // 만약 줄바꿈 '\n'을 만나게 되면
            s[i] = '\0';  // 줄바꿈 문자를 -> 문자열 종료 문자로 바꾸고
            return; // 함수를 종료시키기
        }
        i++; // i를 하나씩 증가하며 문자열 돌기 
    }
}

// [string matching] (텍스트에서 패턴을 찾는) 3가지 방법
// 1.  Brute-Force (직선적 알고리즘)--------------------
void bruteForce(const char T[], const char P[]) {
// 입력 : 텍스트 T[]
//        패턴 P[]  (을 입력받아,)
// 텍스트와 패턴의 길이를 각각 계산해 준 후, 
    int n = slen(T); // 텍스트(T) 길이 : n
    int m = slen(P); // 패턴(P) 길이 : m

    int i, j;

    printf("1. Brute-Force 결과\n");
    // 텍스트 첫 글자(0)부터 시작해 (i)
    // 패턴이 텍스트 끝을 넘어가지 않는 범위인 n-m까지 검사하며
    for (i = 0; i <= n - m; i++) {
        //패턴의 각 문자 P[j]와 i에서 j만큼 떨어진 텍스트 문자 T[i+j]를 하나씩씩 비교해,
        for (j = 0; j < m; j++) {
            // 만약 둘의 글자가 다르면 빠져나가고,
            if (T[i + j] != P[j])
                break;
        }
        // 만약 글자가 모두 일치할 경우우
        if (j == m)
            printf("패턴이 텍스트의 %d번째부터 나타납니다.\n", i); //매칭이 시작된 위치를 출력하기기
    }
    printf("\n");
}

// 2. Rabin-Karp (해시를 이용한 알고리즘)-----------------
void rabinKarp(const char T[], const char P[]) {
// 입력 : 텍스트 T[]
//        패턴 P[]  (을 입력받아,)
// 텍스트와 패턴의 길이를 각각 계산해 준 후, 
    int n = slen(T); // 텍스트(T) 길이 : n
    int m = slen(P); // 패턴(P) 길이 : m
    int h = 1, p = 0, t = 0; // 해시에 사용할 변수들 초기화하기기 
    int i, s;

    // 1) D^(m-1) mod Q 를 계산하고
    //   (D=256, Q=101) //여기서 D는 ASCII를 이용해 256으로 설정하였고, Q
    for (i = 0; i < m - 1; i++)
        h = (h * D) % Q;

    // 2) 초기 해시값을 계산하기 (Horner(호너) 방법을 통해 p, t 계산하기)
    for (i = 0; i < m; i++) {
        p = (D * p + P[i]) % Q;
        t = (D * t + T[i]) % Q;
    }

    printf("2. Rabin-Karp 결과\n");
    // 3) 텍스트 각 위치 별로 패턴 매칭시키기
    for (s = 0; s <= n - m; s++) {
        // 만약 hash 값 p와 t가 동일한 경우 세부 패턴 매칭을 진행하기 
        if (p == t) {
            int k;
            for (k = 0; k < m; k++) {
                // 만약 다를 경우 중단하고 빠져나가기 
                if (T[s + k] != P[k])
                    break; 
            }
            // 만약 모두 같을 경우 매칭이 시작된 위치를 출력시키기
            if (k == m)
                printf("패턴이 텍스트의 %d번째부터 나타남\n", s);
        }

        if (s < n - m) {
            // t(s)와 t(s+1)사이의 관계를 이용한 점화식을 통해서 다음 t값 계산
            // e.g 숫자로 된 문자열로 표현했을 때 
            // 25436 -> 5436 = 10(25436-2x10^3)+6 여기서 t(s) = 25436, t(s+1) = 5436
            t = (D * (t - T[s] * h) + T[s + m]) % Q;
            if (t < 0)
                t += Q; // 음수 방지용!
        }
    }
    printf("\n");
}

// 3-1. KMP용 SP 테이블 먼저 계산하기
// 매칭 전 어디서 suffix와 prefix가 일치하는지 알기 위해
// 만든 최대 접두부 테이블 
void computeSP(const char P[], int m, int SP[]) {
    int k = -1;  // k: 현재까지 일치한 prefix의 마지막 index를 의미 (어디까지 같은지 나타내는 용도도)
                 // 아직 일치한 문자가 없어 돌아갈 위치도 없기 때문에 -1로 표시
    int j;       // j: 패턴 index
    SP[0] = -1;  // prefix와 suffix가 겹치는 가장 긴 길이 
    // 패턴의 1번 인덱스부터 시작해서 패턴 길이전까지
    for (j = 1; j < m; j++) {
        // 만약 불일치 하는 경우, k를 SP[k]값으로 되돌려 더 작은 prefix길이 범위내에서 일치하는게 있는지 다시 확인
        while (k >= 0 && P[k + 1] != P[j])
            k = SP[k];
        // 만약 일치하는 경우, k를 하나 늘리기기
        if (P[k + 1] == P[j])
            k++;
        // 현재 일치하는 길이(k)를 SP 배열에 저장
        SP[j] = k;
    }
}

// 3-2. KMP 매칭 알고리즘 --------------------------------
void kmp(const char T[], const char P[]) {
    int n = slen(T); // n : 텍스트 길이
    int m = slen(P); // m : 패턴 길이
    int *SP = (int *)malloc(sizeof(int) * m); // SP테이블을 먼저 동적 할당해주기기
    int i, k;
    
    // SP 테이블을 만들어 계산하기 
    // 그래야 suffix/prefix match를 해 불필요한 비교 반복을 없앨 수 있음음
    computeSP(P, m, SP);
    printf("3. KMP 결과\n");
    k = -1; // 현재 일치하는 패턴의 최종 index

    // 텍스트 전체 한 글자씩 비교하며,
    for (i = 0; i < n; i++) {
        // 만약 글자가 불일치할 경우 S[K]만큼 다시 되돌아가 비교하고,
        while (k >= 0 && P[k + 1] != T[i])
            k = SP[k];
        // 만약 글자가 일치하는 경우에는 k를 하나 더 늘리며,
        if (P[k + 1] == T[i])
            k++;
        // 전체 패턴이 일치하는 경우에는 위치를 출력하고, k를 재설정하기 
        if (k == m - 1) {
            printf("패턴이 텍스트의 %d번째부터 나타남\n", i - m + 1);
            k = SP[k];
        }
    }
    printf("\n");
    free(SP); //malloc을 통해 할당한 동적 메모리를 해제하기기
}

int main() {
    // T: 입력 받을 텍스트 배열열 P: 입력 받을 패턴 배열
    char T[MAX], P[MAX];
    clock_t start, end; // 수행 시간 측정용 
    double exeTime; // 수행 시간 측정용

    // 1) fgets()로 Text String을 입력 받고, 마지막 '\n'은 trim함수로 떼어주기기
    printf("Text String: ");
    if (!fgets(T, MAX, stdin)) return 0;
    trim(T);

    // 2) Pattern String를 입력받기 (fgets()로 입력 받고, 마지막 '\n'은 trim함수로 떼어주기)
    printf("Pattern String: ");
    if (!fgets(P, MAX, stdin)) return 0;
    trim(P);

    // 1. Brute-Force 수행 및 시간 측정 ---------------
    start = clock(); // 시작 시간을 start에 저장하고
    bruteForce(T, P); // bruteForce 함수를 호출해 매칭한 후 
    end = clock();   // 끝난 시간을 end에 저장하기 
    exeTime = (double)(end - start) / CLOCKS_PER_SEC; // 시작 시간과 끝난 시간을 가지고 수행시간을 구해서
    printf("-> Brute-Force 수행시간: %.6f초\n\n", exeTime); // 수행시간을 출력하기 

    // 2. Rabin-Karp 수행 및 시간 측정 ----------------
    start = clock(); // 시작 시간을 측정하고
    rabinKarp(T, P); // rabinKarp 함수를 호출해 매칭한 후후
    end = clock();  // 끝난 시간 측정하기
    exeTime = (double)(end - start) / CLOCKS_PER_SEC; // 시작 시간과 끝난 시간을 가지고 수행시간을 구해서
    printf("-> Rabin-Karp 수행시간: %.6f초\n\n", exeTime); // 수행시간을 출력하기

    // 3. KMP 수행 및 시간 측정 -----------------------
    start = clock();// 시작 시간을 측정하고
    kmp(T, P); //kmp 함수를 호출해 매칭한 후
    end = clock(); /// 끝난 시간 측정하기
    exeTime = (double)(end - start) / CLOCKS_PER_SEC; // 시작 시간과 끝난 시간을 가지고 수행시간을 구해서서
    printf("-> KMP 수행시간: %.6f초\n", exeTime); // 수행시간을 출력하기

    return 0;
}
