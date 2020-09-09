#include "balance.h"
#include <iostream>
using namespace std;
/*
0 : A
1 : B
2 : C
3 : AB
4 : BC
5 : AC
6 : ABC
*/

typedef struct Pair {
	int coins[2];
} Pair;

typedef struct Six{
	Pair A;
	Pair B;
	Pair C;
	int ret;
	int state;
} Six;

/*
state
-1 마지막
0 pair 3개가 같지 않음
1 pair 3개가 같음
2 pair 3개가 같음 + 55 아님
3 pair 3개가 같음 + 77 아님
4 pair 3개가 같음 + 75
5 pair 9개가 같음
*/

int scale_a[101], scale_b[101], scale_c[101];
int nomal[101]; int fault[101]; int not_known[101];

void add_coin(int scale[], int coin_idx) {
	for (int i = 0; i < NUMBER; i++) {
		if (scale[i] == coin_idx) return;
		else if (scale[i] == -1) {
			scale[i] = coin_idx;
			scale[i + 1] = -1;
			return;
		}
	}
}

int caculate_len(int scale[]) {
	int len = 0;
	for (int i = 0; scale[i] != -1; i++) len++;
	return len;
}

void empty_scale(int a[]) {
	a[0] = -1;
}

void empty_all() {
	empty_scale(scale_a); empty_scale(scale_b); empty_scale(scale_c);
}

void resulting_one_coin_balance(int ret) {
	if (ret == 0) {
		add_coin(nomal, scale_a[0]);
		add_coin(fault, scale_b[0]);
		add_coin(fault, scale_c[0]);
	}
	else if (ret == 1) {
		add_coin(nomal, scale_b[0]);
		add_coin(fault, scale_a[0]);
		add_coin(fault, scale_c[0]);
	}
	else if (ret == 2) {
		add_coin(nomal, scale_c[0]);
		add_coin(fault, scale_a[0]);
		add_coin(fault, scale_b[0]);
	}
	else if (ret == 3) {
		add_coin(nomal, scale_a[0]);
		add_coin(nomal, scale_b[0]);
		add_coin(fault, scale_c[0]);
	}
	else if (ret == 4) {
		add_coin(nomal, scale_b[0]);
		add_coin(nomal, scale_c[0]);
		add_coin(fault, scale_a[0]);
	}
	else if (ret == 5) {
		add_coin(nomal, scale_a[0]);
		add_coin(nomal, scale_c[0]);
		add_coin(fault, scale_b[0]);
	}
	else if (ret == 6) {
		add_coin(not_known, scale_a[0]);
		add_coin(not_known, scale_b[0]);
		add_coin(not_known, scale_c[0]);
	}
	else return;
}

void solution_1() {
	int ret;
	empty_all(); empty_scale(nomal); empty_scale(fault); empty_scale(not_known);
	
	for (int i = 0; i < 99; i = i + 3) {
		add_coin(scale_a, i); add_coin(scale_b, i + 1), add_coin(scale_c, i + 2);
		ret = balance(scale_a, scale_b, scale_c);
		resulting_one_coin_balance(ret);
		empty_all();
	}

	
	int len = caculate_len(not_known);
	add_coin(scale_a, nomal[0]);


	int remain = 0;
	if (len % 6 != 0) {
		len = len - 3;
		remain = 1;
	}


	for (int i = 0; i < len; i = i + 6) {
		add_coin(scale_b, not_known[i]); add_coin(scale_c, not_known[(i + 3)]);
		ret = balance(scale_a, scale_b, scale_c);

		if (ret == 0) {
			for (int i = 0; i < 3; i++)	add_coin(fault, scale_b[0] + i);
			for (int i = 0; i < 3; i++)	add_coin(fault, scale_c[0] + i);
		}
		else if (ret == 3) {
			for (int i = 0; i < 3; i++) add_coin(nomal, scale_b[0] + i);
			for (int i = 0; i < 3; i++) add_coin(fault, scale_c[0] + i);
		}
		else if (ret == 5) {
			for (int i = 0; i < 3; i++) add_coin(nomal, scale_c[0] + i);
			for (int i = 0; i < 3; i++) add_coin(fault, scale_b[0] + i);
		}
		else if (ret == 6) {
			for (int i = 0; i < 3; i++)	add_coin(nomal, scale_b[0] + i);
			for (int i = 0; i < 3; i++)	add_coin(nomal, scale_b[0] + i);
		}

		empty_scale(scale_b); empty_scale(scale_c);
	}


	if (remain == 1) {
		add_coin(scale_b, nomal[1]); add_coin(scale_c, not_known[len]);
		ret = balance(scale_a, scale_b, scale_c);

		if (ret == 3)
			for (int i = 0; i < 3; i++) add_coin(fault, scale_c[0] + i);
		else if (ret == 6)
			for (int i = 0; i < 3; i++)	add_coin(nomal, scale_c[0] + i);

		empty_scale(scale_b); empty_scale(scale_c);
	}


	add_coin(scale_b, nomal[1]); add_coin(scale_c, 99);
	ret = balance(scale_a, scale_b, scale_c);
	if (ret == 3) add_coin(fault, scale_c[0]);
	else if (ret == 6) add_coin(nomal, scale_c[0]);
	empty_scale(scale_b); empty_scale(scale_c);


	for (int i = 0; fault[i] != -1; i++) printf("%d ", fault[i]);
	printf("\n");

	balance(fault, scale_b, scale_c);
}

