#include "stdio.h"
#include "balance.h"
#include "conio.h"

int main()
{
	int fault_coin[100] = { 0, }; // �ҷ� ���� �ִ� �迭
	int temp[100] = { 0, }; // �ӽ÷� �� �迭
	int count = 0; // �ҷ� ���� �ε���
	int count_2 = 0; // �ӽ÷� �� �迭�� �ε���
	int final[100]; // unknown Ȯ���ϴ� �迭
	for (int i = 0; i < 100; i++)
		final[i] = -1;
	int f = 0; // final �迭 �ε���
	int real = 0; // ������ ���� ǥ��

	
	initialize(70); // �ҷ����� �߻� Ȯ�� p

	for (int i = 0; i < 11; i++) // (3, 3, 3) * 11ȸ = 99���� ���� 
	{
		int a[4] = { 9 * i,9 * i + 1,9 * i + 2,-1 };
		int b[4] = { 9 * i + 3,9 * i + 4,9 * i + 5,-1 };
		int c[4] = { 9 * i + 6,9 * i + 7,9 * i + 8,-1 };

		int ret_1 = balance(a, b, c);

		// a�� ���� ���ſ� ���
		if (ret_1 == 0)
		{
			int a_1[4] = { a[0],-1 };
			int a_2[4] = { a[1],-1 };
			int a_3[4] = { a[2],-1 };

			int ret_2 = balance(a_1, a_2, a_3);

			// a�� ������ ��� ���� ������ ��� (7 7 7)
			if (ret_2 == 6)
			{
				int b_1[2] = { b[0],-1 };
				int b_2[2] = { b[1],-1 };
				int b_3[2] = { b[2],-1 };

				int ret_3 = balance(b_1, b_2, b_3);

				// b�� ������ �ϳ��� ������ ��� 
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
				// b�� ������ 2�� ������ ���
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
				// b�� ������ ��� �ҷ� ������ ���
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

				// c�� ������ �ϳ��� ������ ��� 
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
				// c�� ������ 2�� ������ ���
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
				// b�� ������ ��� �ҷ� ������ ���
				else if (ret_4 == 6) // c (5 5 5)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_2[0];
					fault_coin[count++] = c_3[0];
				}
			}
			// a�� ���� ������ 1���� ���_1
			else if (ret_2 == 0) // 
			{
				real = a[0]; // ù��° ������ ����
				fault_coin[count++] = a_2[0];
				fault_coin[count++] = a_3[0];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];
			}
			// a�� ���� ������ 1���� ���_2
			else if (ret_2 == 1)
			{
				real = a[1]; // �ι�° ������ ����
				fault_coin[count++] = a_1[0];
				fault_coin[count++] = a_3[0];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];
			}
			// a�� ���� ������ 1���� ���_3 
			else if (ret_2 == 2)
			{
				real = a[2]; // ����° ������ ����
				fault_coin[count++] = a_1[0];
				fault_coin[count++] = a_2[0];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];
			}
			// a�� ���� ������ 2���� ���_1 
			else if (ret_2 == 3)
			{
				fault_coin[count++] = a_3[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // b�� 2���� c �ϳ� ��
				// b�� ���� ���� 1�� �߰�_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// b�� ���� ���� 1�� �߰�_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// c�� ���� ���� 1�� �߰� 
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];

					final[f++] = b[2];
				}
				// b�� c�� ���� ���� 1���� �߰�
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
				// b[0], b[1], c[0] �ҷ��϶� 
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
			// a�� ���� ������ 2���� ���_2 : a (5 7 7)
			else if (ret_2 == 4)
			{
				fault_coin[count++] = a_1[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // b�� 2���� c �ϳ� ��
				// b�� ���� ���� 1�� �߰�_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// b�� ���� ���� 1�� �߰�_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// c�� ���� ���� 1�� �߰� 
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];

					final[f++] = b[2];
				}
				// b�� c�� ���� ���� 1���� �߰�
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
				// b[0], b[1], c[0] �ҷ��϶� 
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
			// a�� ���� ������ 2���� ���_3 : a (7 5 7)
			else if (ret_2 == 5)
			{
				fault_coin[count++] = a_2[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // b�� 2���� c �ϳ� ��
				// b�� ���� ���� 1�� �߰�_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// b�� ���� ���� 1�� �߰�_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// c�� ���� ���� 1�� �߰� 
				else if (ret_3 == 2)
				{
					fault_coin[count++] = b[0];
					fault_coin[count++] = b[1];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];

					final[f++] = b[2];
				}
				// b�� c�� ���� ���� 1���� �߰�
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
				// b[0], b[1], c[0] �ҷ��϶� 
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
		// b�� ���� ���ſ� ���
		else if (ret_1 == 1)
		{
			int b_1[4] = { b[0],-1 };
			int b_2[4] = { b[1],-1 };
			int b_3[4] = { b[2],-1 };

			int ret_2 = balance(b_1, b_2, b_3);

			// b�� ������ ��� ���� ������ ��� (7 7 7)
			if (ret_2 == 6)
			{
				int a_1[2] = { a[0],-1 };
				int a_2[2] = { a[1],-1 };
				int a_3[2] = { a[2],-1 };

				int ret_3 = balance(a_1, a_2, a_3);

				// a�� ������ �ϳ��� ������ ��� 
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
				// a�� ������ 2�� ������ ���
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
				// a�� ������ ��� �ҷ� ������ ���
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

				// c�� ������ �ϳ��� ������ ��� 
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
				// c�� ������ 2�� ������ ���
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
				// c�� ������ ��� �ҷ� ������ ���
				else if (ret_4 == 6) // c (5 5 5)
				{
					fault_coin[count++] = c_1[0];
					fault_coin[count++] = c_2[0];
					fault_coin[count++] = c_3[0];
				}
			}
			// b�� ���� ������ 1���� ���_1
			else if (ret_2 == 0) // 
			{
				real = b[0]; // ù��° ������ ����
				fault_coin[count++] = b_2[0];
				fault_coin[count++] = b_3[0];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];
			}
			// b�� ���� ������ 1���� ���_2
			else if (ret_2 == 1)
			{
				real = b[1]; // �ι�° ������ ����
				fault_coin[count++] = b_1[0];
				fault_coin[count++] = b_3[0];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];
			}
			// b�� ���� ������ 1���� ���_3 
			else if (ret_2 == 2)
			{
				real = b[2]; // ����° ������ ����
				fault_coin[count++] = b_1[0];
				fault_coin[count++] = b_2[0];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];

				fault_coin[count++] = c[0];
				fault_coin[count++] = c[1];
				fault_coin[count++] = c[2];
			}
			// b�� ���� ������ 2���� ���_1 
			else if (ret_2 == 3)
			{
				fault_coin[count++] = b_3[0];

				int tmp_1[2] = { a[0],-1 };
				int tmp_2[2] = { a[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // a�� 2���� c �ϳ� ��
				// a�� ���� ���� 1�� �߰�_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// a�� ���� ���� 1�� �߰�_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// c�� ���� ���� 1�� �߰� 
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];

					final[f++] = a[2];
				}
				// a�� c�� ���� ���� 1���� �߰�
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
				// a[0], a[1], c[0] �ҷ��϶� 
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
			// b�� ���� ������ 2���� ���_2 : b (5 7 7)
			else if (ret_2 == 4)
			{
				fault_coin[count++] = b_1[0];

				int tmp_1[2] = { a[0],-1 };
				int tmp_2[2] = { a[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // a�� 2���� c �ϳ� ��
				// a�� ���� ���� 1�� �߰�_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// b�� ���� ���� 1�� �߰�_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// c�� ���� ���� 1�� �߰� 
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];

					final[f++] = a[2];
				}
				// a�� c�� ���� ���� 1���� �߰�
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
				// a[0], a[1], c[0] �ҷ��϶� 
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
			// b�� ���� ������ 2���� ���_3 : b (7 5 7)
			else if (ret_2 == 5)
			{
				fault_coin[count++] = b_2[0];

				int tmp_1[2] = { a[0],-1 };
				int tmp_2[2] = { a[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // a�� 2���� c �ϳ� ��
				// a�� ���� ���� 1�� �߰�_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// a�� ���� ���� 1�� �߰�_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = c[0];
					final[f++] = c[1];
					final[f++] = c[2];
				}
				// c�� ���� ���� 1�� �߰� 
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];

					fault_coin[count++] = c[1];
					fault_coin[count++] = c[2];

					final[f++] = a[2];
				}
				// a�� c�� ���� ���� 1���� �߰�
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
				// a[0], a[1], a[0] �ҷ��϶� 
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
		// c�� ���� ���ſ� ���
		else if (ret_1 == 2)
		{
			int c_1[4] = { c[0],-1 };
			int c_2[4] = { c[1],-1 };
			int c_3[4] = { c[2],-1 };

			int ret_2 = balance(c_1, c_2, c_3);

			// c�� ������ ��� ���� ������ ��� (7 7 7)
			if (ret_2 == 6)
			{
				int b_1[2] = { b[0],-1 };
				int b_2[2] = { b[1],-1 };
				int b_3[2] = { b[2],-1 };

				int ret_3 = balance(b_1, b_2, b_3);

				// b�� ������ �ϳ��� ������ ��� 
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
				// b�� ������ 2�� ������ ���
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
				// b�� ������ ��� �ҷ� ������ ���
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

				// a�� ������ �ϳ��� ������ ��� 
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
				// a�� ������ 2�� ������ ���
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
				// a�� ������ ��� �ҷ� ������ ���
				else if (ret_4 == 6) // a (5 5 5)
				{
					fault_coin[count++] = a_1[0];
					fault_coin[count++] = a_2[0];
					fault_coin[count++] = a_3[0];
				}
			}
			// c�� ���� ������ 1���� ���_1
			else if (ret_2 == 0) // 
			{
				real = c[0]; // ù��° ������ ����
				fault_coin[count++] = c_2[0];
				fault_coin[count++] = c_3[0];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];
			}
			// c�� ���� ������ 1���� ���_2
			else if (ret_2 == 1)
			{
				real = c[1]; // �ι�° ������ ����
				fault_coin[count++] = c_1[0];
				fault_coin[count++] = c_3[0];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];
			}
			// a�� ���� ������ 1���� ���_3 
			else if (ret_2 == 2)
			{
				real = c[2]; // ����° ������ ����
				fault_coin[count++] = c_1[0];
				fault_coin[count++] = c_2[0];

				fault_coin[count++] = b[0];
				fault_coin[count++] = b[1];
				fault_coin[count++] = b[2];

				fault_coin[count++] = a[0];
				fault_coin[count++] = a[1];
				fault_coin[count++] = a[2];
			}
			// c�� ���� ������ 2���� ���_1 
			else if (ret_2 == 3)
			{
				fault_coin[count++] = c_3[0];

				int tmp_1[2] = { a[0],-1 };
				int tmp_2[2] = { a[1],-1 };
				int tmp_3[2] = { b[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // b�� 2���� c �ϳ� ��
				// a�� ���� ���� 1�� �߰�_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[0];
					final[f++] = b[1];
					final[f++] = b[2];
				}
				// a�� ���� ���� 1�� �߰�_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[0];
					final[f++] = b[1];
					final[f++] = b[2];
				}
				// b�� ���� ���� 1�� �߰�
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];

					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					final[f++] = a[2];
				}
				// a�� b�� ���� ���� 1���� �߰�
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
				// a[0], a[1], b[0] �ҷ��϶� 
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
			// c�� ���� ������ 2���� ���_2 : c (5 7 7)
			else if (ret_2 == 4)
			{
				fault_coin[count++] = c_1[0];

				int tmp_1[2] = { a[0],-1 };
				int tmp_2[2] = { a[1],-1 };
				int tmp_3[2] = { b[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // a�� 2���� b �ϳ� ��
				// a�� ���� ���� 1�� �߰�_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[0];
					final[f++] = b[1];
					final[f++] = b[2];
				}
				// a�� ���� ���� 1�� �߰�_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[0];
					final[f++] = b[1];
					final[f++] = b[2];
				}
				// b�� ���� ���� 1�� �߰�
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];

					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					final[f++] = a[2];
				}
				// a�� b�� ���� ���� 1���� �߰�
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
				// a[0], a[1], b[0] �ҷ��϶� 
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
			// c�� ���� ������ 2���� ���_3 : c (7 5 7)
			else if (ret_2 == 5)
			{
				fault_coin[count++] = c_2[0];

				int tmp_1[2] = { a[0],-1 };
				int tmp_2[2] = { a[1],-1 };
				int tmp_3[2] = { b[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3); // a�� 2���� b �ϳ� ��
				// b�� ���� ���� 1�� �߰�_1
				if (ret_3 == 0)
				{
					fault_coin[count++] = a[1];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[0];
					final[f++] = b[1];
					final[f++] = b[2];
				}
				// a�� ���� ���� 1�� �߰�_2
				else if (ret_3 == 1)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[2];

					fault_coin[count++] = b[0];
					final[f++] = b[1];
					final[f++] = b[2];
				}
				// b�� ���� ���� 1�� �߰�
				else if (ret_3 == 2)
				{
					fault_coin[count++] = a[0];
					fault_coin[count++] = a[1];

					fault_coin[count++] = b[1];
					fault_coin[count++] = b[2];

					final[f++] = a[2];
				}
				// a�� b�� ���� ���� 1���� �߰�
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
				// a[0], a[1], b[0] �ҷ��϶� 
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

		// a, b�� ���ſ� ���
		else if (ret_1 == 3)
		{
			int a_1[2] = { a[0],-1 };
			int a_2[2] = { a[1],-1 };
			int a_3[2] = { a[2],-1 };

			int ret_2 = balance(a_1, a_2, a_3);
			// a�� b ��� ���� ����
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
			// a�� b�� ���� ���� 2���� ���� ���� ���_1 c�� 755 �Ǵ� 555
			else if (ret_2 == 3) // 7 7 5
			{
				fault_coin[count++] = a_3[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b���� 7 7 / 7 5/ 5 7   
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
			// a�� b�� ���� ���� 2���� ���� ���� ���_2 c�� 755 �Ǵ� 555
			else if (ret_2 == 4) // 5 7 7
			{
				fault_coin[count++] = a_1[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b���� 7 7 / 7 5/ 5 7   
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
			// a�� b�� ���� ���� 2���� ���� ���� ���_3 c�� 755 �Ǵ� 555
			else if (ret_2 == 5) // 7 5 7
			{
				fault_coin[count++] = a_2[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b���� 7 7 / 7 5/ 5 7   
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
			// a�� b�� ���� ���� 1���� ���� ���� ���_1
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
				// b ��
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
			// a�� b�� ���� ���� 1���� ���� ���� ���_2
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
				// b ��
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
			// a�� b�� ���� ���� 1���� ���� ���� ���_3
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
				// b �� 
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
		// c, b�� ���ſ� ���
		else if (ret_1 == 4)
		{
			int c_1[2] = { c[0],-1 };
			int c_2[2] = { c[1],-1 };
			int c_3[2] = { c[2],-1 };

			int ret_2 = balance(c_1, c_2, c_3);
			// c�� b ��� ���� ����
			if (ret_2 == 6)
			{
				real = c[0];
				int a_1[2] = { a[0],-1 };
				int a_2[2] = { a[1],-1 };
				int a_3[2] = { a[2],-1 };

				int ret_3 = balance(a_1, a_2, a_3);
				// a ��
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
			// c�� b�� ���� ���� 2���� ���� ���� ���_1 a�� 755 �Ǵ� 555
			else if (ret_2 == 3) // 7 7 5
			{
				fault_coin[count++] = c_3[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { a[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b���� 7 7 / 7 5/ 5 7   
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
			// c�� b�� ���� ���� 2���� ���� ���� ���_2 a�� 755 �Ǵ� 555
			else if (ret_2 == 4) // 5 7 7
			{
				fault_coin[count++] = c_1[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { a[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b���� 7 7 / 7 5/ 5 7   
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
			// c�� b�� ���� ���� 2���� ���� ���� ���_3 a�� 755 �Ǵ� 555
			else if (ret_2 == 5) // 7 5 7
			{
				fault_coin[count++] = c_2[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { a[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b���� 7 7 / 7 5/ 5 7   
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
			// c�� b�� ���� ���� 1���� ���� ���� ���_1
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
				// b �� 
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
			// c�� b�� ���� ���� 1���� ���� ���� ���_2
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
				// b �� 
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
			// c�� b�� ���� ���� 1���� ���� ���� ���_3
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
				// b �� 
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
		// a, c�� ���ſ� ���
		else if (ret_1 == 5)
		{
			int a_1[2] = { a[0],-1 };
			int a_2[2] = { a[1],-1 };
			int a_3[2] = { a[2],-1 };

			int ret_2 = balance(a_1, a_2, a_3);
			// a�� c ��� ���� ����
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
			// a�� c�� ���� ���� 2���� ���� ���� ���_1 b�� 755 �Ǵ� 555
			else if (ret_2 == 3) // 7 7 5
			{
				fault_coin[count++] = a_3[0];

				int tmp_1[2] = { c[0],-1 };
				int tmp_2[2] = { c[1],-1 };
				int tmp_3[2] = { b[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// c���� 7 7 / 7 5/ 5 7   
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
			// a�� c�� ���� ���� 2���� ���� ���� ���_2 b�� 755 �Ǵ� 555
			else if (ret_2 == 4) // 5 7 7
			{
				fault_coin[count++] = a_1[0];

				int tmp_1[2] = { c[0],-1 };
				int tmp_2[2] = { c[1],-1 };
				int tmp_3[2] = { b[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// c���� 7 7 / 7 5/ 5 7   
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
			// a�� c�� ���� ���� 2���� ���� ���� ���_3 b�� 755 �Ǵ� 555
			else if (ret_2 == 5) // 7 5 7
			{
				fault_coin[count++] = a_2[0];

				int tmp_1[2] = { c[0],-1 };
				int tmp_2[2] = { c[1],-1 };
				int tmp_3[2] = { b[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// c���� 7 7 / 7 5/ 5 7   
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
			// a�� c�� ���� ���� 1���� ���� ���� ���_1
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
				// c �� 
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
			// a�� c�� ���� ���� 1���� ���� ���� ���_2
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
				// c �� 
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
			// a�� c�� ���� ���� 1���� ���� ���� ���_3
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
				// c ��
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

		// a, b, c�� ���� ���
		else if (ret_1 == 6)
		{
			int a_1[2] = { a[0],-1 };
			int a_2[2] = { a[1],-1 };
			int a_3[2] = { a[2],-1 };

			int ret_2 = balance(a_1, a_2, a_3);
			// ���԰� ��� ���� ��� - ���� �ҷ����� �������� ��
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
			// a,b,c ��� ���� ������ 1���� ���_1
			else if (ret_2 == 0)
			{
				fault_coin[count++] = a_2[0];
				fault_coin[count++] = a_3[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b�� c �ҷ� ���� ã��(���� ���� 1��)
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
			// a,b,c ��� ���� ������ 1���� ���_2
			else if (ret_2 == 1)
			{
				fault_coin[count++] = a_1[0];
				fault_coin[count++] = a_3[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b�� c �ҷ� ���� ã��(���� ���� 1��)
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
			// a,b,c ��� ���� ������ 1���� ���_3
			else if (ret_2 == 2)
			{
				fault_coin[count++] = a_1[0];
				fault_coin[count++] = a_2[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b�� c �ҷ� ���� ã��(���� ���� 1��)
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
			// a,b,c ��� ���� ������ 2���� ���_1
			else if (ret_2 == 3)
			{
				fault_coin[count++] = a_3[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b,c ��� ������ 2��
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
			// a,b,c ��� ���� ������ 2���� ���_2
			else if (ret_2 == 4)
			{
				fault_coin[count++] = a_1[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b,c ��� ������ 2��
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
			// a,b,c ��� ���� ������ 2���� ���_1
			else if (ret_2 == 5)
			{
				fault_coin[count++] = a_2[0];

				int tmp_1[2] = { b[0],-1 };
				int tmp_2[2] = { b[1],-1 };
				int tmp_3[2] = { c[0],-1 };

				int ret_3 = balance(tmp_1, tmp_2, tmp_3);
				// b,c ��� ������ 2��
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

	// ������ ����
	final[f++] = 99;

	temp[count_2] = -1; // temp[] �迭 �� -1 �� ����

	int c = f % 3;
	int k = 0;
	// ret_1==6, ret_2=6�� ���
	while (temp[k] != -1 && temp[k + 9] != -1)
	{
		if (count != 0) // �ҷ������� �ϳ��� ã���� ��
		{
			int w_1[2] = { temp[k],-1 };
			int w_2[2] = { temp[k + 9],-1 };
			int w_3[2] = { fault_coin[0],-1 };
			int w_b = balance(w_1, w_2, w_3);

			if (w_b == 0) // A�� ���� B �ҷ�
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
			else if (w_b == 1) // A�� �ҷ� B ����
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
			else if (w_b == 6) // A, B �ҷ�
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
		else // �ҷ� ������ �ϳ��� ã�� ������ ��
		{
			int w_1[2] = { temp[k],-1 };
			int w_2[2] = { temp[k + 9],-1 };
			int w_3[2] = { 99,-1 }; // ���Ƿ� �����Ѱ� �ҷ����� �������� �˼� ����
			int w_b = balance(w_1, w_2, w_3);
			if (w_b == 5 || w_b == 0) // AC ����� B �ҷ�
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
			else if (w_b == 4 || w_b == 1) // BC ����� A �ҷ�
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
			else if (w_b == 2) // C ���� AB �ҷ�
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
		if (count != 0) // �ҷ� ���� ã���� ��
		{
			int w_1[2] = { temp[k],-1 };
			int w_2[2] = { fault_coin[0],-1 };
			int w_3[2] = { fault_coin[1],-1 };
			int w_b = balance(w_1, w_2, w_3);

			if (w_b == 6) // temp[k] ���� �ҷ�
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
		else // �ҷ� ���� �� ã���� ��
		{
			int w_1[2] = { temp[k],-1 };
			int w_2[2] = { 99,-1 };
			int w_3[2] = { 98,-1 };
			int w_b = balance(w_1, w_2, w_3);
			// 0 1 2 3 5 6
			if (w_b == 4 || w_b == 1 || w_b == 2) // ������ ������ �Һ���
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
				if (count != 0) { // �ҷ� ������ ã�� ���
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
				else { // �ҷ� ������ ã�� ���� ���
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

