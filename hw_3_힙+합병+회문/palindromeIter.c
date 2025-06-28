// 2022110151 ���ֿ�   
// ȸ�� (NOT recursive ver.) 
// ���� Ȯ���� �Ǻ��� ���� ��ҹ��ڴ� �������� �ʾҽ��ϴ�. 
// ������ ���� ȸ���� �´� ��쿣 "A"�� �빮�ڷ�,
// ȸ���� �ƴ� ��� "NOT"�� �빮�ڷ� ����߽��ϴ�.  
#include <stdio.h>

//���� �� ���� �Լ�  
int strLen(char *str){
	int len = 0;
	
	// ���ڿ� ���� �����ų� �ٹٲ� �� ������ ���� �� ����  
	while (str[len] != '\0' && str[len] != '\n'){
		len++;
	}
	
	// �ٹٲ� \n�����ֱ� (����� ����� ���� �뵵)
	if (str[len] == '\n'){
		str[len] = '\0';
	} 
	
	//���� ��: ����(len)  
	return len;   
} 

//ȸ������ üũ�ϴ�  �Լ�: Iterative (���X) ver. 
//ȸ��O ��� -> 1 ���� 
//ȸ��X ��� -> 0 ����  
int checkPalindrome(char *str){
	//�Է� �� : ���ڿ�
	
	// ����, ������ �ε��� ���� 
	int left = 0;
	int right = strLen(str) - 1;
	
	while (left < right){
		// left�� right �ε����� ���� ������ ���
		// : left�� right �ε��� �� ĭ �ű�� continue 
		if (str[left] == ' '){
			left++;
			continue;
		} 
		if (str[right] == ' ') {
			right--;
			continue;
		}
		
		// ���� ���� ��� -> ȸ��X -> 0 ���� 
		if(str[left] != str[right]){
			return 0; 
		}
		
		//left�� right�ε����� ��� ���ϱ� ���� ++,--�� �����̱� 
		left++;
		right--; 
	} 
	
	//���� ��� -> ȸ��O -> 1 ����  
	return 1;
	 
} 

//main �Լ�  
int main() {
	// .txt���� ����  
	FILE *fp = fopen("sentences.txt", "r");
	
	//����ó�� : ������ ���� ���  (����)  
	if (fp == NULL){
		printf("Cannot find the file.\n");
		return 1;
	}
	
	char str[100];
	
	printf("Check if the following words are palindromes(not recursive ver.)  ");
	
	//���Ͽ��� ���پ� �о��
	while (fgets(str, sizeof(str), fp) != NULL){
		// ȸ������ üũ�ؼ� �����ǰ� ���
		// - ȸ���̸� ���� 1���� ���ϵ� ȸ���� �´ٴ� ǥ�� ���
		// - ȸ���� �ƴϸ� ������ 0���� ���ϵ� ȸ���� �ƴ϶�� ǥ�� ��� 
	 	if (checkPalindrome(str)) 
			printf(" \n'%s' is A palindrome",str);
		else 
			printf(" \n'%s' is NOT a palindrome",str);
	}
	
	fclose(fp);
	return 0;
	
}

 

 