void initial_pair(Pair* pair) {
	int idx = 0;
	for (int i = 0; i < 120; i = i + 2) {
		pair[idx].coins[0] = i;
		pair[idx++].coins[1] = i + 1;
	}
}

void initial_six(Six* six, Pair* pair) {
	int idx = 0;
	for (int i = 0; i < 17; i++) {
		six[i].A = pair[idx++];
		six[i].B = pair[idx++];
		six[i].C = pair[idx++];
		six[i].ret = 0; six[i].state = -1;
	}
}

void add_pair(int scale[], Pair pair) {
	add_coin(scale, pair.coins[0]);
	add_coin(scale, pair.coins[1]);
}

void add_nomal_fault(Pair pair, int i) {
	add_coin(nomal, pair.coins[i]);
	add_coin(fault, pair.coins[1 - i]);
}

void add_six(int scale[], Six six) {
	add_pair(scale, six.A);
	add_pair(scale, six.B);
	add_pair(scale, six.C);
}

void resulting_equal_six_balance(Six* equal_six, int i, int ret) {
	if (ret == 0) {
		equal_six[i].state = 2;
		equal_six[i + 1].state = 3;
		equal_six[i + 2].state = 3;
		
	}
	else if (ret == 1) {
		equal_six[i].state = 3;
		equal_six[i + 1].state = 2;
		equal_six[i + 2].state = 3;
	}
	else if (ret == 2) {
		equal_six[i].state = 3;
		equal_six[i + 1].state = 3;
		equal_six[i + 2].state = 2;
	}
	else if (ret == 3) {
		equal_six[i].state = 2;
		equal_six[i + 1].state = 2;
		equal_six[i + 2].state = 3;
	}
	else if (ret == 4) {
		equal_six[i].state = 3;
		equal_six[i + 1].state = 2;
		equal_six[i + 2].state = 2;
	}
	else if (ret == 5) {
		equal_six[i].state = 2;
		equal_six[i + 1].state = 3;
		equal_six[i + 2].state = 2;
	}
	else if (ret == 6) {
		equal_six[i].state = 5;
		equal_six[i + 1].state = 5;
		equal_six[i + 2].state = 5;
	}
	else return;
}

void resulting_heavy_six_balance(Six* heavy_six, int i, int ret) {
	if (ret == 0) {
		add_six(nomal, heavy_six[i]);
		heavy_six[i + 1].state = 4;
		heavy_six[i + 2].state = 4;
	}
	else if (ret == 1) {
		add_six(nomal, heavy_six[i+1]);
		heavy_six[i].state = 4;
		heavy_six[i + 2].state = 4;
	}
	else if (ret == 2) {
		add_six(nomal, heavy_six[i+2]);
		heavy_six[i + 1].state = 4;
		heavy_six[i].state = 4;
	}
	else if (ret == 3) {
		add_six(nomal, heavy_six[i]);
		add_six(nomal, heavy_six[i+1]);
		heavy_six[i + 2].state = 4;
	}
	else if (ret == 4) {
		add_six(nomal, heavy_six[i + 2]);
		add_six(nomal, heavy_six[i + 1]);
		heavy_six[i].state = 4;
	}
	else if (ret == 5) {
		add_six(nomal, heavy_six[i]);
		add_six(nomal, heavy_six[i + 2]);
		heavy_six[i + 1].state = 4;
	}
	else if (ret == 6) {
		heavy_six[i].state = 5;
		heavy_six[i + 1].state = 5;
		heavy_six[i + 2].state = 5;
	}
	else return;
}

