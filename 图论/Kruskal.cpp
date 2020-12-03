
int pre[N], m;

struct edge {
    int u, v, w;
    bool operator < (const edge &rhs) const {
        return w < rhs.w;
    }
} e[M * M];

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }

int kruskal() {
    int cnt = 0, ans = 0;
    for (int i = 1; i <= m; i++) {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v) continue;
        ans += e[i].w;
        pre[v] = u;
        cnt++;
        if (cnt == n - 1) break;
    }
    return ans;
}