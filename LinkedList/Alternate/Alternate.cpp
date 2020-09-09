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

ListNode* make_node(element data) {
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->data = data;
	p->link = NULL;

	return p;
}

ListNode* link_node(ListNode *node, ListNode *pre_node) {
	pre_node->link = node;
	pre_node = node;

	return pre_node;
}

ListNode* alternate(ListNode *head_A, ListNode *head_B) {
	ListNode *head_C = NULL;
	ListNode *p_A = head_A;
	ListNode *p_B = head_B;
	ListNode *p_C = NULL;
	ListNode *p_tmp = make_node(0); // 전 노드의 link 변경을 위한 임시 노드

	while ((p_A != NULL) && (p_B != NULL)) {
		p_C = make_node(p_A->data);
		p_tmp = link_node(p_C, p_tmp);
		if (head_C == NULL) head_C = p_C;		// 첫 노드일 때		

		p_C = make_node(p_B->data);
		p_tmp = link_node(p_C, p_tmp);

		p_A = p_A->link;
		p_B = p_B->link;
	}

	for (; p_A != NULL; p_A = p_A->link) {
		p_C = make_node(p_A->data);
		p_tmp = link_node(p_C, p_tmp);
	}
	for (; p_B != NULL; p_B = p_B->link) {
		p_C = make_node(p_B->data);
		p_tmp = link_node(p_C, p_tmp);
	}

	return head_C;
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
		
	display(alternate(pa1, pb1));

	return 0;
}