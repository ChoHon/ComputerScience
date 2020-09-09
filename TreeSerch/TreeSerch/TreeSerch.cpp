#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct TreeNode{
	element data;
	struct TreeNode *left, *right;
} TreeNode;

typedef struct QueueType {
	TreeNode *queue[100];
	int front, rear;
}QueueType;

void init_queue(QueueType *q) {
	q->front = q->rear = 0;
}

int is_empty_queue(QueueType *q) {
	return (q->front == q->rear);
}

int is_full_queue(QueueType *q) {
	return ((q->rear + 1) % 100 == q->front);
}

void enqueue(QueueType *q, TreeNode *t) {
	if (is_full_queue(q)) {
		printf("Queue is full\n");
		exit(1);
	}
	q->rear = (q->rear + 1) % 100;
	q->queue[(q->rear)] = t;
}

TreeNode* dequeue(QueueType *q) {
	if (is_empty_queue(q)) {
		printf("Queue is empty\n");
		exit(1);
	}
	q->front = (q->front + 1) % 100;
	return q->queue[q->front];
}

// 너비 우선 탐색
void level_order(TreeNode *t) {
	QueueType q;
	init_queue(&q);

	if (t == NULL) return;
	enqueue(&q, t);
	while (!is_empty_queue(&q)) {
		t = dequeue(&q);
		printf("%d ", t->data);
		if (t->left) enqueue(&q, t->left);
		if (t->right) enqueue(&q, t->right);
	}
}

int find_max(TreeNode *t) {
	QueueType q;
	int max = t->data;
	init_queue(&q);

	if (t == NULL) exit(1);
	enqueue(&q, t);
	while (!is_empty_queue(&q)) {
		t = dequeue(&q);
		if (t->data > max) max = t->data;
		if (t->left) enqueue(&q, t->left);
		if (t->right) enqueue(&q, t->right);
	}
	return max;
}

int find_min(TreeNode *t) {
	QueueType q;
	int min = t->data;
	init_queue(&q);

	if (t == NULL) exit(1);
	enqueue(&q, t);
	while (!is_empty_queue(&q)) {
		t = dequeue(&q);
		if (t->data < min) min = t->data;
		if (t->left) enqueue(&q, t->left);
		if (t->right) enqueue(&q, t->right);
	}
	return min;
}


int main(void) {
	TreeNode *n1, *n2, *n3, *n4, *n5, *n6;
	int a = NULL;

	n1 = (TreeNode *)malloc(sizeof(TreeNode));
	n2 = (TreeNode *)malloc(sizeof(TreeNode));
	n3 = (TreeNode *)malloc(sizeof(TreeNode));
	n4 = (TreeNode *)malloc(sizeof(TreeNode));
	n5 = (TreeNode *)malloc(sizeof(TreeNode));
	n6 = (TreeNode *)malloc(sizeof(TreeNode));

	n1->data = 20;
	n1->left = n2;
	n1->right = n3;

	n2->data = 60;
	n2->left = n4;
	n2->right = NULL;

	n3->data = 100;
	n3->left = NULL;
	n3->right = n5;

	n4->data = -100;
	n4->left = NULL;
	n4->right = NULL;

	n5->data = 200;
	n5->left = n6;
	n5->right = NULL;

	n6->data = 40;
	n6->left = NULL;
	n6->right = NULL;

	printf("MAX : %d\n", find_max(n1));
	printf("MIN : %d\n", find_min(n1));
	printf("Level Order : ");
	level_order(n1);

	return 0;
}