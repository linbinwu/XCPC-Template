//MlogM

int pre[N], tot;

struct edge {
    int u, v, w;
    bool operator < (const edge &rhs) const {
        return w < rhs.w;
    }
} e[M * M];

int find(int x) { while (x ^ pre[x]) x = pre[x]; return x; }

int kruskal() {//before invoking kruskal, sort array e
    int cnt = 0, ans = 0;
    for (int i = 1; i <= tot; i++) {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v) continue;
        ans += e[i].w;
        pre[v] = u;
        cnt++;
        if (cnt == n - 1) break;
    }
    return ans;
}