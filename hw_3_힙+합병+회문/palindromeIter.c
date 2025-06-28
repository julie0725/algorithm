// 2022110151 이주연   
// 회문 (NOT recursive ver.) 
// 보다 확실한 판별을 위해 대소문자는 구별하지 않았습니다. 
// 강조를 위해 회문이 맞는 경우엔 "A"를 대문자로,
// 회문이 아닌 경우 "NOT"을 대문자로 출력했습니다.  
#include <stdio.h>

//글자 수 세는 함수  
int strLen(char *str){
	int len = 0;
	
	// 문자열 끝이 나오거나 줄바꿈 될 때까지 글자 수 세기  
	while (str[len] != '\0' && str[len] != '\n'){
		len++;
	}
	
	// 줄바꿈 \n없애주기 (깔끔한 출력을 위한 용도)
	if (str[len] == '\n'){
		str[len] = '\0';
	} 
	
	//리턴 값: 길이(len)  
	return len;   
} 

//회문인지 체크하는  함수: Iterative (재귀X) ver. 
//회문O 경우 -> 1 리턴 
//회문X 경우 -> 0 리턴  
int checkPalindrome(char *str){
	//입력 값 : 문자열
	
	// 왼쪽, 오른쪽 인덱스 설정 
	int left = 0;
	int right = strLen(str) - 1;
	
	while (left < right){
		// left와 right 인덱스의 값이 공백인 경우
		// : left와 right 인덱스 한 칸 옮기고 continue 
		if (str[left] == ' '){
			left++;
			continue;
		} 
		if (str[right] == ' ') {
			right--;
			continue;
		}
		
		// 같지 않은 경우 -> 회문X -> 0 리턴 
		if(str[left] != str[right]){
			return 0; 
		}
		
		//left와 right인덱스를 계속 비교하기 위해 ++,--로 움직이기 
		left++;
		right--; 
	} 
	
	//같은 경우 -> 회문O -> 1 리턴  
	return 1;
	 
} 

//main 함수  
int main() {
	// .txt파일 열기  
	FILE *fp = fopen("sentences.txt", "r");
	
	//예외처리 : 파일이 없는 경우  (오류)  
	if (fp == NULL){
		printf("Cannot find the file.\n");
		return 1;
	}
	
	char str[100];
	
	printf("Check if the following words are palindromes(not recursive ver.)  ");
	
	//파일에서 한줄씩 읽어와
	while (fgets(str, sizeof(str), fp) != NULL){
		// 회문인지 체크해서 구별되게 출력
		// - 회문이면 참인 1값이 리턴돼 회문이 맞다는 표현 출력
		// - 회문이 아니면 거짓인 0값이 리턴돼 회문이 아니라는 표현 출력 
	 	if (checkPalindrome(str)) 
			printf(" \n'%s' is A palindrome",str);
		else 
			printf(" \n'%s' is NOT a palindrome",str);
	}
	
	fclose(fp);
	return 0;
	
}

 

 

