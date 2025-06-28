// 2022110151 이주연
// 회문 (NOT recursive ver.) 
// 보다 확실한 판별을 위해 대소문자는 구별하지 않았습니다.  
// 강조를 위해 회문이 맞는 경우엔 "A"를 대문자로,
// 회문이 아닌 경우 "NOT"을 대문자로 출력했습니다.  
#include <stdio.h> 

//글자 수 세는 함수
int strLen(char *str){
	int len = 0;
	
	// 문자열 끝('\0')이 나오거나 줄바꿈('\n') 될 때까지 글자 수 세기  
	while (str[len] != '\0' && str[len] != '\n'){
		len++;
	}

	// 줄바꿈 \n없애주기 (깔끔한 출력을 위한 용도)
    // e.g. 'madam\n' -> 'madam\0' 로 바꿔 불필요한 줄바꿈('\n')이 일어나지 않도록.  
	if (str[len] == '\n'){
		str[len] = '\0';
	}

    //결국 리턴하는 값: 길이(len)  
	return len; 
}

// 재귀 호출을 활용해 회문인지(참인 경우 1) 아닌지(거짓인 경우0) 판별하기기 
int recurPalindrome(char *str, int left, int right){
	// 입력 값 : 문자열 (str), left 인덱스, right 인덱스
	// left는 left+1 상태로, right는 right-1 상태로 재귀 호출하기 위해 
	// left와 right도 입력받는다. 
	
	// (문자가 달라 0을 리턴한 경우를 제외하고)
	// 계속 재귀호출을 통해 left는 오른쪽으로 증가하고 right는 왼쪽으로 감소하다, 
	// 결국 left와 right가 만나면 회문으로 간주해 1 리턴 
	// (회문이 맞다, 참이라는 의미에서 1 리턴) 
	if (left >= right) 
		return 1;

	// left혹은 right 인덱스의 문자가 공백인 경우 건너뛰고 다음 문자 살펴보기 
	// 이때 재귀함수(recurVerPalindrome) 사용 
	if (str[left] == ' ') 
		return recurPalindrome(str, left + 1, right);
	if (str[right] == ' ') 
		return recurPalindrome(str, left, right - 1);

	// left와 right일때 문자를 비교해
	// 만약 문자가 다른 경우 -> 회문X -> 0 리턴
	if (str[left] != str[right]) return 0;

	// !재귀함수 호출!을 통해 다음 쌍(left와 right 문자)을 비교하기  
	// 이때 left 인덱스는 하나 늘리고 (+1)
	// right 인덱스는 하나 줄이기 (-1)
	return recurPalindrome(str, left + 1, right - 1);
}

int main() {
	//sentences.txt 파일 열기
	FILE *fp = fopen("sentences.txt", "r");

	//예외처리 : 파일이 없는 경우  (오류)
	if (fp == NULL){
		printf("파일을 찾을 수 없습니다.\n");
		return 1;
	}

	char str[100]; 

	printf("Check if the following words are palindromes(recursive ver.)  ");

	//파일에서 한줄씩 읽어와
	while (fgets(str, sizeof(str), fp) != NULL){
		// 줄바꿈 제거 (strLen함수 호출을 통해 제거시키기)
		strLen(str);

		// 앞쪽 공백 제거 (새 함수 없이 직접 처리)
		int start = 0;
		while (str[start] == ' ') {
			start++;  // 공백 문자 건너뜀
		}

		// 공백을 건너뛴 부분부터 문자열을 앞으로 당김
		int i = 0;
		while (str[start] != '\0') {
			str[i++] = str[start++];
		}
		// 새 문자열 끝에 NULL 문자 추가
		str[i] = '\0'; 

		//전체 글자수 len(문자열 길이) 
		int len = strLen(str);

		// 회문인지 체크해서 구별되게 출력
		// - 회문이면 참인 1값이 리턴돼 회문이 맞다는 표현 출력
		// - 회문이 아니면 거짓인 0값이 리턴돼 회문이 아니라는 표현 출력 
		if (recurPalindrome(str, 0, len - 1))
			printf(" \n'%s' is A palindrome",str);
		else 
			printf(" \n'%s' is NOT a palindrome",str);
	}

	
	fclose(fp);
	return 0;
}

