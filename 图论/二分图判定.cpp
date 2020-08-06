//不存在奇环即为二分图
int n, m;
int pre[N << 1], rk[N << 1];

int find(int x) { while (x ^ pre[x]) x = pre[x]; return x; }

void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (rk[x] < rk[y]) swap(x, y);
    rk[x] += rk[x] == rk[y];
    pre[y] = x;
}

int main() {

    int u, v; scanf("%d%d", &u, &v);
    if (find(u) == find(v)) cnt++;//flag = 0
    else {
        merge(u + n, v);
        merge(v + n, u);
    }

	

}

