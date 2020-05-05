//用于解决图中两点间多条路中最大/小边权最小/大值问题
//u, v为原图上的点, 则val[lca(u, v)]为u->v间多条路中...
//由于u, v可能在原图中不连通, 所以需要find(u)和find(v)判断一下是不是在一棵树中
//经典问题, 如P4768 [NOI2018]归程, 求v->1路径中前半段路所有路径海拔大于给定h, 后半段路不管海拔高度的最短路
//一条路中最大边权小于等于给定值, 求....

struct Edge {
    int u, v, w;
    bool operator < (const Edge &rhs) const {
        return w > rhs.w;
        //升序为(u, v)间多条路中最大边权最小值
        //降序为(u, v)间多条路中最小边权最大值
    }
} E[MAX];
vector<int> g[MAX];
int pre[MAX], val[MAX], cnt;//cnt为kruskal重构树的点数, 点数最多为2N - 1
int son[MAX], siz[MAX], top[MAX], fa[MAX], dep[MAX];
void dfs(int u, int par) {
    dep[u] = dep[fa[u] = par] + (siz[u] = 1);
    int max_son = -1;
    for (auto &v: g[u])
        if (v != par) {
            dfs(v, u);
            siz[u] += siz[v];
            if (max_son < siz[v])
                son[u] = v, max_son = siz[v];
        }
}
void dfs2(int u, int topf) {
    top[u] = topf;
    if (!son[u]) return;
    dfs2(son[u], topf);
    for (auto &v: g[u])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
}
int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }
void exKruskal() {
    cnt = N; for (int i = 1; i < (N << 1); i++) pre[i] = i;
    sort(E + 1, E + 1 + M);
    for (int i = 1; i <= M; i++) {
        int u = find(E[i].u), v = find(E[i].v);
        if (u == v) continue;
        val[++cnt] = E[i].w;
        pre[u] = pre[v] = cnt;
        g[u].push_back(cnt), g[cnt].push_back(u);
        g[v].push_back(cnt), g[cnt].push_back(v);
        if (cnt == (N << 1) - 1) break;
    }
    //原图不连通的情况, 那形成的就是森林
    for (int i = 1; i <= cnt; i++)
        if (!siz[i]) {//未访问过
            int rt = find(i);//下树剖lca
            dfs(rt, 0); dfs2(rt, rt);
        }
}