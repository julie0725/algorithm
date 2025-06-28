// 2022110151 ���ֿ�
// heap Sort  
#include <stdio.h>

// �� ���� switch�ϱ� ���� ���� swap�Լ�  
// x <-> y
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// �� ���� �Լ�
// �������� ���� heapSort�ڵ� �󿡼� �ּ��� �ִ��� ������ ���������,�˰��� ������ ����
// �ʿ��� �κ��� �־����ϴ�. 
void makeMaxHeap(int a[], int root, int lastNode) {
    //��Ʈ ��� -> �θ� ���� ���� 
    int parent = root;
    int rootValue = a[root];

    // �ڽ� ��� ���� (�迭 index�� 0���� �����ϹǷ� ������ ���� +1)
    int leftson = 2 * parent + 1;
    int rightson = leftson + 1;
    // �ڽ� ���(�� vs ��) �� ū �� ���� ����
    int son;

    while (leftson <= lastNode) {
        // 1) �ڽ� ��峢�� �� �� -> ū ���� son�� �ֱ��
        if (rightson <= lastNode && a[leftson] < a[rightson])
            son = rightson;
        else
            son = leftson;

        // 2) �ڽ� ��� �� ū ��(son��) vs �θ� ��� �� 
        // ���� �ڽ� ��� ���� �θ� ��� ������ �� ũ�� 
        if (rootValue < a[son]) {
            // (a) �ڽ��� �θ� �ڸ���, 
            a[parent] = a[son];
            parent = son;
            // (b) �׸��� �ڽ� ��� �ٽ� ����
            leftson = 2 * parent + 1;
            rightson = leftson + 1;
        } else break; //if (�ڽ� �� <= �θ� ��) -> ���̻� �������� ���� �ʿ�x�Ƿ� �ݺ� �� 
    }
    // �ݺ����� ���� ��, ó���� �����ص� �θ� ��(rootVlue) ������ ��ġ�� �ٽ� �־��ֱ�
    // �ڽ� ���� ��� ����÷� ���� ���ڸ��� ������ �θ� �� ���� �־��ֱ� 
    a[parent] = rootValue; 
}

// �迭 ��� �Լ�
void printArray(int a[], int n) {
	int i;
	
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// �� ���� �Լ�( �������� ���� ) 
void heapSort(int a[], int n) {
	int i;
	
    //  1) max �� ����(�θ� >= �ڽ� ) 
    for (i = n / 2 - 1; i >= 0; i--) {
    	// i�� root�� �ϴ� ����Ʈ���� -> maxHeap�ִ� ������ �����  
        makeMaxHeap(a, i, n - 1);
    }

    // 2) ������  �ִ�(root)�� ���� "�� ��"�� �����鼭 ����
	// �迭�� �� �ں��� �����ؼ� ������ ���� ���ĵǵ��� �ݺ��� ���  
    for (i = n - 1; i > 0; i--) {
    	// a[0]�� ���� heap�� root�Ƿ�, �ִ�.
		// �� �ִ�(root) a[0]�� �� �� ���� a[i]�� �ٲٱ�  
        swap(&a[0], &a[i]);  
		
		// root�� ������ ������ �κ� a[0]~a[i-1]�� ������ �ٽ� heap���� ������Ű��     
		// == ũ�⸦ �ϳ� ���� ���¿��� �ٽ� �ִ� �� �����  
        makeMaxHeap(a, 0, i - 1);    
    }
}

int main() {
    int a[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int n = 10;
    int i;

    // �ʱ� �迭 ���
    printf("�ʱ� �迭: ");
    printArray(a, n);
    //-----------------------------------
    
    // heapSort���� ���� �� makeMaxHeap�� ȣ���� ���� �����߱� ������ 
	// ��ǻ� �ʿ� ������,
	// ������ �������� ������ ���� �迭�� ��� ���ߴ��� �ľ��ϱ� ���� 
	// ȣ���ؼ� ����߽��ϴ�!
    for (i = n / 2 - 1; i >= 0; i--) {
        makeMaxHeap(a, i, n - 1);
    }
    // ������ �� ��� 
    printf("������ ��: ");
    printArray(a, n);

    //------------------------------------
    // �� ���� ����
    heapSort(a, n);
    // ���ĵ� �迭 ���
    printf("���ĵ� �迭: ");
    printArray(a, n);

    return 0;
}

