#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define pi 3.1415926
#define mp(x, y) make_pair(x, y)
#define vi vector<int>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> Pair;
const int MAX = 1e5 + 10;

int N, M;
int dp[MAX][20];//dp[i][j]表示区间[i, i + 2^j - 1]内的最小值
//状态转移方程
//dp[i][j] = min(dp[i][j - 1], dp[i + 2^(j - 1)][j - 1])

int main() {
	ios::sync_with_stdio(0);
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		cin >> dp[i][0];
	for (int j = 1; j < 20; j++)
		for (int i = 1; i + (1 << j) - 1 <= N; i++)
			dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
	while (M--) {
		int l, r;
		cin >> l >> r;
		int k = (int)log2(r - l + 1);
		printf("%d ", min(dp[l][k], dp[r - (1 << k) + 1][k]));
	}
	return 0;
}

