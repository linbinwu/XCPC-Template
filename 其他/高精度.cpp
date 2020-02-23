#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define mp(x, y) make_pair(x, y)
#define fi first
#define se second
#define vi vector<int>
#define qi queue<int>
#define si stack<int>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> Pair;
const int MAX = 2e4 + 10;
int compare(int a[], int b[]) {//高精度比较
	if (a[0] > b[0])return 1;
	if (a[0] < b[0])return -1;
	for (int i = a[0]; i >= 1; i++) {
		if (a[i] > b[i])return 1;
		if (a[i] < b[i])return -1;
	}
	return 0;
}
void add(int a[], int b[]) {//计算a = a + b
	a[0] = max(a[0], b[0]);
	for (int i = 1; i <= a[0]; i++) {
		a[i + 1] = (a[i] + b[i]) / 10;//进位
		a[i] = (a[i] + b[i]) % 10;//取余
	}
	if (a[a[0] + 1] > 0)a[0]++;
}
int minus(int a[], int b[]) {//计算a = a - b
	int flag = compare(a, b);
	if (flag == 0)memset(a, 0, sizeof(a));
	else if (flag == 1) {
		a[0] = max(a[0], b[0]);
		for (int i = 1; i <= a[0]; i++) {
			if (a[i] - b[i] < 0)a[i + 1]--;
			a[i] = (a[i] - b[i] + 10) % 10;
		}
		if (a[a[0]] == 0)a[0]--;
	}
	else {
		a[0] = max(a[0], b[0]);
		for (int i = 1; i <= a[0]; i++) {
			if (b[i] - a[i] < 0)a[i + 1]++;
			a[i] = (b[i] - a[i] + 10) % 10;
		}
		if (a[a[0]] == 0)a[0]--;
		return -1;
	}
	return 0;
}
int mul(int a[], int x) {//高精度乘单精度 a = x * a
	if (x == 0)memset(a, 0, sizeof(a));
	for (int i = 1; i <= a[0]; i++)a[i] *= x;
	for (int i = 1; i <= a[0]; i++) {
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
	int len = a[0];
	while (a[++len] > 0) {
		a[len + 1] = a[len] / 10;
		a[len] %= 10;
		a[0]++;
	}
	return x >= 0 ? 0 : -1;
}
int div(int a[], int x) {//高精度除单精度 a = a / x
	int rst = 0;
	for (int i = a[0]; i >= 1; i--) {
		rst *= 10;
		rst += a[i];
		a[i] = rst / x;
		rst %= x;
	}
	for (int i = a[0]; i >= 1; i--)
		if (a[i] != 0) {
			a[0] = i;
			break;
		}
	return x >= 0 ? 0 : -1;
}
void copy(int a[], int b[]) {//a = b
	for (int i = 0; i <= a[0]; i++)
		a[i] = b[i];
}
int N, num[MAX], ans[MAX], t[MAX];
struct node {
	int m, n;
	ll s;
}a[10010];
bool operator < (const node &a, const node &b) { return a.s < b.s; }
int main() {
	scanf("%d", &N);
	for (int i = 0; i <= N; i++) {
		scanf("%d%d", &a[i].m, &a[i].n);
		a[i].s = 1ll * a[i].m * a[i].n;
	}
	sort(a + 1, a + 1 + N);
	memset(num, 0, sizeof(num));
	int k = 1;
	while (a[0].m) {
		num[k++] = a[0].m % 10;
		a[0].m /= 10;
		num[0]++;
	}
	for (int i = 1; i <= N; i++) {
		copy(t, num);
		div(t, a[i].n);
		if (compare(t, ans) == 1)
			copy(ans, t);
		mul(num, a[i].m);
	}
	for (int i = ans[0]; i >= 1; i--)
		printf("%d", ans[i]);
	printf("\n");
	return 0;
}
