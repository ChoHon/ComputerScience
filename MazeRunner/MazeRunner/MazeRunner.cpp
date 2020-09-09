#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 10

typedef struct {
	short r;
	short c;
} element;

element here = { 1, 0 }, entry = { 1, 0 };

typedef struct StackType {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType *s) {
	s->top = -1;
}

int is_empty(StackType *s) {
	return (s->top == -1);
}

int is_full(StackType *s) {
	return (s->top == MAX_STACK_SIZE - 1);
}

void push(StackType *s, element data) {
	if (is_full(s)) {
		printf("stack is full\n");
		return;
	}
	else s->stack[++(s->top)] = data;
}

element pop(StackType *s) {
	if (is_empty(s)) {
		printf("stack is empty\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}

element peek(StackType *s) {
	if (is_empty(s)) {
		printf("stack is empty");
		exit(1);
	}
	else return s->stack[s->top];
}

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'e', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1', '0', 'x'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

void pushLoc(StackType *s, int r, int c) {
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

void main(void) {
	int r, c;
	StackType s;

	init_stack(&s);
	here = entry;
	
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		pushLoc(&s, r - 1, c);
		pushLoc(&s, r + 1, c);
		pushLoc(&s, r, c - 1);
		pushLoc(&s, r, c + 1);
		
		if (is_empty(&s)) {
			printf("탈출 실패\n");
			return;
		}
		else {
			here = pop(&s);
			printf("{ %d %d }\n", here.r, here.c);
		}
	}
	printf("탈출 성공\n");

	return;
}