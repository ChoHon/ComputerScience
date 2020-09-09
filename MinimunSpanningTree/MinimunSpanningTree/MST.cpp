#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
#define MAX_VERTICES 50
#define MAX_VERTICES_2 7
#define TRUE 1
#define FALSE 0
#define INF 999

int parent[MAX_VERTICES];
int num[MAX_VERTICES];

int weight[MAX_VERTICES_2][MAX_VERTICES_2] = {
	{0, 29, INF, INF, INF, 10, INF},
	{29, 0, 16, INF, INF, INF, 15},
	{INF, 16, 0, 12, INF, INF, INF},
	{INF, INF, 12, 0, 22, INF, 18},
	{INF, INF, INF, 22, 0, 27, 25},
	{10, INF, INF, INF, 27, 0, INF},
	{INF, 15, INF, 18, 25, INF, 0}
};
int selected[MAX_VERTICES_2];
int dist[MAX_VERTICES_2];

typedef struct {
	int key;
	int u;
	int v;
} element;

typedef struct HeapType {
	element heap[MAX_VERTICES];
	int heap_size;
} HeapType;

void init(HeapType *h) {
	h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item) {
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType *h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && ((h->heap[child].key) > h->heap[child + 1].key)) child++;

		if (temp.key <= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	return item;
}

void insert_heap_edge(HeapType *h, int u, int v, int weight) {
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(h, e);
}

void insert_all_edges(HeapType *h) {
	insert_heap_edge(h, 0, 1, 29);
	insert_heap_edge(h, 1, 2, 16);
	insert_heap_edge(h, 2, 3, 12);
	insert_heap_edge(h, 3, 4, 22);
	insert_heap_edge(h, 4, 5, 27);
	insert_heap_edge(h, 5, 0, 10);
	insert_heap_edge(h, 6, 1, 15);
	insert_heap_edge(h, 6, 3, 18);
	insert_heap_edge(h, 6, 4, 25);
}

void set_init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
		num[i] = 1;
	}
}

int set_find(int vertex) {
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p);
	s = i;
	for (i = vertex; (p = parent[i]) >= 0; i = p) parent[i] = s;
	return s;
}

void set_union(int s1, int s2) {
	if (num[s1] < num[s2]) {
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

void kruskal(int n) {
	int edge_accepted = 0;
	HeapType h;
	int uset, vset;
	element e;
	init(&h);
	insert_all_edges(&h);
	set_init(n);
	while (edge_accepted < (n - 1)) {
		e = delete_min_heap(&h);
		uset = set_find(e.u);
		vset = set_find(e.v);
		if (uset != vset) {
			printf("(%d, %d) %d\n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset);
		}
	}
	
}

int get_min_vertex(int n) {
	int v = 0;
	for (int i = 0; i < n; i++) {
		if (!selected[i]) {
			v = i;
			break;
		}
	}

	for (int i = 0; i < n; i++) {
		if (!selected[i] && (dist[i] < dist[v])) v = i;
	}

	return (v);
}

void prim(int s, int n) {
	int i, u, v;
	for (u = 0; u < n; u++) {
		dist[u] = INF;
		selected[u] = FALSE;
	}
	dist[s] = 0;
	for (i = 0; i < n; i++) {
		u = get_min_vertex(n);
		selected[u] = TRUE;
		if (dist[u] == INF) return;
		printf("%d ", u);
		for (v = 0; v < n; v++) 
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < dist[v])
					dist[v] = weight[u][v];
		
	}
}


int main(void) {


	return 0;
}