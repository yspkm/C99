#include <stdio.h>

#define MAX_LEN 100
#define INF 0x7fffffff

unsigned min(unsigned a, unsigned b) {
	return a < b ? a : b;
}

unsigned sumFromOne(unsigned* arr, int last_index) {
	unsigned ret = 0;
	for (int i = 1; i <= last_index; i++) {
		ret += arr[i];
	}
	return ret;
}

int main(void)
{
	int n, m, src_node, dst_node, mid_node, ans_node; 
	unsigned min_num = INF, temp, adj_mat[MAX_LEN + 1][MAX_LEN + 1] = {0};

	scanf("%d %d", &n, &m);
	for (int i = 1; i <= MAX_LEN; i++) {
		for (int j = 1; j <= MAX_LEN; j++) {
			if(i==j) adj_mat[i][j] = 0;
			else adj_mat[i][j] = INF;
		}
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &src_node, &dst_node);
		// undirected graph
		adj_mat[src_node][dst_node] = 1;
		adj_mat[dst_node][src_node] = 1;
	}
	// Floyd Warshall Algorithm
	// https://velog.io/@agugu95/%EC%B5%9C%EB%8B%A8%EA%B2%BD%EB%A1%9C%EC%99%80-%ED%94%8C%EB%A1%9C%EC%9D%B4%EB%93%9CFloyd-Warshall-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98
	for (mid_node = 1; mid_node <= n; mid_node++) {
		for (src_node = 1; src_node <= n; src_node++) {
			for (dst_node = 1; dst_node <= n; dst_node++) {
				temp = adj_mat[src_node][mid_node] + adj_mat[mid_node][dst_node];
				adj_mat[src_node][dst_node] = min(adj_mat[src_node][dst_node], temp);
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		temp = sumFromOne(adj_mat[i], n);
		if (temp < min_num) {
			min_num = temp;
			ans_node = i;
		}
	}
	printf("%d\n", ans_node);

	return 0;
}