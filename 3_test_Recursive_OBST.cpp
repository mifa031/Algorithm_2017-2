#include <stdio.h>
#include <stdlib.h>

long long unit = 0; // 단위연산이 시행된 횟수를 저장하는 전역변수


#define TEST_N 30 // 0~100개 key에 대한 성능을 측정하기 위한 test용 변수
double tree_prob[TEST_N + 1] = { 0 };

typedef struct node* nodePointer;
typedef struct node {
	char* key;
	nodePointer leftChild;
	nodePointer rightChild;
} node;

double optSearchTree(int num, double* prob, int** root);  // 최적 이분검색트리 생성을 위한 정보를 제공하는 함수
double minAvgTime(int i, int j, double* prob, int** root);  // 재귀 함수로써, i~j의 index를 가진 key 집합의 최소 평균 검색시간과 root 배열을 return
nodePointer makeTree(int i, int j, char** tree_key, int** root); // tree_key와 root 배열로 tree를 만드는 함수

void main() {
	for (int i = 0; i <= TEST_N; i++) {
		double min_avg;
		int** root_of;
		root_of = (int**)calloc((i + 2), sizeof(int*));
		for (int j = 0; j < i + 2; j++) {
			root_of[j] = (int*)calloc((i + 1), sizeof(int));
		}

		min_avg = optSearchTree(i, tree_prob, root_of);
		//printf("%d : ", i);
		printf("%lld\n", unit);
	}
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
		unit += 1; // 단위연산 시행횟수 측정
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