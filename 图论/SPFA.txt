bool spfa(int s) {
    for (int i = 1; i <= N; i++) dis[i] = (i == s ? 0 : INF), vis[i] = (i == s), cnt[i] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0, cnt[u]++;
        if (cnt[u] >= N) return false;
        for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
            if (dis[u] + e[i].w < dis[v]) {
                dis[v] = dis[u] + e[i].w;
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
    }
    return true;
}

bool spfa(int u) {//dfs
    vis[u] = 1;
    for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
        if (dis[u] + e[i].w < dis[v]) {
            if (vis[v]) return false;
            else {
                dis[v] = dis[u] + e[i].w;
                if (!spfa(v)) return false;
            }
        }
    vis[u] = 0;
    return true;
}