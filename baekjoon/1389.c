#include <stdio.h>

#define MAX_LEN 100

int main(void)
{
	int n, m, i, idx1, idx2, idx3, len = 0x7fffffff, ans, temp, temp_len = 0;
	int adj_mat[MAX_LEN + 1][MAX_LEN + 1] = {0};

	scanf("%d %d", &n, &m);
	for (i = 0; i < m; i++)
	{
		scanf("%d %d", &idx1, &idx2);
		adj_mat[idx1][idx2] = 1;
		adj_mat[idx2][idx1] = 1;
	}

	for (idx1 = 1; idx1 <= n; idx1++)
	{
		for (idx2 = 1; idx2 <= n; idx2++)
		{
			for (idx3 = 1; idx3 <= n; idx3++)
			{
				if (idx1 == idx2)
				{
					continue;
				}
				if (adj_mat[idx1][idx3] > 0 && adj_mat[idx2][idx1] > 0)
				{
					temp = adj_mat[idx1][idx3] + adj_mat[idx2][idx1];
					if (!adj_mat[idx2][idx3])
					{
						adj_mat[idx2][idx3] = temp;
					}
					else
					{
						adj_mat[idx2][idx3] = adj_mat[idx2][idx3] < temp ? adj_mat[idx2][idx3] : temp;
					}
				}
			}
		}
	}

	for (idx1 = 1; idx1 <= n; idx1++)
	{
		temp_len = 0;
		for (idx2 = 1; idx2 <= n; idx2++)
		{
			temp_len += adj_mat[idx1][idx2];
		}
		if (temp_len < len)
		{
			len = temp_len;
			ans = idx1;
		}
	}
	printf("%d\n", ans);

	return 0;
}
