#include <stdio.h>
#include <stdlib.h>

#define N1 3
#define N2 2
#define N3 4

// 예제 3.7
// key[1] ~ key[N}의 범위를 갖는 N개의 key
char* tree_key1[N1 + 1] = { "", "key1","key2","key3" };
// key[1] ~ key[N]의 각 키가 search key일 확률 key_prob[1] ~ key_prob[N] 
double tree_prob1[N1 + 1] = { 0, 0.7, 0.2, 0.1 };

// 예제 3.8
char* tree_key2[N2 + 1] = { "", "key2","key3" };
double tree_prob2[N2 + 1] = { 0, 0.2, 0.1 };

// 예제 3.9
char* tree_key3[N3 + 1] = { "", "Don","Isabelle","Ralph","Wally" };
double tree_prob3[N3 + 1] = { 0, (double)3 / 8, (double)3 / 8, (double)1 / 8, (double)1 / 8 };

typedef struct node* nodePointer;
typedef struct node {
	char* key;
	nodePointer leftChild;
	nodePointer rightChild;
} node;

// 최적 이분검색트리 생성을 위한 정보를 제공하는 함수
double optSearchTree(int num, double* prob, double** avg_t, int** root);
// tree_key와 root 배열로 tree를 만드는 함수
nodePointer makeTree(int i, int j, char** tree_key, int** root);

void main() {
	// 최소 평균 검색시간
	double min_avg1;
	// avg_time[i][j]: i~j의 index를 가진 key 집합의 최소 평균 검색 시간을 저장하는 배열
	double** avg_time1;
	// root_of[i][j]: i~j의 index를 가진 key의 집합에서, root값으로 선정된 key의 index	
	int** root_of1;
	avg_time1 = (double**)calloc((N1 + 2), sizeof(double*));
	root_of1 = (int**)calloc((N1 + 2), sizeof(int*));
	for (int i = 0; i < N1 + 2; i++) {
		avg_time1[i] = (double*)calloc((N1 + 1), sizeof(double));
		root_of1[i] = (int*)calloc((N1 + 1), sizeof(int));
	}

	double min_avg2;
	double** avg_time2;
	int** root_of2;
	avg_time2 = (double**)calloc((N2 + 2), sizeof(double*));
	root_of2 = (int**)calloc((N2 + 2), sizeof(int*));
	for (int i = 0; i < N2 + 2; i++) {
		avg_time2[i] = (double*)calloc((N2 + 1), sizeof(double));
		root_of2[i] = (int*)calloc((N2 + 1), sizeof(int));
	}

	double min_avg3;
	double** avg_time3;
	int** root_of3;
	avg_time3 = (double**)calloc((N3 + 2), sizeof(double*));
	root_of3 = (int**)calloc((N3 + 2), sizeof(int*));
	for (int i = 0; i < N3 + 2; i++) {
		avg_time3[i] = (double*)calloc((N3 + 1), sizeof(double));
		root_of3[i] = (int*)calloc((N3 + 1), sizeof(int));
	}

	printf("= Dynamic Programming =\n");
	min_avg1 = optSearchTree(N1, tree_prob1, avg_time1, root_of1);
	printf("예제 3.7의 최소 평균 검색시간 : %f\n", min_avg1);
	min_avg2 = optSearchTree(N2, tree_prob2, avg_time2, root_of2);
	printf("예제 3.8의 최소 평균 검색시간 : %f\n", min_avg2);
	min_avg3 = optSearchTree(N3, tree_prob3, avg_time3, root_of3);
	printf("예제 3.9의 최소 평균 검색시간 : %f\n", min_avg3);
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
