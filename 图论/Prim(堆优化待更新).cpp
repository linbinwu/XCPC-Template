int prim() {//待更新，堆优化prim更优
    for (int i = 1; i <= n; i++) minn[i] = INF, vis[i] = 0;
    for (int i = head[1], v = e[i].to; i; i = e[i].nxt, v = e[i].to) minn[v] = min(minn[v], e[i].w);
    //default start point is 1
    minn[1] = 0;
    int num = 0, u = 1, ans = 0;
    while (++num < n) {
        int mn = INF;//minimum number this time
        vis[u] = 1;
        for (int i = 1; i <= n; i++)
            if (!vis[i] && mn > minn[i]) {
                mn = minn[i];
                u = i;
            }
        ans += mn;
        for (int i = head[u], v; i; i = e[i].nxt)
            if (!vis[v = e[i].to]) minn[v] = min(minn[v], e[i].w);
    }
    return ans;
}