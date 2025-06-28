#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 0. 문자열 길이 계산하기  
//    e.g. 문자열'abc' -> slen = 3
int len(const char *s) {
    int i = 0;
    // 문자열이 끝날 때('\0')까지 i++하며 문자열의 길이를 계산하기
    while (s[i] != '\0') i++;  // 문자열 끝까지 반복
    return i;// i에 담긴 문자열 길이를 리턴하기 
}

// 방식 1) Brute-Force 직선적 방식  
void brute_force(const char *T, const char *P, int n, int m, FILE *output_file) {
    int i, j;
    // 텍스트 첫 글자(0)부터 시작해 (i)
    // 패턴이 텍스트 끝을 넘어가지 않는 범위인 n-m까지 검사하며
    for (i = 0; i <= n - m; i++) {  
    	//패턴의 각 문자 P[j]와 i에서 j만큼 떨어진 텍스트 문자 T[i+j]를 하나씩씩 비교해
        for (j = 0; j < m; j++) {  //(패턴 p길이만큼 반복) 
             // 만약 둘의 글자가 다르면 빠져나가고,
            if (T[i + j] != P[j]) 
				break;  
        }
        // 만약 글자가 모두 일치할 경우(패턴이랑 완전히 같을 경우)  
        if (j == m) { 
            fprintf(output_file, "%d\n", i);  // output_file에 인덱스 출력하기 ! 
        }
    }
}

// 방식 2) KMP 알고리즘 ( SP 테이블을 활용해 불피요한 반복 줄이는 방식) 
// 2-1. SP 테이블 계산하기  
void computeSP(const char *P, int m, int *SP) {
    int k = -1; // k: 현재까지 일치한 prefix의 마지막 index를 의미 (어디까지 같은지 나타내는 용도도)
                // 아직 일치한 문자가 없어 돌아갈 위치도 없기 때문에 -1로 표시
    int j;
    SP[0] = -1;  // SP 테이블 초기화 ( SP 테이블: prefix와 suffix가 겹치는 가장 긴 길이 담는 배열)
	// 패턴의 1번 인덱스부터 시작해서 패턴 길이전까지
    for (j = 1; j < m; j++) {  // j는 1부터 m-1까지 반복
        // // 만약 불일치 하는 경우, k를 SP[k]값으로 되돌려 더 작은 prefix길이 범위내에서 일치하는게 있는지 다시 확인
        while (k >= 0 && P[k + 1] != P[j]) {  // (k가 0 이상이고, 문자가 다를 경우) 
            k = SP[k];  // k를 SP[k]값으로 되돌리기  
        }
        // 만약 일치하는 경우, k를 하나 늘리기
        if (P[k + 1] == P[j]) {  
            k++;
        }
        // 현재 일치하는 길이(k)를 SP 배열에 저장
        SP[j] = k;  
    }
}

// 2-2. KMP 알고리즘 함수
void kmp_search(const char *T, const char *P, int n, int m, FILE *output_file) {
    int *SP = malloc(sizeof(int) * m);   // SP테이블을 먼저 동적 할당해주기기
    if (!SP) { perror("malloc"); exit(1); }  // 메모리 할당 실패할 경우 에러 처리 (탈출하기) 
    
	// SP 테이블을 만들어 계산하기 
    // 그래야 suffix/prefix match를 해 불필요한 비교 반복을 없앨 수 있음음
    computeSP(P, m, SP);  

    int j = -1;
    int i;
    
    // 텍스트T 전체를  한 글자씩 돌아가며,  
    for (i = 0; i < n; i++) {  
        // 만약 글자가 불일치할 경우 S[j]만큼 다시 되돌아가 비교하고,
        while (j >= 0 && P[j + 1] != T[i]) { 
            j = SP[j];  
        }
        // 만약 글자가 일치하는 경우에는 j를 하나 더 늘리며,
        if (P[j + 1] == T[i]) {  // 문자가 일치하면 j 증가
            j++;
        }
        // 패턴이 일치하는 경우에는 output_file에 index를 출력하기  
        if (j == m - 1) {  // 패턴이 일치하는 경우
            fprintf(output_file, "%d\n", i - (m - 1));  // (인덱스 출력)
            j = SP[j];  // 그리고 다음 위치로 이동
        }
    }

    free(SP);  // 동적 할당된 메모리 해제
}

// DNA 문자열을 랜덤으로 생성해주는 함수 
// : 주어진 길이만큼 DNA 문자열을 랜덤으로 만들어서 파일에 저장하도록 하는 용도  
void generate_random_dna(const char *filename, int length) {
    const char characters[] = "ACGT";  // 문자열은 ACGT로 사용할 것  
    FILE *file = fopen(filename, "w");  // 파일을 쓰기 모드로 열어서 
	// 만약 파일이 없을 경우에는 에러 처리  
    if (!file) {
        perror("(Error) input.txt 열기 실패 (writing모드로)");
        exit(1);
    }
    int i;
    // 문자열 길이만큼 돌며  
    for (i = 0; i < length; i++) {  
        fputc(characters[rand() % 4], file);  // 문자를 파일에 랜덤으로 저장한 후,  
    }
    fclose(file);  // 파일 닫기 
	// DNA 문자열이 랜덤으로 잘 생성되지 않아 단순히 디버깅 용으로 넣어둔 겁니다! 
    printf("File '%s' has been created with random DNA string of size %d.\n", filename, length);  // 확인 메시지
}

