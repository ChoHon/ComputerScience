#include <stdio.h>
#define MAX_VERTICES 8
#define INF 999

int weight[MAX_VERTICES][MAX_VERTICES] = {
	{0, 9, INF, INF, INF, 14, 15, INF},
	{INF, 0, 24, INF, INF, INF, INF, INF},
	{INF, INF, 0, INF, 2, INF, INF, 19},
	{INF, INF, 6, 0, INF, INF, INF, 6},
	{INF, INF, INF, 11, 0, INF, INF, 16},
	{INF, INF, 18, INF, 30, 0, 5, INF},
	{INF, INF, INF, INF, 20, INF, 0, 44},
	{INF, INF, INF, INF, INF, INF, INF, 0}
};
char vertices_name[] = { 's', '2', '3', '4', '5', '6', '7', 't' };
int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int len, int found[]) {
	int min_idx = 0;
	int min = INF;
	for (int i = 1; i < len; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			min_idx = i;
		}
	}

	return min_idx;
}

int min_of_two(int a, int b) {
	if (a < b) return a;
	else return b;
}

void shortest_path(int start_idx, int len) {
	int idx;

	for (int i = 0; i < len; i++) {
		distance[i] = weight[start_idx][i];
		found[i] = 0;
	}
	found[start_idx] = 1;

	for (int i = 0; i < len - 1; i++) {
		idx = choose(distance, len, found);
		found[idx] = 1;
		for (int j = 0; j < len; j++)
			if (!found[j])
				distance[j] = min_of_two(distance[j], distance[idx] + weight[idx][j]);
		
	}
}

int main(void) {
	shortest_path(0, MAX_VERTICES);	

	for (int i = 0; i < MAX_VERTICES; i++) printf("s -> %c :%3d\n", vertices_name[i], distance[i]);
	return 0;
}