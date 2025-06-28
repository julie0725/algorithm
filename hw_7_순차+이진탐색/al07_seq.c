// 2022110151 ���ֿ�
// 1. ����Ž��  
#include <stdio.h>

#define N 10

//����ü �����ϱ� ( key ���� �����ϱ� ���� �뵵!)
typedef struct {
	int key; 
} Element;

// ����ü �迭 �����ϱ� : �ε��� 1~N���� a[]
Element a[N + 1]; // +1�� �� ������ 1�� index���� ����ϱ� ����! 

// ���� Ž��
int sequential(int k, int* count) {
	int i = 1;

	// ���� i�� �迭 �ȿ� �ְ�, k ��, ã�� ����� ���� �� ã�Ҵٸ� (key�� k���� �ٸ� ��)
	while ((i < N + 1) && (a[i].key != k)) {
		i++; // i �ϳ� �������� �ٽ� ã��
		(*count)++; // ��Ƚ���� �ϳ� ������Ű��
	}

    if (i <= N) {
        return i;  // ã�� ��� ��ġ ��ȯ
    } else {
        return 0;  // �� ã�� ��� 0 ��ȯ
    }
}

int main() {
	int i;

	// 1. �迭�� key�� �ʱ�ȭ 1 2 3 ~ N(=10) key������ �־��ֱ�
	// ( �־��� ��츦 ���� ���̱� ���� 1 2 3 4 5 6 7 8 9 10 ��
	// ���� �������� ��ġ�� 10�� ã�� ����� �����帱 �̴ϴ�!  )
	for (i = 1; i <= N; i++) {
		a[i].key = i;
	}

	int searchSubject = 10;//ã���� �ϴ� ���
	int count = 0; //�� Ƚ��

    // ã���� �ϴ� ��� (searchSubject)�� 
    // 0���� �ʱ�ȭ�� �� Ƚ��(count)�� ������ sequential�Լ� ȣ��
    // ��ȯ�Ǵ� i���� index�� �־��ֱ� 
    //(index�� ���� index��°���� ã������ �˷��ֱ� ���� �뵵!!)
	int index = sequential(searchSubject, &count);

	//��� ���
	printf("2022110151 ���ֿ�\n\n");
	printf("1. [���� Ž��] - Sequential search\n");
	if (index <= N) {
		printf("\nã���� �ϴ� ���(searchSubject)�� %d�� ��\n", searchSubject);
		printf("\n�� Ƚ��(count)�� %d��! (%d�� Index���� ã�ҽ��ϴ�)\n", count, index);
	}
	else {
		printf("Ž�� ���ФФк�Ƚ���� %d\n", count);
	}

	return 0;
}
