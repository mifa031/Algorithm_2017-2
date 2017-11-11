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
double optSearchTree(int num, double* prob, int** root);
// 재귀 함수로써, i~j의 index를 가진 key 집합의 최소 평균 검색시간과 root 배열을 return
double minAvgTime(int i, int j, double* prob, int** root);
// tree_key와 root 배열로 tree를 만드는 함수
nodePointer makeTree(int i, int j, char** tree_key, int** root);

void main() {
	// 최소 평균 검색시간
	double min_avg1;
	// root_of(i,j) : i~j의 index를 가진 key의 집합에서, root값으로 선정된 key의 index
	int** root_of1;
	root_of1 = (int**)calloc((N1 + 2), sizeof(int*));
	for (int i = 0; i < N1 + 2; i++) {
		root_of1[i] = (int*)calloc((N1 + 1), sizeof(int));
	}

	double min_avg2;
	int** root_of2;
	root_of2 = (int**)calloc((N2 + 2), sizeof(int*));
	for (int i = 0; i < N2 + 2; i++) {
		root_of2[i] = (int*)calloc((N2 + 1), sizeof(int));
	}

	double min_avg3;
	int** root_of3;
	root_of3 = (int**)calloc((N3 + 2), sizeof(int*));
	for (int i = 0; i < N3 + 2; i++) {
		root_of3[i] = (int*)calloc((N3 + 1), sizeof(int));
	}

	printf("= Divide-and-Conquer =\n");
	min_avg1 = optSearchTree(N1, tree_prob1, root_of1);
	printf("예제 3.7의 최소 평균 검색시간 : %f\n", min_avg1);
	min_avg2 = optSearchTree(N2, tree_prob2, root_of2);
	printf("예제 3.8의 최소 평균 검색시간 : %f\n", min_avg2);
	min_avg3 = optSearchTree(N3, tree_prob3, root_of3);
	printf("예제 3.9의 최소 평균 검색시간 : %f\n", min_avg3);

}

double optSearchTree(int num, double* prob, int** root) {
	double min_avg;
	return min_avg = minAvgTime(1, num, prob, root);
}

double minAvgTime(int i, int j, double* prob, int** root) {
	double min_avg, temp_min_avg;
	double sigma = 0;
	if (j == i - 1)
		return 0;
	if (i == j)
		return prob[i];
	for (int m = i; m <= j; m++) {
		sigma += prob[m];
	}
	min_avg = minAvgTime(i, i - 1, prob, root) + minAvgTime(i + 1, j, prob, root) + sigma;
	root[i][j] = i;
	for (int k = i; k <= j; k++) {
		temp_min_avg = minAvgTime(i, k - 1, prob, root) + minAvgTime(k + 1, j, prob, root) + sigma;
		if (min_avg > temp_min_avg) {
			min_avg = temp_min_avg;
			root[i][j] = k;
		}
	}
	return min_avg;
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