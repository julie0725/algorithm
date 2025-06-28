#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 0. ���ڿ� ���� ����ϱ�  
//    e.g. ���ڿ�'abc' -> slen = 3
int len(const char *s) {
    int i = 0;
    // ���ڿ��� ���� ��('\0')���� i++�ϸ� ���ڿ��� ���̸� ����ϱ�
    while (s[i] != '\0') i++;  // ���ڿ� ������ �ݺ�
    return i;// i�� ��� ���ڿ� ���̸� �����ϱ� 
}

// ��� 1) Brute-Force ������ ���  
void brute_force(const char *T, const char *P, int n, int m, FILE *output_file) {
    int i, j;
    // �ؽ�Ʈ ù ����(0)���� ������ (i)
    // ������ �ؽ�Ʈ ���� �Ѿ�� �ʴ� ������ n-m���� �˻��ϸ�
    for (i = 0; i <= n - m; i++) {  
    	//������ �� ���� P[j]�� i���� j��ŭ ������ �ؽ�Ʈ ���� T[i+j]�� �ϳ����� ����
        for (j = 0; j < m; j++) {  //(���� p���̸�ŭ �ݺ�) 
             // ���� ���� ���ڰ� �ٸ��� ����������,
            if (T[i + j] != P[j]) 
				break;  
        }
        // ���� ���ڰ� ��� ��ġ�� ���(�����̶� ������ ���� ���)  
        if (j == m) { 
            fprintf(output_file, "%d\n", i);  // output_file�� �ε��� ����ϱ� ! 
        }
    }
}

// ��� 2) KMP �˰��� ( SP ���̺��� Ȱ���� ���ǿ��� �ݺ� ���̴� ���) 
// 2-1. SP ���̺� ����ϱ�  
void computeSP(const char *P, int m, int *SP) {
    int k = -1; // k: ������� ��ġ�� prefix�� ������ index�� �ǹ� (������ ������ ��Ÿ���� �뵵��)
                // ���� ��ġ�� ���ڰ� ���� ���ư� ��ġ�� ���� ������ -1�� ǥ��
    int j;
    SP[0] = -1;  // SP ���̺� �ʱ�ȭ ( SP ���̺�: prefix�� suffix�� ��ġ�� ���� �� ���� ��� �迭)
	// ������ 1�� �ε������� �����ؼ� ���� ����������
    for (j = 1; j < m; j++) {  // j�� 1���� m-1���� �ݺ�
        // // ���� ����ġ �ϴ� ���, k�� SP[k]������ �ǵ��� �� ���� prefix���� ���������� ��ġ�ϴ°� �ִ��� �ٽ� Ȯ��
        while (k >= 0 && P[k + 1] != P[j]) {  // (k�� 0 �̻��̰�, ���ڰ� �ٸ� ���) 
            k = SP[k];  // k�� SP[k]������ �ǵ�����  
        }
        // ���� ��ġ�ϴ� ���, k�� �ϳ� �ø���
        if (P[k + 1] == P[j]) {  
            k++;
        }
        // ���� ��ġ�ϴ� ����(k)�� SP �迭�� ����
        SP[j] = k;  
    }
}

// 2-2. KMP �˰��� �Լ�
void kmp_search(const char *T, const char *P, int n, int m, FILE *output_file) {
    int *SP = malloc(sizeof(int) * m);   // SP���̺��� ���� ���� �Ҵ����ֱ��
    if (!SP) { perror("malloc"); exit(1); }  // �޸� �Ҵ� ������ ��� ���� ó�� (Ż���ϱ�) 
    
	// SP ���̺��� ����� ����ϱ� 
    // �׷��� suffix/prefix match�� �� ���ʿ��� �� �ݺ��� ���� �� ������
    computeSP(P, m, SP);  

    int j = -1;
    int i;
    
    // �ؽ�ƮT ��ü��  �� ���ھ� ���ư���,  
    for (i = 0; i < n; i++) {  
        // ���� ���ڰ� ����ġ�� ��� S[j]��ŭ �ٽ� �ǵ��ư� ���ϰ�,
        while (j >= 0 && P[j + 1] != T[i]) { 
            j = SP[j];  
        }
        // ���� ���ڰ� ��ġ�ϴ� ��쿡�� j�� �ϳ� �� �ø���,
        if (P[j + 1] == T[i]) {  // ���ڰ� ��ġ�ϸ� j ����
            j++;
        }
        // ������ ��ġ�ϴ� ��쿡�� output_file�� index�� ����ϱ�  
        if (j == m - 1) {  // ������ ��ġ�ϴ� ���
            fprintf(output_file, "%d\n", i - (m - 1));  // (�ε��� ���)
            j = SP[j];  // �׸��� ���� ��ġ�� �̵�
        }
    }

    free(SP);  // ���� �Ҵ�� �޸� ����
}

// DNA ���ڿ��� �������� �������ִ� �Լ� 
// : �־��� ���̸�ŭ DNA ���ڿ��� �������� ���� ���Ͽ� �����ϵ��� �ϴ� �뵵  
void generate_random_dna(const char *filename, int length) {
    const char characters[] = "ACGT";  // ���ڿ��� ACGT�� ����� ��  
    FILE *file = fopen(filename, "w");  // ������ ���� ���� ��� 
	// ���� ������ ���� ��쿡�� ���� ó��  
    if (!file) {
        perror("(Error) input.txt ���� ���� (writing����)");
        exit(1);
    }
    int i;
    // ���ڿ� ���̸�ŭ ����  
    for (i = 0; i < length; i++) {  
        fputc(characters[rand() % 4], file);  // ���ڸ� ���Ͽ� �������� ������ ��,  
    }
    fclose(file);  // ���� �ݱ� 
	// DNA ���ڿ��� �������� �� �������� �ʾ� �ܼ��� ����� ������ �־�� �̴ϴ�! 
    printf("File '%s' has been created with random DNA string of size %d.\n", filename, length);  // Ȯ�� �޽���
}

