struct Distance {//树剖版本lca
    ll dis[MAX];
    int son[MAX], siz[MAX], top[MAX], fa[MAX], dep[MAX];
    void dfs(int u, int par, ll d) {
        dep[u] = dep[fa[u] = par] + (siz[u] = 1), dis[u] = d;
        int max_son = -1;
        for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
            if (v != par) {
                dfs(v, u, d + e[i].w);
                siz[u] += siz[v];
                if (max_son < siz[v])
                    son[u] = v, max_son = siz[v];
            }
    }
    void dfs2(int u, int topf) {
        top[u] = topf;
        if (!son[u]) return;
        dfs2(son[u], topf);
        for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
            if (v != fa[u] && v != son[u]) dfs2(v, v);
    }
    int lca(int x, int y) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            x = fa[top[x]];
        }
        return dep[x] < dep[y] ? x : y;
    }
    ll getDis(int x, int y) { return dis[x] + dis[y] - 2 * dis[lca(x, y)]; }
} dis;


int main(){
    dis.dfs(1, 0, 0); dis.dfs2(1, 1);

}