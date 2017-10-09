#include<stdio.h>
#include<malloc.h>

#define ARR_SIZE 11

void mergeSort(int arr[], int num); 
/* arr�� �̹� ���� 1�� �������� ���ҵ� �迭�� ���� �պ����� ����(���Ұ��� ����) */
void mergeUnit(int arr[], int num, int unit); 
/* unit�� ������ arr�� ������ 2�� �������� ����� merge() �Լ� ȣ���Ͽ� arr ���� */
void merge(int arr[], int res_arr[], int l_first_idx, int l_last_idx, int r_last_idx); 
/* arr�� left/right �� �κ����� ���� 2���� �迭�� ���� merge�ϸ鼭 �����Ͽ� res_arr�� ���� */
void arrayCopy(const int src[], int dst[], int size); // �迭�� src���� dst�� ����

int ex_arr[ARR_SIZE] = { 3,4,11,1,2,9,7,10,8,6,5 };

void main() {
	printf("���� �� : ");
	for (int i = 0; i < ARR_SIZE; i++) {
		printf("%d ", ex_arr[i]);
	}
	printf("\n\n");

	mergeSort(ex_arr, ARR_SIZE);

	printf("���� �� : ");
	for (int i = 0; i < ARR_SIZE; i++) {
		printf("%d ", ex_arr[i]);
	}
	printf("\n\n");
}

void mergeSort(int arr[], int num) {
	int unit = 1;

	while (unit < num) {
		mergeUnit(arr, num, unit);
		unit *= 2;
	}
}

void mergeUnit(int arr[], int num, int unit) {
	int i = 0, j;
	int* tmp_arr;
	tmp_arr = (int*)calloc(num, sizeof(int));


	for (; i + 2 * unit - 1 < num; i += (2 * unit)) {
		merge(arr, tmp_arr, i, i + unit - 1, i + 2 * unit - 1);
	}

	if (i + unit - 1 < num - 1) {
		merge(arr, tmp_arr, i, i + unit - 1, num - 1);
	}
	else {
		for (j = i; j < num; j++)
			tmp_arr[j] = arr[j];
	}

	arrayCopy(tmp_arr, arr, num);
	
	free(tmp_arr);
}

void merge(int arr[], int res_arr[], int l_first_idx, int l_last_idx, int r_last_idx) {
	int i = l_first_idx;
	int j = l_last_idx + 1; // r_first_index
	int k = i;

	while (i <= l_last_idx && j <= r_last_idx) {
		if (arr[i] <= arr[j])
			res_arr[k++] = arr[i++];
		else
			res_arr[k++] = arr[j++];
	}

	if (i > l_last_idx) {
		while (j <= r_last_idx)
			res_arr[k++] = arr[j++];
	}
	else {
		while (i <= l_last_idx)
			res_arr[k++] = arr[i++];
	}
}

void arrayCopy(const int src[], int dst[], int size) {
	for (int i = 0; i < size; i++) {
		dst[i] = src[i];
	}
}