// ����ð� �����ϴ� �Լ� - clock�� Ȱ���ؼ� ���۽ð��� ������ �ð� �����ؼ� ���! 
double measure_time(void (*func)(const char*, const char*, int, int, FILE*), const char *T, const char *P, int n, int m, FILE *output_file) {
    clock_t start, end;
    start = clock();  // ���� �ð� �����ϰ�,
	// brute-force�Լ� Ȥ�� kmp �Լ��� �����ϵ��� �Լ� �����͸� �̿��� �������� �Լ� ȣ��   
    func(T, P, n, m, output_file);  // �Լ��� ������ ��,  
    end = clock();  //  ���� �ð� ������, 
    return ((double)(end - start)) / CLOCKS_PER_SEC;  // �� ����ð��� ����ϱ� (�� ������ ǥ��) 
}

int main(int argc, char *argv[]) {
    int i, j;
    // ���α׷��� ����� ��, 1. �Է�����, 2. ����, 3. �˰��� 3���� ���� �ʿ�  
    // ����, ���� ������ ���� ������(���ڰ� ������ ���) ���� ����ϵ��� ���� ó��  
    if (argc != 4) {
        fprintf(stderr, "Usage: %s input.txt PATTERN ALGORITHM\n", argv[0]);
        return 1; 
    }

    // �پ��� ũ��  n�� ������ ������ �� ( ������ �˰���� �ٸ� �˰����� ���ϱ� ����) 
	//  n_values: ����ũ�⸦ ��Ÿ���� �迭 (1000, 10000, 100000, 1000000, 10000000) 
	//  m_values: ���� ���̸� ��Ÿ���� �迭 (5, 10, 15, 20, 30)
	// �� �˰����� ����ð��� �ִ��� ���ǹ��ϰ� ��µǰ� �ϱ� ���� n�� 10�辿 �������װ�,  
	// m�� 5���� 30���� 5������ �÷��ý��ϴ�.  
    int n_values[] = {1000, 10000, 100000, 1000000, 10000000};  
    int m_values[] = {5, 10, 15, 20, 30}; 
    
     // ��� ������ ���� ������ ����
    FILE *output_file;
    
     // CSV ���� ���� (����� �����ϱ� ����)  
    // -> �� ���Ͽ� �� ���� ũ��� �˰��� ���� �ð� ������ ���
    FILE *csv_file = fopen("C:\\Users\\juyeo\\Desktop\\ACCGTAT\\time_results.csv", "w");  // CSV ���� ����

    if (!csv_file) {
        perror("(Error) CSV ���� ���� ����(w����)");
        return 1;
    }

    // CSV ���� ��� �ۼ��ϴ� �κ� 
    fprintf(csv_file, "n, m, brute_force_time, kmp_time\n");  

	// (n_values �迭�� �ִ� �� n ���� ���� �ݺ��ϴµ�, ) 
    for (i = 0; i < sizeof(n_values) / sizeof(n_values[0]); i++) {
    	// ���� �迭 ���� n�� �־��ְ�,  
        int n = n_values[i];

		// (m_values �迭�� �ִ� �� m ���� ���� )
        for (j = 0; j < sizeof(m_values) / sizeof(m_values[0]); j++) {
        	// ���� m_values[j] ���� m ������ ������ ��,  
            int m = m_values[j];

            // 1) DNA ���ڿ��� �������� �����ؼ� (by �Լ� ȣ��)  
            // ( n ũ���� ���� DNA ���ڿ��� ������ ->  input.txt ���Ͽ� �����ϱ� ) 
            generate_random_dna("C:\\Users\\juyeo\\Desktop\\ACCGTAT\\input.txt", n);  // ���� DNA ����

            // 2) input.txt ������ ��� �а�,  
            FILE *fin = fopen(argv[1], "r"); // �Է� ������ �б� ���� ����
            if (!fin) { perror("fopen"); return 1; } //���� ���� ������ ��� ����ó�� 

			// 3) ������ ������ �̵��Ͽ� ũ�⸦ �����ϰ�  
            fseek(fin, 0, SEEK_END);
            int file_size = ftell(fin);  // ���� ũ�� ���ϱ�
            rewind(fin);  // ���� �����ʹ� ó������ �ǵ����� 

            // 4) ���α׷��� �������� �� ���Ͽ��� �ؽ�Ʈ(T)
			// �ؽ�Ʈ�� �޸𸮷� �о���̰�, 
			// ���� \0�� �߰��ؼ� ���ڿ��� �����ϱ�  
			// -> comparing.exe input.txt ACCGTAT brute_force �̷��� ������� �Էµ� ��  
			// input.txt�� argv[1]��  �Ѿ�ͼ� T(ext)�� ����ǵ��� �߽��ϴ�.  
            char *T = malloc(file_size + 1);  // �޸𸮸� �Ҵ��ϰ� 
            fread(T, 1, file_size, fin);  // ������ �ϰ� 
            T[file_size] = '\0';  // ���ڿ� ���� \o �߰��� ���� 
            fclose(fin); //���� �ݱ� 
 			
 			// 5) ���� P�� ����� ����(argv[2])���� ��������  
 			// -> comparing.exe input.txt ACCGTAT brute_force �̷��� ������� �Էµ� ��  
 			//       ���� 
 			// ACCGTAT�� argv[2]�μ� �Ѿ�ͼ� P(attern)���� ��¡�ǵ��� �߽��ϴ�.  
            char *P = argv[2];  
        }
    }

    fclose(csv_file);  // CSV ���� �ݱ�
    return 0; //���α׷� ����  
}

