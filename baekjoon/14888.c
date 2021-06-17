#include <stdio.h>
#include <stdbool.h>

#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3

int g_N = 0, g_max = -1000000000, g_min = 1000000000;
int g_A[100] = {0};
int g_opt[99] = {-1};
bool g_mark[100] = {false};

void fcn(int idx_opd, int idx_opt, int ret)
{
	switch (g_opt[idx_opt])
	{
	case ADD:
		ret += g_A[idx_opd];
		break;
	case SUB:
		ret -= g_A[idx_opd];
		break;
	case MUL:
		ret *= g_A[idx_opd];
		break;
	case DIV:
		ret /= g_A[idx_opd];
		break;
	}

	if (idx_opd == g_N - 1)
	{
		if (ret >= g_max)
			g_max = ret;
		if (ret <= g_min)
			g_min = ret;
		return;
	}

	for (int i = 0; i < g_N - 1; i++)
	{
		if (!g_mark[i])
		{
			bool same = false;
			for (int j = 0; j < i ;j++) {
				if (!g_mark[j] && g_opt[i] == g_opt[j]) {
					same = true;
					break;
				}
			}
			if (same) continue;
			g_mark[i] = true;
			fcn(idx_opd + 1, i, ret);
			g_mark[i] = false;
		}
	}
}

int main(void)
{
	int nh = 0, nc = 0, ng = 0, nj = 0, i;
	scanf("%d", &g_N);
	for (int i = 0; i < g_N; i++)
		scanf("%d \n", &g_A[i]);
	scanf("%d %d %d %d", &nh, &nc, &ng, &nj);

	for (i = 0; i < nh; i++)
		g_opt[i] = ADD;
	for (; i < nh + nc; i++)
		g_opt[i] = SUB;
	for (; i < nh + nc + ng; i++)
		g_opt[i] = MUL;
	for (; i < nh + nc + ng + nj; i++)
		g_opt[i] = DIV;

	for (int i = 0; i < g_N - 1; i++)
	{
		if (i > 0 && g_opt[i] == g_opt[i - 1])
			continue;
		g_mark[i] = true;
		fcn(1, i, g_A[0]);
		g_mark[i] = false;
	}

	printf("%d\n%d\n", g_max, g_min);
	return 0;
}