void resulting_light_six_balance(Six* light_six, int i, int ret) {
	if (ret == 0) {
		light_six[i].state = 4;
		add_six(fault, light_six[i + 1]);
		add_six(fault, light_six[i + 2]);
	}
	else if (ret == 1) {
		light_six[i + 1].state = 4;
		add_six(fault, light_six[i]);
		add_six(fault, light_six[i + 2]);
	}
	else if (ret == 2) {
		light_six[i + 2].state = 4;
		add_six(fault, light_six[i + 1]);
		add_six(fault, light_six[i]);
	}
	else if (ret == 3) {
		light_six[i].state = 4;
		light_six[i + 1].state = 4;
		add_six(fault, light_six[i + 2]);
	}
	else if (ret == 4) {
		light_six[i + 2].state = 4;
		light_six[i + 1].state = 4;
		add_six(fault, light_six[i]);
	}
	else if (ret == 5) {
		light_six[i].state = 4;
		light_six[i + 2].state = 4;
		add_six(fault, light_six[i + 1]);
	}
	else if (ret == 6) {
		light_six[i].state = 5;
		light_six[i + 1].state = 5;
		light_six[i + 2].state = 5;
	}
	else return;
}

void resulting_sf_six_balance(Six* sf_six, int i, int ret) {
	if (ret == 0) {
		add_nomal_fault(sf_six[i].A, 0);
		add_nomal_fault(sf_six[i].B, 1);
		add_nomal_fault(sf_six[i].C, 1);
	}
	else if (ret == 1) {
		add_nomal_fault(sf_six[i].A, 1);
		add_nomal_fault(sf_six[i].B, 0);
		add_nomal_fault(sf_six[i].C, 1);
	}
	else if (ret == 2) {
		add_nomal_fault(sf_six[i].A, 1);
		add_nomal_fault(sf_six[i].B, 1);
		add_nomal_fault(sf_six[i].C, 0);
	}
	else if (ret == 3) {
		add_nomal_fault(sf_six[i].A, 0);
		add_nomal_fault(sf_six[i].B, 0);
		add_nomal_fault(sf_six[i].C, 1);
	}
	else if (ret == 4) {
		add_nomal_fault(sf_six[i].A, 1);
		add_nomal_fault(sf_six[i].B, 0);
		add_nomal_fault(sf_six[i].C, 0);
	}
	else if (ret == 5) {
		add_nomal_fault(sf_six[i].A, 0);
		add_nomal_fault(sf_six[i].B, 1);
		add_nomal_fault(sf_six[i].C, 0);
	}
	else if (ret == 6) {
		add_nomal_fault(sf_six[i].A, 0);
		add_nomal_fault(sf_six[i].B, 0);
		add_nomal_fault(sf_six[i].C, 0);
	}
	else return;
}

