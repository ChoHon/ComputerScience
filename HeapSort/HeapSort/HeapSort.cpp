#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 100000

typedef int element;

typedef struct heaptype {
	element heap[LEN];
	int size;
} heaptype;

void init(heaptype *h) {
	h->size = 0;
}

void insert_max_heap(heaptype *h, element data) {
	int tmp_size;
	tmp_size = ++(h->size);

	while ((tmp_size != 1) && (data > h->heap[tmp_size / 2])) {
		h->heap[tmp_size] = h->heap[tmp_size / 2];
		tmp_size /= 2;
	}

	h->heap[tmp_size] = data;
}

element delete_max_heap(heaptype *h) {
	int parent, child;
	element root, tmp;

	root = h->heap[1];
	tmp = h->heap[(h->size)--];
	parent = 1;
	child = 2;

	while (child <= h->size) {
		if ((child < h->size) && (h->heap[child] < h->heap[child + 1])) child++;
		if (tmp >= h->heap[child]) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = tmp;
	return root;
}

void heap_sort(element a[], int n) {
	heaptype h;
	init(&h);

	for (int i = 0; i < n; i++) insert_max_heap(&h, a[i]);
	for (int i = (n - 1); i >= 0; i--) a[i] = delete_max_heap(&h);
}

void Check_Sort(int array[], int len) {
	for (int i = 0; i < len - 1; i++) {
		if (array[i] > array[i + 1]) {
			printf("정렬이 잘못되었습니다.\n");
			return;
		}
	}
	printf("정렬되어 있습니다.\n");
	return;
}


int main(void) {
	int array[LEN];
	srand((int)time(NULL));
	for (int i = 0; i < LEN; i++) array[i] = rand() % LEN + 1;
	clock_t start, end;

	start = clock();
	heap_sort(array, 100000);
	end = clock();

	Check_Sort(array, LEN);
	printf("걸린 시간: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	return 0;
}