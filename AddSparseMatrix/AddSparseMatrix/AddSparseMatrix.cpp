#include <stdio.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 6
#define MAX_TERMS ROWS*COLS+1

typedef struct {
	int row;
	int col;
	int value;
} element;	// 각 원소 정보 : 행 위치, 열 위치, 값

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;
	int cols;
	int terms;
} SparseMatrix;	// 각 원소 정보 배열, 전체 행 크기, 전체 열 크기, 원소 수

SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b) {
	SparseMatrix c;

	int ca = 0, cb = 0, cc = 0;	// a.data, b.data, c.data의 인덱스

	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;	// 행렬 c 초기화

	if (a.rows != b.rows || a.cols != b.cols) {	// 행렬 a와 b의 크기가 같지 않을 때
		fprintf(stderr, "희소행렬 크기 에러\n\n");
		exit(1);
	}

	while (ca < a.terms && cb < b.terms) {
		// 행 우선순위로 a.data[ca], b.data[cb] 원소의 인덱스 배정
		int inda = a.data[ca].row * a.cols + a.data[ca].col; 
		int indb = b.data[cb].row * b.cols + b.data[cb].col;

		if (inda > indb) {	// b.data[cb]의 원소가 더 앞에 있을 때
			c.data[cc++] = b.data[cb++];	// b.data[cb]을 그대로 c.data[cc]에 대입 후 cb, cc 증가
		}
		else if (inda == indb) {	// a.data[ca], b.data[cb]의 원소가 같은 위치에 있을 때
			if (a.data[ca].value + b.data[cb].value != 0) {	// 두 값을 더했을 때 0이 아닐 때
				c.data[cc].row = a.data[ca].row;
				c.data[cc].col = a.data[ca].col;
				c.data[cc++].value = a.data[ca].value + b.data[cb].value;	
				// c.data[cc]에 행, 열 정보는 그대로 대입하고 value에는 더한 값을 대입 후 cc 증가
			}
			ca++; cb++;	// a.data[ca].value + b.data[cb].value가 0이든 아니든 상관없이 ca, cb 증가
		}
		else {	// a.data[ca]의 원소가 더 앞에 있을 때
			c.data[cc++] = a.data[ca++]; // a.data[ca]을 그대로 c.data[cc]에 대입 후 ca, cc 증가
		}
	}

	for (; ca < a.terms;) c.data[cc++] = a.data[ca++];
	for (; cb < b.terms;) c.data[cc++] = b.data[cb++];
	// 한쪽 행렬의 정보가 모두 계산되었을 때, 다른 행렬의 나머지 값을 그냥 행렬 c로 옮김
	
	c.terms = cc;	// 행렬 c의 항목 수 결정
	return c;
}

void print_sparsematrix(SparseMatrix a) {
	int idx = 0;	// 입력 받은 a.data의 인덱스
	
	for (int i = 0; i < a.rows; i++) {	// 행 우선이므로 행 for문부터
		for (int j = 0; j < a.cols; j++) {	// 열 for문
			if (a.data[idx].row == i && a.data[idx].col == j) {	// a.data[idx]의 (row, col)이 (i, j)와 같을 때
				printf("%3d", a.data[idx++].value);	// value를 출력, 이후에 idx 증가
			}
			else printf("%3d", 0);	// 그 외 (i, j)에는 0 출력
		}
		printf("\n");	// 행 바꿈
	}
	printf("\n");

	return;
}


int main(void) {
	SparseMatrix m1 = { {{0, 0, 1}, {1, 1, 1}, {2, 1, 1}, {3, 2, 1}, {4, 3, 1}, {5, 1, 2}, {5, 3, -1}}, 6, 6, 7 };
	SparseMatrix m2 = { {{0, 0, 1}, {1, 0, 1}, {2, 1, 1}, {3, 2, 1}, {4, 0, 1}, {5, 0, 1}}, 6, 6, 6 };
	SparseMatrix m3;

	m3 = sparse_matrix_add2(m1, m2);

	print_sparsematrix(m1);
	print_sparsematrix(m2);
	print_sparsematrix(m3);

	return 0;
}
