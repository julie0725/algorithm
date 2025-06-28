// 2022110151 ���ֿ�  
// �� ���� (�˰���2 ���)  
#include <stdio.h>

// �� ���� switch�ϱ� ���� ���� swap�Լ�  
// x <-> y
void Swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// �� ���� �Լ�  
void makeMaxHeap(int a[], int root, int lastNode) {
	//�Է� : �迭 a[]�� root���(i), lastNode(������ ���(�� n-1))
	// root���� ���� i(��, �θ���)�� parent�� �����صα�  
    int parent = root;   
	//root�� �ִ� ���� rootValue�� ����   
    int rootValue = a[root];
    
    // index ����ϱ� 
    // - ���� �ڽ� : (�θ���� * 2) + 1             
	//               **����� ���⼭ 1�� ���� ������ �迭�� �ε����� 0���� �����ϱ� ������ �̸� �����ְ��� 1�� ���߽��ϴ�..  
	// - ������ �ڽ� : ���� �ڽ� ���� + 1 
	// - son : �ڽ� �߿��� �� ū ���� ���� ����� 'index'�� ������ ���� 
    int leftson = 2 * parent + 1;
    int rightson = leftson + 1;
    int son;

    // �ڽ��� �ִ� ��� ( ��, ���� �ڽ��� �迭 �ȿ� �ִ� ��쿡��) ������ �ݺ�������  ����  
    while (leftson <= lastNode) {
    	// 1)  "�����ڽ� �� vs ������ �ڽ� �� ���ؼ� -> �� ū ���� son�� ����" 
    	// ����, ������ �ڽ��� �ְ�(rightson <=lastNode: ��, lastNodd���� ���� �ְ�)
		// ���� �ڽ� �� < ������ �ڽ� �� �� ��� -> son�� ������ �ڽ��� ����  
        if (rightson <= lastNode && a[leftson] < a[rightson])
            son = rightson;
        // �׷��� ���� ���, son���� ���� �ڽ��� ����
        else
            son = leftson;

		// 2) ���� �θ��� �� vs (�ڽ� ��� �� ū ���� �����) son���� ���� -> 
		//         - �ڽİ��� �� ū ��� : �ڸ� �ٲٱ� (�ڽİ��� �θ� �ڸ��� ������)   
        if (rootValue < a[son]) {
        	// (�θ� �� < �ڽ� �� �϶�)  �ڽ� ���� �θ� �ڸ��� �ְ�,  
            a[parent] = a[son];
            //�ڽ��� new �θ�� �������ְ�,  
            parent = son;
            //new �θ� �������� �ڽ� �ε���(���� �ڽ�, ������ �ڽ�)�� �ٽ� ����Ѵ�.  
            // ����� �迭 �ε����� 0���� �����ϴ� ���⼭�� leftson�� 2*parent �� 1�� �������. (�� �����ߴ�!) 
            leftson = 2 * parent + 1;
            rightson = leftson + 1;
        } else break; //if (�ڽ� �� <= �θ� ��) -> ���̻� �������� ���� �ʿ�x�Ƿ� �ݺ� �� 
    }
    // �ݺ����� ���� ��, ó���� �����ص� �θ� ��(rootVlue) ������ ��ġ�� �ٽ� �־��ֱ�
    // �ڽ� ���� ��� ����÷� ���� ���ڸ��� ������ �θ� �� ���� �־��ֱ� 
    a[parent] = rootValue;
}

// �ܼ� �迭 ��¿� (�ܰ躰�� Ȯ���ϴ� �뵵)  
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
	
	//����, �ʱ� ������ �迭(initial array)����ϱ�  
    printf("�ʱ� �迭 A : ");
    printArray(a, n);
    printf("-----------\n") ;


    // i��  n/2 - 1 ���� 0���� �����ϸ�  �� subtree�� �ִ� ������ ���� �� �ֵ��� makeMaxHeap ȣ��
	// �̶�, �� ���� ������ �ܰ躰�� ���� ����
	// �� ���� �Լ�(==makeMaxHeap �Լ�) ȣ�� ��, ���� �迭 ����(printArray�Լ� ȣ��)�� ���  
    for (i = n/2 - 1; i >= 0; i--) {
        printf("i = %d�� ��:\n", i);
        //�� ���� �Լ� ȣ��  
        makeMaxHeap(a, i, n - 1);
        //���� �迭 ���� ����� ���� printArrayȣ��  (�������� ���� printArray �Լ��� ���� ó���߽��ϴ�.)  
        printf("�迭 ����: ");
        printArray(a, n);
    }

    // ������ �� ������ �迭�� ����ϱ�
	printf("-----------\n") ;  
    printf("\n���������� ��: "); 
    printArray(a, n);
    return 0;
}