// 수행시간 측정하는 함수 - clock을 활용해서 시작시간과 끝나는 시간 측정해서 계산! 
double measure_time(void (*func)(const char*, const char*, int, int, FILE*), const char *T, const char *P, int n, int m, FILE *output_file) {
    clock_t start, end;
    start = clock();  // 시작 시간 측정하고,
	// brute-force함수 혹은 kmp 함수를 실행하도록 함수 포인터를 이용해 동적으로 함수 호출   
    func(T, P, n, m, output_file);  // 함수를 실행한 후,  
    end = clock();  //  끝난 시간 측정해, 
    return ((double)(end - start)) / CLOCKS_PER_SEC;  // 총 수행시간을 계산하기 (초 단위로 표현) 
}

int main(int argc, char *argv[]) {
    int i, j;
    // 프로그램이 실행될 때, 1. 입력파일, 2. 패턴, 3. 알고리즘 3개의 인자 필요  
    // 만약, 인자 개수가 맞지 않으면(인자가 부족한 경우) 오류 출력하도록 에러 처리  
    if (argc != 4) {
        fprintf(stderr, "Usage: %s input.txt PATTERN ALGORITHM\n", argv[0]);
        return 1; 
    }

    // 다양한 크기  n을 가지고 실행할 것 ( 직선적 알고리즘과 다른 알고리즘을 비교하기 위해) 
	//  n_values: 파일크기를 나타내는 배열 (1000, 10000, 100000, 1000000, 10000000) 
	//  m_values: 패턴 길이를 나타내는 배열 (5, 10, 15, 20, 30)
	// 두 알고리즘의 수행시간이 최대한 유의미하게 출력되게 하기 위해 n을 10배씩 증가시켰고,  
	// m도 5에서 30까지 5단위로 늘려봤습니다.  
    int n_values[] = {1000, 10000, 100000, 1000000, 10000000};  
    int m_values[] = {5, 10, 15, 20, 30}; 
    
     // 출력 파일을 위한 포인터 변수
    FILE *output_file;
    
     // CSV 파일 열기 (결과를 저장하기 위해)  
    // -> 이 파일에 각 파일 크기와 알고리즘 실행 시간 정보를 기록
    FILE *csv_file = fopen("C:\\Users\\juyeo\\Desktop\\ACCGTAT\\time_results.csv", "w");  // CSV 파일 열기

    if (!csv_file) {
        perror("(Error) CSV 파일 열기 실패(w모드로)");
        return 1;
    }

    // CSV 파일 헤더 작성하는 부분 
    fprintf(csv_file, "n, m, brute_force_time, kmp_time\n");  

	// (n_values 배열에 있는 각 n 값에 대해 반복하는데, ) 
    for (i = 0; i < sizeof(n_values) / sizeof(n_values[0]); i++) {
    	// 현재 배열 값을 n에 넣어주고,  
        int n = n_values[i];

		// (m_values 배열에 있는 각 m 값에 대해 )
        for (j = 0; j < sizeof(m_values) / sizeof(m_values[0]); j++) {
        	// 현재 m_values[j] 값을 m 변수에 저장한 후,  
            int m = m_values[j];

            // 1) DNA 문자열을 랜덤으로 생성해서 (by 함수 호출)  
            // ( n 크기의 랜덤 DNA 문자열을 생성해 ->  input.txt 파일에 저장하기 ) 
            generate_random_dna("C:\\Users\\juyeo\\Desktop\\ACCGTAT\\input.txt", n);  // 랜덤 DNA 생성

            // 2) input.txt 파일을 열어서 읽고,  
            FILE *fin = fopen(argv[1], "r"); // 입력 파일을 읽기 모드로 열기
            if (!fin) { perror("fopen"); return 1; } //파일 열기 실패할 경우 에러처리 

			// 3) 파일의 끝까지 이동하여 크기를 측정하고  
            fseek(fin, 0, SEEK_END);
            int file_size = ftell(fin);  // 파일 크기 구하기
            rewind(fin);  // 파일 포인터는 처음으로 되돌리기 

            // 4) 프로그램을 실행했을 떄 파일에서 텍스트(T)
			// 텍스트를 메모리로 읽어들이고, 
			// 끝에 \0을 추가해서 문자열을 종료하기  
			// -> comparing.exe input.txt ACCGTAT brute_force 이렇게 명령줄이 입력될 때  
			// input.txt가 argv[1]로  넘어와서 T(ext)로 저장되도록 했습니다.  
            char *T = malloc(file_size + 1);  // 메모리를 할당하고 
            fread(T, 1, file_size, fin);  // 파일을 일거 
            T[file_size] = '\0';  // 문자열 끝에 \o 추가한 다음 
            fclose(fin); //파일 닫기 
 			
 			// 5) 패턴 P를 명령줄 인자(argv[2])에서 가져오기  
 			// -> comparing.exe input.txt ACCGTAT brute_force 이렇게 명령줄이 입력될 떄  
 			//       ㅁㄱ 
 			// ACCGTAT가 argv[2]로서 넘어와서 P(attern)으로 저징되도록 했습니다.  
            char *P = argv[2];  
        }
    }

    fclose(csv_file);  // CSV 파일 닫기
    return 0; //프로그램 종료  
}

