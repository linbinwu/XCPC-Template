struct edge {
    int u, v, w;
} e[MAX];

bool BellmanFord(int s) {//判负环
    for (int i = 1; i <= n; i++) dis[i] = (i == s ? 0 : INF);
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++)
            if (dis[e[j].u] + e[j].w < dis[e[j].v])
                dis[e[j].v] = dis[e[j].u] + e[j].w;
    for (int i = 1; i <= m; i++)
        if (dis[e[i].u] + e[i].w < dis[e[i].v])
            return false;
    return true;
}