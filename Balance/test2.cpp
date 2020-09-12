#include "stdio.h"
#include "balance.h"
#include "conio.h"

int main()
{
	int fault_coin[100] = { 0, }; // 불량 동전 넣는 배열
	int temp[100] = { 0, }; // 임시로 쓸 배열
	int count = 0; // 불량 동전 인덱스
	int count_2 = 0; // 임시로 쓸 배열의 인덱스
	int final[100]; // unknown 확인하는 배열
	for (int i = 0; i < 100; i++)
		final[i] = -1;
	int f = 0; // final 배열 인덱스
	int real = 0; // 정상인 동전 표시

	
	initialize(70); // 불량동전 발생 확률 p

	for (int i = 0; i < 11; i++) // (3, 3, 3) * 11회 = 99개의 동전 
	{
		int a[4] = { 9 * i,9 * i + 1,9 * i + 2,-1 };
		int b[4] = { 9 * i + 3,9 * i + 4,9 * i + 5,-1 };
		int c[4] = { 9 * i + 6,9 * i + 7,9 * i + 8,-1 };

		int ret_1 = balance(a, b, c);

		// a가 가장 무거울 경우
		if (ret_1 == 0)
		{
			int a_1[4] = { a[0],-1 };
			int a_2[4] = { a[1],-1 };
			int a_3[4] = { a[2],-1 };

			int ret_2 = balance(a_1, a_2, a_3);

			// a의 동전이 모두 정상 동전일 경우 (7 7 7)
			if (ret_2 == 6)
			{
				int b_1[2] = { b[0],-1 };
				int b_2[2] = { b[1],-1 };
				int b_3[2] = { b[2],-1 };

				int ret_3 = balance(b_1, b_2, b_3);

				// b의 동전이 하나만 정상일 경우 
				if (ret_3 == 0) // b (7 5 5)
				{
					fault_coin[count++] = b_2[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 1) // b (5 7 5)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 2) // b (7 5 5)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_2[0];
				}
				// b의 동전이 2개 정상일 경우
				else if (ret_3 == 3) // b (7 7 5)
				{
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 4) // b (5 7 7)
				{
					fault_coin[count++] = b_1[0];
				}
				else if (ret_3 == 5) // b (7 5 7)
				{
					fault_coin[count++] = b_2[0];
				}
				// b의 동전이 모두 불량 동전일 경우
				else if (ret_3 == 6) // b (5 5 5)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_2[0];
					fault_coin[count++] = b_3[0];
				}

				int c_1[2] = { c[0],-1 };
				int c_2[2] = { c[1],-1 };
				int c_3[2] = { c[2],-1 };

				int ret_4 = balance(c_1, c_2, c_3);

				// c의 동전이 하나만 정상일 경우 
				if (ret_4 == 0) // c (7 5 5)
				{
					fault_coin[count++] = c_2[0];
					fault_coin[count++] = c_3[0];
				}
				else if (ret_4 == 1) // c (5 7 5)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_3[0];
				}
				else if (ret_4 == 2) // c (7 5 5)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_2[0];
				}
				// c의 동전이 2개 정상일 경우
				else if (ret_4 == 3) // c (7 7 5)
				{
					fault_coin[count++] = c_3[0];
				}
				else if (ret_4 == 4) // c (5 7 7)
				{
					fault_coin[count++] = c_1[0];
				}
				else if (ret_4 == 5) // c (7 5 7)
				{
					fault_coin[count++] = c_2[0];
				}
				// b의 동전이 모두 불량 동전일 경우
				else if (ret_4 == 6) // c (5 5 5)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_2[0];
					fault_coin[count++] = c_3[0];
				}
			}
			// a의 정상 동전이 1개인 경우_1
			else if (ret_2 == 0) // 
			{
				real = a[0]; // 첫번째 동전이 정상
				fault_coin[count++] = a_2[0];
				fault_coin[count++] = a_3[0];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];
			}
			// a의 정상 동전이 1개인 경우_2
			else if (ret_2 == 1)
			{
				real = a[1]; // 두번째 동전이 정상
				fault_coin[count++] = a_1[0];
				fault_coin[count++] = a_3[0];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];
			}
			// a의 정상 동전이 1개인 경우_3 
			else if (ret_2 == 2)
			{
				real = a[2]; // 세번째 동전이 정상
				fault_coin[count++] = a_1[0];
				fault_coin[count++] = a_2[0];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];
			}
			// a의 정상 동전이 2개인 경우_1 
			else if (ret_2 == 3)
			{
				fault_coin[count++] = a_3[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // b의 2개와 c 하나 비교
				// b에 정상 동전 1개 발견_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// b에 정상 동전 1개 발견_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// c에 정상 동전 1개 발견 
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];

					final[f++] = b[2];
				}
				// b와 c에 정상 동전 1개씩 발견
				else if (ret_3 == 4)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				// b[0], b[1], c[0] 불량일때 
				else if (ret_3 == 6)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[0];

					final[f++] = b[2];
					final[f++] = c[1];
					final[f++] = c[2];
				}
			}
			// a의 정상 동전이 2개인 경우_2 : a (5 7 7)
			else if (ret_2 == 4)
			{
				fault_coin[count++] = a_1[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // b의 2개와 c 하나 비교
				// b에 정상 동전 1개 발견_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// b에 정상 동전 1개 발견_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// c에 정상 동전 1개 발견 
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];

					final[f++] = b[2];
				}
				// b와 c에 정상 동전 1개씩 발견
				else if (ret_3 == 4)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				// b[0], b[1], c[0] 불량일때 
				else if (ret_3 == 6)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[0];

					final[f++] = b[2];
					final[f++] = c[1];
					final[f++] = c[2];
				}
			}
			// a의 정상 동전이 2개인 경우_3 : a (7 5 7)
			else if (ret_2 == 5)
			{
				fault_coin[count++] = a_2[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // b의 2개와 c 하나 비교
				// b에 정상 동전 1개 발견_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// b에 정상 동전 1개 발견_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// c에 정상 동전 1개 발견 
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];

					final[f++] = b[2];
				}
				// b와 c에 정상 동전 1개씩 발견
				else if (ret_3 == 4)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				// b[0], b[1], c[0] 불량일때 
				else if (ret_3 == 6)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[0];

					final[f++] = b[2];
					final[f++] = c[1];
					final[f++] = c[2];
				}
			}
		}
		// b가 가장 무거울 경우
		else if (ret_1 == 1)
		{
			int b_1[4] = { b[0],-1 };
			int b_2[4] = { b[1],-1 };
			int b_3[4] = { b[2],-1 };

			int ret_2 = balance(b_1, b_2, b_3);

			// b의 동전이 모두 정상 동전일 경우 (7 7 7)
			if (ret_2 == 6)
			{
				int a_1[2] = { a[0],-1 };
				int a_2[2] = { a[1],-1 };
				int a_3[2] = { a[2],-1 };

				int ret_3 = balance(a_1, a_2, a_3);

				// a의 동전이 하나만 정상일 경우 
				if (ret_3 == 0) // a (7 5 5)
				{
					fault_coin[count++] = a_2[0];
					fault_coin[count++] = a_3[0];
				}
				else if (ret_3 == 1) // a (5 7 5)
				{
					fault_coin[count++] = a_1[0];
					fault_coin[count++] = a_3[0];
				}
				else if (ret_3 == 2) // a (7 5 5)
				{
					fault_coin[count++] = a_1[0];
					fault_coin[count++] = a_2[0];
				}
				// a의 동전이 2개 정상일 경우
				else if (ret_3 == 3) // a (7 7 5)
				{
					fault_coin[count++] = a_3[0];
				}
				else if (ret_3 == 4) // a (5 7 7)
				{
					fault_coin[count++] = a_1[0];
				}
				else if (ret_3 == 5) // a (7 5 7)
				{
					fault_coin[count++] = a_2[0];
				}
				// a의 동전이 모두 불량 동전일 경우
				else if (ret_3 == 6) // a (5 5 5)
				{
					fault_coin[count++] = a_1[0];
					fault_coin[count++] = a_2[0];
					fault_coin[count++] = a_3[0];
				}

				int c_1[2] = { c[0],-1 };
				int c_2[2] = { c[1],-1 };
				int c_3[2] = { c[2],-1 };

				int ret_4 = balance(c_1, c_2, c_3);

				// c의 동전이 하나만 정상일 경우 
				if (ret_4 == 0) // c (7 5 5)
				{
					fault_coin[count++] = c_2[0];
					fault_coin[count++] = c_3[0];
				}
				else if (ret_4 == 1) // c (5 7 5)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_3[0];
				}
				else if (ret_4 == 2) // c (7 5 5)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_2[0];
				}
				// c의 동전이 2개 정상일 경우
				else if (ret_4 == 3) // c (7 7 5)
				{
					fault_coin[count++] = c_3[0];
				}
				else if (ret_4 == 4) // c (5 7 7)
				{
					fault_coin[count++] = c_1[0];
				}
				else if (ret_4 == 5) // c (7 5 7)
				{
					fault_coin[count++] = c_2[0];
				}
				// c의 동전이 모두 불량 동전일 경우
				else if (ret_4 == 6) // c (5 5 5)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_2[0];
					fault_coin[count++] = c_3[0];
				}
			}
			// b의 정상 동전이 1개인 경우_1
			else if (ret_2 == 0) // 
			{
				real = b[0]; // 첫번째 동전이 정상
				fault_coin[count++] = b_2[0];
				fault_coin[count++] = b_3[0];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];
			}
			// b의 정상 동전이 1개인 경우_2
			else if (ret_2 == 1)
			{
				real = b[1]; // 두번째 동전이 정상
				fault_coin[count++] = b_1[0];
				fault_coin[count++] = b_3[0];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];
			}
			// b의 정상 동전이 1개인 경우_3 
			else if (ret_2 == 2)
			{
				real = b[2]; // 세번째 동전이 정상
				fault_coin[count++] = b_1[0];
				fault_coin[count++] = b_2[0];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];
			}
			// b의 정상 동전이 2개인 경우_1 
			else if (ret_2 == 3)
			{
				fault_coin[count++] = b_3[0];

				int tmp_1[2] = { a[0],-1 };
				int tmp_2[2] = { a[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // a의 2개와 c 하나 비교
				// a에 정상 동전 1개 발견_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// a에 정상 동전 1개 발견_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// c에 정상 동전 1개 발견 
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];

					final[f++] = a[2];
				}
				// a와 c에 정상 동전 1개씩 발견
				else if (ret_3 == 4)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				// a[0], a[1], c[0] 불량일때 
				else if (ret_3 == 6)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];
					fault_coin[count++] = c[0];

					final[f++] = a[2];
					final[f++] = c[1];
					final[f++] = c[2];
				}
			}
			// b의 정상 동전이 2개인 경우_2 : b (5 7 7)
			else if (ret_2 == 4)
			{
				fault_coin[count++] = b_1[0];

				int tmp_1[2] = { a[0],-1 };
				int tmp_2[2] = { a[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // a의 2개와 c 하나 비교
				// a에 정상 동전 1개 발견_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// b에 정상 동전 1개 발견_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// c에 정상 동전 1개 발견 
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];

					final[f++] = a[2];
				}
				// a와 c에 정상 동전 1개씩 발견
				else if (ret_3 == 4)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				// a[0], a[1], c[0] 불량일때 
				else if (ret_3 == 6)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];
					fault_coin[count++] = c[0];

					final[f++] = a[2];
					final[f++] = c[1];
					final[f++] = c[2];
				}
			}
			// b의 정상 동전이 2개인 경우_3 : b (7 5 7)
			else if (ret_2 == 5)
			{
				fault_coin[count++] = b_2[0];

				int tmp_1[2] = { a[0],-1 };
				int tmp_2[2] = { a[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // a의 2개와 c 하나 비교
				// a에 정상 동전 1개 발견_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// a에 정상 동전 1개 발견_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// c에 정상 동전 1개 발견 
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];

					final[f++] = a[2];
				}
				// a와 c에 정상 동전 1개씩 발견
				else if (ret_3 == 4)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				// a[0], a[1], a[0] 불량일때 
				else if (ret_3 == 6)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];
					fault_coin[count++] = c[0];

					final[f++] = a[2];
					final[f++] = c[1];
					final[f++] = c[2];
				}
			}
		}
		// c가 가장 무거울 경우
		else if (ret_1 == 2)
		{
			int c_1[4] = { c[0],-1 };
			int c_2[4] = { c[1],-1 };
			int c_3[4] = { c[2],-1 };

			int ret_2 = balance(c_1, c_2, c_3);

			// c의 동전이 모두 정상 동전일 경우 (7 7 7)
			if (ret_2 == 6)
			{
				int b_1[2] = { b[0],-1 };
				int b_2[2] = { b[1],-1 };
				int b_3[2] = { b[2],-1 };

				int ret_3 = balance(b_1, b_2, b_3);

				// b의 동전이 하나만 정상일 경우 
				if (ret_3 == 0) // b (7 5 5)
				{
					fault_coin[count++] = b_2[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 1) // b (5 7 5)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 2) // b (7 5 5)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_2[0];
				}
				// b의 동전이 2개 정상일 경우
				else if (ret_3 == 3) // b (7 7 5)
				{
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 4) // b (5 7 7)
				{
					fault_coin[count++] = b_1[0];
				}
				else if (ret_3 == 5) // b (7 5 7)
				{
					fault_coin[count++] = b_2[0];
				}
				// b의 동전이 모두 불량 동전일 경우
				else if (ret_3 == 6) // b (5 5 5)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_2[0];
					fault_coin[count++] = b_3[0];
				}

				int a_1[2] = { a[0],-1 };
				int a_2[2] = { a[1],-1 };
				int a_3[2] = { a[2],-1 };

				int ret_4 = balance(a_1, a_2, a_3);

				// a의 동전이 하나만 정상일 경우 
				if (ret_4 == 0) // a (7 5 5)
				{
					fault_coin[count++] = a_2[0];
					fault_coin[count++] = a_3[0];
				}
				else if (ret_4 == 1) // a (5 7 5)
				{
					fault_coin[count++] = a_1[0];
					fault_coin[count++] = a_3[0];
				}
				else if (ret_4 == 2) // a (7 5 5)
				{
					fault_coin[count++] = a_1[0];
					fault_coin[count++] = a_2[0];
				}
				// a의 동전이 2개 정상일 경우
				else if (ret_4 == 3) // a (7 7 5)
				{
					fault_coin[count++] = a_3[0];
				}
				else if (ret_4 == 4) // a (5 7 7)
				{
					fault_coin[count++] = a_1[0];
				}
				else if (ret_4 == 5) // a (7 5 7)
				{
					fault_coin[count++] = a_2[0];
				}
				// a의 동전이 모두 불량 동전일 경우
				else if (ret_4 == 6) // a (5 5 5)
				{
					fault_coin[count++] = a_1[0];
					fault_coin[count++] = a_2[0];
					fault_coin[count++] = a_3[0];
				}
			}
			// c의 정상 동전이 1개인 경우_1
			else if (ret_2 == 0) // 
			{
				real = c[0]; // 첫번째 동전이 정상
				fault_coin[count++] = c_2[0];
				fault_coin[count++] = c_3[0];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];
			}
			// c의 정상 동전이 1개인 경우_2
			else if (ret_2 == 1)
			{
				real = c[1]; // 두번째 동전이 정상
				fault_coin[count++] = c_1[0];
				fault_coin[count++] = c_3[0];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];
			}
			// a의 정상 동전이 1개인 경우_3 
			else if (ret_2 == 2)
			{
				real = c[2]; // 세번째 동전이 정상
				fault_coin[count++] = c_1[0];
				fault_coin[count++] = c_2[0];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];
			}
			// c의 정상 동전이 2개인 경우_1 
			else if (ret_2 == 3)
			{
				fault_coin[count++] = c_3[0];

				int tmp_1[2] = { a[0],-1 };
				int tmp_2[2] = { a[1],-1 };
				int tmp_3[2] = { b[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // b의 2개와 c 하나 비교
				// a에 정상 동전 1개 발견_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[0];
					final[f++] = b[1];
					final[f++] = b[2];
				}
				// a에 정상 동전 1개 발견_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[0];
					final[f++] = b[1];
					final[f++] = b[2];
				}
				// b에 정상 동전 1개 발견
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];

					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					final[f++] = a[2];
				}
				// a와 b에 정상 동전 1개씩 발견
				else if (ret_3 == 4)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
				// a[0], a[1], b[0] 불량일때 
				else if (ret_3 == 6)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];
					fault_coin[count++] = b[0];

					final[f++] = a[2];
					final[f++] = b[1];
					final[f++] = b[2];
				}
			}
			// c의 정상 동전이 2개인 경우_2 : c (5 7 7)
			else if (ret_2 == 4)
			{
				fault_coin[count++] = c_1[0];

				int tmp_1[2] = { a[0],-1 };
				int tmp_2[2] = { a[1],-1 };
				int tmp_3[2] = { b[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // a의 2개와 b 하나 비교
				// a에 정상 동전 1개 발견_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[0];
					final[f++] = b[1];
					final[f++] = b[2];
				}
				// a에 정상 동전 1개 발견_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[0];
					final[f++] = b[1];
					final[f++] = b[2];
				}
				// b에 정상 동전 1개 발견
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];

					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					final[f++] = a[2];
				}
				// a와 b에 정상 동전 1개씩 발견
				else if (ret_3 == 4)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
				// a[0], a[1], b[0] 불량일때 
				else if (ret_3 == 6)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];
					fault_coin[count++] = b[0];

					final[f++] = a[2];
					final[f++] = b[1];
					final[f++] = b[2];
				}
			}
			// c의 정상 동전이 2개인 경우_3 : c (7 5 7)
			else if (ret_2 == 5)
			{
				fault_coin[count++] = c_2[0];

				int tmp_1[2] = { a[0],-1 };
				int tmp_2[2] = { a[1],-1 };
				int tmp_3[2] = { b[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // a의 2개와 b 하나 비교
				// b에 정상 동전 1개 발견_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[0];
					final[f++] = b[1];
					final[f++] = b[2];
				}
				// a에 정상 동전 1개 발견_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[0];
					final[f++] = b[1];
					final[f++] = b[2];
				}
				// b에 정상 동전 1개 발견
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];

					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					final[f++] = a[2];
				}
				// a와 b에 정상 동전 1개씩 발견
				else if (ret_3 == 4)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
				// a[0], a[1], b[0] 불량일때 
				else if (ret_3 == 6)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];
					fault_coin[count++] = b[0];

					final[f++] = a[2];
					final[f++] = b[1];
					final[f++] = b[2];
				}
			}
		}

		// a, b가 무거울 경우
		else if (ret_1 == 3)
		{
			int a_1[2] = { a[0],-1 };
			int a_2[2] = { a[1],-1 };
			int a_3[2] = { a[2],-1 };

			int ret_2 = balance(a_1, a_2, a_3);
			// a와 b 모두 정상 동전
			if (ret_2 == 6)
			{
				real = a[0];
				int c_1[2] = { c[0],-1 };
				int c_2[2] = { c[1],-1 };
				int c_3[2] = { c[2],-1 };

				int ret_3 = balance(c_1, c_2, c_3);
				// c
				if (ret_3 == 0)
				{
					fault_coin[count++] = c_2[0];
					fault_coin[count++] = c_3[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_3[0];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_2[0];
				}
				else if (ret_3 == 3)
				{
					fault_coin[count++] = c_3[0];
				}
				else if (ret_3 == 4)
				{
					fault_coin[count++] = c_1[0];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = c_2[0];
				}
				else if (ret_3 == 6)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_2[0];
					fault_coin[count++] = c_3[0];
				}
			}
			// a와 b가 정상 동전 2개씩 갖고 있을 경우_1 c는 755 또는 555
			else if (ret_2 == 3) // 7 7 5
			{
				fault_coin[count++] = a_3[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b에는 7 7 / 7 5/ 5 7   
				if (ret_3 == 0) // 7 5 5
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 1) // 5 7 5 
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 3) // 7 7 5
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 4) // 5 7 7
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 5) // 7 5 7
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 6) // 7 7 7 
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
			}
			// a와 b가 정상 동전 2개씩 갖고 있을 경우_2 c는 755 또는 555
			else if (ret_2 == 4) // 5 7 7
			{
				fault_coin[count++] = a_1[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b에는 7 7 / 7 5/ 5 7   
				if (ret_3 == 0) // 7 5 5
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 1) // 5 7 5 
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 3) // 7 7 5
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 4) // 5 7 7
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 5) // 7 5 7
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 6) // 7 7 7 
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
			}
			// a와 b가 정상 동전 2개씩 갖고 있을 경우_3 c는 755 또는 555
			else if (ret_2 == 5) // 7 5 7
			{
				fault_coin[count++] = a_2[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b에는 7 7 / 7 5/ 5 7   
				if (ret_3 == 0) // 7 5 5
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 1) // 5 7 5 
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 3) // 7 7 5
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 4) // 5 7 7
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 5) // 7 5 7
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 6) // 7 7 7 
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
			}
			// a와 b에 정상 동전 1개씩 갖고 있을 경우_1
			else if (ret_2 == 0)
			{
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];

				int b_1[2] = { b[0],-1 };
				int b_2[2] = { b[1],-1 };
				int b_3[2] = { b[2],-1 };

				int ret_3 = balance(b_1, b_2, b_3);
				// b 비교
				if (ret_3 == 0)
				{
					fault_coin[count++] = b_2[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_2[0];
				}
			}
			// a와 b에 정상 동전 1개씩 갖고 있을 경우_2
			else if (ret_2 == 1)
			{
				fault_coin[count++] = a[0];
				fault_coin[count++] = a[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];

				int b_1[2] = { b[0],-1 };
				int b_2[2] = { b[1],-1 };
				int b_3[2] = { b[2],-1 };

				int ret_3 = balance(b_1, b_2, b_3);
				// b 비교
				if (ret_3 == 0)
				{
					fault_coin[count++] = b_2[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_2[0];
				}
			}
			// a와 b에 정상 동전 1개씩 갖고 있을 경우_3
			else if (ret_2 == 2)
			{
				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];

				int b_1[2] = { b[0],-1 };
				int b_2[2] = { b[1],-1 };
				int b_3[2] = { b[2],-1 };

				int ret_3 = balance(b_1, b_2, b_3);
				// b 비교 
				if (ret_3 == 0)
				{
					fault_coin[count++] = b_2[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_2[0];
				}
			}
		}
		// c, b가 무거울 경우
		else if (ret_1 == 4)
		{
			int c_1[2] = { c[0],-1 };
			int c_2[2] = { c[1],-1 };
			int c_3[2] = { c[2],-1 };

			int ret_2 = balance(c_1, c_2, c_3);
			// c와 b 모두 정상 동전
			if (ret_2 == 6)
			{
				real = c[0];
				int a_1[2] = { a[0],-1 };
				int a_2[2] = { a[1],-1 };
				int a_3[2] = { a[2],-1 };

				int ret_3 = balance(a_1, a_2, a_3);
				// a 비교
				if (ret_3 == 0)
				{
					fault_coin[count++] = a_2[0];
					fault_coin[count++] = a_3[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a_1[0];
					fault_coin[count++] = a_3[0];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a_1[0];
					fault_coin[count++] = a_2[0];
				}
				else if (ret_3 == 3)
				{
					fault_coin[count++] = a_3[0];
				}
				else if (ret_3 == 4)
				{
					fault_coin[count++] = a_1[0];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = a_2[0];
				}
				else if (ret_3 == 6)
				{
					fault_coin[count++] = a_1[0];
					fault_coin[count++] = a_2[0];
					fault_coin[count++] = a_3[0];
				}
			}
			// c와 b가 정상 동전 2개씩 갖고 있을 경우_1 a는 755 또는 555
			else if (ret_2 == 3) // 7 7 5
			{
				fault_coin[count++] = c_3[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { a[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b에는 7 7 / 7 5/ 5 7   
				if (ret_3 == 0) // 7 5 5
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = a[0];

					final[f++] = a[1];
					final[f++] = a[2];
				}
				else if (ret_3 == 1) // 5 7 5 
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = a[0];

					final[f++] = a[1];
					final[f++] = a[2];
				}
				else if (ret_3 == 3) // 7 7 5
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = a[0];

					final[f++] = a[1];
					final[f++] = a[2];
				}
				else if (ret_3 == 4) // 5 7 7
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];
				}
				else if (ret_3 == 5) // 7 5 7 
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];
				}
				else if (ret_3 == 6) // 7 7 7 
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];
				}
			}
			// c와 b가 정상 동전 2개씩 갖고 있을 경우_2 a는 755 또는 555
			else if (ret_2 == 4) // 5 7 7
			{
				fault_coin[count++] = c_1[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { a[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b에는 7 7 / 7 5/ 5 7   
				if (ret_3 == 0) // 7 5 5
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = a[0];

					final[f++] = a[1];
					final[f++] = a[2];
				}
				else if (ret_3 == 1) // 5 7 5 
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = a[0];

					final[f++] = a[1];
					final[f++] = a[2];
				}
				else if (ret_3 == 3) // 7 7 5
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = a[0];

					final[f++] = a[1];
					final[f++] = a[2];
				}
				else if (ret_3 == 4) // 5 7 7
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];
				}
				else if (ret_3 == 5) // 7 5 7
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];
				}
				else if (ret_3 == 6) // 7 7 7 
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];
				}
			}
			// c와 b가 정상 동전 2개씩 갖고 있을 경우_3 a는 755 또는 555
			else if (ret_2 == 5) // 7 5 7
			{
				fault_coin[count++] = c_2[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { a[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b에는 7 7 / 7 5/ 5 7   
				if (ret_3 == 0) // 7 5 5
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = a[0];

					final[f++] = a[1];
					final[f++] = a[2];
				}
				else if (ret_3 == 1) // 5 7 5 
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = a[0];

					final[f++] = a[1];
					final[f++] = a[2];
				}
				else if (ret_3 == 3) // 7 7 5
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = a[0];

					final[f++] = a[1];
					final[f++] = a[2];
				}
				else if (ret_3 == 4) // 5 7 7
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];
				}
				else if (ret_3 == 5) // 7 5 7
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];
				}
				else if (ret_3 == 6) // 7 7 7  
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];
				}
			}
			// c와 b에 정상 동전 1개씩 갖고 있을 경우_1
			else if (ret_2 == 0)
			{
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];

				int b_1[2] = { b[0],-1 };
				int b_2[2] = { b[1],-1 };
				int b_3[2] = { b[2],-1 };

				int ret_3 = balance(b_1, b_2, b_3);
				// b 비교 
				if (ret_3 == 0)
				{
					fault_coin[count++] = b_2[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_2[0];
				}
			}
			// c와 b에 정상 동전 1개씩 갖고 있을 경우_2
			else if (ret_2 == 1)
			{
				fault_coin[count++] = c[0];
				fault_coin[count++] = c[2];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];

				int b_1[2] = { b[0],-1 };
				int b_2[2] = { b[1],-1 };
				int b_3[2] = { b[2],-1 };

				int ret_3 = balance(b_1, b_2, b_3);
				// b 비교 
				if (ret_3 == 0)
				{
					fault_coin[count++] = b_2[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_2[0];
				}
			}
			// c와 b에 정상 동전 1개씩 갖고 있을 경우_3
			else if (ret_2 == 2)
			{
				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];

				int b_1[2] = { b[0],-1 };
				int b_2[2] = { b[1],-1 };
				int b_3[2] = { b[2],-1 };

				int ret_3 = balance(b_1, b_2, b_3);
				// b 비교 
				if (ret_3 == 0)
				{
					fault_coin[count++] = b_2[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_2[0];
				}
			}
		}
		// a, c가 무거울 경우
		else if (ret_1 == 5)
		{
			int a_1[2] = { a[0],-1 };
			int a_2[2] = { a[1],-1 };
			int a_3[2] = { a[2],-1 };

			int ret_2 = balance(a_1, a_2, a_3);
			// a와 c 모두 정상 동전
			if (ret_2 == 6)
			{
				real = a[0];
				int b_1[2] = { b[0],-1 };
				int b_2[2] = { b[1],-1 };
				int b_3[2] = { b[2],-1 };

				int ret_3 = balance(b_1, b_2, b_3);
				// b
				if (ret_3 == 0)
				{
					fault_coin[count++] = b_2[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_2[0];
				}
				else if (ret_3 == 3)
				{
					fault_coin[count++] = b_3[0];
				}
				else if (ret_3 == 4)
				{
					fault_coin[count++] = b_1[0];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = b_2[0];
				}
				else if (ret_3 == 6)
				{
					fault_coin[count++] = b_1[0];
					fault_coin[count++] = b_2[0];
					fault_coin[count++] = b_3[0];
				}
			}
			// a와 c가 정상 동전 2개씩 갖고 있을 경우_1 b는 755 또는 555
			else if (ret_2 == 3) // 7 7 5
			{
				fault_coin[count++] = a_3[0];

				int tmp_1[2] = { c[0],-1 };
				int tmp_2[2] = { c[1],-1 };
				int tmp_3[2] = { b[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// c에는 7 7 / 7 5/ 5 7   
				if (ret_3 == 0) // 7 5 5
				{
					fault_coin[count++] = c[1];
					fault_coin[count++] = b[0];

					final[f++] = b[1];
					final[f++] = b[2];
				}
				else if (ret_3 == 1) // 5 7 5 
				{
					fault_coin[count++] = c[0];
					fault_coin[count++] = b[0];

					final[f++] = b[1];
					final[f++] = b[2];
				}
				else if (ret_3 == 3) // 7 7 5
				{
					fault_coin[count++] = c[2];
					fault_coin[count++] = b[0];

					final[f++] = b[1];
					final[f++] = b[2];
				}
				else if (ret_3 == 4) // 5 7 7
				{
					fault_coin[count++] = c[0];
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
				else if (ret_3 == 5) // 7 5 7
				{
					fault_coin[count++] = c[1];
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
				else if (ret_3 == 6) // 7 7 7 
				{
					fault_coin[count++] = c[2];
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
			}
			// a와 c가 정상 동전 2개씩 갖고 있을 경우_2 b는 755 또는 555
			else if (ret_2 == 4) // 5 7 7
			{
				fault_coin[count++] = a_1[0];

				int tmp_1[2] = { c[0],-1 };
				int tmp_2[2] = { c[1],-1 };
				int tmp_3[2] = { b[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// c에는 7 7 / 7 5/ 5 7   
				if (ret_3 == 0) // 7 5 5
				{
					fault_coin[count++] = c[1];
					fault_coin[count++] = b[0];

					final[f++] = b[1];
					final[f++] = b[2];
				}
				else if (ret_3 == 1) // 5 7 5 
				{
					fault_coin[count++] = c[0];
					fault_coin[count++] = b[0];

					final[f++] = b[1];
					final[f++] = b[2];
				}
				else if (ret_3 == 3) // 7 7 5
				{
					fault_coin[count++] = c[2];
					fault_coin[count++] = b[0];

					final[f++] = b[1];
					final[f++] = b[2];
				}
				else if (ret_3 == 4) // 5 7 7
				{
					fault_coin[count++] = c[0];
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
				else if (ret_3 == 5) // 7 5 7
				{
					fault_coin[count++] = c[1];
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
				else if (ret_3 == 6) // 7 7 7 
				{
					fault_coin[count++] = c[2];
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
			}
			// a와 c가 정상 동전 2개씩 갖고 있을 경우_3 b는 755 또는 555
			else if (ret_2 == 5) // 7 5 7
			{
				fault_coin[count++] = a_2[0];

				int tmp_1[2] = { c[0],-1 };
				int tmp_2[2] = { c[1],-1 };
				int tmp_3[2] = { b[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// c에는 7 7 / 7 5/ 5 7   
				if (ret_3 == 0) // 7 5 5
				{
					fault_coin[count++] = c[1];
					fault_coin[count++] = b[0];

					final[f++] = b[1];
					final[f++] = b[2];
				}
				else if (ret_3 == 1) // 5 7 5 
				{
					fault_coin[count++] = c[0];
					fault_coin[count++] = b[0];

					final[f++] = b[1];
					final[f++] = b[2];
				}
				else if (ret_3 == 3) // 7 7 5
				{
					fault_coin[count++] = c[2];
					fault_coin[count++] = b[0];

					final[f++] = b[1];
					final[f++] = b[2];
				}
				else if (ret_3 == 4) // 5 7 7
				{
					fault_coin[count++] = c[0];
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
				else if (ret_3 == 5) // 7 5 7
				{
					fault_coin[count++] = c[1];
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
				else if (ret_3 == 6) // 7 7 7 
				{
					fault_coin[count++] = c[2];
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
				}
			}
			// a와 c에 정상 동전 1개씩 갖고 있을 경우_1
			else if (ret_2 == 0)
			{
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				int c_1[2] = { c[0],-1 };
				int c_2[2] = { c[1],-1 };
				int c_3[2] = { c[2],-1 };

				int ret_3 = balance(c_1, c_2, c_3);
				// c 비교 
				if (ret_3 == 0)
				{
					fault_coin[count++] = c_2[0];
					fault_coin[count++] = c_3[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_3[0];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_2[0];
				}
			}
			// a와 c에 정상 동전 1개씩 갖고 있을 경우_2
			else if (ret_2 == 1)
			{
				fault_coin[count++] = a[0];
				fault_coin[count++] = a[2];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				int c_1[2] = { c[0],-1 };
				int c_2[2] = { c[1],-1 };
				int c_3[2] = { c[2],-1 };

				int ret_3 = balance(c_1, c_2, c_3);
				// c 비교 
				if (ret_3 == 0)
				{
					fault_coin[count++] = c_2[0];
					fault_coin[count++] = c_3[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_3[0];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_2[0];
				}
			}
			// a와 c에 정상 동전 1개씩 갖고 있을 경우_3
			else if (ret_2 == 2)
			{
				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				int c_1[2] = { c[0],-1 };
				int c_2[2] = { c[1],-1 };
				int c_3[2] = { c[2],-1 };

				int ret_3 = balance(c_1, c_2, c_3);
				// c 비교
				if (ret_3 == 0)
				{
					fault_coin[count++] = c_2[0];
					fault_coin[count++] = c_3[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_3[0];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_2[0];
				}
			}
		}

		// a, b, c가 같을 경우
		else if (ret_1 == 6)
		{
			int a_1[2] = { a[0],-1 };
			int a_2[2] = { a[1],-1 };
			int a_3[2] = { a[2],-1 };

			int ret_2 = balance(a_1, a_2, a_3);
			// 무게가 모두 같은 경우 - 전부 불량인지 정상인지 모름
			if (ret_2 == 6)
			{
				temp[count_2++] = a[0];
				temp[count_2++] = a[1];
				temp[count_2++] = a[2];
				temp[count_2++] = b[0];
				temp[count_2++] = b[1];
				temp[count_2++] = b[2];
				temp[count_2++] = c[0];
				temp[count_2++] = c[1];
				temp[count_2++] = c[2];
			}
			// a,b,c 모두 정상 동전이 1개일 경우_1
			else if (ret_2 == 0)
			{
				fault_coin[count++] = a_2[0];
				fault_coin[count++] = a_3[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b와 c 불량 동전 찾기(정상 동전 1개)
				if (ret_3 == 0)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 4)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 6)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[0];

					final[f++] = b[2];
					final[f++] = c[1];
					final[f++] = c[2];
				}
			}
			// a,b,c 모두 정상 동전이 1개일 경우_2
			else if (ret_2 == 1)
			{
				fault_coin[count++] = a_1[0];
				fault_coin[count++] = a_3[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b와 c 불량 동전 찾기(정상 동전 1개)
				if (ret_3 == 0)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 4)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 6)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[0];

					final[f++] = b[2];
					final[f++] = c[1];
					final[f++] = c[2];
				}
			}
			// a,b,c 모두 정상 동전이 1개일 경우_3
			else if (ret_2 == 2)
			{
				fault_coin[count++] = a_1[0];
				fault_coin[count++] = a_2[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b와 c 불량 동전 찾기(정상 동전 1개)
				if (ret_3 == 0)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 4)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];
				}
				else if (ret_3 == 6)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[0];

					final[f++] = b[2];
					final[f++] = c[1];
					final[f++] = c[2];
				}
			}
			// a,b,c 모두 정상 동전이 2개일 경우_1
			else if (ret_2 == 3)
			{
				fault_coin[count++] = a_3[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b,c 모두 정상동전 2개
				if (ret_3 == 0)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = c[0];
				}
				else if (ret_3 == 3)
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[0];
				}
				else if (ret_3 == 4)
				{
					fault_coin[count++] = b[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = b[1];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 6) // 7 7 7
				{
					fault_coin[count++] = b[2];

					final[f++] = c[1];
					final[f++] = c[2];
				}
			}
			// a,b,c 모두 정상 동전이 2개일 경우_2
			else if (ret_2 == 4)
			{
				fault_coin[count++] = a_1[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b,c 모두 정상동전 2개
				if (ret_3 == 0)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = c[0];
				}
				else if (ret_3 == 3)
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[0];
				}
				else if (ret_3 == 4)
				{
					fault_coin[count++] = b[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = b[1];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 6) // 7 7 7
				{
					fault_coin[count++] = b[2];

					final[f++] = c[1];
					final[f++] = c[2];
				}
			}
			// a,b,c 모두 정상 동전이 2개일 경우_1
			else if (ret_2 == 5)
			{
				fault_coin[count++] = a_2[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b,c 모두 정상동전 2개
				if (ret_3 == 0)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = c[0];
				}
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = c[0];
				}
				else if (ret_3 == 3)
				{
					fault_coin[count++] = b[2];
					fault_coin[count++] = c[0];
				}
				else if (ret_3 == 4)
				{
					fault_coin[count++] = b[0];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 5)
				{
					fault_coin[count++] = b[1];

					final[f++] = c[1];
					final[f++] = c[2];
				}
				else if (ret_3 == 6) // 7 7 7
				{
					fault_coin[count++] = b[2];

					final[f++] = c[1];
					final[f++] = c[2];
				}
			}
		}
	}

	// 마지막 동전
	final[f++] = 99;

	temp[count_2] = -1; // temp[] 배열 끝 -1 값 설정

	int c = f % 3;
	int k = 0;
	// ret_1==6, ret_2=6인 경우
	while (temp[k] != -1 && temp[k + 9] != -1)
	{
		if (count != 0) // 불량동전을 하나라도 찾았을 때
		{
			int w_1[2] = { temp[k],-1 };
			int w_2[2] = { temp[k + 9],-1 };
			int w_3[2] = { fault_coin[0],-1 };
			int w_b = balance(w_1, w_2, w_3);

			if (w_b == 0) // A가 정상 B 불량
			{
				fault_coin[count++] = temp[k + 9];
				fault_coin[count++] = temp[k + 10];
				fault_coin[count++] = temp[k + 11];
				fault_coin[count++] = temp[k + 12];
				fault_coin[count++] = temp[k + 13];
				fault_coin[count++] = temp[k + 14];
				fault_coin[count++] = temp[k + 15];
				fault_coin[count++] = temp[k + 16];
				fault_coin[count++] = temp[k + 17];
			}
			else if (w_b == 1) // A가 불량 B 정상
			{
				fault_coin[count++] = temp[k];
				fault_coin[count++] = temp[k + 1];
				fault_coin[count++] = temp[k + 2];
				fault_coin[count++] = temp[k + 3];
				fault_coin[count++] = temp[k + 4];
				fault_coin[count++] = temp[k + 5];
				fault_coin[count++] = temp[k + 6];
				fault_coin[count++] = temp[k + 7];
				fault_coin[count++] = temp[k + 8];
			}
			else if (w_b == 6) // A, B 불량
			{
				fault_coin[count++] = temp[k];
				fault_coin[count++] = temp[k + 1];
				fault_coin[count++] = temp[k + 2];
				fault_coin[count++] = temp[k + 3];
				fault_coin[count++] = temp[k + 4];
				fault_coin[count++] = temp[k + 5];
				fault_coin[count++] = temp[k + 6];
				fault_coin[count++] = temp[k + 7];
				fault_coin[count++] = temp[k + 8];

				fault_coin[count++] = temp[k + 9];
				fault_coin[count++] = temp[k + 10];
				fault_coin[count++] = temp[k + 11];
				fault_coin[count++] = temp[k + 12];
				fault_coin[count++] = temp[k + 13];
				fault_coin[count++] = temp[k + 14];
				fault_coin[count++] = temp[k + 15];
				fault_coin[count++] = temp[k + 16];
				fault_coin[count++] = temp[k + 17];
			}
		}
		else // 불량 동전을 하나도 찾지 못했을 때
		{
			int w_1[2] = { temp[k],-1 };
			int w_2[2] = { temp[k + 9],-1 };
			int w_3[2] = { 99,-1 }; // 임의로 설정한값 불량인지 정상인진 알수 없음
			int w_b = balance(w_1, w_2, w_3);
			if (w_b == 5 || w_b == 0) // AC 정상들 B 불량
			{
				fault_coin[count++] = temp[k + 9];
				fault_coin[count++] = temp[k + 10];
				fault_coin[count++] = temp[k + 11];
				fault_coin[count++] = temp[k + 12];
				fault_coin[count++] = temp[k + 13];
				fault_coin[count++] = temp[k + 14];
				fault_coin[count++] = temp[k + 15];
				fault_coin[count++] = temp[k + 16];
				fault_coin[count++] = temp[k + 17];
			}
			else if (w_b == 4 || w_b == 1) // BC 정상들 A 불량
			{
				fault_coin[count++] = temp[k];
				fault_coin[count++] = temp[k + 1];
				fault_coin[count++] = temp[k + 2];
				fault_coin[count++] = temp[k + 3];
				fault_coin[count++] = temp[k + 4];
				fault_coin[count++] = temp[k + 5];
				fault_coin[count++] = temp[k + 6];
				fault_coin[count++] = temp[k + 7];
				fault_coin[count++] = temp[k + 8];
			}
			else if (w_b == 2) // C 정상 AB 불량
			{
				fault_coin[count++] = temp[k];
				fault_coin[count++] = temp[k + 1];
				fault_coin[count++] = temp[k + 2];
				fault_coin[count++] = temp[k + 3];
				fault_coin[count++] = temp[k + 4];
				fault_coin[count++] = temp[k + 5];
				fault_coin[count++] = temp[k + 6];
				fault_coin[count++] = temp[k + 7];
				fault_coin[count++] = temp[k + 8];

				fault_coin[count++] = temp[k + 9];
				fault_coin[count++] = temp[k + 10];
				fault_coin[count++] = temp[k + 11];
				fault_coin[count++] = temp[k + 12];
				fault_coin[count++] = temp[k + 13];
				fault_coin[count++] = temp[k + 14];
				fault_coin[count++] = temp[k + 15];
				fault_coin[count++] = temp[k + 16];
				fault_coin[count++] = temp[k + 17];
			}
		}
		k = k + 18;
	}
	if (temp[k] != -1)
	{
		if (count != 0) // 불량 동전 찾았을 때
		{
			int w_1[2] = { temp[k],-1 };
			int w_2[2] = { fault_coin[0],-1 };
			int w_3[2] = { fault_coin[1],-1 };
			int w_b = balance(w_1, w_2, w_3);

			if (w_b == 6) // temp[k] 전부 불량
			{
				fault_coin[count++] = temp[k];
				fault_coin[count++] = temp[k + 1];
				fault_coin[count++] = temp[k + 2];
				fault_coin[count++] = temp[k + 3];
				fault_coin[count++] = temp[k + 4];
				fault_coin[count++] = temp[k + 5];
				fault_coin[count++] = temp[k + 6];
				fault_coin[count++] = temp[k + 7];
				fault_coin[count++] = temp[k + 8];
			}
		}
		else // 불량 동전 못 찾았을 때
		{
			int w_1[2] = { temp[k],-1 };
			int w_2[2] = { 99,-1 };
			int w_3[2] = { 98,-1 };
			int w_b = balance(w_1, w_2, w_3);
			// 0 1 2 3 5 6
			if (w_b == 4 || w_b == 1 || w_b == 2) // 불정정 불정불 불불정
			{
				fault_coin[count++] = temp[k];
				fault_coin[count++] = temp[k + 1];
				fault_coin[count++] = temp[k + 2];
				fault_coin[count++] = temp[k + 3];
				fault_coin[count++] = temp[k + 4];
				fault_coin[count++] = temp[k + 5];
				fault_coin[count++] = temp[k + 6];
				fault_coin[count++] = temp[k + 7];
				fault_coin[count++] = temp[k + 8];
			}
		}
	}

	final[f] = -1;

	if (f != 0)
	{
		for (f = 0; final[f] != -1 && final[f + 1] != -1 && final[f + 2] != -1; f = f + 3)
		{
			int final_1[2] = { final[f],-1 };
			int final_2[2] = { final[f + 1],-1 };
			int final_3[2] = { final[f + 2],-1 };

			int ret_3 = balance(final_1, final_2, final_3);

			if (ret_3 == 0)
			{
				fault_coin[count++] = final_2[0];
				fault_coin[count++] = final_3[0];
			}
			else if (ret_3 == 1)
			{
				fault_coin[count++] = final_1[0];
				fault_coin[count++] = final_3[0];
			}
			else if (ret_3 == 2)
			{
				fault_coin[count++] = final_1[0];
				fault_coin[count++] = final_2[0];
			}
			else if (ret_3 == 3)
			{
				fault_coin[count++] = final_3[0];
			}
			else if (ret_3 == 4)
			{
				fault_coin[count++] = final_1[0];
			}
			else if (ret_3 == 5)
			{
				fault_coin[count++] = final_2[0];
			}
			else if (ret_3 == 6)
			{
				if (count != 0) { // 불량 동전을 찾은 경우
					int w_1[2] = { final_1[0],-1 };
					int w_3[2] = { fault_coin[0],-1 };
					int w_2[2] = { fault_coin[1],-1 };
					int w_b = balance(w_1, w_2, w_3);

					if (w_b == 6)
					{
						fault_coin[count++] = final_1[0];
						fault_coin[count++] = final_2[0];
						fault_coin[count++] = final_3[0];
					}
				}
				else { // 불량 동전을 찾지 못한 경우
					int w_1[2] = { final_1[0],-1 };
					int w_3[2] = { 99,-1 };
					int w_2[2] = { 98,-1 };
					int w_b = balance(w_1, w_2, w_3);

					if (w_b == 4 || w_b == 1 || w_b == 2)
					{
						fault_coin[count++] = final_1[0];
						fault_coin[count++] = final_2[0];
						fault_coin[count++] = final_3[0];
					}
				}
			}
		}

		if (c == 1)
		{
			int final_1[2] = { final[f],-1 };
			int final_2[2] = { fault_coin[1],-1 };
			int final_3[2] = { fault_coin[0],-1 };

			int ret_3 = balance(final_1, final_2, final_3);

			if (ret_3 == 6) {
				fault_coin[count++] = final[f];
			}
		}

		if (c == 2)
		{
			int final_1[2] = { final[f],-1 };
			int final_2[2] = { final[f + 1],-1 };
			int final_3[2] = { fault_coin[0],-1 };

			int ret_3 = balance(final_1, final_2, final_3);

			if (ret_3 == 0) {
				fault_coin[count++] = final_2[0];
			}
			else if (ret_3 == 1) {
				fault_coin[count++] = final_1[0];
			}
			else if (ret_3 == 6) {
				fault_coin[count++] = final_1[0];
				fault_coin[count++] = final_2[0];
			}
		}

	}

	fault_coin[count] = -1;

	int A[100] = { 0, };
	for (k = 0; k < 100; k++)
	{
		A[k] = fault_coin[k];
	}
	int B[100], C[100];
	B[0] = -1;
	C[0] = -1;

	balance(A, B, C);

	getchar();
	return 0;

}

