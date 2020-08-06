bool spfa(int s) {
    for (int i = 1; i <= n; i++) dis[i] = (i == s ? 0 : INF), vis[i] = (i == s), cnt[i] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0, cnt[u]++;
        if (cnt[u] >= n) return false;
        for (int i = head[u], v; i; i = e[i].nxt)
            if (dis[u] + e[i].w < dis[v = e[i].to]) {
                dis[v] = dis[u] + e[i].w;
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
    }
    return true;
}

bool spfa(int u) {//dfs
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt)
        if (dis[u] + e[i].w < dis[v = e[i].to]) {
            if (vis[v]) return false;
            else {
                dis[v] = dis[u] + e[i].w;
                if (!spfa(v)) return false;
            }
        }
    vis[u] = 0;
    return true;
}