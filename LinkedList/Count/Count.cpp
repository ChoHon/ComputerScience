#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
	element data;
	struct ListNode *link;
} ListNode;

void display(ListNode *list) {
	ListNode *node = list;
	printf("( ");
	for (; node != NULL; node = node->link) printf("%d ", node->data);
	printf(" )");
}

int count_node(ListNode *list, element data) {
	int count = 0;
	ListNode *p = list;

	for (; p != NULL; p = p->link) {
		if (p->data == data) count++;
	}

	return count;
}

int main(void) {
	ListNode *pa1, *pa2, *pa3;
	pa1 = (ListNode *)malloc(sizeof(ListNode));
	pa1->data = 10;
	pa1->link = NULL;

	pa2 = (ListNode *)malloc(sizeof(ListNode));
	pa2->data = 20;
	pa2->link = NULL;
	pa1->link = pa2;

	pa3 = (ListNode *)malloc(sizeof(ListNode));
	pa3->data = 30;
	pa3->link = NULL;
	pa2->link = pa3;

	ListNode *pb1, *pb2, *pb3;
	pb1 = (ListNode *)malloc(sizeof(ListNode));
	pb1->data = 40;
	pb1->link = NULL;

	pb2 = (ListNode *)malloc(sizeof(ListNode));
	pb2->data = 50;
	pb1->link = pb2;

	pb3 = (ListNode *)malloc(sizeof(ListNode));
	pb3->data = 60;
	pb3->link = NULL;
	pb2->link = pb3;

	printf("%d\n", count_node(pa1, 40));

	return 0;
}