#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
int soduku[9][9];
int order;
int num;
bool judge(int count, int target)
{
	int row = count / order;
	int col = count % order;
	int i;
	int j;
	for (i = 0; i < order; i++)
	{
		if (soduku[row][i] == target && i != col)
		{
			return false;
		}
	}
	for (i = 0; i < order; i++)
	{
		if (soduku[i][col] == target && i != row)
		{
			return false;
		}
	}
	int s = sqrt(order);
	if (order == 9 || order == 4)
	{
		int realrow = row / s * s;
		int realcol = col / s * s;
		for (i = realrow; i < realrow + s; i++)
		{
			for (j = realcol; j < realcol + s; j++)
			{
				if (soduku[i][j] == target && i != row && j != col)
				{
					return false;
				}
			}
		}
	}
	if (order == 6)
	{
		int realrow = row / 2 * 2;
		int realcol = col / 3 * 3;
		for (i = realrow; i < realrow + 2; i++)
		{
			for (j = realcol; j < realcol + 3; j++)
			{
				if (soduku[i][j] == target && i != row && j != col)
				{
					return false;
				}
			}
		}
	}
	if (order == 8)
	{
		int realrow = row / 4 * 4;
		int realcol = col / 2 * 2;
		for (i = realrow; i < realrow + 4; i++)
		{
			for (j = realcol; j < realcol + 2; j++)
			{
				if (soduku[i][j] == target && i != row && j != col)
				{
					return false;
				}
			}
		}
	}

	return true;
}
void insert(int count, FILE* fp)
{
	int row = count / order;
	int col = count % order;
	int i;
	int j;
	bool flag;
	if (count == order * order)
	{
		for (i = 0; i < order; i++)
		{
			for (j = 0; j < order; j++)
			{
				fprintf(fp, "%d ", soduku[i][j]);

			}
			fprintf(fp, "\n");

		}
		fprintf(fp, "\n");
		return;
	}
	if (soduku[row][col] != 0)
	{
		insert(count + 1, fp);

	}
	else
	{
		for (i = 1; i <= order; i++)
		{
			soduku[row][col] = i;
			flag = judge(count, soduku[row][col]);
			if (flag)
			{
				insert(count + 1, fp);
			}
		}
		soduku[row][col] = 0;
	}
}

int main(int argc, char* argv[])
{
	int i;
	int j;
	int z;
	FILE* fp1;
	FILE* fp2;
	order = atoi(argv[2]);
	num = atoi(argv[4]);
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	if (fp1 == NULL)
	{
		cout << "fp1打不开嗷";
		exit(1);
	}
	if (fp2 == NULL)
	{
		cout << "fp2打不开嗷";
		exit(1);
	}
	for (i = 0; i < num; i++)
	{
		memset(soduku, 0, 81);
		for (j = 0; j < order; j++)
		{
			for (z = 0; z < order; z++)
			{
				fscanf(fp1, "%d", &soduku[j][z]);
			}
		}
		insert(0, fp2);
	}
	fclose(fp2);
	return 0;
}