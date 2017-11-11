#include <stdio.h>
#include <stdlib.h>

int unit = 0; // ���������� ����� Ƚ���� �����ϴ� ��������

#define TEST_N 30 // 0~30�� key�� ���� ������ �����ϱ� ���� test�� ����
double tree_prob[TEST_N + 1] = { 0 };

typedef struct node* nodePointer;
typedef struct node {
	char* key;
	nodePointer leftChild;
	nodePointer rightChild;
} node;

double optSearchTree(int num, double* prob, double** avg_t, int** root); // ���� �̺а˻�Ʈ�� ������ ���� ������ �����ϴ� �Լ�
nodePointer makeTree(int i, int j, char** tree_key, int** root); // tree_key�� root �迭�� tree�� ����� �Լ�

void main() {
	for (int i = 0; i <= TEST_N; i++) {
		double min_avg;
		double** avg_time;
		int** root_of;
		avg_time = (double**)calloc((i + 2), sizeof(double*));
		root_of = (int**)calloc((i + 2), sizeof(int*));
		for (int j = 0; j < i + 2; j++) {
			avg_time[j] = (double*)calloc((i + 1), sizeof(double));
			root_of[j] = (int*)calloc((i + 1), sizeof(int));
		}

		min_avg = optSearchTree(i, tree_prob, avg_time, root_of);
		printf("%d : ", i);
		printf("%d\n", unit);
	}
}

double optSearchTree(int num, double* prob, double** avg_t, int** root) {
	int i, j, k, m, diagonal;
	double min, sigma = 0;
	int min_k;
	double min_avg;
	for (i = 1; i <= num; i++) {
		avg_t[i][i - 1] = 0;
		avg_t[i][i] = prob[i];
		root[i][i] = i;
		root[i][i - 1] = 0;
	}
	avg_t[num + 1][num] = 0;
	root[num + 1][num] = 0;
	for (diagonal = 1; diagonal <= num - 1; diagonal++)
		for (i = 1; i <= num - diagonal; i++) {
			j = i + diagonal;

			min = avg_t[i][i - 1] + avg_t[i + 1][j];
			min_k = i;
			for (k = i; k <= j; k++) {
				unit += 1; // �������� ����Ƚ�� ����
				if (min > avg_t[i][k - 1] + avg_t[k + 1][j]) {
					min = avg_t[i][k - 1] + avg_t[k + 1][j];
					min_k = k;
				}
			}
			sigma = 0;
			for (m = i; m <= j; m++) {
				sigma += prob[m];
			}
			avg_t[i][j] = min + sigma;
			root[i][j] = min_k;
		}
	return min_avg = avg_t[1][num];
}

nodePointer makeTree(int i, int j, char** tree_key, int** root) {
	int k;
	nodePointer temp_node;

	k = root[i][j];
	if (k == 0)
		return NULL;
	else {
		temp_node = (nodePointer)malloc(sizeof(node));
		temp_node->key = tree_key[k];
		temp_node->leftChild = makeTree(i, k - 1, tree_key, root);
		temp_node->rightChild = makeTree(k + 1, j, tree_key, root);
	}
	return temp_node;
}