void solution_2() {
	int ret;
	int idx_equal = 0;
	int idx_not_equal = 0;
	empty_all(); empty_scale(nomal); empty_scale(fault); empty_scale(not_known);

	Pair pair[60];
	Six six[17];
	Six equal_six[17]; Six not_equal_six[17];
	Six heavy_six[17]; Six light_six[17]; Six equal_three_six[17];
	Six sf_six[17];

	initial_pair(pair); initial_six(six, pair);
	initial_six(equal_six, pair); initial_six(not_equal_six, pair);
	initial_six(heavy_six, pair); initial_six(light_six, pair); initial_six(equal_three_six, pair);
	initial_six(sf_six, pair);

	for (int i = 0; i < 16; i++) {
		add_pair(scale_a, six[i].A);
		add_pair(scale_b, six[i].B);
		add_pair(scale_c, six[i].C);

		six[i].ret = balance(scale_a, scale_b, scale_c);


		if (six[i].ret == 6) {
			six[i].state = 1;
			equal_six[idx_equal++] = six[i];
		}
		else {
			six[i].state = 0;
			not_equal_six[idx_not_equal++] = six[i];
		}

		empty_all();
	}

	for (int i = 0; equal_six[i].state != -1; i = i + 3) {
		add_six(scale_a, equal_six[i]);

		if (equal_six[i + 1].state == -1) add_six(scale_b, equal_six[1]);
		else add_six(scale_b, equal_six[i + 1]);

		if (equal_six[i + 2].state == -1) add_six(scale_c, equal_six[0]);
		else add_six(scale_c, equal_six[i + 2]);

		ret = balance(scale_a, scale_b, scale_c);
		resulting_equal_six_balance(equal_six, i, ret);

		empty_all();
	}

	int h_idx = 0; int l_idx = 0; int th_idx = 0;
	for (int i = 0; equal_six[i].state != -1; i++) {
		if (equal_six[i].state == 2) heavy_six[h_idx++] = equal_six[i];
		else if (equal_six[i].state == 3) light_six[l_idx++] = equal_six[i];
		else if (equal_six[i].state == 5) equal_three_six[th_idx++] = equal_six[i];
	}

	for (int i = 0; heavy_six[i].state != -1; i = i + 3) {
		add_six(scale_a, heavy_six[i]);

		if (heavy_six[i + 1].state == -1) add_six(scale_b, heavy_six[1]);
		else add_six(scale_b, heavy_six[i + 1]);

		if (heavy_six[i + 2].state == -1) add_six(scale_c, heavy_six[0]);
		else add_six(scale_c, heavy_six[i + 2]);

		ret = balance(scale_a, scale_b, scale_c);
		resulting_heavy_six_balance(heavy_six, i, ret);

		empty_all();
	}

	for (int i = 0; light_six[i].state != -1; i = i + 3) {
		add_six(scale_a, light_six[i]);

		if (light_six[i + 1].state == -1) add_six(scale_b, light_six[1]);
		else add_six(scale_b, light_six[i + 1]);

		if (light_six[i + 2].state == -1) add_six(scale_c, light_six[0]);
		else add_six(scale_c, light_six[i + 2]);

		ret = balance(scale_a, scale_b, scale_c);
		resulting_light_six_balance(light_six, i, ret);

		empty_all();
	}

	int sf_idx = 0;
	for (int i = 0; heavy_six[i].state != -1; i++) {
		if (heavy_six[i].state == 4) sf_six[sf_idx++] = heavy_six[i];
		else if (heavy_six[i].state == 5) equal_three_six[th_idx++] = heavy_six[i];
	}
	for (int i = 0; light_six[i].state != -1; i++) {
		if (light_six[i].state == 4) sf_six[sf_idx++] = light_six[i];
		else if (light_six[i].state == 5) equal_three_six[th_idx++] = light_six[i];
	}

	for (int i = 0; sf_six[i].state != -1; i++) {
		add_coin(scale_a, sf_six[i].A.coins[0]);
		add_coin(scale_b, sf_six[i].B.coins[0]);
		add_coin(scale_c, sf_six[i].C.coins[0]);

		ret = balance(scale_a, scale_b, scale_c);
		resulting_sf_six_balance(sf_six, i, ret);

		empty_all();
	}

	for (int i = 0; heavy_six[i].state != -1; i++) if (heavy_six[i + 1].state == -1) printf("heavy_six : %d\n", i);
	for (int i = 0; light_six[i].state != -1; i++) if (light_six[i + 1].state == -1) printf("light_six : %d\n", i);
	for (int i = 0; sf_six[i].state != -1; i++) if (sf_six[i + 1].state == -1) printf("sf_six : %d\n", i);
	for (int i = 0; equal_three_six[i].state != -1; i++) if (equal_three_six[i + 1].state == -1) printf("equal_three_six : %d\n", i);
}

int main() {
	initialize(5); // 불량 동전의 확률 p = 33%
	
	solution_2();

	return 0;
}