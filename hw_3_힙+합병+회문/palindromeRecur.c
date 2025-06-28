// 2022110151 ���ֿ�
// ȸ�� (NOT recursive ver.) 
// ���� Ȯ���� �Ǻ��� ���� ��ҹ��ڴ� �������� �ʾҽ��ϴ�.  
// ������ ���� ȸ���� �´� ��쿣 "A"�� �빮�ڷ�,
// ȸ���� �ƴ� ��� "NOT"�� �빮�ڷ� ����߽��ϴ�.  
#include <stdio.h> 

//���� �� ���� �Լ�
int strLen(char *str){
	int len = 0;
	
	// ���ڿ� ��('\0')�� �����ų� �ٹٲ�('\n') �� ������ ���� �� ����  
	while (str[len] != '\0' && str[len] != '\n'){
		len++;
	}

	// �ٹٲ� \n�����ֱ� (����� ����� ���� �뵵)
    // e.g. 'madam\n' -> 'madam\0' �� �ٲ� ���ʿ��� �ٹٲ�('\n')�� �Ͼ�� �ʵ���.  
	if (str[len] == '\n'){
		str[len] = '\0';
	}

    //�ᱹ �����ϴ� ��: ����(len)  
	return len; 
}

// ��� ȣ���� Ȱ���� ȸ������(���� ��� 1) �ƴ���(������ ���0) �Ǻ��ϱ�� 
int recurPalindrome(char *str, int left, int right){
	// �Է� �� : ���ڿ� (str), left �ε���, right �ε���
	// left�� left+1 ���·�, right�� right-1 ���·� ��� ȣ���ϱ� ���� 
	// left�� right�� �Է¹޴´�. 
	
	// (���ڰ� �޶� 0�� ������ ��츦 �����ϰ�)
	// ��� ���ȣ���� ���� left�� ���������� �����ϰ� right�� �������� �����ϴ�, 
	// �ᱹ left�� right�� ������ ȸ������ ������ 1 ���� 
	// (ȸ���� �´�, ���̶�� �ǹ̿��� 1 ����) 
	if (left >= right) 
		return 1;

	// leftȤ�� right �ε����� ���ڰ� ������ ��� �ǳʶٰ� ���� ���� ���캸�� 
	// �̶� ����Լ�(recurVerPalindrome) ��� 
	if (str[left] == ' ') 
		return recurPalindrome(str, left + 1, right);
	if (str[right] == ' ') 
		return recurPalindrome(str, left, right - 1);

	// left�� right�϶� ���ڸ� ����
	// ���� ���ڰ� �ٸ� ��� -> ȸ��X -> 0 ����
	if (str[left] != str[right]) return 0;

	// !����Լ� ȣ��!�� ���� ���� ��(left�� right ����)�� ���ϱ�  
	// �̶� left �ε����� �ϳ� �ø��� (+1)
	// right �ε����� �ϳ� ���̱� (-1)
	return recurPalindrome(str, left + 1, right - 1);
}

int main() {
	//sentences.txt ���� ����
	FILE *fp = fopen("sentences.txt", "r");

	//����ó�� : ������ ���� ���  (����)
	if (fp == NULL){
		printf("������ ã�� �� �����ϴ�.\n");
		return 1;
	}

	char str[100]; 

	printf("Check if the following words are palindromes(recursive ver.)  ");

	//���Ͽ��� ���پ� �о��
	while (fgets(str, sizeof(str), fp) != NULL){
		// �ٹٲ� ���� (strLen�Լ� ȣ���� ���� ���Ž�Ű��)
		strLen(str);

		// ���� ���� ���� (�� �Լ� ���� ���� ó��)
		int start = 0;
		while (str[start] == ' ') {
			start++;  // ���� ���� �ǳʶ�
		}

		// ������ �ǳʶ� �κк��� ���ڿ��� ������ ���
		int i = 0;
		while (str[start] != '\0') {
			str[i++] = str[start++];
		}
		// �� ���ڿ� ���� NULL ���� �߰�
		str[i] = '\0'; 

		//��ü ���ڼ� len(���ڿ� ����) 
		int len = strLen(str);

		// ȸ������ üũ�ؼ� �����ǰ� ���
		// - ȸ���̸� ���� 1���� ���ϵ� ȸ���� �´ٴ� ǥ�� ���
		// - ȸ���� �ƴϸ� ������ 0���� ���ϵ� ȸ���� �ƴ϶�� ǥ�� ��� 
		if (recurPalindrome(str, 0, len - 1))
			printf(" \n'%s' is A palindrome",str);
		else 
			printf(" \n'%s' is NOT a palindrome",str);
	}

	
	fclose(fp);
	return 0;
}

