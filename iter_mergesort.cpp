#include<stdio.h>
#include<malloc.h>

#define ARR_SIZE 11

void mergeSort(int arr[], int num); 
/* arr을 이미 원소 1개 단위까지 분할된 배열로 보고 합병정렬 수행(분할과정 생략) */
void mergeUnit(int arr[], int num, int unit); 
/* unit개 단위로 arr을 나누고 2개 단위씩을 묶어가며 merge() 함수 호출하여 arr 정렬 */
void merge(int arr[], int res_arr[], int l_first_idx, int l_last_idx, int r_last_idx); 
/* arr을 left/right 두 부분으로 나눠 2개의 배열로 보고 merge하면서 정렬하여 res_arr에 저장 */
void arrayCopy(const int src[], int dst[], int size); // 배열을 src에서 dst로 복사

int ex_arr[ARR_SIZE] = { 3,4,11,1,2,9,7,10,8,6,5 };

void main() {
	printf("정렬 전 : ");
	for (int i = 0; i < ARR_SIZE; i++) {
		printf("%d ", ex_arr[i]);
	}
	printf("\n\n");

	mergeSort(ex_arr, ARR_SIZE);

	printf("정렬 후 : ");
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