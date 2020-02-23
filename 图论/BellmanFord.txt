struct edge {
    int u, v, w;
} e[MAX];

bool BellmanFord(int s) {//判负环
    for (int i = 1; i <= N; i++) dis[i] = (i == s ? 0 : INF);
    for (int i = 1; i < N; i++)
        for (int j = 1; j <= M; j++)
            if (dis[e[j].u] + e[j].w < dis[e[j].v])
                dis[e[j].v] = dis[e[j].u] + e[j].w;
    for (int i = 1; i <= M; i++)
        if (dis[e[i].u] + e[i].w < dis[e[i].v])
            return false;
    return true;
}