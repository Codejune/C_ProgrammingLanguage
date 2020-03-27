#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double** matrix;

void creatMatrix(int size) { // ��� ����
	int i;
	matrix = (double**)calloc(size, sizeof(double*));
	for (i = 0; i < size; i++) 
		matrix[i] = (double*)calloc(size + 1, sizeof(double));
}

void assignMatrix(int size) { // ��� �Է�
	int i, j;
	printf("input Elements:\n");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size + 1; j++)
			scanf("%lf", &matrix[i][j]);
	}
}

void printMatrix(int size) { // ��� ���
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size + 1; j++)
			printf("%.3lf ", matrix[i][j]);
		printf("\n");
	}
}

void swap(int size, int a, int b) { // �� ��ġ ����
	for (int i = 0; i < size + 1; i++) {
        double temp = matrix[a][i];
		matrix[a][i] = matrix[b][i];
		matrix[b][i] = temp;
	}
}

void gauss_jordan(double** matrix, int size) { // ���콺 ���� �ҰŹ�
    // ���콺 �Ұ�
    for (int i = 0; i < size - 1; i++) {
        // ��� �밢���� 0�� ��� �� swap
        if (!matrix[i][i]) {                   
            for (int j = i + 1; j < size; j++) 
                if (matrix[j][i]) {
                    swap(matrix, size, i, j);
                    break;
                }
            i--;
        // ����� �밢���� �ƴ� ���
        } else {   
            double divide = matrix[i][i]; //������ �ϸ鼭 i��° ����� �ٲ�Ƿ� �̸� �����س��ƾ��մϴ�
            
            for (int j = 0; j < size + 1; j++)
                 matrix[i][j] *= (1 / divide); //i��° �࿡ R(i)�� i��° ����� ������ ���մϴ�
            
            for (int j = i + 1; j < size; j++){
                double multiply = matrix[j][i]; //���������� matrix[j][i]�� ������ �ϸ鼭 ���� �ٲ�Ƿ� �̸� �����س��ƾ��մϴ�
                                                //multiply�� �ʿ��� ����: i��° ����� 1�� ����� ����
                for (int k = 0; k < size + 1; k++)
                    matrix[j][k] -= (matrix[i][k] * multiply); //R(i)��° ��� R(j)��° ���� ���մϴ�
                
            }
        }
    }

    double temp = matrix[size - 1][size - 1]; //������ ���� i��° ����� �����س����ϴ�
    for (int i = 0; i < size + 1; i++)
        matrix[size - 1][i] *= (1 / temp); //������ �࿡ i��° ����� ������ŭ ���մϴ�
     

    // ���콺 ���� �Ұ�
    for (int i = size - 1; i > 0; i--) { // �Ųٷ�
        for (int j = i - 1; j >= 0; j--) {
            double multiply = matrix[j][i]; //�����ϸ鼭 �ٲ�� ���̴� �̸� ����
            for (int k = i; k < size + 1; k++)
                matrix[j][k] -= (matrix[i][k] * multiply);
        }
    }
}

int main(void) {
	int size;
	printf("Programming Language assignment #3(Exit : -1)\n");
	printf("Matrix size(ex. [3*3]-> 3): ");
	scanf("%d", &size);
	creatMatrix(size);
	assignMatrix(size);
    gauss_jordan(matrix, size);
    printMatrix(size);
}